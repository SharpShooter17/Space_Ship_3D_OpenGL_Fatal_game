#ifndef STATEKWROGA_H
#define STATEKWROGA_H

#include "StatekKosmiczny.h"

enum FormacjaWroga{ Random,
                    V,
                    Odwrocone_V,
                    DwieKolumny_I_I,
                    Kolumn5x5x5x4,
                    Okrag2,
                    PolOkrag,
                    Okrag,
                    Sfera,
                    maximum,
                    };

class StatekWroga : public StatekKosmiczny
{
    public:

        StatekWroga( Vector polozenie, Vector dir = Vector( 0.0f, 0.0f, 1.0f ),
                    FireMode mode = PojedynczaKula  );
        ~StatekWroga();

        virtual void Draw();
        virtual void Move( float &LoopTime, FormacjaWroga &mode );
        virtual void Fire( float &LoopTime, Vector &pozycja_gracza );

    protected:

    private:

        float CoIleStrzal;
        float timeToShoot;
};

#endif // STATEKWROGA_H
