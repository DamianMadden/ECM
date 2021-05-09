#include <Windows.h>
#include <WinUser.h>
#include <unordered_map>
#include <fstream>
using namespace std;

#include "ecmStatus.h"
#include "ecmMemory.h"

HANDLE process;
HWND window;
unordered_map<string, LPCVOID> addresses;

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
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    if (uSent != ARRAYSIZE(inputs))
        return false;

    return true;
}

bool keydown(WORD key)
{
    INPUT in;

    in.type = INPUT_KEYBOARD;
    in.ki.wVk = key;
    UINT uSent = SendInput(1, &in, sizeof(INPUT));

    if (uSent != 1)
        return false;

    Sleep(50);

    in.ki.dwFlags = KEYEVENTF_KEYUP;
    uSent = SendInput(1, &in, sizeof(INPUT));

    if (uSent != 1)
        return false;

    return true;
}

bool enableInput()
{
    return EnableWindow(window, true);
}

/*
bool disableInput()
{
    return EnableWindow(window, false);
}
*/