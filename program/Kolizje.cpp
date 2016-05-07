#include <SFML/Audio.hpp>
#include <cstdlib>
#define DegToRad 3.14159265358979323846/180.0f

#include "../include/Gracz.h"
#include "../include/HUD.h"
#include "../include/StatekWroga.h"
#include "../include/Bullet.h"
#include "../include/Asteroida.h"
#include "../include/Nagroda.h"

std::vector < Nagroda > vNagrody;

extern std::vector < StatekWroga > vStatkiWroga;
extern std::vector < Asteroida > Asteroids;
extern std::vector < Bullet > vPociskiGracza;
extern std::vector < Bullet > vPociskiWroga;
extern Gracz Player;
extern HUD hud;

#define LiczbaDzwiekow 11
extern sf::Music sounds[ LiczbaDzwiekow ];

bool czyKolizjaSfer( Vector *v1, float *r1, Vector *v2, float *r2 )
{
    float odleglosc = sqrt( ( v1->X - v2->X ) * ( v1->X - v2->X ) +
                            ( v1->Y - v2->Y ) * ( v1->Y - v2->Y ) +
                            ( v1->Z - v2->Z ) * ( v1->Z - v2->Z ) );

    if ( odleglosc < ( *r1 + *r2 ) )
        return true;
    else
        return false;
}

void Rozprysk_asteroidy_na_mniejsze_kawalki( Vector &xyz, float &R )
{
    int Ilosc_odlamkow = rand() % 30 + 10;
    for ( int i = 0; i < Ilosc_odlamkow; ++i ){
        float x = R * cos( i * 360 / Ilosc_odlamkow * DegToRad );
        float z = R * sin( i * 360 / Ilosc_odlamkow * DegToRad );

        Asteroids.push_back( Asteroida( xyz, Vector( x, 0.0f, z ), 3.0f ) );
        Asteroids[ Asteroids.size() - 1 ].setR( R / Ilosc_odlamkow );
    }

    sounds[7].setPosition( xyz.X, xyz.Y, xyz.Z );
    sounds[7].play();

    hud.rozbitych_asteroid++;
}

void Kolizja_Asteroida_Pocisk()
{
    for ( int i = 0; i < Asteroids.size(); ++i ) {

        for ( int j = 0; j < vPociskiGracza.size(); ++j  ) {
            if ( czyKolizjaSfer( &vPociskiGracza[j].getXYZ(), &vPociskiGracza[j].getR(),
                                 &Asteroids[i].getXYZ(), &Asteroids[i].getR() ) ) {
                vPociskiGracza.erase( vPociskiGracza.begin() + j );
                hud.addPoints( 25 );
                if ( !Asteroids[ i ].bCzyCala( -50 ) ) {
                    if ( ( rand() % 20 ) <= 5 ){
                        vNagrody.push_back( Nagroda( Asteroids[i].getXYZ() ) );
                    }
                    Rozprysk_asteroidy_na_mniejsze_kawalki( Asteroids[i].getXYZ(), Asteroids[i].getR() );
                    Asteroids.erase( Asteroids.begin() + i );
                    hud.addPoints( 150 );
                    hud.addInfo( "Zniszczono asteroide", LightBlue );
                }
            }
        }

        for ( int j = 0; j < vPociskiWroga.size(); ++j  ) {
            if ( czyKolizjaSfer( &vPociskiWroga[j].getXYZ(), &vPociskiWroga[j].getR(),
                                 &Asteroids[i].getXYZ(), &Asteroids[i].getR() ) ) {
                vPociskiWroga.erase( vPociskiWroga.begin() + j );
                if ( !Asteroids[ i ].bCzyCala( -50 ) ) {
                    Rozprysk_asteroidy_na_mniejsze_kawalki( Asteroids[i].getXYZ(), Asteroids[i].getR() );
                    Asteroids.erase( Asteroids.begin() + i );
                }
            }
        }

    }
}

void Asteroida_wyszla_z_pola_widzenia()
{
    for ( int i = 0; i < Asteroids.size(); ++i ) {
        Vector v = Asteroids[i].getXYZ();
        if ( v.Z > ( Player.getZ() + 5.0f ) ||
             v.Z < ( Player.getZ() - 150.0f ) ||
             v.X < - 50.0f ||
             v.X > 50.0f ||
             v.Y < - 50.0f ||
             v.Y > 50.0f  ) {
            Asteroids.erase( Asteroids.begin() + i );
        }
    }
}

