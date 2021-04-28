#ifndef ECMPROFILE_H
#define ECMPROFILE_H

#include "imgui.h"
#include "ecmMemory.h"

#include <SDL.h>
#include <WinUser.h>
#include <fstream>
using namespace std;

enum actionType
{
    atCooldown = 0,
    atThreshold = 1
};

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

bool loadProfile(const char* pFilename, ecmProfile *pProfile)
{
    fstream inFile;
    inFile.open(pFilename, ios_base::in);
    
    if (!inFile.is_open())
        return false;

    while (!inFile.eof())
    {
        ecmAction action;
        string buffer;
        int x;

        inFile >> buffer
            >> action.cooldown
            >> action.casttime
            >> x;

        action.code = SDL_GetKeyFromName(buffer.c_str());

        switch ((actionType)x)
        {
        case atCooldown:
            pProfile->actions.push_back(action);
            break;
        case atThreshold:
            pProfile->thresholds.push_back(action);
            break;
        }
    }

    return true;
}

bool saveProfile(const char* pFilename, ecmProfile *pProfile)
{
    fstream outFile;
    outFile.open(pFilename, ios_base::out);

    if (!outFile.is_open())
        return false;

    for (unsigned int i = 0; i < pProfile->actions.size(); ++i)
    {
        outFile << pProfile->actions[i].toString()
            << ' ' << pProfile->actions[i].cooldown
            << ' ' << pProfile->actions[i].casttime
            << ' ' << atCooldown
            << endl;
    }
    for (unsigned int i = 0; i < pProfile->thresholds.size(); ++i)
    {
        outFile << pProfile->thresholds[i].toString()
            << ' ' << pProfile->thresholds[i].cooldown
            << ' ' << pProfile->actions[i].casttime
            << ' ' << atThreshold
            << endl;
    }

    return true;
}

void drawProfile(ecmProfile* pProfile)
{
    if (ImGui::Button("Load Profile"))
    {
        // File Dialog
    }

    if (pProfile != nullptr)
    {
        for (unsigned int i = 0; i < pProfile->actions.size(); ++i)
        {
            ImGui::Text(pProfile->actions.at(i).toString());
            ImGui::SameLine();
            char buffer[10] = {};
            sprintf_s(buffer, "X##action%d", i);
            if (ImGui::Button(buffer))
                pProfile->actions.erase(pProfile->actions.begin() + i);
        }
    }
    else
    {
        ImGui::Text("Load a profile");
    }

}

#endif