#include <fstream>
#include "imgui.h"
#include "ecmWaypoint.h"
#include "ecmWaypoints.h"
#include "ecmStatus.h"

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

void nextWaypoint(ecmWaypoints* pWaypoints)
{
    waypoint next;
    int highest = pWaypoints->waypoints.size() - 1;
    pWaypoints->currWaypoint = (highest + (pWaypoints->currWaypoint + 1)) % highest;
}

bool move(ecmStatus* pStatus, ecmWaypoints* pWaypoints)
{
    waypoint next;
    int highest = pWaypoints->waypoints.size() - 1;
    pWaypoints->currWaypoint = (highest + (pWaypoints->currWaypoint + 1)) % highest;

    
    // calculate rotation necessary > threshold
    
    // keydown UP + rotate?
}

/*
waypoint next(const waypoint& pos, ecmWaypoints* pWaypoints)
{
    // Just doing circle waypoints for now
    // pWaypoints->mode

    vector<waypoint>* pWP = &pWaypoints->waypoints;
    int highest = pWP->size() - 1;
    if (highest < 1)
        return pWP->at(0);

    int i = closest(pos, pWP);
    int prevIndex = (highest + (i - 1)) % highest, nextIndex = (highest + (i + 1)) % highest;

    float prevDist, nextDist;
    prevDist = magSq(pos - pWP->at(prevIndex));
    nextDist = magSq(pos - pWP->at(nextIndex));

    if (nextDist > prevDist)
        return pos;
    else
        return next

}
*/