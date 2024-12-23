#pragma once

#include "SHV SDK/natives.h"
#include "SHV SDK/types.h"
#include "SHV SDK/enums.h"
#include "Screen.hpp"
#include <map>
#include <vector>
#include <string>

struct MissionState {
    static bool active;
};

static Hash RELATIONSHIP_MISSION_LIKE;
static Hash RELATIONSHIP_MISSION_NEUTRAL;
static Hash RELATIONSHIP_MISSION_AGGRESSIVE;
static Hash RELATIONSHIP_MISSION_PEDESTRIAN;
static Hash RELATIONSHIP_MISSION_DISLIKE;
static Hash RELATIONSHIP_MISSION_MASS_SHOOTER;

void ScriptMain();
void OnAbort();
