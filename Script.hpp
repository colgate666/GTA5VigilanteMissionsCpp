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

static Hash RELATIONSHIP_MISSION_LIKE;
static Hash RELATIONSHIP_MISSION_NEUTRAL;
static Hash RELATIONSHIP_MISSION_AGGRESSIVE;
static Hash RELATIONSHIP_MISSION_PEDESTRIAN;
static Hash RELATIONSHIP_MISSION_DISLIKE;
static Hash RELATIONSHIP_MISSION_MASS_SHOOTER;

void ScriptMain();
void OnAbort();
