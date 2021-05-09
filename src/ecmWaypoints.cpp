#define _HAS_STD_BYTE 0

#include <fstream>
#include "imgui.h"
#include "ecmWaypoint.h"
#include "ecmWaypoints.h"
#include "ecmStatus.h"
#include "ecmMemory.h"

bool saveWaypoints(char* pFile, ecmWaypoints* pWaypoints)
{
    fstream outFile;
    outFile.open(pFile, ios_base::out);

    if (!outFile.is_open())
        return false;

    outFile << pWaypoints->mode << endl;

    for (unsigned int i = 0; i < pWaypoints->waypoints.size(); ++i)
    {
        outFile << pWaypoints->waypoints[i].x << " "
                << pWaypoints->waypoints[i].y << " "
                << pWaypoints->waypoints[i].z << endl;
    }

    outFile.close();

    return true;
}

bool loadWaypoints(char* pFile, ecmWaypoints* pWaypoints)
{
    fstream inFile;
    inFile.open(pFile, ios_base::in);

    if (!inFile.is_open())
        return false;

    int x;
    inFile >> x;

    pWaypoints->mode = (wayMode)x;

    waypoint buffer;
    while (!inFile.eof())
    {
        inFile >> buffer.x >> buffer.y >> buffer.z;
        pWaypoints->waypoints.push_back(buffer);
    }

    inFile.close();

    return true;
}

void drawWaypoints(ecmWaypoints *pWaypoints, waypoint *pPos)
{
    if (ImGui::Button("Save Waypoints"))
    {
        // File Dialog
        saveWaypoints("waypoints", pWaypoints);
    }

    if (ImGui::Button("Load Waypoints"))
    {
        // File Dialog
        loadWaypoints("waypoints", pWaypoints);
    }

    if (ImGui::Button("Add Waypoint"))
    {
        pWaypoints->waypoints.push_back(*pPos);
    }

    for (unsigned int i = 0; i < pWaypoints->waypoints.size(); ++i)
    {
        ImGui::Text(pWaypoints->waypoints.at(i).toString().c_str());
        ImGui::SameLine();
        char buffer[10] = {};
        sprintf_s(buffer, "X##%d", i);
        if (ImGui::Button(buffer))
            pWaypoints->waypoints.erase(pWaypoints->waypoints.begin() + i);
    }
}

bool move(ecmStatus* pStatus, ecmWaypoints* pWaypoints)
{
    // Rotate if necessary
    float angle = rotationBetween(pStatus->pos, pWaypoints->waypoints[pWaypoints->currWaypoint]);
    if (abs(angle) > 0.2)
    {
        if (angle < 0)
        {
            if (!keypress(VK_RIGHT))
                return false;
        }
        else
        {
            if (!keypress(VK_LEFT))
                return false;
        }
    }

    // If close enough, advance to next waypoint
    if (distance(pStatus->pos - pWaypoints->waypoints[pWaypoints->currWaypoint]) < 5)
    {
        unsigned int highest = pWaypoints->waypoints.size() - 1;
        pWaypoints->currWaypoint = (highest + (pWaypoints->currWaypoint + 1)) % highest;
    }

    if (!keypress(VK_UP))
        return false;

    return true;
    }