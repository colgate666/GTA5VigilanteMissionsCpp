#pragma once

#include "inc/natives.h"
#include "inc/types.h"
#include "MissionPed.h"
#include "Screen.hpp"
#include "Music.hpp"
#include "Blip.hpp"

namespace MOST_WANTED_SIMPLE {
    enum eMostWantedTarget {
        WangFang
    };

    struct MissionData {
        eMostWantedTarget target;
        int currentObjective = 0;
        Blip objectiveBlip = 0;
        Vector3 objectiveLocation;
        bool intensityIncreased = false;
        std::vector<MissionPed> enemies = {};
        std::vector<MissionPed> hostages = {};
        std::vector<MissionPed> police = {};
        std::vector<Vehicle> vehicles = {};
    };

    void Process();
    void Start(eMostWantedTarget target);
    void Quit(bool playerDied);
    void ResetState();
    bool RemoveDeadEnemies();
}