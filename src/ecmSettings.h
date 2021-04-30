#ifndef ECMSETTINGS_H
#define ECMSETTINGS_H

#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "imgui.h"

#define BUFFER_SIZE 64

struct ecmSettings
{
    bool activeCombat;
    bool lootMobs;
    bool skinMobs;
    bool harvestMinerals;
    bool harvestHerbs;

    int lootRadius;
    int foodQty;
    int drinkQty;

    char foodName[BUFFER_SIZE];
    char drinkName[BUFFER_SIZE];
    char mailName[BUFFER_SIZE];
    char groundMount[BUFFER_SIZE];
    char flyMount[BUFFER_SIZE];

    unordered_map<string, int64_t> memAddresses;
};

bool loadSettings(char* pFile, ecmSettings* pSettings);
bool saveSettings(char* pFile, ecmSettings* pSettings);
void drawSettings(ecmSettings* pSettings);

#endif