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
}

private:

protected:

int maint()
{
    return 0;
}