#ifndef ECMSTATUS_H
#define ECMSTATUS_H

#include "imgui.h"
#include "ecmWaypoint.h"

#define BUFFER_SIZE 64

struct ecmStatus
{
    char charName[BUFFER_SIZE];
    float rotation;

#ifdef DEBUG
    float angle;
#endif

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

    bool running;

    struct
    {
        uint32_t targetting;
        char name[BUFFER_SIZE];
        int health;
        int maxHealth;
        int mana;
        int maxMana;
    } target;
};

void drawStatus(ecmStatus* pStatus, bool attached);

#endif