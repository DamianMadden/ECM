#define _HAS_STD_BYTE 0

#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

#include <Windows.h>

#include "imgui.h"
#include "ecmSettings.h"

enum eSettings
{
    activeCombat,
    lootMobs,
    skinMobs,
    pointRadius,
    foodQty,
    drinkQty,
    foodName,
    drinkName,
    groundMount,
    flyMount,
    setCount
};

const string setStrings[] =
{
    "ActiveCombat",
    "LootMobs",
    "SkinMobs",
    "PointRadius"
    "FoodQty",
    "DrinkQty",
    "FoodName",
    "DrinkName",
    "GroundMount",
    "FlyMount"
};

static const char* modText[] =
{
  "Shift",
  "Ctrl",
  "Alt"
};

static const modifierKeys modList[] =
{
  ecmMOD_Shift,
  ecmMOD_Ctrl,
  ecmMOD_Alt
};

static const char* bindNames[] =
{
    "Target",
    "Last Target",
    "Loot",
    "Drop Target",
    "Forward",
    "Left",
    "Right"
};

static WORD keyBinds[kbCount] = {
    VK_TAB,
    VK_F11,
    VK_F12,
    VK_ESCAPE,
    VK_UP,
    VK_LEFT,
    VK_RIGHT
};

WORD SDLtoVK(SDL_Scancode key)
{
    switch (key)
    {
    case SDL_SCANCODE_RETURN:
        return VK_RETURN;
    case SDL_SCANCODE_ESCAPE:
        return VK_ESCAPE;
    case SDL_SCANCODE_BACKSPACE:
        return VK_BACK;
    case SDL_SCANCODE_TAB:
        return VK_TAB;
    case SDL_SCANCODE_SPACE:
        return VK_SPACE;
    case SDL_SCANCODE_0:
        return '0';
    case SDL_SCANCODE_1:
        return '1';
    case SDL_SCANCODE_2:
        return '2';
    case SDL_SCANCODE_3:
        return '3';
    case SDL_SCANCODE_4:
        return '4';
    case SDL_SCANCODE_5:
        return '5';
    case SDL_SCANCODE_6:
        return '6';
    case SDL_SCANCODE_7:
        return '7';
    case SDL_SCANCODE_8:
        return '8';
    case SDL_SCANCODE_9:
        return '9';
    case SDL_SCANCODE_A:
        return 'A';
    case SDL_SCANCODE_B:
        return 'B';
    case SDL_SCANCODE_C:
        return 'C';
    case SDL_SCANCODE_D:
        return 'D';
    case SDL_SCANCODE_E:
        return 'E';
    case SDL_SCANCODE_F:
        return 'F';
    case SDL_SCANCODE_G:
        return 'G';
    case SDL_SCANCODE_H:
        return 'H';
    case SDL_SCANCODE_I:
        return 'I';
    case SDL_SCANCODE_J:
        return 'J';
    case SDL_SCANCODE_K:
        return 'K';
    case SDL_SCANCODE_L:
        return 'L';
    case SDL_SCANCODE_M:
        return 'M';
    case SDL_SCANCODE_N:
        return 'N';
    case SDL_SCANCODE_O:
        return 'O';
    case SDL_SCANCODE_P:
        return 'P';
    case SDL_SCANCODE_Q:
        return 'Q';
    case SDL_SCANCODE_R:
        return 'R';
    case SDL_SCANCODE_S:
        return 'S';
    case SDL_SCANCODE_T:
        return 'T';
    case SDL_SCANCODE_U:
        return 'U';
    case SDL_SCANCODE_V:
        return 'V';
    case SDL_SCANCODE_W:
        return 'W';
    case SDL_SCANCODE_X:
        return 'X';
    case SDL_SCANCODE_Y:
        return 'Y';
    case SDL_SCANCODE_Z:
        return 'Z';
    case SDL_SCANCODE_F1:
        return VK_F1;
    case SDL_SCANCODE_F2:
        return VK_F2;
    case SDL_SCANCODE_F3:
        return VK_F3;
    case SDL_SCANCODE_F4:
        return VK_F4;
    case SDL_SCANCODE_F5:
        return VK_F5;
    case SDL_SCANCODE_F6:
        return VK_F6;
    case SDL_SCANCODE_F7:
        return VK_F7;
    case SDL_SCANCODE_F8:
        return VK_F8;
    case SDL_SCANCODE_F9:
        return VK_F9;
    case SDL_SCANCODE_F10:
        return VK_F10;
    case SDL_SCANCODE_F11:
        return VK_F11;
    case SDL_SCANCODE_F12:
        return VK_F12;
    }

    return 0;
}

WORD GetKey(keyBind key)
{
    return keyBinds[key];
}

void SetKey(keyBind bind, WORD key)
{
    keyBinds[bind] = key;
}

