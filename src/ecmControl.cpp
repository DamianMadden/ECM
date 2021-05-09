#define _HAS_STD_BYTE 0

#include "ecmControl.h"
#include "ecmStatus.h"
#include "ecmProfile.h"
#include "ecmWaypoints.h"
#include "ecmSettings.h"

#include <vector>

bool combat = false;

bool runControl(ecmStatus *pStatus, ecmProfile *pProfile, ecmSettings *pSettings, ecmWaypoints *pWaypoints)
{
	if (pStatus->target.targetting)
	{
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
		if (!move(pStatus, pWaypoints))
			return false;
	}
	else
	{
		if (!move(pStatus, pWaypoints))
			return false;
	}

	return true;
	
	/*if (pSettings->harvestMinerals || pSettings->harvestHerbs)
	{
		// scanForNodes

	}*/

	// No other action due, sleep or return and let main sleep

}