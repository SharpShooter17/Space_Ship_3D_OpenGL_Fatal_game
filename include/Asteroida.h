#ifndef ASTEROIDA_H
#define ASTEROIDA_H

#include <Vector.h>

class Asteroida
{
    public:
        Asteroida( Vector polozenie, Vector kierunek = Vector( 0.0f, 0.0f, 1.0f ), float speed = 1.0f );
        ~Asteroida();

        void Draw();
        void Move( float & LoopTime );

        inline Vector &getXYZ() { return xyz; }
        inline float &getR() { return promien; }
        inline void setR( float r ) { promien = r; }

        bool bCzyCala( float n )
        {
            zycie += n;
            if ( zycie > 0 )
                return true;
            else return false;
        }

    protected:
    private:

        Vector xyz;
        Vector dir;
        Vector Rotacja;
        float rot;
        float promien;
        float szybkosc;

        short zycie;
};

#endif // ASTEROIDA_H
