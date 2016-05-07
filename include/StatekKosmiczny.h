#ifndef STATEKKOSMICZNY_H
#define STATEKKOSMICZNY_H

#include <iostream>
using namespace std;

#include "Vector.h"
#include <vector>

#include "Bullet.h"

enum FireMode{
            PojedynczaKula = 0,
            SeriaKul = 1,
            PodwojneKule,
            W3Kierumkach,
            SeriaW3Kierunkach,
            };

class StatekKosmiczny
{
    public:

        StatekKosmiczny( float speed = 1.0f, float r = 1.0f ,
                        Vector Vxyz = Vector(), Vector dir = Vector(),
                        FireMode mod = PojedynczaKula, short moc = 100 );
        virtual ~StatekKosmiczny();

        inline virtual void wLewo( float &LoopTime ) { if ( xyz.X > - 10.0f ) xyz.X -= LoopTime * szybkosc; }
        inline virtual void wPrawo( float &LoopTime ) { if ( xyz.X < 10.0f ) xyz.X += LoopTime * szybkosc; }
        inline virtual void wGore( float &LoopTime ) { if ( xyz.Y < 10.0f ) xyz.Y += LoopTime * szybkosc; }
        inline virtual void wDol( float &LoopTime ) { if ( xyz.Y > - 10.0f ) xyz.Y -= LoopTime * szybkosc; }


        virtual void UstawKamere();
        virtual void Fire( std::vector< Bullet > &vPociski, Vector dir = Vector( 0.0f, 0.0f, -1.0f ), float r = 0.04f, float speed = 5.0f );

        virtual void Draw() = 0;

        inline Vector &getXYZ() { return xyz; }
        inline float &getX() { return xyz.X; }
        inline float &getY() { return xyz.Y; }
        inline float &getZ() { return xyz.Z; }
        inline float &getR() { return promien; }

        inline bool bStrataZycia( short n )
        {
            sprawnosc += n;
            if ( sprawnosc > 0 ) return false;
            else return true;
        }
        inline void addSprawnosc( short n ) { sprawnosc += n; }

    protected:

        Vector xyz;
        Vector vKierumek;
        float katPion;
        float katPoziom;
        float szybkosc;
        float promien;
        FireMode RodzajOgnia;
        short sprawnosc;

    private:

};

#endif // STATEKKOSMICZNY_H
