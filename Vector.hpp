#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>

/**
   represents a two-dimensional position in the game world
 **/
class Vector {
public:
  // initialize x and y to 0
  Vector();
  // copy constructor; intialize x and y to other's x and y
  Vector(const Vector & other);
  // initialize x and y to d1 and d2 respectively
  Vector(double d1, double d2);
  void setX(double d);
  void setY(double d);
  double getX() const;
  double getY() const;
  // returns x for [0] and y for [1], throws assertion failure for other values
  double & operator[](std::size_t idx);
  const double & operator[](std::size_t idx) const;
  // set x and y to other's x and y
  Vector & operator=(const Vector & other);
  // returns a new vector with this x and y negated
  Vector operator-() const;
  // add other's x and y to this x and y, modifies this
  Vector& operator+=(const Vector & other);
  // subtract other's x and y from this x and y, modifies this
  Vector& operator-=(const Vector & other);
  // multiplies this x and y both by other, modifies this
  Vector& operator*=(const double & other);
  // divides this x and y both by other, modifies this
  Vector& operator/=(const double & other);
private:
  // x coordinate
  double m_x;
  // y coordinate
  double m_y;
};

// streams out "x, y" to out
std::ostream & operator<<(std::ostream & out, const Vector & vector);
// compares lhs x and y to rhs x and y
bool operator==(const Vector & lhs, const Vector & rhs);
bool operator!=(const Vector & lhs, const Vector & rhs);
// return a new vector that is the sum of the x's and y's of these vectors
Vector operator+(const Vector & lhs, const Vector & rhs);
// return a new vector that is the difference of the x's and y's of these vectors
Vector operator-(const Vector & lhs, const Vector & rhs);
// return a new vector that is the product of lhs x and y each with rhs
Vector operator*(const Vector & lhs, const double & rhs);
// return a new vector that is the quotient of lhs x and y each with rhs
Vector operator/(const Vector & lhs, const double & rhs);
// same as above
Vector operator*(const double & lhs, const Vector & rhs);
Vector operator/(const double & lhs, const Vector & rhs);

#endif
