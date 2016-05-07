#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#define MAX(a,b) ((a < b) ?  (b) : (a))

class Vector
{
public:
    Vector();
    Vector( float x, float y, float z ) : X(x), Y(y), Z(z) {}
    virtual ~Vector();
    float X, Y,Z;

    void Normalize()
    {
        float m = MAX(X,Y);
        m = MAX(m, Z);
        X /=m;
        Y /=m;
        Z/=m;
    }

    Vector operator+(const Vector & v)
    {
        return Vector(X+v.X, Y+v.Y, Z+v.Z);
    }

    Vector operator-(const Vector & v)
    {
        return Vector(X-v.X, Y-v.Y, Z-v.Z);
    }

    Vector operator *( const double & d )
    {
        Vector ret;
        ret.X = this->X * d;
        ret.Y = this->Y * d;
        ret.Z = this->Z * d;
        return ret;
    }

    float Odleglosc( Vector & xyz )
    {
        return sqrt( (X+xyz.X)*(X+xyz.X) +(Y+xyz.Y)*(Y+xyz.Y)+ (Z+xyz.Z) * (Z+xyz.Z));
    }

protected:
private:
    };

#endif // VECTOR_H
