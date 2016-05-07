#include <SFML/OpenGL.hpp>

#include "../include/Gracz.h"
#include "../include/StatekWroga.h"
#include "../include/HUD.h"
#include "../include/MenadzerNPC.h"
#include "../include/Nagroda.h"

#include <GL/glu.h>

const double ViewNear = 1;
const double ViewFar = 100;

extern unsigned int Width;
extern unsigned int Height;

extern GLuint list_SkyBox;

extern Gracz Player;
extern HUD hud;
extern MenadzerNPC MenagerNPC;
extern void Logika();
extern std::vector < Bullet > vPociskiGracza;
extern std::vector < Bullet > vPociskiWroga;
extern std::vector < Nagroda > vNagrody;
extern float LoopTime;

void SkyBox()
{
    glPushMatrix();

        glTranslatef( Player.getX(), Player.getY(), Player.getZ() - 99 );
        glScalef( 43.0f, 43.0f, 1.0f );
        glCallList( list_SkyBox );

    glPopMatrix();
}

void Draw()
{
    MenagerNPC.DrawVEnemyShips();

    for ( int i = 0; i < vPociskiWroga.size(); ++i){
        vPociskiWroga[i].Draw();
    }

    for ( int i = 0; i < vPociskiGracza.size(); ++i){
        vPociskiGracza[i].Draw();
    }

    for ( int i = 0; i < vNagrody.size(); ++i ){
        vNagrody[i].Draw();
    }
}

void RenderScene( void )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glPushMatrix();

        glTranslatef( 0.0f, 0.0f, - ( ViewNear + ViewFar ) / 2.0f
                                   + ( ViewNear + ViewFar ) / 2.0f - 0.0f );

         Player.UstawKamere();

         SkyBox();
         Draw();

        hud.DrawHUD( LoopTime );


    glPopMatrix();

    glFlush();
}

void ChangeSize( int width, int height )
{
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0f, width / height, ViewNear, ViewFar );

    Width = width;
    Height = height;
}
