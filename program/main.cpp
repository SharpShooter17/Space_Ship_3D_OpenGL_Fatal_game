#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cstdlib>

unsigned int Width = 1024;
unsigned int Height = 768;

extern void Inicjuj( sf::RenderWindow &app );
extern void ChangeSize( int width, int height );
extern void GameLoop( sf::RenderWindow &app, bool &bczyGra, bool &bMenu );
extern void MenuLoop( sf::RenderWindow &app, bool &bMenu, bool &bczyGra );

#define LiczbaTextur 8
extern GLuint t_textures[ LiczbaTextur ];

sf::RenderWindow app;

int main(int argc, char *argv[])
{
    app.create( sf::VideoMode( 512, 64 ), "Loading...", sf::Style::Titlebar, sf::ContextSettings() );
    app.setVerticalSyncEnabled( true );

        Inicjuj( app );

        bool bMenu = true;
        bool bczyGra = false;

    app.close();

    app.create( sf::VideoMode(Width, Height), "Space Ship 3D", sf::Style::Fullscreen, sf::ContextSettings(32) );
    app.setVerticalSyncEnabled( true );

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    glHint( GL_FOG_HINT, GL_NICEST );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

    glShadeModel( GL_FLAT );

    ChangeSize( Width, Height );

    while( app.isOpen() ) {
        if ( bMenu ){
            MenuLoop( app, bMenu, bczyGra );
        }

        if ( bczyGra ){
            GameLoop( app, bczyGra, bMenu );
        }
    }

    for ( int i = 0; i < LiczbaTextur; ++i ){
        glDeleteTextures( 1, &t_textures[i] );
    }

    return EXIT_SUCCESS;
}
