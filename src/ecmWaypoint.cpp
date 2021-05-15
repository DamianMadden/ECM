#include "ecmWaypoint.h"

#include <vector>
using namespace std;

int closest(waypoint *pPos, vector<waypoint> *pWaypoints)
{
    if (pWaypoints->size() < 1)
        return -1;

    float minDistance = FLT_MAX;
    int minIndex = 0;
    for (unsigned int i = 0; i < pWaypoints->size(); ++i)
    {
        waypoint* pPoint = &pWaypoints->at(i);
        if (pPoint->type == wtCommand)
            continue;

        float dist = magSq(*pPos - *pPoint);
        if (dist < minDistance)
        {
            minIndex = i;
            minDistance = dist;
        }
    }
    return minIndex;
}
