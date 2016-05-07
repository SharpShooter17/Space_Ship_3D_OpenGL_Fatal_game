#include <SFML/OpenGL.hpp>
#include <OGLcolors.h>

#include "../include/Nagroda.h"
#include <cstdlib>

extern GLuint list_award;

Nagroda::Nagroda( Vector &XYZ ) : xyz( XYZ ), r( 0.3f ), rot( 0.0f )
{
    life = repair = change_weapon = false;

    switch( rand() % 3 )
    {
    case Zycie:
        life = true;
        break;
    case Naprawa:
        repair = true;
        break;
    case Zmiana_broni:
        change_weapon = true;
        break;
    default:
        life = true;
        break;
    }
}

Nagroda::~Nagroda()
{
}

void Nagroda::Draw()
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

        glColor3fv( White );
        glTranslatef( xyz.X, xyz.Y, xyz.Z );
        glRotatef( rot, 0.0f, 1.0f, 1.0f );
        glScaled( 0.4f, 0.4f, 0.4f );
        glCallList( list_award );

    glPopMatrix();

    rot += 0.2f;
}
