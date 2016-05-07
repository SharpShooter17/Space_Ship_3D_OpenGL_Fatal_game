#ifndef GRACZ_H
#define GRACZ_H

#include "StatekKosmiczny.h"

class Gracz : public StatekKosmiczny
{
    public:

        Gracz();
        virtual ~Gracz();
        virtual void Draw();
        virtual void Move( float &LoopTime );
        void StrataZycia();
        inline void DodajZycie() { ++iloscZyc; }
        inline short getLife() { return iloscZyc; }

        inline bool bStrataZycia( short n )
        {
            timeBlood = 1.0f;
            return StatekKosmiczny::bStrataZycia( n );
        }

        ///Dla Hudu
        inline short &getSprawnosc() { return sprawnosc; }
        inline short &getZyc() { return iloscZyc; }
        inline FireMode &getRodzajBroni() { return RodzajOgnia; }
        inline void NextWeapon()
        {
            if ( RodzajOgnia != SeriaW3Kierunkach ) {
                RodzajOgnia = ( FireMode ) ( ( int ) RodzajOgnia + 1 );
            }
        }

        float timeBlood;

    protected:

    private:

        short iloscZyc;

};

#endif // GRACZ_H
