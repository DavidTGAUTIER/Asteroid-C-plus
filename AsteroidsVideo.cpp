#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "oldConsoleGameEngine.h"

class OneLoneCoder_Asteroids : public olcConsoleGameEngine
{
public:
    OneLoneCoder_Asteroids()
    {
        m_sAppName = L"Asteroids";
    }


private:

protected:
    //Called by olcConsoleGameEngine
    virtual bool OnUserCreate()
    {
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
    
    return 0;
}