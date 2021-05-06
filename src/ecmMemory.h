#ifndef ECMMEMORY_H
#define ECMMEMORY_H

#include <Windows.h>
using namespace std;

#include "imgui.h"
#include "ecmWaypoint.h"

struct ecmStatus;

bool attach(char *pWName);
bool loadAddresses(char *pFile);
bool read(LPCVOID pAdd, void *pBuffer, unsigned int bytes);
bool updateStatus(ecmStatus *pStatus);
bool keypress(WORD key);
bool keydown(WORD key);
bool keyup(WORD key);

#endif