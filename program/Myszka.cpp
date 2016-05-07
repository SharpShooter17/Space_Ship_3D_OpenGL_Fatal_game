#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdio>
#include <iostream>

#include "../include/HUD.h"
#include "../include/Gracz.h"
#include "../include/Bullet.h"

extern unsigned int Width ;
extern unsigned int Height;
extern std::vector < Bullet > vPociskiGracza;

int last_x = Width / 2;
int last_y = Height / 2;

extern HUD hud;
extern Gracz Player;
float PlayerTimeToFire = 0.0f;

#define LiczbaDzwiekow 11
extern sf::Music sounds[ LiczbaDzwiekow ];

void MouseControl( float &LoopTime  )
{
    PlayerTimeToFire += LoopTime;

    if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && PlayerTimeToFire >= 0.35f ) {
        Vector dir( hud.getCrossX() - Player.getX(),
                    hud.getCrossY() - Player.getY(),
                    - 2.3f );   ///dzieki tej wartosci kula strzela na srodku krzyzyka!
        dir.Normalize();

        Player.Fire( vPociskiGracza, dir );

        PlayerTimeToFire = 0.0f;

        sounds[3].setVolume( 45 );
        sounds[3].play();
    }
}

void MouseReset( sf::RenderWindow &app, bool bResetKursora = false )
{
    sf::Mouse::setPosition( sf::Vector2i( Width / 2, Height / 2 ), app );
    last_x = Width / 2;
    last_y = Height / 2;
    if ( bResetKursora )
        hud.ResetCross();
}

void MoveMouse( int x, int y, sf::RenderWindow &app )
{
    float Long = sqrt( ( Width/2 - x ) * ( Width/2 - x ) + ( Height/2 - y ) * ( Height/2 - y ) );

    if ( Long > 200 ) {
        MouseReset( app, false );
    }

    float move_x, move_y;

    move_x = ( x - last_x ) * hud.sensitivityMouse;
    move_y = ( - y + last_y ) * hud.sensitivityMouse;

    hud.moveCross( move_x, move_y );

    last_x = x;
    last_y = y;
}
