#include "../include/MenadzerNPC.h"
#include "../include/Asteroida.h"
#include "../include/HUD.h"
#include <cstdlib>
#include <ctime>
#define DegToRad 3.14159265358979323846/180.0f

extern HUD hud;
std::vector < StatekWroga > vStatkiWroga;
std::vector < Asteroida > Asteroids;

MenadzerNPC::MenadzerNPC( float *z ) : mode( Random ), gdzieJestGraczZ( z )
{}

MenadzerNPC::~MenadzerNPC()
{}

void MenadzerNPC::NowaKonstrukcja( )
{
    switch( mode )
    {
    case Random:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Rozproszenie", Silver );
            while ( vStatkiWroga.size() < 200 ) {
                float x = ( rand() % 100 - 100 ) * 0.1f;
                float y = ( rand() % 100 - 100 ) * 0.1f;
                float z = ( rand() % 150 + 100 ) * ( - 1 ) + *gdzieJestGraczZ;

                float a = rand() % 10 * 0.1f;
                float b = rand() % 10 * 0.1f;

                Vector dir( a, b, 1.0f );
                dir.Normalize();
                vStatkiWroga.push_back( StatekWroga( Vector(x, y, z), dir  ) );
            }

            MakeAsteroids( 700 );

            break;
        }
    case V:
        {
            hud.addInfo( "Nowa konstrukcja wroga: V", Silver );
            /** Tak beda lecialy statki wroga!
                   *         *
                    *       *
                     *     *
                      *   *
                       * *
                        *
            **/

            vStatkiWroga.push_back( Vector( 0.0f, 0.0f, *gdzieJestGraczZ -100.0f ) );

            vStatkiWroga.push_back( Vector( 0.5f, 0.0f, *gdzieJestGraczZ -100.5f ) );
            vStatkiWroga.push_back( Vector( -0.5f, 0.0f, *gdzieJestGraczZ -100.5f ) );

            vStatkiWroga.push_back( Vector( 1.0f, 0.0f, *gdzieJestGraczZ -101.0f ) );
            vStatkiWroga.push_back( Vector( -1.0f, 0.0f, *gdzieJestGraczZ -101.0f ) );

            vStatkiWroga.push_back( Vector( 1.5f, 0.0f, *gdzieJestGraczZ -101.5f ) );
            vStatkiWroga.push_back( Vector( -1.5f, 0.0f, *gdzieJestGraczZ -101.5f ) );

            vStatkiWroga.push_back( Vector( 2.0f, 0.0f, *gdzieJestGraczZ -102.0f ) );
            vStatkiWroga.push_back( Vector( -2.0f, 0.0f, *gdzieJestGraczZ -102.0f ) );

            vStatkiWroga.push_back( Vector( 2.5f, 0.0f, *gdzieJestGraczZ -102.5f ) );
            vStatkiWroga.push_back( Vector( -2.5f, 0.0f, *gdzieJestGraczZ -102.5f ) );

            break;
            MakeAsteroids( 600 );
        }
    case Odwrocone_V:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Odwrocone V", Silver );
            /**
                        *
                       * *
                      *   *
                     *     *
                    *       *
                   *         *
            **/

            vStatkiWroga.push_back( Vector( 0.0f, 0.0f, *gdzieJestGraczZ -102.5f ) );

            vStatkiWroga.push_back( Vector( 0.5f, 0.0f, *gdzieJestGraczZ -102.0f ) );
            vStatkiWroga.push_back( Vector( -0.5f, 0.0f, *gdzieJestGraczZ -102.0f ) );

            vStatkiWroga.push_back( Vector( 1.0f, 0.0f, *gdzieJestGraczZ -101.5f ) );
            vStatkiWroga.push_back( Vector( -1.0f, 0.0f, *gdzieJestGraczZ -101.5f ) );

            vStatkiWroga.push_back( Vector( 1.5f, 0.0f, *gdzieJestGraczZ -101.0f ) );
            vStatkiWroga.push_back( Vector( -1.5f, 0.0f, *gdzieJestGraczZ -101.0f ) );

            vStatkiWroga.push_back( Vector( 2.0f, 0.0f, *gdzieJestGraczZ -100.5f ) );
            vStatkiWroga.push_back( Vector( -2.0f, 0.0f, *gdzieJestGraczZ -100.5f ) );

            vStatkiWroga.push_back( Vector( 2.5f, 0.0f, *gdzieJestGraczZ -100.0f ) );
            vStatkiWroga.push_back( Vector( -2.5f, 0.0f, *gdzieJestGraczZ -100.0f ) );

            MakeAsteroids( 500 );
            break;
        }
    case DwieKolumny_I_I:
        {
            hud.addInfo( "Nowa konstrukcja wroga: 2 Kolumny", Silver );
            for ( int i = 0; i < 10; ++i ){
                vStatkiWroga.push_back( Vector( -1.0f, 0.0f, *gdzieJestGraczZ -100.0f - 0.7f * i ) );
                vStatkiWroga.push_back( Vector( 1.0f, 0.0f, *gdzieJestGraczZ -100.0f - 0.7f * i ) );
            }
            MakeAsteroids( 450 );
            break;
        }
    case Kolumn5x5x5x4:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Szyk bojowy", Silver );
            int liczba_kolumn = 5;

             for ( int i = 0; i < liczba_kolumn; ++i ){
                    for ( int j = 0; j < liczba_kolumn; ++j ){
                        for ( int k = 0; k < liczba_kolumn; ++k){
                            vStatkiWroga.push_back( Vector( -8.0f + j * 0.7f, 8.0f - k * 0.7f, *gdzieJestGraczZ -100.0f - 0.7f * i ) );
                        }
                    }
                }

              for ( int i = 0; i < liczba_kolumn; ++i ){
                    for ( int j = 0; j < liczba_kolumn; ++j ){
                        for ( int k = 0; k < liczba_kolumn; ++k){
                            vStatkiWroga.push_back( Vector( 8.0f - j * 0.7f, 8.0f - k * 0.7f, *gdzieJestGraczZ -100.0f - 0.7f * i ) );
                        }
                    }
                }

              for ( int i = 0; i < liczba_kolumn; ++i ){
                    for ( int j = 0; j < liczba_kolumn; ++j ){
                        for ( int k = 0; k < liczba_kolumn; ++k){
                            vStatkiWroga.push_back( Vector( -8.0f + j * 0.7f, -8.0f - k * 0.7f, *gdzieJestGraczZ -100.0f - 0.7f * i ) );
                        }
                    }
                }

              for ( int i = 0; i < liczba_kolumn; ++i ){
                    for ( int j = 0; j < liczba_kolumn; ++j ){
                        for ( int k = 0; k < liczba_kolumn; ++k){
                            vStatkiWroga.push_back( Vector( 8.0f - j * 0.7f, -8.0f - k * 0.7f, *gdzieJestGraczZ -100.0f - 0.7f * i ) );
                        }
                    }
                }

            MakeAsteroids( 350 );

            break;
        }
    case PolOkrag:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Pol okrag", Silver );
            float S = *gdzieJestGraczZ -125.0f;
            float x = 0.0f;
            float z = 0.0f;
            float r = 5.0f;

            for ( int i = 0; i < 180 / 10; ++i ){
                x = 0.0 + r * cos( i * 10 * DegToRad );
                z = 0.0 + r * sin( i * 10 * DegToRad );
                vStatkiWroga.push_back( Vector( x, 0.0f, S + z ) );
            }
            break;
            MakeAsteroids( 450 );
        }
    case Okrag:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Poziomy okrag ", Silver );
            float S = *gdzieJestGraczZ -125.0f;
            float x, z = 0.0f;
            float r = 5.0f;

            for ( int i = 0; i < 360 / 10; ++i ){
                x = 0.0 + r * cos( i * 10 * DegToRad );
                z = 0.0 + r * sin( i * 10 * DegToRad );
                vStatkiWroga.push_back( Vector( x, 0.0f, S + z ) );
            }
            MakeAsteroids( 500 );
            break;
        }
    case Sfera:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Kula", Silver );
            float S = *gdzieJestGraczZ -125.0f;
            float x = 0.0f;
            float z = 0.0f;
            float r = 5.0f;

            vStatkiWroga.push_back( Vector( x, 5.0f, S + z ) );
            vStatkiWroga.push_back( Vector( x, -5.0f, S + z ) );

            for ( int i = 0; i < 360 / 15; ++i ){
                x = 0.0 + r * cos( i * 15 * DegToRad );
                z = 0.0 + r * sin( i * 15 * DegToRad );
                vStatkiWroga.push_back( Vector( x, 0.0f, S + z ) );
            }

            r = 4.0f;
            for ( int i = 0; i < 360 / 30; ++i ){
                x = 0.0 + r * cos( i * 30 * DegToRad );
                z = 0.0 + r * sin( i * 30 * DegToRad );

                vStatkiWroga.push_back( Vector( x, 1.0f, S + z ) );
                vStatkiWroga.push_back( Vector( x, -1.0f, S + z ) );
            }

            r = 3.0f;
            for ( int i = 0; i < 360 / 60; ++i ){
                x = 0.0 + r * cos( i * 60 * DegToRad );
                z = 0.0 + r * sin( i * 60 * DegToRad );

                vStatkiWroga.push_back( Vector( x, 2.0f, S + z ) );
                vStatkiWroga.push_back( Vector( x, -2.0f, S + z ) );
            }

            r = 2.0f;
            for ( int i = 0; i < 360 / 120; ++i ){
                x = 0.0 + r * cos( i * 120 * DegToRad );
                z = 0.0 + r * sin( i * 120 * DegToRad );

                vStatkiWroga.push_back( Vector( x, 3.0f, S + z ) );
                vStatkiWroga.push_back( Vector( x, -3.0f, S + z ) );
            }

            r = 1.0f;
            for ( int i = 0; i < 360 / 180; ++i ){
                x = 0.0 + r * cos( i * 180 * DegToRad );
                z = 0.0 + r * sin( i * 180 * DegToRad );

                vStatkiWroga.push_back( Vector( x, 4.0f, S + z ) );
                vStatkiWroga.push_back( Vector( x, -4.0f, S + z ) );
            }

        MakeAsteroids( 500 );

        break;
        }
    case Okrag2:
        {
            hud.addInfo( "Nowa konstrukcja wroga: Pionowy okrag", Silver );
            float S = *gdzieJestGraczZ -125.0f;
                float x, y = 0.0f;
                float r = 5.0f;

                for ( int i = 0; i < 360 / 10; ++i ){
                    x = 0.0 + r * cos( i * 10 * DegToRad );
                    y = 0.0 + r * sin( i * 10 * DegToRad );
                    vStatkiWroga.push_back( Vector( x, y, S ) );
                }
                MakeAsteroids( 500 );
            break;
        }
    default:
        break;
    }
}

