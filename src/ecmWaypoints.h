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
    vector<waypoint> waypoints;
};

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

void drawWaypoints(ecmWaypoints *pWaypoints)
{
    if (ImGui::Button("Load Waypoints"))
    {
        // File Dialog
    }

    if (ImGui::Button("Add Waypoint"))
    {
        pWaypoints->add = true;
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

#endif