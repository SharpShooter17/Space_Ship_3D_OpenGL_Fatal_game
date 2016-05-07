#include <SFML/OpenGL.hpp>
#include <OGLcolors.h>

#include "../include/StatekWroga.h"
#include "../include/Asteroida.h"
#include "../include/Gracz.h"
#include "../include/Bullet.h"
#include <ctime>
#include <cstdlib>

#define DegToRad M_PI/180.0f

extern GLuint list_dron;
extern Gracz Player;
extern std::vector < StatekWroga > vStatkiWroga;
extern std::vector < Asteroida > Asteroids;
extern std::vector < Bullet > vPociskiWroga;

StatekWroga::StatekWroga( Vector polozenie, Vector dir, FireMode mode ) :
                            StatekKosmiczny( 0.87f, 0.3f, polozenie, dir, mode ),
                            timeToShoot( 0.0f )
{
    CoIleStrzal = rand() % 500 + 200;
    CoIleStrzal *= 0.01;
}

StatekWroga::~StatekWroga()
{
}

void StatekWroga::Draw()
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

        glColor3fv( White );
        glTranslatef( xyz.X, xyz.Y, xyz.Z );

        glCallList( list_dron );

    glPopMatrix();
}

void StatekWroga::Move( float &LoopTime, FormacjaWroga &mode )
{
    xyz = xyz + vKierumek * LoopTime * szybkosc;
}

void StatekWroga::Fire( float &LoopTime, Vector &pozycja_gracza )
{
    timeToShoot +=LoopTime;

    if ( pozycja_gracza.Odleglosc( xyz ) > 75 )
        return;

    if ( timeToShoot >= CoIleStrzal ) {
        Vector dir = pozycja_gracza - xyz;
        dir.Normalize();

        StatekKosmiczny::Fire( vPociskiWroga, dir, 0.03f, 0.15f );
        timeToShoot = 0.0f;
    }
}
