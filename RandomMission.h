#pragma once

#include "inc/natives.h"
#include "inc/types.h"
#include "Utils.h"
#include "MissionPed.h"
#include "Script.hpp"
#include "Screen.hpp"
#include "Music.hpp"

namespace RANDOM_MISSION {
    enum eMissionType {
        StolenVehicle,
        Assault,
        GangActivity,
        SuspectOnTheRun,
        MassShooter,
        PacificBankRobbery,
        FleecaBankRobbery
    };

    struct MissionData {
        eMissionType missionType;
        int currentObjective = 0;
        int currentBank = 0;
        Blip objectiveBlip = 0;
        Vector3 objectiveLocation;
        int actionToTake;
        int shootRange;
        bool actionTaken = false;
        int startTime;
        bool timerStarted = false;
        bool actionStarted = false;
        std::vector<MissionPed> enemies = {};
        std::vector<MissionPed> hostages = {};
        std::vector<MissionPed> police = {};
        std::vector<Vehicle> vehicles = {};
    };

    void Start(eMissionType type);
    void Process();
    void Quit(bool playerDied);
    void ResetState();
    void RemoveDeadEnemies();
}