void Kolizja_Asteroida_Statek_Wroga()
{
    for ( int j = 0; j < vStatkiWroga.size(); ++j ){
        for ( int i = 0; i < Asteroids.size(); ++i ){
            if ( czyKolizjaSfer( &vStatkiWroga[j].getXYZ(), &vStatkiWroga[j].getR(),
                                 &Asteroids[i].getXYZ(), &Asteroids[i].getR() ) ) {
                Rozprysk_asteroidy_na_mniejsze_kawalki( Asteroids[i].getXYZ(), Asteroids[i].getR() );
                Asteroids.erase( Asteroids.begin() + i );
                if ( vStatkiWroga[j].bStrataZycia( - 10 ) ){
                    vStatkiWroga.erase( vStatkiWroga.begin() + j );
                }
            }
        }
    }
}

void Kolizja_Asteroida_Gracz()
{
    for ( int i = 0; i < Asteroids.size(); ++i ){
        if ( czyKolizjaSfer( &Player.getXYZ(), &Player.getR(),
                             &Asteroids[i].getXYZ(), &Asteroids[i].getR() ) ) {
                Asteroids.erase( Asteroids.begin() + i );
                hud.addInfo( "Uderzenie przez asteroide!", OrangeRed );
                if ( Player.bStrataZycia( - Asteroids[i].getR() * 50 ) ) {
                    Player.StrataZycia();
                    hud.addInfo( "Straciles zycie", Red );
                    hud.Straconych_zyc++;
                }
                sounds[5].play();
            }
    }
}

void Kolizja_Kula_Wrog()
{
    for ( int i = 0; i < vStatkiWroga.size(); ++i ) {

        for ( int j = 0; j < vPociskiGracza.size(); ++j ) {

            if ( czyKolizjaSfer( &vStatkiWroga[i].getXYZ(), &vStatkiWroga[i].getR(),
                                 &vPociskiGracza[j].getXYZ(), &vPociskiGracza[j].getR() ) ) {
                vPociskiGracza.erase( vPociskiGracza.begin() + j );

                if ( vStatkiWroga[i].bStrataZycia( -50 ) ){
                    if ( ( rand() % 10 ) <= 3 ){
                        vNagrody.push_back( Nagroda( vStatkiWroga[i].getXYZ() ) );
                    }
                    sounds[9].setPosition( vStatkiWroga[i].getX(),
                                           vStatkiWroga[i].getY(),
                                           vStatkiWroga[i].getZ() );
                    sounds[9].play();
                    vStatkiWroga.erase( vStatkiWroga.begin() + i );
                    hud.addPoints( 100 );
                    hud.addInfo( "Zniszczyles statek wroga!", Olive );
                    hud.rozbitych_statkow_wroga++;
                }

                --j;
                hud.addPoints( 50 );
            }
                continue;
        }
    }
}

void Kolizja_Pocisk_Wyszedl_Poza_Pole_Widzenia()
{
    for ( int i = 0; i < vPociskiGracza.size(); ++i ) {
        Vector v = vPociskiGracza[i].getXYZ();
        if ( v.Z > ( Player.getZ() + 15.0f ) ||
             v.Z < ( Player.getZ() - 110.0f ) ||
             v.X < - 50.0f ||
             v.X > 50.0f ||
             v.Y < - 50.0f ||
             v.Y > 50.0f  ) {
            vPociskiGracza.erase( vPociskiGracza.begin() + i );
        }
    }

    for ( int i = 0; i < vPociskiWroga.size(); ++i ) {
        Vector v = vPociskiWroga[i].getXYZ();
        if ( v.Z > ( Player.getZ() + 15.0f ) ||
             v.Z < ( Player.getZ() - 110.0f ) ||
             v.X < - 50.0f ||
             v.X > 50.0f ||
             v.Y < - 50.0f ||
             v.Y > 50.0f  ) {
            vPociskiWroga.erase( vPociskiWroga.begin() + i );
        }
    }

}

void Wrog_Wyszedl_z_POLA_widzenia()
{
    for ( int i = 0; i < vStatkiWroga.size(); ++i ) {
        Vector v = vStatkiWroga[i].getXYZ();
        if ( v.Z > ( Player.getZ() + 5.0f ) ||
             v.Z < ( Player.getZ() - 150.0f ) ||
             v.X < - 50.0f ||
             v.X > 50.0f ||
             v.Y < - 50.0f ||
             v.Y > 50.0f  ) {
            vStatkiWroga.erase( vStatkiWroga.begin() + i );
        }
    }
}

