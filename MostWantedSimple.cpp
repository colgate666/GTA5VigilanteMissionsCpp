#include "pch.h"

#include "MostWantedSimple.h"
#include <vector>

auto missionData = MOST_WANTED_SIMPLE::MissionData();

void MOST_WANTED_SIMPLE::Start(const eMostWantedTarget target) {
    missionData.target = target;
    auto blipName = "blip";
    auto lesterMessage = "Suspect found!";

    switch (missionData.target) {
        case WangFang: {
            missionData.objectiveLocation = {-356.5191f, -61.93171f, 54.0f};
            blipName = "Wang Fang's location";
            lesterMessage = "He's in a ~y~parking lot~w~ trying to score a meth deal. I'm sending you the location.";
            break;
        }
    }

    if (const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true); MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords, missionData.objectiveLocation, false) <= 600) {
        SCREEN::ShowNotification("Mission not available");
        return;
    }

    MUSIC::StartTrack();
    missionData.objectiveBlip = BLIPS::CreateObjectiveBlip(missionData.objectiveLocation, blipName);
    missionData.currentObjective = 0;
    missionData.intensityIncreased = false;
    SCREEN::ShowTextMessage("CHAR_LESTER", "Lester", "Wanted Suspect", lesterMessage);
    MissionState::active = true;
    MissionState::type = 1;
}

void InitializeEntities() {
    switch (missionData.target) {
        case MOST_WANTED_SIMPLE::WangFang: {
            const std::vector pedSpawns = {
                std::make_tuple(-384.9535f, -89.48703f, 54.42385f, -9.292741f),
                std::make_tuple(-391.0056f, -89.59114f, 54.42527f, -24.26937f),
                std::make_tuple(-392.5017f, -88.84636f, 54.42527f, -20.79102f),
                std::make_tuple(-381.1948f, -86.44048f, 54.42526f, 24.15284f),
                std::make_tuple(-392.8951f, -64.03995f, 55.79881f, 47.97223f),
                std::make_tuple(-366.7247f, -57.3772f, 54.41915f, 176.8367f),
                std::make_tuple(-362.2732f, -59.05697f, 54.4193f, -169.0289f),
                std::make_tuple(-345.1667f, -56.89451f, 54.41919f, -83.99975f),
                std::make_tuple(-344.9188f, -54.98076f, 54.41921f, -147.9862f),
                std::make_tuple(-342.8146f, -57.18469f, 54.41929f, 44.56654f),
                std::make_tuple(-350.1284f, -46.48768f, 54.42538f, -8.606504f),
                std::make_tuple(-313.5885f, -78.25857f, 54.42533f, -85.72867f),
                std::make_tuple(-315.5716f, -84.64844f, 54.42538f, -54.99984f)
            };

            const Hash bossModel = MISC::GET_HASH_KEY("G_M_M_ChiBoss_01");
            const Hash goonModel = MISC::GET_HASH_KEY("G_M_M_ChiGoon_02");

            STREAMING::REQUEST_MODEL(bossModel);
            STREAMING::REQUEST_MODEL(goonModel);

            while (!STREAMING::HAS_MODEL_LOADED(bossModel) || !STREAMING::HAS_MODEL_LOADED(goonModel)) {
                WAIT(1);
            }

            for (size_t i = 0; const auto& [x, y, z, rotation] : pedSpawns) {
                Hash model = goonModel;

                if (i == 0) {
                    model = bossModel;
                }

                Ped ped = PED::CREATE_PED(0, model, {x, y, z}, rotation, false, true);
                missionData.enemies.emplace_back(ped, RELATIONSHIP_MISSION_NEUTRAL, false, true);

                if (i == 0) {
                    BLIPS::CreateForEnemyPed(ped, BlipSpriteBountyHit, "Wang Fang");
                } else {
                    BLIPS::CreateForEnemyPed(ped, BlipSpriteEnemy, "Fang Goon");
                }

                i++;
            }

            TASK::TASK_USE_MOBILE_PHONE(missionData.enemies[0].ped, true, 0);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[1].ped, "WORLD_HUMAN_DRUG_DEALER", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[2].ped, "WORLD_HUMAN_SMOKING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[3].ped, "WORLD_HUMAN_LEANING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[4].ped, "WORLD_HUMAN_BINOCULARS", 0, true);
            TASK::TASK_USE_MOBILE_PHONE(missionData.enemies[5].ped, true, 0);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[6].ped, missionData.enemies[5].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_GUARD_CURRENT_POSITION(missionData.enemies[7].ped, 15.0f, 10.0f, true);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[8].ped, missionData.enemies[9].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[9].ped, missionData.enemies[8].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[10].ped, "WORLD_HUMAN_SMOKING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[11].ped, "WORLD_HUMAN_GUARD_STAND", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[12].ped, "WORLD_HUMAN_AA_SMOKE", 0, true);

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(bossModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(goonModel);

            const Hash vehicleModel = MISC::GET_HASH_KEY("youga");
            STREAMING::REQUEST_MODEL(vehicleModel);

            while (!STREAMING::HAS_MODEL_LOADED(vehicleModel)) {
                WAIT(1);
            }

            const Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehicleModel, {-386.1818f, -92.67248f, 53.92717f}, -171.5226f, false, true, false);
            missionData.vehicles.push_back(vehicle);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModel);
            break;
        }
    }
}

