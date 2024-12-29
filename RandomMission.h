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

    void Start(eMissionType type);
    void Process();
    void Quit(bool playerDied);
}