#include "../include/Gracz.h"
#include <SFML/Audio.hpp>

#define LiczbaDzwiekow 10
extern sf::Music sounds[LiczbaDzwiekow];

Gracz::Gracz() : StatekKosmiczny( 2.0f, 0.5f,
                                 Vector ( 0.0f, 0.0f, 0.0f),
                                 Vector( 0.0f, 0.0f, -1.0f ),
                                 PojedynczaKula, 100 ),
                                 iloscZyc( 3 ), timeBlood( 0.0f )
{
}

Gracz::~Gracz()
{
}

void Gracz::Draw()
{
}

void Gracz::Move( float &LoopTime )
{
    xyz = xyz + vKierumek * LoopTime * szybkosc;

    if ( timeBlood > 0 )
        timeBlood -= LoopTime;

}

void Gracz::StrataZycia()
{
    --iloscZyc;
    sprawnosc = 100.0f;
    RodzajOgnia = PojedynczaKula;
    sounds[8].play();
}
