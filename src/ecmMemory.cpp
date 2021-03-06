#pragma warning (disable : 4312 )

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

bool attached()
{
    return process != 0;
}

void detach()
{
    process = NULL;
}

WORD CHARtoVK(char key)
{
    if (key >= '0' && key <= '9')
        return key;
    if (key >= 'A' && key <= 'Z')
        return key;
    if (key >= 'a' && key <= 'z')
        return key;

    switch (key)
    {
    case '/':
        return VK_DIVIDE;
    case ' ':
        return VK_SPACE;
    default:
        return 0;
    }
}

void stopKeys()
{
    for (auto i = keymap.begin(); i != keymap.end(); ++i)
        keyup(i->first);

    keymap.clear();
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    if (!IsWindowVisible(hwnd))
        return true;

    char buffer[100];
    GetWindowTextA(hwnd, buffer, 100);
    
    if (buffer[0] != '\0')
    {
        if (ImGui::Button(buffer))
            attach(buffer);
    }

    return true;
}

bool listWindows()
{
    ImGui::TextUnformatted("Process List");
    ImGui::Separator();
    return EnumWindows(EnumWindowsProc, NULL);
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
    */

    return true;
}

bool keypress(WORD key)
{
    if (!PostMessage(window, WM_KEYDOWN, key, 0x00110001))
        return false;
    
    Sleep(15);

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
    if (!keypress(VK_RETURN))
        return false;

    Sleep(25);

    for (unsigned int i = 0; i < str.length(); ++i)
    {
        if (!keypress(CHARtoVK(str.at(i))))
            return false;
    }
    
    if (!keypress(VK_RETURN))
        return false;

    return true;
}

bool click(WORD x, WORD y)
{
    uint32_t pos = (y << 16) + x;

    if (!PostMessage(window, WM_LBUTTONDOWN, 1, pos))
        return false;

    Sleep(5);

    if (!PostMessage(window, WM_LBUTTONUP, 0, pos))
        return false;

    return true;
}
