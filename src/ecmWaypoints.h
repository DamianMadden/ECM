#ifndef ECMWAYPOINTS_H
#define ECMWAYPOINTS_H

#include <fstream>
#include "imgui.h"
#include "ecmWaypoint.h"
#include "ecmStatus.h"

enum wayMode
{
    wmCircle = 0,
    wmReverse = 1,
    wmSequential = 2
};

struct ecmWaypoints
{
    bool add;
    wayMode mode;
    int currWaypoint;
    vector<waypoint> waypoints;
};

bool saveWaypoints(char* pFile, ecmWaypoints* pWaypoints);
bool loadWaypoints(char* pFile, ecmWaypoints* pWaypoints);
void drawWaypoints(ecmWaypoints* pWaypoints);
waypoint next(const waypoint& pos, ecmWaypoints* pWaypoints);

#endif