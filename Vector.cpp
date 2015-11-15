#include "Vector.hpp"
#include <cassert>
// see Vector.hpp for documentation
Vector::Vector() : m_x(0), m_y(0) {}

Vector::Vector(double d1, double d2) : m_x(d1), m_y(d2) {}

Vector::Vector(const Vector & other) {
    this->setX(other.getX());
    this->setY(other.getY());
}

void Vector::setX(double d) {
    m_x = d;
}

void Vector::setY(double d) {
    m_y = d;
}

double Vector::getX() const {
    return m_x;
}

double Vector::getY() const {
    return m_y;
}

double & Vector::operator[](std::size_t idx) {
    assert(idx == 0 || idx == 1);
    if (idx == 0) {
        return m_x;
    } else {
        return m_y;
    }
}

const double & Vector::operator[](std::size_t idx) const {
    return (*this)[idx];
}

Vector & Vector::operator=(const Vector & other) {
    this->setX(other.getX());
    this->setY(other.getY());
    return *this;
}

Vector Vector::operator-() const {
    return Vector(-this->getX(), -this->getY());
}

Vector& Vector::operator+=(const Vector & other) {
    this->setX(this->getX() + other.getX());
    this->setY(this->getY() + other.getY());
    return *this;
}

Vector& Vector::operator-=(const Vector & other) {
    this->setX(this->getX() - other.getX());
    this->setY(this->getY() - other.getY());
    return *this;
}

Vector& Vector::operator*=(const double & other){
    this->setX(this->getX() * other);
    this->setY(this->getY() * other);
    return *this;
}

Vector& Vector::operator/=(const double & other){
    assert(other != 0);
    this->setX(this->getX() / other);
    this->setY(this->getY() / other);
    return *this;
}

std::ostream & operator<<(std::ostream & out, const Vector & vector) {
    return out << vector.getX() << " " << vector.getY();
}

bool operator==(const Vector & lhs, const Vector & rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

bool operator!=(const Vector & lhs, const Vector & rhs) {
    return !(lhs == rhs);
}

Vector operator+(const Vector & lhs, const Vector & rhs) {
    return Vector(lhs)+=rhs;
}

Vector operator-(const Vector & lhs, const Vector & rhs) {
    return Vector(lhs)+=rhs;
}

Vector operator*(const Vector & lhs, const double & rhs) {
    return Vector(lhs)*=rhs;
}

Vector operator/(const Vector & lhs, const double & rhs) {
    return Vector(lhs)/=rhs;
}

Vector operator*(const double & lhs, const Vector & rhs) {
    return rhs*lhs;
}
Vector operator/(const double & lhs, const Vector & rhs) {
    return rhs/lhs;
}
