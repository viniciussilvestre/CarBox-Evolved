#include <cmath>
#include <string>
#ifndef CAR_CG_H
#define CAR_CG_H

struct vetor3
{
    float x, y, z;
    vetor3() :x(0.0), y(0.0), z(0.0) {}
    vetor3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
    vetor3 operator + (const vetor3&v) const
    {
        return {x + v.x, y + v.y, z + v.z};
    }
    vetor3 operator * (float k) const
    {
        return {x*k, y*k, z*k};
    }
    [[nodiscard]] float mag() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    void normalize()
    {
        float m = mag();
        x = x/m;
        y = y/m;
        z = z/m;
    }
};

#endif //CAR_CG_H
