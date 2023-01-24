#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_Asteroids : public olcConsoleGameEngine
{
public:
    OneLoneCoder_Asteroids()
    {
        m_sAppName = L"Asteroids";
    }


private:
    struct sSpaceObject
    {
        float x;
        float y;
        float dx;
        float dy;
        int nSize;
    };

    vector<sSpaceObject> vecAsteroids;

protected:
    //Called by olcConsoleGameEngine
    virtual bool OnUserCreate()
    {
        vecAsteroids.push_back({ 20.0f, 20.0f, 8.0f, -6.0f, (int)16})

        // Update and draw asteroids
        for(auto &a: vecAsteroids)
        return true;
    }

    //Called by olcConsoleGameEngine
    virtual bool OnUserUpdate(float fElapsedTime)
    {
        // Clear Screen
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);
        return true;
    }
}

int maint()
{
    // Use olcConsoleGameEngine derived app
    OneLoneCoder_Asteroids game;
    game.ConstructConsole(160, 100, 8, 8);
    game.Start();
    return 0;
}