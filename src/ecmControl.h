#ifndef ECMCONTROL_H
#define ECMCONTROL_H

#include "ecmStatus.h"
#include "ecmProfile.h"
#include "ecmWaypoints.h"
#include "ecmSettings.h"

enum actionState
{
	asIdle,			// Might be needed in some waypoint sets to wait for an action
	asNavigation,	
	asActing,
	asCombat,
	asLocked,
	asLooting
};

void controlThread(ecmStatus* pStatus, ecmProfile* pProfile, ecmSettings* pSettings, ecmWaypoints* pWaypoints);

#endif