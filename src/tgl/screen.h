#ifndef _TGL__SCREEN_H_
#define _TGL__SCREEN_H_

namespace tgl
{

class Screen
{
  public:
    Screen(int p_x = 0, int p_y = 0, int p_w = 0, int p_h = 0,
        double p_n = 0.0f, double p_f = 1.0f);
    // Setters / Getters
    int getX();
    void setX(int p_x);
    int getY();
    void setY(int p_y);
    int getWidth();
    void setWidth(int p_w);
    int getHeight();
    void setHeight(int p_h);
    double getNear();
    void setNear(double p_n);
    double getFar();
    void setFar(double p_f);

    inline int x() { return m_x; }
    inline int y() { return m_y; }
    inline int width() { return m_width; }
    inline int height() { return m_height; }


  private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    double m_near;
    double m_far;
};


}


#endif /* _TGL__SCREEN_H_ */
