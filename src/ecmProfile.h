#ifndef ECMPROFILE_H
#define ECMPROFILE_H

#include "imgui.h"
#include "ecmMemory.h"
#include "ecmStatus.h"

#include <SDL.h>
#include <WinUser.h>
#include <fstream>
using namespace std;

enum actionType
{
    atCooldown = 0,
    atHealth = 1,
    atMana = 2,
    atBuff = 3,
    atNone
};

struct ecmAction
{
    actionType type;
    WORD key;
    SDL_Scancode code;
    uint64_t cooldown;
    uint64_t casttime;
    uint64_t last;
    float threshold;

    const char* toString()
    {
        return SDL_GetKeyName(this->code);
    }

    bool doAction(ecmStatus *pStatus)
    {
        auto now = (SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency()) * 1000;
        if (now - this->last <= cooldown)
            return false;

        switch (this->type)
        {
        case atHealth:
            if (pStatus->health > this->threshold)
                return false;
            
            break;

        case atMana:
            if (pStatus->mana > this->threshold)
                return false;
            
            break;

        default:
            break;
        }

        last = now;
        return keypress(key);
    }
};

struct ecmProfile
{
    vector<ecmAction> thresholds;
    vector<ecmAction> actions;
};

bool loadProfile(const char* pFilename, ecmProfile* pProfile);
bool saveProfile(const char* pFilename, ecmProfile* pProfile);
void drawProfile(ecmProfile* pProfile);

#endif