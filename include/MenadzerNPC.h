#ifndef MENADZERNPC_H
#define MENADZERNPC_H

#include "StatekWroga.h"

class MenadzerNPC
{
    public:

        MenadzerNPC( float *z );
        virtual ~MenadzerNPC();

        void NowaKonstrukcja();
        void czyNowaKonstrukcja();

        void DrawVEnemyShips();
        void ControlEnemyShips( float &LoopTime, Vector &xyz );

    protected:
    private:

        float *gdzieJestGraczZ;
        FormacjaWroga mode;

        void MakeAsteroids( int n );
};

#endif // MENADZERNPC_H
