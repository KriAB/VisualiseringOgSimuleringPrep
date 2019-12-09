#include "gsl_math.h"
#include <array>
#include <vector>

//#include <QElapsedTimer>

namespace gsl
{
    double rad2deg(double rad)
    {
        return rad * (180.0 / PI_D);
    }

    double deg2rad(double deg)
    {
        return deg * (PI_D / 180.0);
    }

    float rad2degf(float rad)
    {
        return rad * (180.0f / PI);
    }

    float deg2radf(float deg)
    {
        return deg * (PI / 180.0f);
    }

    float mod(float x, float y)
    {
        // same as (x % y)
        int timesY = static_cast<int>(x / y);
        return x - (timesY * y);
    }

    //Calculates the points on a bezier curve. Input t from 0 to 1
    Vector3D bezierCurve(std::vector<Vector3D> points, float t, unsigned long long degree)
    {
        for (unsigned long long k = 0; k < degree; ++k) {
            for (unsigned long long i = 0; i < degree - k - 1; ++i)
                points[i] = points[i] * (1.0f - t) + points[i + 1] * t;
        }
        return points[0];
    }

    //Calculates the points on a basis spline curve. Input t from 0 to 1.
    Vector3D bSpline(const std::vector<Vector3D>& points, const std::vector<float> &t, float x, unsigned long long degree)
    {
        // CALCULATE VALID KNOT INTERVAL 'MY'
        unsigned long long my;
        for (my = 0; my < points.size(); my++) {
            if (x < t[my+1])
                break;
        }
        // CALCULATE BASIS FUNCTIONS
        std::vector<float> basis(t.size());
        for (unsigned long long j = 0; j <= degree; j++) {
            for (unsigned long long i = (my-j); i <= my; i++) {
                if (j == 0) {
                    basis[i] = 1.0f;
                } else {
                    float left, right;
                    if (basis[i] != 0.0f)
                        left = ((x - t[i]) / (t[i+j] - t[i])) * basis[i];
                    else
                        left = 0.0f;
                    if (basis[i+1] != 0.0f)
                        right = ((t[i+j+1] - x) / (t[i+j+1] - t[i+1])) * basis[i+1];
                    else
                        right = 0.0f;
                    basis[i] = left + right;
                }
            }
        }
        // MULTIPLY POINTS WITH BASIS FUNCTIONS
        Vector3D result;
        for (unsigned long long i = 0; i < points.size(); i++)
            result += points[i] * basis[i];
        return result;
    }

    Vector3D up()
    {
        return Vector3D(0.0f, 1.0f, 0.0f);
    }

    Vector3D right()
    {
        return Vector3D(1.0f, 0.0f, 0.0f);
    }

    Vector3D forward()
    {
        return Vector3D(0.0f, 0.0f, 1.0f);
    }

    Vector3D one()
    {
        return Vector3D(1.0f, 1.0f, 1.0f);
    }

    Vector3D zero()
    {
        return Vector3D(0.0f, 0.0f, 0.0f);
    }

    float clamp(float x, float min, float max)
    {
        if (x < min)
            x = min;
        else if (x > max)
            x = max;
        return x;
    }

    Vector2D lerp2D(float time, Vector2D a, Vector2D b)
    {
        return a*(1.f-time) + b*time;
    }

    Vector3D lerp3D(float time, Vector3D a, Vector3D b)
    {
        return a*(1.f-time) + b*time;
    }
}
