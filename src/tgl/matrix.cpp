#include "matrix.h"
#include "vector.h"

#include <stdexcept>
#include <cmath>


namespace tgl
{

//--------------------------------------------------------------------------------
// Public Functions

Matrix::Matrix() 
{
    loadIdentity();
}

void Matrix::loadIdentity() 
{
    int array_index = 0;

    // Fill in zeroes except for the diagonal.
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            // Ones on diagonal.
            if(i == j) {
                m_data[array_index++] = 1.0f;
                continue;
            }
            // Zeroes everywhere else!
            m_data[array_index++] = 0.0f;
        }
    }
}

void Matrix::translate(double p_x/* = 0*/, double p_y/* = 0*/, double p_z/* = 0*/)
{
    // Add the desired coordinates to the translation vector of
    // ... the matrix.
    m_data[3] += p_x;
    m_data[7] += p_y;
    m_data[11] += p_z;
}

void Matrix::scale(double p_x/* = 1*/, double p_y/* = 1*/, double p_z/* = 1*/)
{
    // Setup the scaling factors in the matrix.
    m_data[0] *= p_x;
    m_data[5] *= p_y;
    m_data[10] *= p_z;
}

void Matrix::rotateY(double p_angle)
{
    Matrix m;

    m[0] = std::cos(p_angle);
    m[2] = -std::sin(p_angle);
    m[8] = std::sin(p_angle);
    m[10] = std::cos(p_angle);

    Matrix &myself = *this;
    
    myself = myself * m;
}

double Matrix::getPoint(unsigned int p_point) const
{
    if(p_point > 16) {
        throw std::out_of_range("Matrix index out of range.");
    }

    return m_data[p_point];
}

Matrix& Matrix::operator=(const Matrix &p_m)
{
    // Copy all the values received from the matrix.
    for(int i = 0; i < 16; i++) {
        m_data[i] = p_m.getPoint(i);
    }

    return *this;
}

double& Matrix::operator[](unsigned int p_index)
{    
    if(p_index > 15) {
        throw std::out_of_range("Matrix index out of range.");
    }

    return m_data[p_index];
}

Matrix Matrix::operator+(Matrix &p_m)
{
    Matrix m;

    for(int i = 0; i < 16; i++) {
        m[i] = m_data[i] + p_m[i];
    }

    return m;
}

Matrix Matrix::operator*(Matrix &p_m)
{
    Matrix m;
    int a_index = 0;
    int b_index = 0;
    double dot_product = 0.0f;

    for(int i = 0; i < 16; i++) {
        dot_product = 0.0f;

        for(int j = 0; j < 4; j++) {
            a_index = (static_cast<int>(i/4) * 4) + j;
            b_index = (i%4) + (j*4);
            dot_product += (*this)[a_index] * p_m[b_index];
        }

        m[i] = dot_product;
    }

    return m;
}

Vector Matrix::operator*(Vector &p_v)
{
    Vector v;
    Matrix &m = *this;

    v[0] = m[0]*p_v[0] + m[1]*p_v[1] + m[2]*p_v[2] + m[3]*p_v[3];
    v[1] = m[4]*p_v[0] + m[5]*p_v[1] + m[6]*p_v[2] + m[7]*p_v[3];
    v[2] = m[8]*p_v[0] + m[9]*p_v[1] + m[10]*p_v[2] + m[11]*p_v[3];
    v[3] = m[12]*p_v[0] + m[13]*p_v[1] + m[14]*p_v[2] + m[15]*p_v[3];

    return v;
}

}
