#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/hud.h"
#include "../include/Gracz.h"
#include "StopWatch.h"

extern void ChangeSize( int width, int height );
extern void RenderScene();
extern void Logika( float &LoopTime );

extern void KeyControl( float & LoopTime ,sf::RenderWindow &app );
extern void MoveMouse( int x, int y, sf::RenderWindow &app );
extern void MouseControl(float &LoopTime);
extern void Joystick( float &LoopTime, sf::RenderWindow &app );

CStopWatch TimeLoop;
float LoopTime;
extern Gracz Player;
extern const unsigned int Width ;
extern const unsigned int Height ;

extern HUD hud;

#define LiczbaDzwiekow 11
extern sf::Music sounds[ LiczbaDzwiekow ];

extern void ResetGame();

void GameLoop( sf::RenderWindow &app, bool &bczyGra, bool &bMenu )
{
    ResetGame();

    bool pauseGame = false;

    sf::Mouse::setPosition( sf::Vector2i( Width / 2, Height / 2 ), app );
    app.setMouseCursorVisible( false );

    sounds[2].play();

    while ( bczyGra )
    {
        LoopTime = TimeLoop.GetElapsedSeconds();
        TimeLoop.Reset();

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                bczyGra = false;
                bMenu = false;
                app.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                ChangeSize( event.size.width, event.size.height );
            }
            else if ( ( event.type == sf::Event::KeyReleased ) &&
                      ( event.key.code == sf::Keyboard::Escape ) ){
                bczyGra = false;
                bMenu = true;
            }

            if ( ( ( event.type == sf::Event::JoystickButtonReleased ) &&
                 ( event.joystickButton.button == 0 ) )  ||
                ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P ) ){
                pauseGame = !pauseGame;
                if ( pauseGame == true ) {
                    app.setMouseCursorVisible( true );
                    sounds[2].pause();
                } else {
                    sf::Mouse::setPosition( sf::Vector2i( Width / 2, Height / 2 ), app );
                    app.setMouseCursorVisible( false );
                    LoopTime = 0.0f;
                    TimeLoop.Reset();
                    sounds[2].play();
                }
            }
        }

        KeyControl( LoopTime, app );
        if ( !pauseGame ) {
            MoveMouse( sf::Mouse::getPosition( app ).x, sf::Mouse::getPosition( app ).y, app );
            MouseControl( LoopTime );
            Joystick( LoopTime, app );
            if ( Player.getLife() < 0 ) {
                bczyGra = false;
                bMenu = true;
            }
            Logika( LoopTime );
            RenderScene();
            app.display();
        }
    }

    sounds[2].stop();
    hud.sendScore();
}
