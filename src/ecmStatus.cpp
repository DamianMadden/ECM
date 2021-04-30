#include "imgui.h"
#include "ecmWaypoint.h"
#include "ecmStatus.h"

void drawStatus(ecmStatus *pStatus)
{
    ImGui::Text("Name: %s", pStatus->charName);
    ImGui::Text("Health: %d", pStatus->health);
    ImGui::Text("Mana: %d", pStatus->mana);
    ImGui::Text("Rotation: %.3f", pStatus->rotation);

    ImGui::Text("Experience: %d\t%d/hr", pStatus->exp, pStatus->exp);
    ImGui::Text("Deaths: %d\t%d/hr", pStatus->deaths, pStatus->deaths);
    ImGui::Text("Loots: %d\t%d/hr", pStatus->loots, pStatus->loots);
    ImGui::Text("Kills: %d\t%d/hr", pStatus->kills, pStatus->kills);

    if (pStatus->target.targetting)
    {
        ImGui::Text("Name: %s", pStatus->target.name);
        ImGui::Text("Health: %d", pStatus->target.health);
        ImGui::Text("Mana: %d", pStatus->target.mana);
    }
    else
    {
        ImGui::Text("No Target");
    }
}