#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "../include/Gracz.h"
#include "../include/HUD.h"

extern Gracz Player;
extern HUD hud;
extern void MouseReset( sf::RenderWindow &app, bool bResetKursora = false );

bool bKeyPressed[ sf::Keyboard::KeyCount ];

void KeyControl( float &LoopTime, sf::RenderWindow &app )
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) {
        Player.wPrawo( LoopTime );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) {
        Player.wLewo( LoopTime );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) {
        Player.wDol( LoopTime );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) {
        Player.wGore( LoopTime );
    }

    ///Reset myszki
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) ) {
        MouseReset( app, true );
    }

    ///Czulosc myszki

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::PageUp ) ) {
        hud.changeMouseSensitivity( 1 );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::PageDown ) ) {
        hud.changeMouseSensitivity( -1 );
    }
}
