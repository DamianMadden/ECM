#ifndef ECMMEMORY_H
#define ECMMEMORY_H

#include <Windows.h>
using namespace std;

#include "imgui.h"
#include "ecmWaypoint.h"

struct ecmStatus;

bool attached();
bool attach(char *pWName);
void detach();
bool loadAddresses(char *pFile);
bool read(LPCVOID pAdd, void *pBuffer, unsigned int bytes);
bool updateStatus(ecmStatus *pStatus);
bool keypress(WORD key);
bool keydown(WORD key);	
bool keyup(WORD key);
void stopKeys();
bool chatString(string str);
bool click(WORD x, WORD y);
bool listWindows();

#endif