#include "vector.h"
#include "screen.h"

#include <stdexcept>
#include <iostream>
#include <cmath>


namespace tgl
{

//--------------------------------------------------------------------------------
// Public Functions

Vector::Vector()
{
    m_data[0] = 0.0;
    m_data[1] = 0.0;
    m_data[2] = 0.0;
    m_data[3] = 1.0;
}

Vector::Vector(double p_x, double p_y, double p_z, double p_w/* = 1.0*/)
{
    m_data[0] = p_x;
    m_data[1] = p_y;
    m_data[2] = p_z;
    m_data[3] = p_w;
}

void Vector::setPointCoords(double p_x, double p_y, double p_z)
{
    m_data[0] = p_x;
    m_data[1] = p_y;
    m_data[2] = p_z;
    m_data[3] = 1.0;
}

double Vector::dot(Vector &p_v)
{
    double dot_product = 0;

    for(int i = 0; i < 3; i++) {
        dot_product += m_data[i] * p_v[i];
    }

    return dot_product;
}

Vector Vector::cross(const Vector &p_vector)
{
    Vector cross;

    cross[0] = (m_data[1] * p_vector[2]) - (m_data[2] * p_vector[1]);
    cross[1] = (m_data[2] * p_vector[0]) - (m_data[0] * p_vector[2]);
    cross[2] = (m_data[0] * p_vector[1]) - (m_data[1] * p_vector[0]);
    cross[3] = 0;

    return cross;
}

double Vector::len()
{
    return std::sqrt(
        (x()*x()) +
        (y()*y()) +
        (z()*z()));
}

void Vector::perspectiveDivide()
{
    m_data[0] /= m_data[3];
    m_data[1] /= m_data[3];
    m_data[2] /= m_data[3];
    m_data[3] = 1;
}

Vector Vector::viewportTransformation(Screen &p_screen)
{
    Vector v;

    v[0] = (static_cast<double>(p_screen.getWidth()) / 2.0) * m_data[0] +
        (static_cast<double>(p_screen.getX()) + 
            static_cast<double>(p_screen.getWidth()) / 2.0);

    v[1] = -(static_cast<double>(p_screen.getHeight()) / 2.0) * m_data[1] +
        (static_cast<double>(p_screen.getY()) + 
            static_cast<double>(p_screen.getHeight()) / 2.0);

    v[2] = ((p_screen.getFar() - p_screen.getNear()) / 2.0) * m_data[2] +
        ((p_screen.getFar() + p_screen.getNear()) / 2.0);

    return v;
}

double &Vector::operator[](int p_index)
{
    if(p_index > 4) {
        throw std::out_of_range("Vector:: index out of range.");
    }

    return m_data[p_index];
}

double Vector::operator[](int p_index) const
{
    if(p_index > 4) {
        throw std::out_of_range("Vector:: index out of range.");
    }

    return m_data[p_index];
}

Vector Vector::operator-(const Vector &p_vector)
{
    Vector sub;

    sub[0] = this->m_data[0] - p_vector[0];
    sub[1] = this->m_data[1] - p_vector[1];
    sub[2] = this->m_data[2] - p_vector[2];
    sub[3] = this->m_data[3] - p_vector[3];

    return sub;
}

Vector &Vector::operator+=(const Vector &p_vector)
{
    this->m_data[0] += p_vector[0];
    this->m_data[1] += p_vector[1];
    this->m_data[2] += p_vector[2];
    this->m_data[3] += p_vector[3];

    return *this;
}

Vector &Vector::operator=(const Vector &p_vector)
{
    m_data[0] = p_vector[0];
    m_data[1] = p_vector[1];
    m_data[2] = p_vector[2];
    m_data[3] = p_vector[3];

    return *this;
}

Vector &Vector::operator/=(double p_const)
{
    m_data[0] /= p_const;
    m_data[1] /= p_const;
    m_data[2] /= p_const;

    return *this;
}

}
