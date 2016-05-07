#include <SFML/OpenGL.hpp>

#include "../include/Gracz.h"
#include "../include/StatekWroga.h"
#include "../include/MenadzerNPC.h"
#include "../include/HUD.h"

extern sf::RenderWindow app;

std::vector < Bullet > vPociskiWroga;
std::vector < Bullet > vPociskiGracza;
std::string nickname = "Podaj nick";

Gracz Player;
MenadzerNPC MenagerNPC( &Player.getZ() );
HUD hud( &Player.getXYZ(), &Player.getZyc(), &Player.getSprawnosc(),
         &Player.getRodzajBroni(), &Player.timeBlood, &app, &nickname );

extern float LoopTime;
float TimeToFire = 0.0f;

extern void Kolizja();

void Logika( float &LoopTime )
{
    Kolizja();

    Player.Move( LoopTime );

    for ( int i = 0; i < vPociskiWroga.size(); ++i){
        vPociskiWroga[i].Move( LoopTime );
    }
    for ( int i = 0; i < vPociskiGracza.size(); ++i){
        vPociskiGracza[i].Move( LoopTime );
    }

    MenagerNPC.ControlEnemyShips( LoopTime, Player.getXYZ() );

    MenagerNPC.czyNowaKonstrukcja();
}
