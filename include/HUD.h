#ifndef HUD_H
#define HUD_H

#include "StatekKosmiczny.h"
#include <deque>
#include <SFML/Graphics.hpp>
#include <Vector.h>
#include "OGLcolors.h"
#include <cstdio>

struct Information
{
    string str;
    const float *color;
};

class HUD
{
    public:
        HUD( Vector *XYZ, short *life,
             short *stan, FireMode *mod,
             float *timeBlood, sf::RenderWindow *window,
             std::string *nick );
        ~HUD();

        inline float getCrossX() { return x_cross + xyz->X; }
        inline float getCrossY() { return y_cross + xyz->Y; }
        inline void ResetCross() { x_cross = 0.0f; y_cross = 0.0f; return; }
        void moveCross( float x, float y );

        void DrawHUD( float &LoopTime );

        inline void addPoints( float n )
        {
            punktow += n;
            char points[32];
            sprintf( points, "Dodano punktow: %i", (int) (n) );
            addInfo( points, Yellow );
        }

        void changeMouseSensitivity( short n );
        void addInfo( char *str, const float *color );

        float sensitivityMouse;

        void DrawString( float &LoopTime );

        ///staty
        int Straconych_zyc;
        int rozbitych_statkow_wroga;
        int zdobytych_nagrod;
        int rozwalonych_nagrod;
        int rozbitych_asteroid;

        void sendScore();

    protected:
    private:

        sf::RenderWindow *app;

        std::deque < Information > Info;
        float timer;
        short mouseSensitivity;
        float x_cross, y_cross;
        Vector *xyz;
        short *zyc;
        short *sprawnosc;
        FireMode *RodzajBroni;
        float *BloodTimer;
        std::string *name;
        ///staty
        int punktow;

        void DrawCross();
        void DrawSprawnosc();
        void DrawWeapon();
        void DrawLife();
        void DrawPoints();
        void DrawBlood();

};

#endif // HUD_H
