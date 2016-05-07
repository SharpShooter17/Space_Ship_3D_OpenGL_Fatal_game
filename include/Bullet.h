#ifndef BULLET_H
#define BULLET_H

#include <Vector.h>

class Bullet
{
    public:
        Bullet( Vector XYZ, Vector DIR, float r = 0.3f, float speed = 10.0f );
        ~Bullet();

        void Draw();
        void Move( float & LoopTime );
        inline Vector &getXYZ() { return xyz; }
        inline float &getR() { return promien; }

    protected:
    private:

        Vector xyz;
        Vector dir;
        float szybkosc;
        float promien;
        float rot;
        float startRotate;
};

#endif // BULLET_H
