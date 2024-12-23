#pragma once

#include "SHV SDK/natives.h"
#include "SHV SDK/types.h"
#include "Utils.h"
#include "MissionPed.h"
#include "Script.hpp"
#include "Screen.hpp"

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