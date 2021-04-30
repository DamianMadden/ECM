#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "imgui.h"
#include "ecmSettings.h"

enum eSettings
{
    activeCombat,
    lootMobs,
    skinMobs,
    harvestMinerals,
    harvestHerbs,

    lootRadius,
    foodQty,
    drinkQty,

    foodName,
    drinkName,
    mailName,
    groundMount,
    flyMount,
    setCount
};

const string setStrings[] =
{
    "ActiveCombat",
    "LootMobs",
    "SkinMobs",
    "HarvestMinerals",
    "HarvestHerbs",

    "LootRadius",
    "FoodQty",
    "DrinkQty",

    "FoodName",
    "DrinkName",
    "MailName",
    "GroundMount",
    "FlyMount"
};

bool loadSettings(char *pFile, ecmSettings *pSettings)
{
    fstream inFile;
    inFile.open(pFile);

    if (!inFile.is_open())
        return false;

    while (!inFile.eof())
    {
        string key;
        string val;

        inFile >> key >> val;

        int i = 0;
        for (; i < setCount; ++i)
        {
            if (setStrings[i] == key)
                break;
        }

        if (i == setCount)
            return false;

        switch ((eSettings)i)
        {
            case foodName:
                val.copy(pSettings->foodName, BUFFER_SIZE);
                break;
            case drinkName:
                val.copy(pSettings->drinkName, BUFFER_SIZE);
                break;
            case mailName:
                val.copy(pSettings->mailName, BUFFER_SIZE);
                break;
            case groundMount:
                val.copy(pSettings->groundMount, BUFFER_SIZE);
                break;
            case flyMount:
                val.copy(pSettings->flyMount, BUFFER_SIZE);
                break;

            case activeCombat:
                pSettings->activeCombat = val == "true" ? true : false;
                break;
            case lootMobs:
                pSettings->lootMobs = val == "true" ? true : false;
                break;
            case skinMobs:
                pSettings->skinMobs = val == "true" ? true : false;
                break;
            case harvestMinerals:
                pSettings->harvestMinerals = val == "true" ? true : false;
                break;
            case harvestHerbs:
                pSettings->harvestHerbs = val == "true" ? true : false;
                break;

            case lootRadius:
                pSettings->lootRadius = stoi(val);
                break;
            case foodQty:
                pSettings->foodQty = stoi(val);
                break;
            case drinkQty:
                pSettings->drinkQty = stoi(val);
                break;
        }
    }

    inFile.close();

    return true;
}

bool saveSettings(char* pFile, ecmSettings* pSettings)
{
    fstream outFile;
    outFile.open(pFile);

    if (!outFile.is_open())
        return false;

    outFile << "FoodName " << pSettings->foodName << endl;
    outFile << "DrinkName " << pSettings->drinkName << endl;
    outFile << "MailName " << pSettings->mailName << endl;
    outFile << "GroundMount " << pSettings->groundMount << endl;
    outFile << "FlyMount " << pSettings->flyMount << endl;

    outFile << "ActiveCombat " << (pSettings->activeCombat ? "true" : "false") << endl;
    outFile << "LootMobs " << (pSettings->lootMobs ? "true" : "false") << endl;
    outFile << "SkinMobs " << (pSettings->skinMobs ? "true" : "false") << endl;
    outFile << "HarvestMinerals " << (pSettings->harvestMinerals ? "true" : "false") << endl;
    outFile << "HarvestHerbs " << (pSettings->harvestHerbs ? "true" : "false") << endl;

    outFile << "LootRadius " << pSettings->lootRadius << endl;
    outFile << "FoodQty " << pSettings->foodQty << endl;
    outFile << "DrinkQty " << pSettings->drinkQty << endl;

    outFile.close();

    return true;
}

void drawSettings(ecmSettings *pSettings)
{
    if (ImGui::BeginChild("Settings"))
    {
        ImGui::Checkbox("Aggressive", &pSettings->activeCombat);
        ImGui::Checkbox("Loot Mobs", &pSettings->lootMobs);
        ImGui::Checkbox("Skin Mobs", &pSettings->skinMobs);
        ImGui::Checkbox("Harvest Minerals", &pSettings->harvestMinerals);
        ImGui::Checkbox("Harvest Herbs", &pSettings->harvestHerbs);

        ImGui::SliderInt("Loot Radius", &pSettings->lootRadius, 0, 100);
        ImGui::SliderInt("Food Quantity", &pSettings->foodQty, 0, 300);
        ImGui::SliderInt("Drink Quantity", &pSettings->drinkQty, 0, 300);

        ImGui::InputText("Food Name", &pSettings->foodName[0], BUFFER_SIZE);
        ImGui::InputText("Drink Name", &pSettings->drinkName[0], BUFFER_SIZE);
        ImGui::InputText("Mail Recipient", &pSettings->mailName[0], BUFFER_SIZE);
        ImGui::InputText("Ground Mount", &pSettings->groundMount[0], BUFFER_SIZE);
        ImGui::InputText("Flying Mount", &pSettings->flyMount[0], BUFFER_SIZE);
    }
    ImGui::EndChild();
}
