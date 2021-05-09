#include "ecmWaypoint.h"

#include <vector>
#include <string>
using namespace std;

int closest(waypoint& pos, vector<waypoint> *pWaypoints)
{
    if (pWaypoints->size() < 1)
        return -1;

    float minDistance = FLT_MAX;
    int minIndex = 0;
    for (unsigned int i = 0; i < pWaypoints->size(); ++i)
    {
        float dist = magSq(pWaypoints->at(i) - pos);
        if (dist < minDistance)
        {
            minIndex = i;
            minDistance = dist;
        }
    }
    return minIndex;
}
