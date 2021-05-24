#define _HAS_STD_BYTE 0

#include <iostream>
#include <fstream>
using namespace std;

#include "imgui.h"
#include "ecmWaypoint.h"
#include "ecmWaypoints.h"
#include "ecmStatus.h"
#include "ecmMemory.h"
#include "ecmSettings.h"

bool saveWaypoints(char* pFile, ecmWaypoints* pWaypoints)
{
    fstream outFile;
    outFile.open(pFile, ios_base::out);

    if (!outFile.is_open())
        return false;

    outFile << pWaypoints->mode << endl;

    for (unsigned int i = 0; i < pWaypoints->waypoints.size(); ++i)
    {
        waypoint *pPoint = &pWaypoints->waypoints[i];
        outFile << pPoint->type << " ";

        switch (pPoint->type)
        {
        case wtNormal:
        case wtFlying:
            outFile << pPoint->x << " "
                    << pPoint->y << " "
                    << pPoint->z << endl;
            break;
        case wtCommand:
            outFile << string(pPoint->command) << endl;
            break;
        case wtClick:
            outFile << pPoint->x << " "
                    << pPoint->y << endl;
            break;
        }
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

    int mode;
    inFile >> mode;
    pWaypoints->mode = (wayMode)mode;

    waypoint buffer;
    while (!inFile.eof())
    {
        int y;
        inFile >> y;

        buffer.type = (pointTypes)y;

        switch (buffer.type)
        {
        case wtNormal:
        case wtFlying:
            inFile >> buffer.x >> buffer.y >> buffer.z;
            break;
        case wtCommand:
            inFile >> buffer.command;
            break;
        case wtClick:
            inFile >> buffer.x >> buffer.y;
        }
        
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

    static char commandbuffer[100] = {};
    ImGui::InputText("Command", commandbuffer, 100);
    if (ImGui::Button("Add Command"))
    {
        waypoint command = {};
        command.command = string(commandbuffer);
        command.type = wtCommand;
        pWaypoints->waypoints.push_back(command);
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
    unsigned int highest = pWaypoints->waypoints.size();
    while (pWaypoints->waypoints[pWaypoints->currWaypoint].type == wtCommand)
    {
        chatString(pWaypoints->waypoints[pWaypoints->currWaypoint].command);
        pWaypoints->currWaypoint = (highest + (pWaypoints->currWaypoint + 1)) % highest;
    }
    while (pWaypoints->waypoints[pWaypoints->currWaypoint].type == wtClick)
    {
        click((WORD)pWaypoints->waypoints[pWaypoints->currWaypoint].x, (WORD)pWaypoints->waypoints[pWaypoints->currWaypoint].y);
        pWaypoints->currWaypoint = (highest + (pWaypoints->currWaypoint + 1)) % highest;
    }

    // Rotate if necessary
    float angle = rotationBetween(pStatus->pos, pWaypoints->waypoints[pWaypoints->currWaypoint]);
    angle = fmod(angle, TWOPI);

    float difference = pStatus->rotation + PI - angle;
    difference = fmod(difference, TWOPI);

    if (difference > .25)
    {
        if (!keyup(GetKey(kbForward)))
            return false;
        if (!keyup(GetKey(kbLeft)))
            return false;
        if (!keydown(GetKey(kbRight)))
            return false;
    }
    else if (difference < -.25)
    {
        if (!keyup(GetKey(kbForward)))
            return false;
        if (!keyup(GetKey(kbRight)))
            return false;
        if (!keydown(GetKey(kbLeft)))
            return false;
    }
    else
    {
        if (!keyup(GetKey(kbLeft)))
            return false;
        if (!keyup(GetKey(kbRight)))
            return false;
        if (!keydown(GetKey(kbForward)))
            return false;
    }

    // If close enough, advance to next waypoint
    if (distance(pStatus->pos - pWaypoints->waypoints[pWaypoints->currWaypoint]) < 10)
        pWaypoints->currWaypoint = (highest + (pWaypoints->currWaypoint + 1)) % highest;

    return true;
}