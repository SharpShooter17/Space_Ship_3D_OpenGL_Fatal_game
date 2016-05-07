#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <OGLcolors.h>

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

extern Rank Top10[10];

extern void Write( std::string &str, int x, int y, int sizeCharacter,sf::RenderWindow &app, const float *color );

extern void ChangeSize( int width, int height );
extern sf::Font font;

extern std::string nickname;

extern unsigned int Width;
extern unsigned int Height;

void MenuLoop( sf::RenderWindow &app, bool &bMenu, bool &bczyGra )
{
    sf::Text StartGame;
    StartGame.setFont( font );
    StartGame.setString( "Start Gry!" );
    StartGame.setCharacterSize( 40 );
    StartGame.setColor( sf::Color::Green );
    StartGame.setPosition( ( Width/2 - StartGame.getLocalBounds().width/2 ), 100 );

    sf::Text Nick;
    Nick.setFont( font );
    Nick.setString( nickname );
    Nick.setCharacterSize( 30 );
    Nick.setColor( sf::Color::Green );
    Nick.setPosition( ( Width/2 - Nick.getLocalBounds().width/2 ), 50 );

    sf::Text Exit;
    Exit.setFont( font );
    Exit.setString( "Wyjscie!" );
    Exit.setCharacterSize( 40 );
    Exit.setColor( sf::Color::Green );
    Exit.setPosition( ( Width/2 - Exit.getLocalBounds().width/2 ), 700 );

    sf::Text TheBestOf;
    TheBestOf.setFont( font );
    TheBestOf.setString( "Lista najlepszych:" );
    TheBestOf.setCharacterSize( 40 );
    TheBestOf.setColor( sf::Color::Green );
    TheBestOf.setPosition( ( Width/2 - TheBestOf.getLocalBounds().width/2 ), 150 );

    sf::Mouse::setPosition( sf::Vector2i( Width/2, Height/2 ), app );
    app.setMouseCursorVisible( true );

    sf::Event event;
    while ( bMenu ) {

        while ( app.pollEvent( event ) ) {
            if (event.type == sf::Event::Closed) {
                bczyGra = false;
                bMenu = false;
                app.close();
            }
            else if (event.type == sf::Event::Resized) {
                ChangeSize( event.size.width, event.size.height );
            }

            ///zmiana koloru napisu Start gry
            if (sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height){
                    StartGame.setColor(sf::Color::Red);
                }
                else{
                    StartGame.setColor(sf::Color::Green);
                }

            ///Start Gry! :D
            if ( ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height) ||
                sf::Joystick::isButtonPressed(0, 8) ) {
                    bczyGra = true;
                    bMenu = false;
                    return;
                }

            if ( event.type == sf::Event::TextEntered && nickname.size() < 20 &&
                event.key.code != sf::Keyboard::BackSpace && event.key.code != sf::Keyboard::Space ) {
                nickname +=  event.text.unicode;
                Nick.setString( nickname );
                Nick.setPosition( ( Width/2 - Nick.getLocalBounds().width/2 ), 50 );
            }
                else if (event.key.code == sf::Keyboard::BackSpace && nickname.size() > 0){
                    nickname.erase(nickname.end() - 1);
                    Nick.setString( nickname );
                    Nick.setPosition( ( Width/2 - Nick.getLocalBounds().width/2 ), 50 );
                }

            if ( ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                sf::Mouse::getPosition(app).x > Exit.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > Exit.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < Exit.getGlobalBounds().left + Exit.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < Exit.getGlobalBounds().top +  Exit.getGlobalBounds().height) ||
                sf::Joystick::isButtonPressed(0, 8) ) {
                    bczyGra = false;
                    bMenu = false;
                    app.close();
                    return;
                }

            if (sf::Mouse::getPosition(app).x > Exit.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > Exit.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < Exit.getGlobalBounds().left + Exit.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < Exit.getGlobalBounds().top +  Exit.getGlobalBounds().height){
                    Exit.setColor(sf::Color::Red);
                }
                else{
                    Exit.setColor(sf::Color::Green);
                }

        }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        std::string a( "Nick:" );
        Write( a, 25, 200, 28, app, Yellow );
        a = "Punkty:";
        Write( a, 340, 200, 28, app, YellowGreen );
        a = "Popsute statki wroga:";
        Write( a, 512, 200, 28, app, Orange );

        for ( int i = 0; i < 10; ++i ) {
                Write( Top10[i].name, 25, 230 + i * 30, 28, app, Yellow );
                char temp[128];
                sprintf( temp, "%i", Top10[i].punkty );
                std::string tmp = temp;
                Write( tmp, 340, 230 + i * 30, 28, app, YellowGreen );
                sprintf( temp, "%i", Top10[i].statki );
                tmp = temp;
                Write( tmp, 512, 230 + i * 30, 28, app, Orange );
            }

        app.pushGLStates();

            app.draw( StartGame );
            app.draw( Nick );
            app.draw( TheBestOf );
            app.draw( Exit );

        app.popGLStates();

        app.display();
    }
}
