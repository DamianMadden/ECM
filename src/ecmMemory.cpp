#include <Windows.h>
#include <WinUser.h>
#include <unordered_map>
#include <fstream>
using namespace std;

#include "ecmStatus.h"
#include "ecmMemory.h"

static HANDLE process;
static unordered_map<string, LPCVOID> addresses;

bool attach(char* pWName)
{
    HWND hwnd = FindWindowA(NULL, pWName);

    if (hwnd == NULL)
        return false;

    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);
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
    /*
    if (!read(addresses["Health"], &pStatus->health, sizeof(pStatus->health))) return false;
    if (!read(addresses["MaxHealth"], &pStatus->maxHealth, sizeof(pStatus->maxHealth))) return false;
    if (!read(addresses["Mana"], &pStatus->mana, sizeof(pStatus->mana))) return false;
    if (!read(addresses["MaxMana"], &pStatus->maxMana, sizeof(pStatus->maxMana))) return false;
    if (!read(addresses["Experience"], &pStatus->exp, sizeof(pStatus->exp))) return false;
    if (!read(addresses["Alive"], &pStatus->alive, sizeof(pStatus->alive))) return false;
    if (!read(addresses["Targetting"], &pStatus->target, sizeof(pStatus->health))) return false;
    if (!read(addresses["TarName"], &pStatus->target.name, BUFFER_SIZE)) return false;
    if (!read(addresses["TarHealth"], &pStatus->target.health, sizeof(pStatus->target.mana))) return false;
    if (!read(addresses["TarMana"], &pStatus->target.mana, sizeof(pStatus->target.mana))) return false;
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
    {
        return false;
    }

    return true;
}