#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../include/Gracz.h"
#include "../include/Bullet.h"
#include "../include/HUD.h"

#define LiczbaDzwiekow 11
extern sf::Music sounds[ LiczbaDzwiekow ];

extern Gracz Player;
extern HUD hud;
extern float PlayerTimeToFire;
extern std::vector < Bullet > vPociskiGracza;

extern void MouseReset( sf::RenderWindow &app, bool bResetKursora = false );

void Joystick( float &LoopTime, sf::RenderWindow &app )
{
    for ( int i = 0; i < 8; ++i ) {
       if( sf::Joystick::isButtonPressed( 0, i ) ) {
            std::cout << i << std::endl;
        }
    }

    if ( sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 75  ) {
        Player.wPrawo( LoopTime );
    }

    if ( sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -75 ) {
        Player.wLewo( LoopTime );
    }

    if ( sf::Joystick::getAxisPosition(0, sf::Joystick::Y) >= 75 ) {
        Player.wDol( LoopTime );
    }

    if ( sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= -75 ) {
        Player.wGore( LoopTime );
    }

    if ( sf::Joystick::isButtonPressed( 0, 5 ) && PlayerTimeToFire >= 0.35f ) {
        Vector dir( hud.getCrossX() - Player.getX(),
                    hud.getCrossY() - Player.getY(),
                    - 2.3f );   ///dzieki tej wartosci kula strzela na srodku krzyzyka!
        dir.Normalize();

        Player.Fire( vPociskiGracza, dir );

        PlayerTimeToFire = 0.0f;

        sounds[3].setVolume( 45 );
        sounds[3].play();
    }

    ///Reset myszki
    if ( sf::Joystick::isButtonPressed( 0, 7 ) ) {
        MouseReset( app, true );
    }

    ///Czulosc myszki

    if ( sf::Joystick::isButtonPressed( 0, 4 ) ) {
        hud.changeMouseSensitivity( 1 );
    }

    if ( sf::Joystick::isButtonPressed( 0, 6 ) ) {
        hud.changeMouseSensitivity( -1 );
    }
}
