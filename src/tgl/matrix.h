#ifndef _MATRIX_H_
#define _MATRIX_H_

namespace tgl
{

class Vector;


class Matrix
{
  public:
    Matrix();
    // Matrix functions
    void loadIdentity(); // Load the identity matrix into this matrix's data.erte
    
    // Matrix functions
    void translate(double p_x = 0, double p_y = 0, double p_z = 0);
    void scale(double p_x = 1, double p_y = 1, double p_z = 1);
    void rotateY(double p_angle);

    // Access data.
    double getPoint(unsigned int p_point) const;

    // Matrix operations
    double& operator[](unsigned int p_index);
    Matrix& operator=(const Matrix &p_m);
    Matrix operator+(Matrix &p_m);
    Matrix operator*(Matrix &p_m);
    Vector operator*(Vector &p_v);
    

  private:
    double m_data[16];
};

}

#endif /* _MATRIX_H_ */
