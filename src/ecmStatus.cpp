#include "imgui.h"
#include "ecmWaypoint.h"
#include "ecmStatus.h"

void drawStatus(ecmStatus *pStatus, bool attached)
{
    if (attached)
    {
        if (ImGui::Button("Start"))
            pStatus->running = true;
        ImGui::SameLine();
        if (ImGui::Button("Stop"))
            pStatus->running = false;

        ImGui::Text("Name: %s", pStatus->charName);
        ImGui::Text("Health: %d/%d", pStatus->health, pStatus->maxHealth);
        ImGui::Text("Mana: %d/%d", pStatus->mana, pStatus->maxMana);
        ImGui::Text("Rotation: %.3f", pStatus->rotation);

        ImGui::Text("Experience: %d\t%d/hr", pStatus->exp, pStatus->exp);
        ImGui::Text("Deaths: %d\t%d/hr", pStatus->deaths, pStatus->deaths);
        ImGui::Text("Loots: %d\t%d/hr", pStatus->loots, pStatus->loots);
        ImGui::Text("Kills: %d\t%d/hr", pStatus->kills, pStatus->kills);

        if (pStatus->target.targetting)
        {
            ImGui::Text("Name: %s", pStatus->target.name);
            ImGui::Text("Health: %d/%d", pStatus->target.health, pStatus->target.maxHealth);
            ImGui::Text("Mana: %d/%d", pStatus->target.mana, pStatus->target.maxMana);
        }
        else
        {
            ImGui::Text("No Target");
        }
    }
    else
    {
        ImGui::Text("Not attached to process");
    }
}