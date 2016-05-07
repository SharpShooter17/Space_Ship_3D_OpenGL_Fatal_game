#include <SFML/OpenGL.hpp>
#include <OGLcolors.h>

#include "../include/Bullet.h"

#define DegToRad M_PI/180.0f

extern GLuint list_bullet;

Bullet::Bullet( Vector XYZ, Vector DIR, float r, float speed ) :
                xyz( XYZ ), dir( DIR ), promien( r ), szybkosc( speed ),
                rot( 0.0f )
{
    if ( dir.Z <= 0 )
        startRotate = 180.0f;
    else
        startRotate = 0.0f;
}

Bullet::~Bullet()
{
}

void Bullet::Draw()
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

        glColor3fv( White );
        glTranslatef( xyz.X, xyz.Y, xyz.Z );
        glRotatef( startRotate, 0.0f, 1.0f, 0.0f );
        glRotatef( rot, 0.0f, 0.0f, 1.0f );
        glCallList( list_bullet );

    glPopMatrix();
}

void Bullet::Move( float &LoopTime )
{
     xyz = xyz + ( dir * LoopTime * szybkosc );
     rot += 100 * LoopTime;
}
