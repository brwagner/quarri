#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>

class Vector {
public:
    Vector();
    Vector(const Vector & other);
    Vector(double d1, double d2);
    void setX(double d);
    void setY(double d);
    double getX() const;
    double getY() const;
    double & operator[](std::size_t idx);
    const double & operator[](std::size_t idx) const;
    Vector & operator=(const Vector & other);
    Vector operator-() const;
    Vector& operator+=(const Vector & other);
    Vector& operator-=(const Vector & other);
    Vector& operator*=(const double & other);
    Vector& operator/=(const double & other);
private:
  double m_x;
  double m_y;
};

std::ostream & operator<<(std::ostream & out, const Vector & vector);
bool operator==(const Vector & lhs, const Vector & rhs);
bool operator!=(const Vector & lhs, const Vector & rhs);
Vector operator+(const Vector & lhs, const Vector & rhs);
Vector operator-(const Vector & lhs, const Vector & rhs);
Vector operator*(const Vector & lhs, const double & rhs);
Vector operator/(const Vector & lhs, const double & rhs);
Vector operator*(const double & lhs, const Vector & rhs);
Vector operator/(const double & lhs, const Vector & rhs);

#endif
