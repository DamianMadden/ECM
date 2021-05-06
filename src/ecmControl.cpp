#define _HAS_STD_BYTE 0

#include "ecmControl.h"
#include "ecmStatus.h"
#include "ecmProfile.h"
#include "ecmWaypoints.h"
#include "ecmSettings.h"

#include <vector>



bool runControl(ecmStatus *pStatus, ecmProfile *pProfile, ecmSettings *pSettings, ecmWaypoints *pWaypoints)
{
	if (pStatus->target.targetting)
	{
		keyup(VK_UP);

		if (pStatus->target.health > 0)
		{
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
		}
		else
		{
			//if lootMobs, skinMobs
			keypress(VK_F12); // Interact

			Sleep(5000);

			keypress(VK_ESCAPE);

			return true;
		}
	}
	else if (pSettings->activeCombat)
	{
		keypress(VK_TAB);
	}

	bool ret = move(pStatus, pWaypoints);

	sleep(50);

	return ret;
	
	/*if (pSettings->harvestMinerals || pSettings->harvestHerbs)
	{
		// scanForNodes

	}*/

	// No other action due, sleep or return and let main sleep

}