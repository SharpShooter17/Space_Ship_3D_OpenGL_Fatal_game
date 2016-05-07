#include <SFML/OpenGL.hpp>
#include <OGLcolors.h>

#include "../include/Asteroida.h"
#include <cstdlib>

extern GLuint list_rock;

Asteroida::Asteroida( Vector polozenie, Vector kierunek, float speed ) : xyz( polozenie ),
                                                                         dir( kierunek ),
                                                                         szybkosc( speed )
{
    float x = rand() % 10 * 0.1f;
    float y = rand() % 10 * 0.1f;
    float z = rand() % 10 * 0.1f;
    Rotacja = Vector( x, y, z );
    Rotacja.Normalize();
    promien = rand() % 10 * 0.1f;
    zycie = promien * 1000;
}

Asteroida::~Asteroida()
{
}

void Asteroida::Draw()
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

        glColor3fv( White );
        glTranslatef( xyz.X, xyz.Y, xyz.Z );
        glRotatef( rot, Rotacja.X, Rotacja.Y, Rotacja.Z );
        glScalef( promien, promien, promien );
        glCallList( list_rock );

    glPopMatrix();
}

void Asteroida::Move( float & LoopTime )
{
    xyz = xyz + dir * LoopTime * szybkosc;
    rot += LoopTime * 10.0f;
}
