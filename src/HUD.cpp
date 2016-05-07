#include <SFML/Network.hpp>
#include <sstream>
#include "../include/HUD.h"
#include <GL/glu.h>

extern GLuint list_cross, list_life, list_blood, list_scope;
extern sf::Font font;
extern const unsigned int Width;
extern const unsigned int Height;

void Write( std::string &str, int x, int y, int sizeCharacter,sf::RenderWindow &app, const float *color );

HUD::HUD( Vector *XYZ, short *life, short *stan, FireMode *mod, float *timeBlood, sf::RenderWindow *window, std::string *nick ) :
    x_cross( 0.0f ), y_cross( 0.0f ), xyz( XYZ ), zyc( life ),
    sprawnosc( stan ), RodzajBroni( mod ), punktow( 0 ), BloodTimer( timeBlood ),
    mouseSensitivity( 5 ), sensitivityMouse( 0.005f ), timer( 0.0f ), app( window ), name(nick)
{
    zdobytych_nagrod = Straconych_zyc = rozbitych_asteroid = rozbitych_statkow_wroga = rozwalonych_nagrod = 0;
}

HUD::~HUD()
{
}

void HUD::addInfo( char *str, const float *color )
{
    Information temp;
    temp.str = str;
    temp.color = color;

    Info.push_front( temp );
    timer = 0.0f;
}

void HUD::changeMouseSensitivity( short n )
{
    if ( mouseSensitivity > 0 || n > 0 ) {
        mouseSensitivity += n;
        sensitivityMouse += n * 0.001f;
    }

    char str[32];
    sprintf( str, "Czulosc myszki: %i", mouseSensitivity );

    addInfo( str, GreenYellow );
}

void HUD::DrawString( float &LoopTime  )
{
    if ( Info.size() > 5 )
        Info.pop_back();

    timer += LoopTime;
    if ( timer > 3.0f ){
        Information temp;
        temp.str = " ";
        temp.color = White;
        Info.push_front( temp );
        timer = 0.0f;
    }

    for ( int i = 0; i < Info.size(); ++i ){
        Write( Info[i].str, 25, Height - 100 - 20 * i, 15, *app, Info[i].color );
    }
}

void HUD::moveCross( float x, float y )
{
    x_cross += x; y_cross += y;
}

void HUD::DrawHUD( float &LoopTime )
{
    DrawString( LoopTime );
    DrawCross();
    DrawPoints();
    DrawSprawnosc();
    DrawLife();
    DrawWeapon();
    if ( *BloodTimer > 0.0f )
        DrawBlood();
}

void HUD::DrawLife()
{
     glMatrixMode( GL_MODELVIEW );
    for ( int i = 0; i < *zyc; ++i ){
            glPushMatrix();
                glTranslatef( xyz->X + 0.7 - i * 0.1, xyz->Y + 0.75f, xyz->Z - 2.2f );
                glScalef( 0.05f, 0.05f, 0.05f );
                glCallList( list_life );
            glPopMatrix();
        }
}

void HUD::DrawSprawnosc()
{
    char Sprawnosc[25];
    sprintf(Sprawnosc,"Wytrzymalosc: %i", ( int )( *sprawnosc ));
    std::string str = Sprawnosc;
    Write( str, 25, Height - 50, 30, *app, GreenYellow );
}

void HUD::DrawWeapon()
{
    char Bron[28];
    switch ( *RodzajBroni )
    {
    case PojedynczaKula:
        sprintf(Bron,"Bron: Jablko ciskacz");
        break;
    case SeriaKul:
        sprintf(Bron,"Bron: Pustynna furia");
        break;
    case PodwojneKule:
        sprintf(Bron,"Bron: Ciskomiot");
        break;
    case W3Kierumkach:
        sprintf(Bron,"Bron: Potrojna furia");
        break;
    case SeriaW3Kierunkach:
        sprintf(Bron,"Bron: The best of!");
        break;
    }
    std::string str = Bron;
    Write( str, Width - 375, Height - 50, 30, *app, Khaki );
}

void HUD::DrawPoints()
{
    char Punkty[30];
    sprintf(Punkty,"Punkty: %i", ( int )( punktow ));
    std::string str = Punkty;
    Write( str, 25, 5, 30, *app, Gold );
}

void HUD::DrawCross()
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

        glTranslatef( xyz->X + x_cross, xyz->Y + y_cross, xyz->Z - 2.3f );
        glScalef( 0.05f, 0.05f, 0.05f );
        glCallList( list_cross );

    glPopMatrix();
}

void HUD::DrawBlood()
{
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
        glTranslatef( xyz->X, xyz->Y, xyz->Z - 2.1f );
        glScalef( 0.5f , 0.5f, 1.0f );
        glCallList( list_blood );
    glPopMatrix();
}

void Write( std::string &str, int x, int y, int sizeCharacter,sf::RenderWindow &app, const float *color )
{
    app.pushGLStates();
        sf::Text pisz;
        pisz.setCharacterSize( sizeCharacter );
        pisz.setPosition( x, y );
        pisz.setFont( font );
        pisz.setString( str );
        pisz.setColor( sf::Color( color[0] * 255, color[1] * 255, color[2] * 255, color[3] * 255 ) );
        app.draw( pisz );
    app.popGLStates();
}

void HUD::sendScore()
{
    // prepare the request
    sf::Http::Request request("pli.php", sf::Http::Request::Post);

    // encode the parameters in the request body
    std::ostringstream stream;
    stream << "&score=" << punktow
           << "&zyc=" << Straconych_zyc
           << "&StatkowRozbitych=" << rozbitych_statkow_wroga
           << "&zdobytych_nagrod=" << zdobytych_nagrod
           << "&rozwalonych_nagrod=" << rozwalonych_nagrod
           << "&rozbitych_asteroid=" << rozbitych_asteroid
           << "&nickname=" << *name;
    request.setBody(stream.str());

    // send the request
    sf::Http http("http://matrixxx.cba.pl/");
    sf::Http::Response response = http.sendRequest( request );
}
