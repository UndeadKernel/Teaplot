#include "screen.h"

namespace tgl
{


//--------------------------------------------------------------------------------
// Public Functions

Screen::Screen(int p_x/* = 0*/, int p_y/* = 0*/, int p_w/* = 0*/, int p_h/* = 0*/,
    double p_n/* = 0.0f*/, double p_f/*= 1.0f*/)
    : m_x(p_x)
    , m_y(p_y)
    , m_width(p_w)
    , m_height(p_h)
    , m_near(p_n)
    , m_far(p_f)
{

}

int Screen::getX()
{
    return m_x;
}

void Screen::setX(int p_x)
{
    m_x = p_x;
}

int Screen::getY()
{
    return m_y;
}

void Screen::setY(int p_y)
{
    m_y = p_y;
}

int Screen::getWidth()
{
    return m_width;
}

void Screen::setWidth(int p_w)
{
    m_width = p_w;
}

int Screen::getHeight()
{
    return m_height;
}

void Screen::setHeight(int p_h)
{
    m_height = p_h;
}

double Screen::getNear()
{
    return m_near;
}

void Screen::setNear(double p_n)
{
    m_near = p_n;
}

double Screen::getFar()
{
    return m_far;
}

void Screen::setFar(double p_f)
{
    m_far = p_f;
}


//--------------------------------------------------------------------------------
// Private Functions

}
