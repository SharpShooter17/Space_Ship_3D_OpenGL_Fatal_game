#ifndef NAGRODA_H
#define NAGRODA_H

#include <Vector.h>

enum Award{
            Zycie = 0,
            Naprawa = 1,
            Zmiana_broni = 2
          };

class Nagroda
{
    public:
        Nagroda( Vector &XYZ );
        ~Nagroda();

        void Draw();

        bool life;
        bool repair;
        bool change_weapon;

        Vector xyz;
        float r;

    protected:

    private:

        float rot;
};

#endif // NAGRODA_H
