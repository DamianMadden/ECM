#include "imgui.h"
#include "ecmMemory.h"
#include "ecmProfile.h"

#include <SDL.h>
#include <WinUser.h>
#include <fstream>
using namespace std;

WORD SDLKtoVK(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_RETURN:
        return VK_RETURN;
    case SDLK_ESCAPE:
        return VK_ESCAPE;
    case SDLK_BACKSPACE:
        return VK_BACK;
    case SDLK_TAB:
        return VK_TAB;
    case SDLK_SPACE:
        return VK_SPACE;
    case SDLK_0:
        return '0';
    case SDLK_1:
        return '1';
    case SDLK_2:
        return '2';
    case SDLK_3:
        return '3';
    case SDLK_4:
        return '4';
    case SDLK_5:
        return '5';
    case SDLK_6:
        return '6';
    case SDLK_7:
        return '7';
    case SDLK_8:
        return '8';
    case SDLK_9:
        return '9';
    case SDLK_F1:
        return VK_F1;
    }

    return 0;
}

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
            >> action.threshold
            >> action.cooldown
            >> action.casttime
            >> x;

        if (buffer.empty())
            continue;

        action.code = SDL_GetKeyFromName(buffer.c_str());
        action.key = SDLKtoVK(action.code);

        switch ((actionType)x)
        {
        case atCooldown:
            pProfile->actions.push_back(action);
            break;
        default:
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
            << ' ' << pProfile->actions[i].threshold
            << ' ' << pProfile->actions[i].cooldown
            << ' ' << pProfile->actions[i].casttime
            << ' ' << pProfile->actions[i].type
            << endl;
    }
    for (unsigned int i = 0; i < pProfile->thresholds.size(); ++i)
    {
        outFile << pProfile->thresholds[i].toString()
            << ' ' << pProfile->thresholds[i].threshold
            << ' ' << pProfile->thresholds[i].cooldown
            << ' ' << pProfile->thresholds[i].casttime
            << ' ' << pProfile->thresholds[i].type
            << endl;
    }

    return true;
}

void drawProfile(ecmProfile* pProfile)
{
    if (ImGui::Button("Save Profile"))
    {
        if (!saveProfile("profile", pProfile))
        {
            // Err
        }
    }
    if (ImGui::Button("Load Profile"))
    {
        if (!loadProfile("profile", pProfile))
        {
            // Err
        }
    }

    static ecmAction action = {};
    static char keyBuffer[20] = {};
    static int cooldown = 0, casttime;
    ImGui::InputText("Key", keyBuffer, 20);
    ImGui::InputInt("Cooldown MS", &cooldown);
    ImGui::InputInt("Casttime MS", &casttime);
    ImGui::InputFloat("Threshold", &action.threshold);

    static actionType type = atNone;
    
    if (ImGui::Button("Add Action"))
        type = atCooldown;

    if (ImGui::Button("Add Health Threshold"))
        type = atHealth;

    if (ImGui::Button("Add Mana Threshold"))
        type = atMana;

    if (type != atNone)
    {
        action.code = SDL_GetKeyFromName(keyBuffer);
        action.key = SDLKtoVK(action.code);

        action.cooldown = cooldown;
        action.casttime = casttime;
        if (type == atCooldown)
            pProfile->actions.push_back(action);
        else
            pProfile->thresholds.push_back(action);

        type = atNone;
    }

    for (unsigned int i = 0; i < pProfile->actions.size(); ++i)
    {
        ImGui::Text(pProfile->actions.at(i).toString());
        ImGui::Text("Cast: %d", pProfile->actions.at(i).casttime);
        ImGui::Text("Cooldown: %d", pProfile->actions.at(i).cooldown);
        ImGui::Text("Threshold: %f", pProfile->actions.at(i).threshold);

        ImGui::SameLine();
        char buffer[20] = {};
        sprintf_s(buffer, "X##act%d", i);
        if (ImGui::Button(buffer))
            pProfile->actions.erase(pProfile->actions.begin() + i);
    }

}