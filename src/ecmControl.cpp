#define _HAS_STD_BYTE 0

#include "ecmControl.h"
#include "ecmStatus.h"
#include "ecmProfile.h"
#include "ecmWaypoint.h"
#include "ecmWaypoints.h"
#include "ecmSettings.h"

#include <vector>

bool combat = false;

bool runControl(ecmStatus* pStatus, ecmProfile* pProfile, ecmSettings* pSettings, ecmWaypoints* pWaypoints)
{
	if (pStatus->target.targetting)
	{
		if (!keyup(VK_UP))
			return false;
		if (!keyup(VK_LEFT))
			return false;
		if (!keyup(VK_RIGHT))
			return false;

		combat = true;

		vector<ecmAction>* pAct = &pProfile->thresholds;
		for (unsigned int i = 0; i < pAct->size(); ++i)
		{
			if (pAct->at(i).doAction(pStatus))
				return true;
		}

		pAct = &pProfile->actions;
		for (unsigned int i = 0; i < pAct->size(); ++i)
		{
			if (pAct->at(i).doAction(pStatus))
				return true;
		}

		return true;
	}
	else if (combat)
	{
		if (pSettings->lootMobs)
		{
			if (!keypress(VK_F11)) // last target
				return false;
			if (!keypress(VK_F12)) // Interact
				return false;

			Sleep(5000);

			if (!keypress(VK_ESCAPE))
				return false;
		}

		combat = false;
	}
	else if (pSettings->activeCombat)
	{
		if (!keypress(VK_TAB))
			return false;
	}

	if (!move(pStatus, pWaypoints))
		return false;

	return true;
}

void controlThread(ecmStatus* pStatus, ecmProfile* pProfile, ecmSettings* pSettings, ecmWaypoints* pWaypoints)
{
	while (!pStatus->done)
	{
		pWaypoints->currWaypoint = closest(&pStatus->pos, &pWaypoints->waypoints);
		while (pStatus->running)
		{
			if (!runControl(pStatus, pProfile, pSettings, pWaypoints))
			{
				pStatus->running = false;
				pStatus->attached = false;
			}
			Sleep(DWORD(1000 / 30));
		}
		stopKeys();
		Sleep(DWORD(200));
	}
}
