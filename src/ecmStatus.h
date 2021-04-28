#ifndef ECMSTATUS_H
#define ECMSTATUS_H

#define BUFFER_SIZE 64

#include <chrono>
#include <string>
#include <Windows.h>

#include "imgui.h"
#include "ecmWaypoint.h"

struct ecmStatus
{
    char charName[BUFFER_SIZE];
    int health;
    int maxHealth;
    int mana;
    int maxMana;

    bool alive;

    int exp;
    int deaths;
    int loots;
    int kills;

    waypoint pos;
    waypoint next;

    struct
    {
        bool targetting;
        char name[BUFFER_SIZE];
        int health;
        int mana;
    } target;
};

void drawStatus(ecmStatus *pStatus)
{
    ImGui::Text("Name: %s", pStatus->charName);
    ImGui::Text("Health: %d", pStatus->health);
    ImGui::Text("Mana: %d", pStatus->mana);

    ImGui::Text("Experience: %d\t%d/hr", pStatus->exp, pStatus->exp);
    ImGui::Text("Deaths: %d\t%d/hr", pStatus->deaths, pStatus->deaths);
    ImGui::Text("Loots: %d\t%d/hr", pStatus->loots, pStatus->loots);
    ImGui::Text("Kills: %d\t%d/hr", pStatus->kills, pStatus->kills);

    if (pStatus->target.targetting)
    {
        ImGui::Text("Name: %s", pStatus->target.name);
        ImGui::Text("Health: %d", pStatus->target.health);
        ImGui::Text("Mana: %d", pStatus->target.mana);
    }
    else
    {
        ImGui::Text("No Target");
    }
}

#endif