void Kolizja_Kula_gracz()
{
    for ( int i = 0; i < vPociskiWroga.size(); ++i ) {
        if ( czyKolizjaSfer( &Player.getXYZ(), &Player.getR(),
                             &vPociskiWroga[i].getXYZ(), &vPociskiWroga[i].getR() ) ){
            vPociskiWroga.erase( vPociskiWroga.begin() + i );
            hud.addInfo( "Zostales trafiony!", OrangeRed );
            sounds[10].play();
            if ( Player.bStrataZycia( -25 ) ) {
                Player.StrataZycia();
                hud.addInfo( "Straciles zycie", Red );
                hud.Straconych_zyc++;
            }
        }
    }
}

void Kolizja_Wrog_gracz()
{
    for ( int i = 0; i < vStatkiWroga.size(); ++i ){
        if ( czyKolizjaSfer( &Player.getXYZ(), &Player.getR(),
                             &vStatkiWroga[i].getXYZ(), &vStatkiWroga[i].getR() ) ) {
                vStatkiWroga.erase( vStatkiWroga.begin() + i );
                hud.addInfo( "Kolizja z wrogiem!", OrangeRed );
                sounds[6].play();
                if ( Player.bStrataZycia( -30 ) ) {
                    Player.StrataZycia();
                    hud.addInfo( "Straciles zycie", Red );
                    hud.Straconych_zyc++;
                }
            }
    }
}

void Kolizja_Gracz_Nagroda()
{
    for ( int i = 0; i < vNagrody.size(); ++i ){
        if ( czyKolizjaSfer( &Player.getXYZ(), &Player.getR(),
                             &vNagrody[i].xyz, &vNagrody[i].r ) ) {
            if ( vNagrody[i].life ){
                Player.DodajZycie();
                hud.addInfo( "Nagroda: 1 Zycie", Green );
            }
            else if ( vNagrody[i].repair ){
                Player.addSprawnosc( 100 );
                hud.addInfo( "Nagroda: Naprawa statku", Green );
            }
            else if ( vNagrody[i].change_weapon ){
                Player.NextWeapon();
                hud.addInfo( "Nagroda: Ulepszenie broni", Green );
            }

             vNagrody.erase( vNagrody.begin() + i );
             sounds[4].play();
             hud.zdobytych_nagrod++;
        }
    }
}

void Kolizja_Kula_nagroda()
{
    for ( int i = 0; i < vNagrody.size(); ++i ){
        for ( int j = 0; j < vPociskiGracza.size(); ++j ){
            if ( czyKolizjaSfer( &vNagrody[i].xyz, &vNagrody[i].r,
                             &vPociskiGracza[j].getXYZ(), &vPociskiGracza[j].getR() ) ){
                                vNagrody.erase( vNagrody.begin() + i );
                                hud.addInfo( "Trafiles w nagrode...", Purple );
                                hud.rozwalonych_nagrod++;
                             }
        }

        for ( int j = 0; j < vPociskiWroga.size(); ++j ){
            if ( czyKolizjaSfer( &vNagrody[i].xyz, &vNagrody[i].r,
                             &vPociskiWroga[j].getXYZ(), &vPociskiWroga[j].getR() ) ){
                                vNagrody.erase( vNagrody.begin() + i );
                                hud.addInfo( "Pocisk wroga trafil nagrode", Purple );
                             }
        }

    }
}

void Nagroda_wyszla_z_pola_widzenia()
{
    for ( int i = 0; i < vNagrody.size(); ++i ) {
        Vector v = vNagrody[i].xyz;
        if ( v.Z > ( Player.getZ() + 5.0f ) ||
             v.Z < ( Player.getZ() - 120.0f ) ||
             v.X < - 50.0f ||
             v.X > 50.0f ||
             v.Y < - 50.0f ||
             v.Y > 50.0f  ) {
            vNagrody.erase( vNagrody.begin() + i );
        }
    }
}

void Kolizja()
{
    sf::Listener::setPosition( Player.getX(), Player.getY(), Player.getZ() );

    Kolizja_Kula_Wrog();
    Kolizja_Kula_gracz();
    Kolizja_Wrog_gracz();
    Kolizja_Gracz_Nagroda();
    Kolizja_Kula_nagroda();

    Kolizja_Pocisk_Wyszedl_Poza_Pole_Widzenia();
    Wrog_Wyszedl_z_POLA_widzenia();
    Nagroda_wyszla_z_pola_widzenia();

    Asteroida_wyszla_z_pola_widzenia();
    Kolizja_Asteroida_Pocisk();
    //Kolizja_Asteroida_Statek_Wroga();
    Kolizja_Asteroida_Gracz();
}
