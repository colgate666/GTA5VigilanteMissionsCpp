#include "pch.h"
#include "Script.hpp"
#include "json.hpp"
#include "RandomMission.h"

#include "GTAVMenuBase/menu.h"

bool MissionState::active;
int MissionState::type;
NativeMenu::Menu menu;

bool calculateCrimes;
int firstCrime;
int secondCrime;
int thirdCrime;

Hash RELATIONSHIP_MISSION_LIKE;
Hash RELATIONSHIP_MISSION_NEUTRAL;
Hash RELATIONSHIP_MISSION_AGGRESSIVE;
Hash RELATIONSHIP_MISSION_PEDESTRIAN;
Hash RELATIONSHIP_MISSION_DISLIKE;
Hash RELATIONSHIP_MISSION_MASS_SHOOTER;

std::array<const char*, 7> missionNames = {
    "Stolen Vehicle",
    "Assault",
    "Gang Activity",
    "Suspect on the run",
    "Mass shooter",
    "Pacific Bank Robbery",
    "Fleeca Bank robbery"
};

void ReadConfig() {
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

bool canStartPacific() {
    const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

    return MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords, {224.4161f, 208.0313f, 104.5419f}, false) >= 1500;
}

void menuTick() {
    menu.CheckKeys();

    if (menu.CurrentMenu("mainmenu")) {
        menu.Title("Police Computer");
        menu.Subtitle("Los Santos Police");

        if (menu.MenuOption("Current Crimes", "random", { "Ongoing crimes" })) {
            calculateCrimes = true;
        }
    }
    else if (menu.CurrentMenu("random")) {
        menu.Title("Current Crimes");
        menu.Subtitle("Los Santos Police");

        if (calculateCrimes) {
            const bool canStartPacificRobbery = canStartPacific();
            calculateCrimes = false;
            firstCrime = MISC::GET_RANDOM_INT_IN_RANGE(0, 7);

            while (firstCrime == RANDOM_MISSION::eMissionType::PacificBankRobbery && !canStartPacificRobbery) {
                firstCrime = MISC::GET_RANDOM_INT_IN_RANGE(0, 7);
            }

            secondCrime = MISC::GET_RANDOM_INT_IN_RANGE(0, 7);

            while ((secondCrime == RANDOM_MISSION::eMissionType::PacificBankRobbery && !canStartPacificRobbery) || secondCrime == firstCrime) {
                secondCrime = MISC::GET_RANDOM_INT_IN_RANGE(0, 7);
            }

            thirdCrime = MISC::GET_RANDOM_INT_IN_RANGE(0, 7);

            while ((thirdCrime == RANDOM_MISSION::eMissionType::PacificBankRobbery && !canStartPacificRobbery) || thirdCrime == firstCrime || thirdCrime == secondCrime) {
                thirdCrime = MISC::GET_RANDOM_INT_IN_RANGE(0, 7);
            }
        }

        if (menu.Option(missionNames[firstCrime])) {
            RANDOM_MISSION::Start(static_cast<RANDOM_MISSION::eMissionType>(firstCrime));
            menu.CloseMenu();
        }

        if (menu.Option(missionNames[secondCrime])) {
            RANDOM_MISSION::Start(static_cast<RANDOM_MISSION::eMissionType>(secondCrime));
            menu.CloseMenu();
        }

        if (menu.Option(missionNames[thirdCrime])) {
            RANDOM_MISSION::Start(static_cast<RANDOM_MISSION::eMissionType>(thirdCrime));
            menu.CloseMenu();
        }
    }

    menu.EndMenu();
}

[[noreturn]] int main() {
    while (DLC::GET_IS_LOADING_SCREEN_ACTIVE()) {
        WAIT(0);
    }

    ReadConfig();
    menu.ReadSettings();

    for (;;) {
        menuTick();

        if (MissionState::active) {
            if (MissionState::type == 0) {
                RANDOM_MISSION::Process();
            }
        }
        else if (!menu.IsThisOpen() && !MISC::GET_MISSION_FLAG() && PED::IS_PED_IN_ANY_POLICE_VEHICLE(PLAYER::PLAYER_PED_ID()) && PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) {
            if (const Vehicle currentVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false); VEHICLE::IS_VEHICLE_STOPPED(currentVehicle)) {
                SCREEN::ShowHelpText("Press ~INPUT_CONTEXT~ to access the police computer", true);

                if (PAD::IS_CONTROL_JUST_PRESSED(0, 51)) {
                    menu.OpenMenu();
                }
            }
        }

        if (menu.IsThisOpen()) {
            if (!PED::IS_PED_IN_ANY_POLICE_VEHICLE(PLAYER::PLAYER_PED_ID())) {
                menu.CloseMenu();
            }
            else if (const Vehicle currentVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false); !VEHICLE::IS_VEHICLE_STOPPED(currentVehicle)) {
                menu.CloseMenu();
            }
        }

        WAIT(0);
    }
}

void ScriptMain() {
    srand(GetTickCount64());
    main();
}

void OnAbort() {
    if (MissionState::active) {
        if (MissionState::type == 0) {
            RANDOM_MISSION::Quit(true);
        }
    }
}