void MenadzerNPC::czyNowaKonstrukcja()
{
    if ( vStatkiWroga.size() <= 1 ) {
        mode = ( FormacjaWroga ) ( ( int ) ( mode ) + 1 );
        if ( mode == maximum )
            mode = Random;

        NowaKonstrukcja();
    }

    MakeAsteroids( 1 );
}

void MenadzerNPC::DrawVEnemyShips()
{
    for ( int i = 0; i < vStatkiWroga.size(); ++i ) {
        vStatkiWroga[i].Draw();
    }
    for ( int i = 0; i < Asteroids.size(); ++i){
        Asteroids[i].Draw();
    }
}

void MenadzerNPC::ControlEnemyShips( float &LoopTime, Vector &xyz  )
{
    for ( int i = 0; i < vStatkiWroga.size(); ++i ) {
        vStatkiWroga[i].Move( LoopTime, mode );
        vStatkiWroga[i].Fire( LoopTime, xyz );
    }

    for ( int i = 0; i < Asteroids.size(); ++i){
        Asteroids[i].Move( LoopTime );
    }

}

void MenadzerNPC::MakeAsteroids( int n )
{
    for ( int i = n; i > 0; --i  ){
        if ( Asteroids.size() > 1000 )
            break;

        float x = ( rand() % 150 - 150 ) * 0.1f;
        float y = ( rand() % 150 - 150 ) * 0.1f;
        float z = ( rand() % 150 + 100 ) * ( - 1 ) + *gdzieJestGraczZ;

        float a = rand() % 10 * 0.1f;
        float b = rand() % 10 * 0.1f;

        Vector dir( a, b, 1.0f );
        dir.Normalize();
        Asteroids.push_back( Asteroida( Vector( x, y, z ), dir, ( rand() % 20 + 10 ) * 0.1f ) );
    }

    return;
}
