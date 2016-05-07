#include <SFML/Graphics.hpp>
#include "../include/Gracz.h"
#include "../include/HUD.h"
#include "../include/StatekWroga.h"
#include "../include/Bullet.h"
#include "../include/Asteroida.h"
#include "../include/Nagroda.h"
#include "../include/MenadzerNPC.h"

extern std::string nickname;
extern std::vector < Nagroda > vNagrody;
extern std::vector < StatekWroga > vStatkiWroga;
extern std::vector < Asteroida > Asteroids;
extern std::vector < Bullet > vPociskiGracza;
extern std::vector < Bullet > vPociskiWroga;
extern Gracz Player;
extern HUD hud;
extern sf::RenderWindow app;
extern MenadzerNPC MenagerNPC;

void ResetGame()
{
    vNagrody.clear();
    vStatkiWroga.clear();
    Asteroids.clear();
    vPociskiGracza.clear();
    vPociskiWroga.clear();
    Player = Gracz();
    hud = HUD( &Player.getXYZ(), &Player.getZyc(), &Player.getSprawnosc(),
         &Player.getRodzajBroni(), &Player.timeBlood, &app, &nickname );
    MenagerNPC = MenadzerNPC( &Player.getZ() );
}