bool MOST_WANTED_SIMPLE::RemoveDeadEnemies() {
    for (size_t i = 0; i < missionData.enemies.size(); i++)
    {
        MissionPed& enemy = missionData.enemies.at(i);

        if (!PED::IS_PED_DEAD_OR_DYING(enemy.ped, 1))
        {
            continue;
        }

        if (!PED::CAN_PED_RAGDOLL(enemy.ped))
        {
            PED::SET_PED_CAN_RAGDOLL(enemy.ped, true);
        }

        enemy.RemoveBlip();
        enemy.Delete();

        missionData.enemies.erase(missionData.enemies.begin() + i);
        return true;
    }

    return false;
}

void MOST_WANTED_SIMPLE::Process() {
    switch (missionData.currentObjective) {
        case 0: {
            if (const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true); MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords, missionData.objectiveLocation, false) <= 200) {
                InitializeEntities();
                MUSIC::MidIntensityTrack();
                HUD::REMOVE_BLIP(&missionData.objectiveBlip);
                missionData.currentObjective = 1;
            }
            else {
                const char* subtitle;

                switch (missionData.target) {
                    case WangFang: {
                        subtitle = "Go to the ~y~parking lot~w~.";
                        break;
                    }
                }

                SCREEN::ShowSubtitle(subtitle, 100);
            }
            break;
        }
        case 1: {
            SCREEN::ShowSubtitle("Kill the ~r~targets~w~.", 100);

            if (RemoveDeadEnemies() && !missionData.intensityIncreased) {
                MUSIC::HighIntensityTrack();
                missionData.intensityIncreased = true;
            }

            if (missionData.enemies.empty()) {
                Quit(false);
                return;
            }

            for (MissionPed& enemy : missionData.enemies) {
                enemy.Process();
            }

            break;
        }
    }
}


void MOST_WANTED_SIMPLE::ResetState() {
    if (HUD::DOES_BLIP_EXIST(missionData.objectiveBlip)) {
        HUD::REMOVE_BLIP(&missionData.objectiveBlip);
    }

    for (MissionPed& enemy : missionData.enemies) {
        enemy.Delete();
    }

    for (MissionPed& hostage : missionData.hostages) {
        hostage.Delete();
    }

    for (Vehicle& vehicle : missionData.vehicles) {
        ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);
    }

    for (MissionPed& cop : missionData.police) {
        cop.Delete();
    }

    missionData.enemies.clear();
    missionData.hostages.clear();
    missionData.vehicles.clear();
    missionData.police.clear();
    missionData.currentObjective = 0;
}

void MOST_WANTED_SIMPLE::Quit(const bool playerDied) {
    MissionState::active = false;

    if (playerDied) {
        MUSIC::StopTrack();
        MUSIC::MissionFailedSound();
    } else {
        MUSIC::MissionCompletedSound();
    }

    if (!playerDied) {
        const Hash playerModel = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());
        Hash statName;

        if (playerModel == MISC::GET_HASH_KEY("Player_Zero")) {
            statName = MISC::GET_HASH_KEY("SP0_TOTAL_CASH");
        }
        else if (playerModel == MISC::GET_HASH_KEY("Player_One")) {
            statName = MISC::GET_HASH_KEY("SP1_TOTAL_CASH");
        }
        else {
            statName = MISC::GET_HASH_KEY("SP2_TOTAL_CASH");
        }

        int money;
        STATS::STAT_GET_INT(statName, &money, -1);
        STATS::STAT_SET_INT(statName, money + 1000, true);

        PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 2, false);
        SCREEN::ShowTextMessage("CHAR_LESTER", "Lester", "Wanted Suspect", "Good job, your cut of the reward is already in your account.");
    }

    ResetState();
}