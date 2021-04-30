#ifndef ECMPROFILE_H
#define ECMPROFILE_H

#include "imgui.h"
#include "ecmMemory.h"

#include <SDL.h>
#include <WinUser.h>
#include <fstream>
using namespace std;

struct ecmAction
{
    WORD key;
    SDL_Keycode code;
    uint64_t cooldown;
    uint64_t casttime;
    uint64_t last;

    const char* toString()
    {
        return SDL_GetKeyName(this->code);
    }

    bool doAction(uint64_t now)
    {
        if (now - this->last <= cooldown)
            return false;

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