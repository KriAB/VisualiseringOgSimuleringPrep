#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <iostream>

namespace gsl
{

class Vector2D
{
public:
    // Constructor
    Vector2D(float x_in = 0.0, float y_in = 0.0);
    Vector2D(const int v);
    Vector2D(const double v);

    // Operators
    Vector2D operator+ (const Vector2D &rhs) const;     // v + v
    Vector2D operator- (const Vector2D &rhs) const;     // v - v
    Vector2D &operator+=(const Vector2D &rhs);          // v += v
    Vector2D &operator-=(const Vector2D &rhs);          // v -= v
    Vector2D operator-() const;                         // -v
    Vector2D operator*(float lhs) const;                // v * f
    const Vector2D &operator = (const Vector2D& rhs);   // v = v

    friend Vector2D operator*(const Vector2D &lhs, const Vector2D &rhs);    // v * v

    //functions
    float length() const;
    void normalize();
    Vector2D normalized();
    class Vector3D barycentricCoordinates(const Vector2D &p1, const Vector2D &p2, const Vector2D &p3);
    void print();
    friend std::ostream &operator<<(std::ostream &out, const Vector2D &rhs);

    friend float cross(const Vector2D &v1, const Vector2D &v2);
    friend float dot(const Vector2D &v1, const Vector2D &v2);
    friend Vector2D normalize(const Vector2D &v);

    //Getters and setters
    float getX() const;
    void setX(const float &value);

    float getY() const;
    void setY(const float &value);

    //Friend functions
    friend std::ostream& operator<<(std::ostream &out, const Vector2D &rhs);

    float x;
    float y;
    float cross2(const Vector2D &v1, const Vector2D &v2);
};

} //namespace

#endif // VECTOR2D_H
