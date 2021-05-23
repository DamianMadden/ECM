#ifndef ECMSETTINGS_H
#define ECMSETTINGS_H

#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

#include <SDL.h>
#include <Windows.h>

#include "imgui.h"

#define BUFFER_SIZE 64

enum modifierKeys
{
    ecmMOD_Mask = 511,
    ecmMOD_Shift = 512,
    ecmMOD_Ctrl = 1024,
    ecmMOD_Alt = 2048
};

enum keyBind
{
    kbTarget,
    kbLastTarget,
    kbLoot,
    kbUntarget,
    kbForward,
    kbLeft,
    kbRight,
    kbCount
};

struct ecmSettings
{
    bool activeCombat;
    bool lootMobs;
    bool skinMobs;

    float pointRadius;

    int foodQty;
    int drinkQty;

    char foodName[BUFFER_SIZE];
    char drinkName[BUFFER_SIZE];

    char groundMount[BUFFER_SIZE];
    char flyMount[BUFFER_SIZE];

    unordered_map<string, int64_t> memAddresses;
};

WORD SDLtoVK(SDL_Scancode key);

WORD GetKey(keyBind key);
void SetKey(keyBind bind, WORD key);

bool loadSettings(char* pFile, ecmSettings* pSettings);
bool saveSettings(char* pFile, ecmSettings* pSettings);
void drawSettings(ecmSettings* pSettings);

#endif