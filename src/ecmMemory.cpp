#include <Windows.h>
#include <WinUser.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;

#include "ecmStatus.h"
#include "ecmMemory.h"

HANDLE process;
HWND window;
unordered_map<string, LPCVOID> addresses;
unordered_map<WORD, int> keymap;

void stopKeys()
{
    for (auto i = keymap.begin(); i != keymap.end(); ++i)
        keyup(i->first);

    keymap.clear();
}

bool attach(char* pWName)
{
    window = FindWindowA(NULL, pWName);

    if (window == NULL)
        return false;

    DWORD procID;
    GetWindowThreadProcessId(window, &procID);
    process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

    return true;
}

bool loadAddresses(char* pFile)
{
    fstream file;
    file.open(pFile, ios_base::in);

    if (!file.is_open())
        return false;

    while (!file.eof())
    {
        string key;
        string ptr;

        file >> key >> ptr;

        LPCVOID pointer = (LPCVOID)stol(ptr, nullptr, 16);
        addresses[key] = pointer;
    }

    file.close();

    return true;
}

bool read(LPCVOID pAdd, void *pBuffer, unsigned int bytes)
{
    if (!ReadProcessMemory(process, pAdd, pBuffer, bytes, NULL))
        return false;
    return true;
}

bool updateStatus(ecmStatus *pStatus)
{
    if (!read(addresses["CharName"], &pStatus->charName, BUFFER_SIZE)) return false;
    if (!read(addresses["Rotation"], &pStatus->rotation, sizeof(pStatus->rotation))) return false;
    if (!read(addresses["CharX"], &pStatus->pos.x, sizeof(pStatus->pos.x))) return false;
    if (!read(addresses["CharY"], &pStatus->pos.y, sizeof(pStatus->pos.y))) return false;
    if (!read(addresses["CharZ"], &pStatus->pos.z, sizeof(pStatus->pos.z))) return false;

    if (!read(addresses["Targetting"], &pStatus->target.targetting, sizeof(pStatus->target.targetting))) return false;

    /*
    if (!read(addresses["Health"], &pStatus->health, sizeof(pStatus->health))) return false;
    if (!read(addresses["MaxHealth"], &pStatus->maxHealth, sizeof(pStatus->maxHealth))) return false;
    if (!read(addresses["Mana"], &pStatus->mana, sizeof(pStatus->mana))) return false;
    if (!read(addresses["MaxMana"], &pStatus->maxMana, sizeof(pStatus->maxMana))) return false;
    if (!read(addresses["Experience"], &pStatus->exp, sizeof(pStatus->exp))) return false;
    if (!read(addresses["Alive"], &pStatus->alive, sizeof(pStatus->alive))) return false;
    if (!read(addresses["TarName"], &pStatus->target.name, BUFFER_SIZE)) return false;
    if (!read(addresses["TarHealth"], &pStatus->target.health, sizeof(pStatus->target.mana))) return false;
    if (!read(addresses["TarMaxHealth"], &pStatus->target.mana, sizeof(pStatus->target.mana))) return false;
    if (!read(addresses["TarMana"], &pStatus->target.health, sizeof(pStatus->target.mana))) return false;
    if (!read(addresses["TarMaxMana"], &pStatus->target.mana, sizeof(pStatus->target.mana))) return false;
    */

    return true;
}

bool keypress(WORD key)
{
    if (!PostMessage(window, WM_KEYDOWN, key, 0x00110001))
        return false;

    return PostMessage(window, WM_KEYUP, key, 0xC0110001);
}

bool keydown(WORD key)
{
    ++keymap[key];

    if (keymap[key] == 1 || keymap[key] % 15 == 0)
    {
        if (!PostMessage(window, WM_KEYDOWN, key, 0x00110001))
            return false;
    }
    return true;
}

bool keyup(WORD key)
{
    if (keymap[key] > 0)
    {
        if (!PostMessage(window, WM_KEYUP, key, 0xC0110001))
            return false;

        keymap[key] = 0;
    }
    return true;
}

bool chatString(string str)
{
    for (unsigned int i = 0; i < str.length(); ++i)
    {
        // Lookup character in table
        // str.at(i);
        //if (!keypress())
        //    return false;
    }

    return true;
}
