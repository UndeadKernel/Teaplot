#ifndef _VECTOR_H_
#define _VECTOR_H_


namespace tgl
{

class Screen;


class Vector 
{
  public:
    Vector();
    Vector(double p_x, double p_y, double p_z, double p_w = 1.0);
    // Init functions.
    void setPointCoords(double p_x, double p_y, double p_z);
    // Vector functions.
    double dot(Vector &p_v);
    Vector cross(const Vector &p_vector);
    double len();

    // Transformations
    void perspectiveDivide();
    Vector viewportTransformation(Screen &p_screen);

    // Vector operations
    double& operator[](int p_index);
    double operator[](int p_index) const;
    Vector operator-(const Vector &p_vector);
    Vector &operator+=(const Vector &p_vector);
    Vector &operator=(const Vector &p_vector);
    Vector &operator/=(double p_const);

    inline double x() const { return m_data[0]; }
    inline double y() const { return m_data[1]; }
    inline double z() const { return m_data[2]; }
    inline double w() const { return m_data[3]; }

    
  private:
    // Vector data structure;
    double m_data[4];
};

}



#endif /* _VECTOR_H_ */
