#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include <OGLcolors.h>
#include <cstdio>
#include <fstream>
#include <StopWatch.h>
#include <iostream>

#include "../TGALoader/targa.h"
#include "../OBJLoader/loadObj.h"

GLuint list_SkyBox, list_cross,
        list_life, list_blood,
        list_dron, list_rock,
        list_bullet, list_award,
        list_scope;

GLuint model_award, model_rock, model_bullet, model_space_ship;

#define LiczbaTextur 8

GLuint t_textures[ LiczbaTextur ];

#define LiczbaDzwiekow 11

sf::Music sounds[ LiczbaDzwiekow ];

sf::Font font;

extern bool DownloadFile();
extern void Write( std::string &str, int x, int y, int sizeCharacter,sf::RenderWindow &app, const float *color );

struct Rank
{
    int punkty;
    int zycia;
    int statki;
    int nagrody_zdobyte;
    int rozwalone_nagrody;
    int rozbite_asteroidy;
    std::string name;
};

Rank Top10[10];

void pisz( sf::RenderWindow &app, std::string & str )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    app.pushGLStates();
        Write( str, 25, 17, 30, app, YellowGreen );
    app.popGLStates();
    app.display();
}

void Inicjuj( sf::RenderWindow &app )
{
    font.loadFromFile( "fonts/comicbd.ttf" );

    std::string str( "Ladowanie textur..." );
    CStopWatch timer;

    pisz( app, str );

    const char *chTextures[ LiczbaTextur ] = {  "textures/background.tga",
                                                "textures/cross.tga",
                                                "textures/life.tga",
                                                "textures/blood.tga",
                                                "textures/enemy.tga",
                                                "textures/comet.tga",
                                                "textures/bullet.tga",
                                                "textures/award.tga" };

    GLsizei width, height;
    GLenum format, type;
    GLvoid *pixels;

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    for ( int i = 0; i < LiczbaTextur; ++i ){

        if ( !load_targa( chTextures[i], width, height, format, type, pixels) ){
            str = "Brak pliku ";
            str += chTextures[i];
            pisz( app, str );
            while ( timer.GetElapsedSeconds() < 1.0f ){
                continue;
            }
        }

        glGenTextures(1,&t_textures[ i ]);
        glBindTexture(GL_TEXTURE_2D, t_textures[ i ]);
        gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,width,height,format,type,pixels);

        delete [] (unsigned char *)pixels;
    }

    str = "Ladowanie modeli...";
    pisz( app, str );

    load_obj( "models/award/WoodenBox02.obj", model_award );
    load_obj( "models/comet/Rock.obj", model_rock );
    load_obj( "models/bullet/bullet.obj", model_bullet );
    load_obj( "models/SpaceShip/fighter.obj", model_space_ship );

    str = "Ladowanie dzwiekow...";
    pisz( app, str );

    const char *chMusic[ LiczbaDzwiekow ] = {   "sounds/MenuBackground#1.ogg",
                                                "sounds/MenuBackground#2.ogg",
                                                "sounds/Background.ogg",
                                                "sounds/fire.ogg",
                                                "sounds/Award.ogg",
                                                "sounds/ColShipComet.ogg",
                                                "sounds/ColShipShip.ogg",
                                                "sounds/CometExplo.ogg",
                                                "sounds/lifeLost.ogg",
                                                "sounds/ShipExplo.ogg",
                                                "sounds/hit.ogg" };

    for ( int i = 0; i < LiczbaDzwiekow; ++i ){
        if ( !sounds[i].openFromFile( chMusic[i] ) ){
            str = "Brak pliku ";
            str += chMusic[i];
            pisz( app, str );
            while ( timer.GetElapsedSeconds() < 1.0f ){
                continue;
            }
        }
    }

    sounds[0].setRelativeToListener( true );
    sounds[1].setRelativeToListener( true );
    sounds[2].setRelativeToListener( true );
    sounds[3].setRelativeToListener( true );
    sounds[4].setRelativeToListener( true );
    sounds[8].setRelativeToListener( true );
    sounds[10].setRelativeToListener( true );

    sounds[2].setLoop( true );
    sounds[2].setVolume( 20 );

    sounds[9].setMinDistance( 7.0f );
    sounds[9].setAttenuation( 15.0f );
    sounds[7].setMinDistance( 7.0f );
    sounds[7].setAttenuation( 15.0f );

    sf::Listener::setGlobalVolume( 100.f );
    sf::Listener::setDirection( 0.0f, 0.0f, -1.0f );

    str = "Inicjowaie list wyswietlania...";
    pisz( app, str );

    ///Lista tla!
    list_SkyBox = glGenLists( 1 );
    glNewList( list_SkyBox, GL_COMPILE );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[0] );

        glBegin( GL_QUADS );
            ///Tyl
            glNormal3f( 0.0f, 0.0f, 1.0f );

            glTexCoord2f(0, 1); glVertex3f(-1, -1, 1);
            glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
            glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
            glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);

        glEnd();

        glDisable( GL_TEXTURE_2D );

    glEndList();

    ///Lista celownika
    list_cross = glGenLists( 1 );
    glNewList( list_cross, GL_COMPILE );

        glColor3fv( White );

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_BLEND );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[1] );

        glBegin( GL_QUADS );

            glNormal3f( 0.0f, 0.0f, 1.0f );

            glTexCoord2f(0, 1); glVertex3f(-1, -1, 1);
            glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
            glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
            glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);

        glEnd();

        glDisable( GL_TEXTURE_2D );

        glDisable( GL_BLEND );

    glEndList();

    ///lista zycia
    list_life = glGenLists( 1 );
    glNewList( list_life, GL_COMPILE );

        glColor3fv( White );

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_BLEND );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[2] );

        glBegin( GL_QUADS );

            glNormal3f( 0.0f, 0.0f, 1.0f );

            glTexCoord2f(0, 1); glVertex3f(-1, -1, 1);
            glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
            glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
            glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);

        glEnd();

        glDisable( GL_TEXTURE_2D );

        glDisable( GL_BLEND );

    glEndList();

    ///lista krwi
    list_blood = glGenLists( 1 );
    glNewList( list_blood, GL_COMPILE );

        glColor3fv( White );

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_BLEND );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[3] );

        glBegin( GL_QUADS );

            glNormal3f( 0.0f, 0.0f, 1.0f );

            glTexCoord2f(0, 1); glVertex3f(-1, -1, 1);
            glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
            glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
            glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);

        glEnd();

        glDisable( GL_TEXTURE_2D );

        glDisable( GL_BLEND );

    glEndList();

    list_dron = glGenLists( 1 );
    glNewList( list_dron, GL_COMPILE );

        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );

        glEnable( GL_COLOR_MATERIAL );
        glColorMaterial( GL_FRONT, GL_AMBIENT );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[4] );

        glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
        glScalef( 0.22f, 0.22f, 0.22f );

        glCallList( model_space_ship );

        glDisable( GL_TEXTURE_2D );


        glDisable( GL_COLOR_MATERIAL );
        glDisable( GL_LIGHTING );

    glEndList();

    list_award = glGenLists( 1 );
    glNewList( list_award, GL_COMPILE );

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, t_textures[7] );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT, GL_AMBIENT );

    glCallList( model_award );

    glDisable( GL_COLOR_MATERIAL );
    glDisable( GL_LIGHTING );

    glDisable( GL_TEXTURE_2D );

    glEndList();

    list_rock = glGenLists( 1 );
    glNewList( list_rock, GL_COMPILE );

        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );

        glEnable( GL_COLOR_MATERIAL );
        glColorMaterial( GL_FRONT, GL_AMBIENT );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[5] );

        glCallList( model_rock );

        glDisable( GL_TEXTURE_2D );

        glDisable( GL_COLOR_MATERIAL );
        glDisable( GL_LIGHTING );

    glEndList();

    list_bullet = glGenLists( 1 );
    glNewList( list_bullet, GL_COMPILE );

        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, t_textures[6] );

        glScaled(0.7,0.7,0.7);
        glCallList( model_bullet );

        glDisable( GL_TEXTURE_2D );

    glEndList();

    str = "Pobieranie rankingu...";
    pisz( app, str );

    if ( DownloadFile() ) {
        str = "Pobieranie zakonczone...";
    } else {
        str = "Nie udalo sie pobrac rankingu!";
    }

    pisz( app, str );

    while ( timer.GetElapsedSeconds() < 1.0f ){
        continue;
    }

    str = "Tworzenie rankingu...";
    pisz( app, str );

    std::ifstream fin( "ranking.txt" );

        if ( fin.good() ) {
            for ( int i = 0; i < 10; ++i ) {
                fin >> Top10[i].punkty;
                fin >> Top10[i].zycia;
                fin >> Top10[i].statki;
                fin >> Top10[i].nagrody_zdobyte;
                fin >> Top10[i].rozwalone_nagrody;
                fin >> Top10[i].rozbite_asteroidy;
                char ch;
                fin.get( ch );
                ch = 'p';
                while ( ch != '\n' && ch != '\r' ) {
                    fin.get( ch );
                    Top10[i].name += ch;
                }
            }
        } else {
            str = "Plik ranking.txt nie nadaje sie do odczytu! ";
            pisz( app, str );
            while ( timer.GetElapsedSeconds() < 1.0f ){
                continue;
            }
        }

    fin.close();

    str = "Gotowe!";
    pisz( app, str );
}
