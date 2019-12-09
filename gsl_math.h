#ifndef GSL_MATH_H
#define GSL_MATH_H

#include <vector>
#include "vector2d.h"
#include "vector3d.h"
#include "math_constants.h"

namespace gsl
{
    class Quaternion;

    // Functions
    double rad2deg(double rad);
    double deg2rad(double deg);
    float rad2degf(float rad);
    float deg2radf(float deg);
    float mod(float x, float y);
    float clamp(float x, float min, float max);

    // Interpolation
    // remember time can only be between 0 and 1
    Vector2D lerp2D(float time, Vector2D start, Vector2D end); // Move a straight line with linear time-step between points
    Vector3D lerp3D(float time, Vector3D start, Vector3D end);

    // Lerp between quaternion rotations,
    // remember time can only be between 0 and 1
    Quaternion qLerp(float time, Quaternion start, Quaternion end);
    Quaternion qLerp(float time, Vector3D start, Vector3D end);
    Vector3D qLerpEuler(float time, Quaternion start, Quaternion end);
    Vector3D qLerpEuler(float time, Vector3D start, Vector3D end);

    // Curves
    Vector3D bezierCurve(std::vector<Vector3D> points, float t, unsigned long long degree = 3);
    Vector3D bSpline(const std::vector<Vector3D>& points, const std::vector<float>& t, float x, unsigned long long degree = 3);

    // Basic vector directions
    Vector3D up();
    Vector3D right();
    Vector3D forward();
    Vector3D one();
    Vector3D zero();


}

#endif // GSL_MATH_H
