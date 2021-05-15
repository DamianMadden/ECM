#ifndef ECMWAYPOINT_H
#define ECMWAYPOINT_H

#define PI 3.14159f
#define TWOPI 6.28318f
#define HALFPI 1.570795f

#include <vector>
#include <string>
using namespace std;

enum pointTypes
{
    wtNormal,
    wtCommand,
    wtFlying
};

struct waypoint
{
    pointTypes type;

    float x;
    float y;
    float z;

    string command;

    waypoint operator+(waypoint& w)
    {
        this->x += w.x;
        this->y += w.y;
        this->z += w.z;
        return *this;
    }

    waypoint operator-(waypoint& w)
    {
        this->x -= w.x;
        this->y -= w.y;
        this->z -= w.z;
        return *this;
    }

    string toString()
    {
        char buffer[64] = {};
        switch (this->type)
        {
        case wtNormal:
            sprintf_s(buffer, "%.3f, %.3f, %.3f", this->x, this->y, this->z);
            return string(buffer);
        case wtCommand:
            return this->command;
        default:
            return string();
        }
        
    }
};

inline float magSq(const waypoint& w)
{
    return w.x * w.x + w.y * w.y + w.z * w.z;
}

inline float distance(const waypoint& w)
{
    return sqrtf(w.x * w.x + w.y * w.y + w.z * w.z);
}

inline float rotationBetween(const waypoint& w1, const waypoint& w2)
{
    return HALFPI - atan2f(w1.x - w2.x, w1.y - w2.y);
}

int closest(waypoint* pPos, vector<waypoint>* pWaypoints);

#endif