const char* GetKeyName(WORD key)
{
    switch (key)
    {
    case VK_RETURN:
        return "Return";
    case VK_ESCAPE:
        return "Escape";
    case VK_BACK:
        return "Backspace";
    case VK_TAB:
        return "Tab";
    case VK_SPACE:
        return "Space";

    case '0':
        return "0";
    case '1':
        return "1";
    case '2':
        return "2";
    case '3':
        return "3";
    case '4':
        return "4";
    case '5':
        return "5";
    case '6':
        return "6";
    case '7':
        return "7";
    case '8':
        return "8";
    case '9':
        return "9";
            
    case 'A':
        return "A";
    case 'B':
        return "B";
    case 'C':
        return "C";
    case 'D':
        return "D";
    case 'E':
        return "E";
    case 'F':
        return "F";
    case 'G':
        return "G";
    case 'H':
        return "H";
    case 'I':
        return "I";
    case 'J':
        return "J";
    case 'K':
        return "K";
    case 'L':
        return "L";
    case 'M':
        return "M";
    case 'N':
        return "N";
    case 'O':
        return "O";
    case 'P':
        return "P";
    case 'Q':
        return "Q";
    case 'R':
        return "R";
    case 'S':
        return "S";
    case 'T':
        return "T";
    case 'U':
        return "U";
    case 'V':
        return "V";
    case 'W':
        return "W";
    case 'X':
        return "X";
    case 'Y':
        return "Y";
    case 'Z':
        return "Z";

    case VK_F1:
        return "F1";
    case VK_F2:
        return "F2";
    case VK_F3:
        return "F3";
    case VK_F4:
        return "F4";
    case VK_F5:
        return "F5";
    case VK_F6:
        return "F6";
    case VK_F7:
        return "F7";
    case VK_F8:
        return "F8";
    case VK_F9:
        return "F9";
    case VK_F10:
        return "F10";
    case VK_F11:
        return "F11";
    case VK_F12:
        return "F12";

    case VK_UP:
        return "Up";
    case VK_LEFT:
        return "Left";
    case VK_RIGHT:
        return "Right";
    case VK_DOWN:
        return "Down";

    default:
        return "";
    }
}

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
    outFile << "GroundMount " << pSettings->groundMount << endl;
    outFile << "FlyMount " << pSettings->flyMount << endl;

    outFile << "ActiveCombat " << (pSettings->activeCombat ? "true" : "false") << endl;
    outFile << "LootMobs " << (pSettings->lootMobs ? "true" : "false") << endl;
    outFile << "SkinMobs " << (pSettings->skinMobs ? "true" : "false") << endl;

    outFile << "FoodQty " << pSettings->foodQty << endl;
    outFile << "DrinkQty " << pSettings->drinkQty << endl;

    outFile.close();

    return true;
}

void drawSettings(ecmSettings *pSettings)
{
    static int target = -1;
    static WORD currentKey = 0;

    if (ImGui::BeginChild("Settings"))
    {
        ImGui::Checkbox("Aggressive", &pSettings->activeCombat);
        ImGui::Checkbox("Loot Mobs", &pSettings->lootMobs);
        ImGui::Checkbox("Skin Mobs", &pSettings->skinMobs);

        ImGui::SliderInt("Food Quantity", &pSettings->foodQty, 0, 300);
        ImGui::SliderInt("Drink Quantity", &pSettings->drinkQty, 0, 300);

        ImGui::InputText("Food Name", &pSettings->foodName[0], BUFFER_SIZE);
        ImGui::InputText("Drink Name", &pSettings->drinkName[0], BUFFER_SIZE);
        ImGui::InputText("Ground Mount", &pSettings->groundMount[0], BUFFER_SIZE);
        ImGui::InputText("Flying Mount", &pSettings->flyMount[0], BUFFER_SIZE);

        if (target != -1)
        {
            ImGuiIO io = ImGui::GetIO();

            for (int i = 0; i < 512; ++i)
            {
                if (io.KeysDown[i])
                    currentKey = i;
            }

            if (currentKey != 0)
            {
                if (io.KeyShift)
                    currentKey |= ecmMOD_Shift;
                if (io.KeyCtrl)
                    currentKey |= ecmMOD_Ctrl;
                if (io.KeyAlt)
                    currentKey |= ecmMOD_Alt;

                SetKey((keyBind)target, SDLtoVK(SDL_Scancode(currentKey & ecmMOD_Mask)));
                currentKey = 0;
                target = -1;
            }
        }

        ImGui::Columns(2);
        for (int i = 0; i < kbCount; ++i)
        {
            if (ImGui::Button(bindNames[i], ImVec2(-1, 0)))
            {
                if (target == i)
                {
                    target = -1;
                }
                else
                {
                    currentKey = 0;
                    target = i;
                }
            }

            if (target == i)
            {
                ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), 0xFF0000FF, 0.0f, ImDrawFlags_RoundCornersNone, 2.0f);
            }

            ImGui::NextColumn();
            ImGui::Text("%s", GetKeyName(GetKey((keyBind)i)));
            ImGui::NextColumn();
        }
    }
    ImGui::EndChild();
}
