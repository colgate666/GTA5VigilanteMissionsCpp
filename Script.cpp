#include "pch.h"
#include "Script.hpp"
#include "json.hpp"

bool MissionState::active;

void ReadConfig() {
    /*std::ifstream i("SurvivalsData\\config.json");
    i >> j;
    i.close();

    Data::intermissionDuration = j["Gameplay"]["IntermissionDuration"];
    tpPointsEnabled = j["Gameplay"]["TPMarkers"];
    Data::infiniteWaveControl = static_cast<Controls>(j["Controls"]["StartInfiniteWaves"]);
    Data::timedSurvivalControl = static_cast<Controls>(j["Controls"]["StartTimedSurvival"]);
    Data::cancelControl = static_cast<Controls>(j["Controls"]["CancelSurvival"]);
    Data::reloadTriggerPedsControl = static_cast<Controls>(j["Controls"]["ReloadTriggerPeds"]);
    Data::hardcoreSurvivalControl = static_cast<Controls>(j["Controls"]["StartHardcoreSurvival"]);*/

    const Hash playerGroupHash = MISC::GET_HASH_KEY("PLAYER");
    const Hash copsRelGroup = MISC::GET_HASH_KEY("COP");
    const Hash mPedRelGroup = MISC::GET_HASH_KEY("CIVMALE");
    const Hash fPedRelGroup = MISC::GET_HASH_KEY("CIVFEMALE");

    PED::ADD_RELATIONSHIP_GROUP("RELATIONSHIP_MISSION_LIKE", &RELATIONSHIP_MISSION_LIKE);
    PED::ADD_RELATIONSHIP_GROUP("RELATIONSHIP_MISSION_NEUTRAL", &RELATIONSHIP_MISSION_NEUTRAL);
    PED::ADD_RELATIONSHIP_GROUP("RELATIONSHIP_MISSION_AGGRESSIVE", &RELATIONSHIP_MISSION_AGGRESSIVE);
    PED::ADD_RELATIONSHIP_GROUP("RELATIONSHIP_MISSION_PEDESTRIAN", &RELATIONSHIP_MISSION_PEDESTRIAN);
    PED::ADD_RELATIONSHIP_GROUP("RELATIONSHIP_MISSION_DISLIKE", &RELATIONSHIP_MISSION_DISLIKE);
    PED::ADD_RELATIONSHIP_GROUP("RELATIONSHIP_MISSION_MASS_SHOOTER", &RELATIONSHIP_MISSION_MASS_SHOOTER);

    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipLike, playerGroupHash, RELATIONSHIP_MISSION_LIKE);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipLike, RELATIONSHIP_MISSION_LIKE, playerGroupHash);

    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipNeutral, playerGroupHash, RELATIONSHIP_MISSION_NEUTRAL);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipNeutral, RELATIONSHIP_MISSION_NEUTRAL, playerGroupHash);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipNeutral, copsRelGroup, RELATIONSHIP_MISSION_NEUTRAL);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipNeutral, RELATIONSHIP_MISSION_NEUTRAL, copsRelGroup);

    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, playerGroupHash, RELATIONSHIP_MISSION_AGGRESSIVE);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, RELATIONSHIP_MISSION_AGGRESSIVE, playerGroupHash);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, copsRelGroup, RELATIONSHIP_MISSION_AGGRESSIVE);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, RELATIONSHIP_MISSION_AGGRESSIVE, copsRelGroup);

    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipDislike, playerGroupHash, RELATIONSHIP_MISSION_DISLIKE);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipDislike, RELATIONSHIP_MISSION_DISLIKE, playerGroupHash);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipDislike, copsRelGroup, RELATIONSHIP_MISSION_DISLIKE);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipDislike, RELATIONSHIP_MISSION_DISLIKE, copsRelGroup);

    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, playerGroupHash, RELATIONSHIP_MISSION_MASS_SHOOTER);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, RELATIONSHIP_MISSION_MASS_SHOOTER, playerGroupHash);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, copsRelGroup, RELATIONSHIP_MISSION_MASS_SHOOTER);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, RELATIONSHIP_MISSION_MASS_SHOOTER, copsRelGroup);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, fPedRelGroup, RELATIONSHIP_MISSION_MASS_SHOOTER);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, RELATIONSHIP_MISSION_MASS_SHOOTER, fPedRelGroup);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, mPedRelGroup, RELATIONSHIP_MISSION_MASS_SHOOTER);
    PED::SET_RELATIONSHIP_BETWEEN_GROUPS(RelationshipHate, RELATIONSHIP_MISSION_MASS_SHOOTER, mPedRelGroup);
}

int main() {
    while (DLC::GET_IS_LOADING_SCREEN_ACTIVE()) {
        WAIT(0);
    }

    ReadConfig();

    while (true) {
        WAIT(0);
    }
}

void ScriptMain() {
    srand(GetTickCount64());
    main();
}

void OnAbort() {

}
