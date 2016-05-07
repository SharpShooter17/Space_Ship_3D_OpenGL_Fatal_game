#include <SFML/OpenGL.hpp>
#include <OGLcolors.h>

#include "../include/StatekKosmiczny.h"
#include <cmath>

#define DegToRad 3.14159265358979323846/180.0f

StatekKosmiczny::StatekKosmiczny( float speed, float r, Vector Vxyz, Vector dir, FireMode mod, short moc ) :
                                katPion( 0.0f ), katPoziom( 0.0f ),
                                promien( r ), szybkosc ( speed ),
                                xyz( Vxyz ), vKierumek( dir ),
                                RodzajOgnia( mod ), sprawnosc( moc )
{
}

StatekKosmiczny::~StatekKosmiczny()
{
}

void StatekKosmiczny::UstawKamere()
{
    glTranslatef( -xyz.X, -xyz.Y - 0.0f, -xyz.Z - 0.0f );
}

void StatekKosmiczny::Fire( std::vector< Bullet > &vPociski, Vector dir, float r, float speed)
{
    switch( RodzajOgnia )
    {
    case PojedynczaKula:
         vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );
         break;
    case SeriaKul:
         vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );
         vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir, dir, r, speed  ) );
         vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir * 2, dir, r, speed  ) );
         break;
    case PodwojneKule:
         vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + Vector( - 0.08f, 0.0f, 0.0f ), dir, r, speed  ) );
         vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + Vector( 0.08f, 0.0f, 0.0f ), dir, r, speed  ) );
        break;
    case W3Kierumkach:
        {
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );

            float angle = atan2( dir.Z, dir.X ) * 180.0f / 3.14159265358979323846;

            dir.X = cos( ( angle + 2.0f ) * DegToRad );
            dir.Z = sin( ( angle + 2.0f ) * DegToRad );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );

            dir.X = cos( ( angle - 2.0f ) * DegToRad );
            dir.Z = sin( ( angle - 2.0f ) * DegToRad );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );

            break;
        }
    case SeriaW3Kierunkach:
        {
            float angle = atan2( dir.Z, dir.X ) * 180.0f / 3.14159265358979323846;
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir, dir, r, speed  ) );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir * 2, dir, r, speed  ) );

            dir.X = cos( ( angle + 2.0f ) * DegToRad );
            dir.Z = sin( ( angle + 2.0f ) * DegToRad );

            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir, dir, r, speed  ) );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir * 2, dir, r, speed  ) );

            dir.X = cos( ( angle - 2.0f ) * DegToRad );
            dir.Z = sin( ( angle - 2.0f ) * DegToRad );

            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ), dir, r, speed  ) );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir, dir, r, speed  ) );
            vPociski.push_back( Bullet( xyz + dir * ( promien + r + 0.1f ) + dir * 2, dir, r, speed  ) );

            break;
        }
    default:
        RodzajOgnia = SeriaKul;
        break;
    }
}
