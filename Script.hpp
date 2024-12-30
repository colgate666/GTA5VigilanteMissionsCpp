#pragma once

#include "inc/natives.h"
#include "inc/types.h"
#include "inc/enums.h"
#include "Screen.hpp"
#include <map>
#include <vector>
#include <string>

struct MissionState {
    static bool active;
    static int type;
};

extern Hash RELATIONSHIP_MISSION_LIKE;
extern Hash RELATIONSHIP_MISSION_NEUTRAL;
extern Hash RELATIONSHIP_MISSION_AGGRESSIVE;
extern Hash RELATIONSHIP_MISSION_PEDESTRIAN;
extern Hash RELATIONSHIP_MISSION_DISLIKE;
extern Hash RELATIONSHIP_MISSION_MASS_SHOOTER;

void ScriptMain();
void OnAbort();
