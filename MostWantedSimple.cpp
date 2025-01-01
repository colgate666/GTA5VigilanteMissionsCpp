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
        case TonyMussolini: {
            missionData.objectiveLocation = {-2075.674f, -1020.837f, 4.88413f};
            blipName = "Tony Mussolini's location";
            lesterMessage = "He's having a party at his ~y~yacht~w~ right now and he is moving it to international waters. I'm sending you the location.";
            break;
        }
    }

    if (const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true); MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords, missionData.objectiveLocation, false) <= 600) {
        SCREEN::ShowNotification("Mission not available");
        return;
    }

    switch (missionData.target) {
        case TonyMussolini: {
            STREAMING::REQUEST_IPL("smboat");
            STREAMING::REQUEST_IPL("apa_smboat_lodlights");
            break;
        }
    }

    MUSIC::StartTrack();
    AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", true);
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
        case MOST_WANTED_SIMPLE::TonyMussolini: {
            Hash lieutModel = MISC::GET_HASH_KEY("G_M_M_ArmLieut_01");
            Hash goonModel = MISC::GET_HASH_KEY("G_M_M_ArmGoon_01");
            Hash bossModel = MISC::GET_HASH_KEY("G_M_M_ArmBoss_01");
            Hash goonModel2 = MISC::GET_HASH_KEY("G_M_Y_ArmGoon_02");
            Hash bossWifeModel = MISC::GET_HASH_KEY("U_F_Y_SpyActress");
            Hash captainModel = MISC::GET_HASH_KEY("S_M_M_Pilot_01");

            STREAMING::REQUEST_MODEL(lieutModel);
            STREAMING::REQUEST_MODEL(goonModel);
            STREAMING::REQUEST_MODEL(bossModel);
            STREAMING::REQUEST_MODEL(goonModel2);
            STREAMING::REQUEST_MODEL(bossWifeModel);
            STREAMING::REQUEST_MODEL(captainModel);

            while (!STREAMING::HAS_MODEL_LOADED(lieutModel) ||
                !STREAMING::HAS_MODEL_LOADED(goonModel) ||
                !STREAMING::HAS_MODEL_LOADED(bossModel) ||
                !STREAMING::HAS_MODEL_LOADED(goonModel2) ||
                !STREAMING::HAS_MODEL_LOADED(captainModel) ||
                !STREAMING::HAS_MODEL_LOADED(bossWifeModel)
            ) {
                WAIT(1);
            }

            const std::vector<std::tuple<float, float, float, float>> lieutSpawns = {
               std::make_tuple(-2108.266f, -1016.047f, 8.9718f, 0.0f),
               std::make_tuple(-2105.627f, -1004.96f, 8.972195f, 152.007f),
               std::make_tuple(-2085.525f, -1016.216f, 8.971098f, 110.6088f),
               std::make_tuple(-2096.059f, -1018.372f, 5.884164f, -179.2764f)
            };

            const std::vector<std::tuple<float, float, float, float>> goonSpawns = {
               std::make_tuple(-2110.015f, -1009.474f, 8.967435f, -113.8403f),
               std::make_tuple(-2093.168f, -1016.17f, 8.980458f, 12.00086f),
               std::make_tuple(-2071.25f, -1021.291f, 11.91093f, -116.1681f),
               std::make_tuple(-2106.087f, -1010.83f, 5.885402f, 164.6348f),
               std::make_tuple(-2072.322f, -1019.197f, 5.88413f, 66.99957f)
            };

            const std::vector<std::tuple<float, float, float, float>> bossSpawns = {
               std::make_tuple(-2095.083f, -1020.348f, 8.972371f, 121.5841f),
               std::make_tuple(-2055.187f, -1028.713f, 8.971491f, -38.99986f),
               std::make_tuple(-2054.666f, -1027.393f, 8.971491f, -139.9988f),
               std::make_tuple(-2098.274f, -1014.407f, 5.884346f, -111.1938f),
               std::make_tuple(-2053.446f, -1032.708f, 8.971491f, 44.60005f)
            };

            const std::vector<std::tuple<float, float, float, float>> goon2Spawns = {
               std::make_tuple(-2081.607f, -1020.792f, 8.971145f, -70.96234f),
               std::make_tuple(-2080.355f, -1017.989f, 8.971145f, -120.9996f),
               std::make_tuple(-2036.194f, -1033.776f, 8.971484f, -104.2428f),
               std::make_tuple(-2033.164f, -1042.431f, 5.882326f, 47.5585f),
               std::make_tuple(-2034.393f, -1042.101f, 5.882571f, -47.96439f),
               std::make_tuple(-2018.398f, -1039.799f, 2.446023f, -94.58332f),
               std::make_tuple(-2081.947f, -1019.532f, 8.971145f, -103.9729f),
               std::make_tuple(-2081.561f, -1018.354f, 8.971145f, -127.0124f)
            };

            const std::tuple<float, float, float, float> bossWifeSpawn = std::make_tuple(-2092.133f, -1020.985f, 8.969188f, -10.27278f);
            const std::tuple<float, float, float, float> captainSpawn = std::make_tuple(-2085.273f, -1017.958f, 12.7819f, 58.85679f);

            // Spawn lieutenants
            for (const auto& [x, y, z, rotation] : lieutSpawns) {
               Ped ped = PED::CREATE_PED(26, lieutModel, {x, y, z}, rotation, false, true);
               missionData.enemies.emplace_back(ped, RELATIONSHIP_MISSION_NEUTRAL, false, true);

                BLIPS::CreateForEnemyPed(ped, BlipSpriteEnemy, "Wanted Criminal");
            }

            // Spawn goons
            for (const auto& [x, y, z, rotation] : goonSpawns) {
               Ped ped = PED::CREATE_PED(26, goonModel, {x, y, z}, rotation, false, true);
               missionData.enemies.emplace_back(ped, RELATIONSHIP_MISSION_NEUTRAL, false, true);

                BLIPS::CreateForEnemyPed(ped, BlipSpriteEnemy, "Wanted Criminal");
            }

            // Spawn bosses
            for (size_t i = 0; const auto& [x, y, z, rotation] : bossSpawns) {
                Ped ped = PED::CREATE_PED(26, bossModel, {x, y, z}, rotation, false, true);
                missionData.enemies.emplace_back(ped, RELATIONSHIP_MISSION_NEUTRAL, false, true);

                if (i == 0) {
                    BLIPS::CreateForEnemyPed(ped, BlipSpriteBountyHit, "Tony Mussolini");
                }
                else {
                    BLIPS::CreateForEnemyPed(ped, BlipSpriteEnemy, "Wanted Criminal");
                }

                i++;
            }

            // Spawn goon2s
            for (const auto& [x, y, z, rotation] : goon2Spawns) {
               Ped ped = PED::CREATE_PED(26, goonModel2, {x, y, z}, rotation, false, true);
               missionData.enemies.emplace_back(ped, RELATIONSHIP_MISSION_NEUTRAL, false, true);

                BLIPS::CreateForEnemyPed(ped, BlipSpriteEnemy, "Wanted Criminal");
            }

            // Spawn boss wife
            auto [bwX, bwY, bwZ, bwRotation] = bossWifeSpawn;
            Ped bossWife = PED::CREATE_PED(26, bossWifeModel, {bwX, bwY, bwZ}, bwRotation, false, true);
            missionData.enemies.emplace_back(bossWife, RELATIONSHIP_MISSION_NEUTRAL, false, true);

            BLIPS::CreateForEnemyPed(bossWife, BlipSpriteEnemy, "Tony's Wife");

            // Spawn captain
            auto [cX, cY, cZ, cRotation] = captainSpawn;
            Ped captain = PED::CREATE_PED(26, captainModel, {cX, cY, cZ}, cRotation, false, true);
            missionData.enemies.emplace_back(captain, RELATIONSHIP_MISSION_NEUTRAL, false, true);

            BLIPS::CreateForEnemyPed(captain, BlipSpriteEnemy, "Ship Captain");

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(lieutModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(goonModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(bossModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(goonModel2);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(bossWifeModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(captainModel);

            Hash hookerModel = MISC::GET_HASH_KEY("S_F_Y_Hooker_01");
            Hash stripperModel = MISC::GET_HASH_KEY("S_F_Y_Stripper_01");
            Hash stripperModel2 = MISC::GET_HASH_KEY("MP_F_StripperLite");
            Hash bartenderModel = MISC::GET_HASH_KEY("S_F_Y_Bartender_01");
            Hash stripperModel3 = MISC::GET_HASH_KEY("S_F_Y_StripperLite");

            STREAMING::REQUEST_MODEL(hookerModel);
            STREAMING::REQUEST_MODEL(stripperModel);
            STREAMING::REQUEST_MODEL(stripperModel2);
            STREAMING::REQUEST_MODEL(stripperModel3);
            STREAMING::REQUEST_MODEL(bartenderModel);

            while (!STREAMING::HAS_MODEL_LOADED(hookerModel) ||
                !STREAMING::HAS_MODEL_LOADED(stripperModel) ||
                !STREAMING::HAS_MODEL_LOADED(stripperModel2) ||
                !STREAMING::HAS_MODEL_LOADED(stripperModel3) ||
                !STREAMING::HAS_MODEL_LOADED(bartenderModel)
            ) {
                WAIT(1);
            }

            const std::vector<std::tuple<float, float, float, float>> hookerSpawns = {
               std::make_tuple(-2106.914f, -1015.075f, 8.971136f, 117.6287f),
               std::make_tuple(-2108.665f, -1014.475f, 8.971003f, -147.2106f),
               std::make_tuple(-2104.866f, -1005.519f, 8.972008f, 101.7841f)
            };

            const std::vector<std::tuple<float, float, float, float>> stripperSpawns = {
               std::make_tuple(-2073.048f, -1018.083f, 5.88413f, -131.9684f),
               std::make_tuple(-2073.715f, -1019.312f, 5.88413f, -79.23396f),
               std::make_tuple(-2106.218f, -1010.064f, 9.925285f, 104.7895f),
               std::make_tuple(-2095.372f, -1015.403f, 5.884346f, 69.90386f)
            };

            // Individual spawns for other models
            const std::tuple<float, float, float, float> stripper2Spawn = std::make_tuple(-2106.418f, -1011.327f, 10.00431f, 71.78985f);
            const std::tuple<float, float, float, float> bartenderSpawn = std::make_tuple(-2094.614f, -1014.906f, 8.980458f, -108.951f);
            const std::tuple<float, float, float, float> stripper3Spawn = std::make_tuple(-2078.302f, -1020.068f, 8.971491f, 73.27193f);

            // Spawn hookers
            for (const auto& [x, y, z, rotation] : hookerSpawns) {
               Ped ped = PED::CREATE_PED(26, hookerModel, {x, y, z}, rotation, false, true);
               missionData.hostages.emplace_back(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false);
            }

            // Spawn strippers
            for (const auto& [x, y, z, rotation] : stripperSpawns) {
               Ped ped = PED::CREATE_PED(26, stripperModel, {x, y, z}, rotation, false, true);
               missionData.hostages.emplace_back(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false);
            }

            // Spawn stripper2
            auto [s2X, s2Y, s2Z, s2Rotation] = stripper2Spawn;
            Ped stripper2 = PED::CREATE_PED(26, stripperModel2, {s2X, s2Y, s2Z}, s2Rotation, false, true);
            missionData.hostages.emplace_back(stripper2, RELATIONSHIP_MISSION_PEDESTRIAN, true, false);

            // Spawn bartender
            auto [bX, bY, bZ, bRotation] = bartenderSpawn;
            Ped bartender = PED::CREATE_PED(26, bartenderModel, {bX, bY, bZ}, bRotation, false, true);
            missionData.hostages.emplace_back(bartender, RELATIONSHIP_MISSION_PEDESTRIAN, true, false);

            // Spawn stripper3
            auto [s3X, s3Y, s3Z, s3Rotation] = stripper3Spawn;
            Ped stripper3 = PED::CREATE_PED(26, stripperModel3, {s3X, s3Y, s3Z}, s3Rotation, false, true);
            missionData.hostages.emplace_back(stripper3, RELATIONSHIP_MISSION_PEDESTRIAN, true, false);

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hookerModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(stripperModel);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(stripperModel2);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(stripperModel3);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(bartenderModel);

            Hash helicopterModel = MISC::GET_HASH_KEY("maverick");

            STREAMING::REQUEST_MODEL(helicopterModel);

            while (!STREAMING::HAS_MODEL_LOADED(helicopterModel)) {
                WAIT(1);
            }

            Vehicle vehicle = VEHICLE::CREATE_VEHICLE(helicopterModel, {-2042.405f, -1031.714f, 12.08313f}, 76.36571f, false, true, false);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicle);

            missionData.vehicles.push_back(vehicle);

            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[6].ped, "WORLD_HUMAN_GUARD_STAND", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[5].ped, "WORLD_HUMAN_AA_SMOKE", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[3].ped, "WORLD_HUMAN_DRINKING", 0, true);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[0].ped, missionData.hostages[0].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_CHAT_TO_PED(missionData.hostages[0].ped, missionData.enemies[0].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_CHAT_TO_PED(missionData.hostages[1].ped, missionData.enemies[0].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[1].ped, missionData.hostages[2].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_USE_MOBILE_PHONE(missionData.hostages[2].ped, true, 0);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[8].ped, "WORLD_HUMAN_CHEERING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[7].ped, "WORLD_HUMAN_CHEERING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[22].ped, "WORLD_HUMAN_CHEERING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[23].ped, "WORLD_HUMAN_CHEERING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.hostages[9].ped, "WORLD_HUMAN_YOGA", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[9].ped, "WOLRD_HUMAN_BINOCULARS", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[11].ped, "WORLD_HUMAN_GUARD_STAND", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[10].ped, "WORLD_HUMAN_GUARD_STAND", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[15].ped, "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.hostages[6].ped, "WORLD_HUMAN_YOGA", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.hostages[3].ped, "WORLD_HUMAN_YOGA", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.hostages[4].ped, "WORLD_HUMAN_YOGA", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[2].ped, "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[17].ped, "WORLD_HUMAN_DRINKING", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.hostages[7].ped, "WOLRD_HUMAN_PARTYING", 0, true);
            TASK::TASK_CHAT_TO_PED(missionData.hostages[8].ped, missionData.enemies[17].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[12].ped, "WORLD_HUMAN_DRINKING", 0, true);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[13].ped, missionData.enemies[14].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[14].ped, missionData.enemies[13].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[18].ped, "WORLD_HUMAN_BINOCULARS", 0, true);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[19].ped, "WOLRD_HUMAN_SMOKING", 0, true);
            TASK::TASK_CHAT_TO_PED(missionData.enemies[20].ped, missionData.enemies[19].ped, 16, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f);
            TASK::TASK_START_SCENARIO_IN_PLACE(missionData.enemies[21].ped, "WORLD_HUMAN_AA_SMOKE", 0, true);
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
    if (PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID())) {
        Quit(true);
        return;
    }

    if (missionData.currentObjective != 2) {
        PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
        PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), false);
    }

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
                    case TonyMussolini: {
                        subtitle = "Go to the ~y~yacht~w~.";
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
                PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 3, false);
                PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), false);
                MUSIC::MidIntensityTrack();
                missionData.currentObjective = 2;
                return;
            }

            for (MissionPed& enemy : missionData.enemies) {
                enemy.Process();
            }

            if (missionData.target == TonyMussolini && missionData.helicopterAlive) {
                if (ENTITY::IS_ENTITY_DEAD(missionData.vehicles[0], true)) {
                    missionData.helicopterAlive = false;
                    Blip blip = BLIPS::GetBlipForEntity(missionData.vehicles[0]);

                    if (HUD::DOES_BLIP_EXIST(blip)) {
                        HUD::REMOVE_BLIP(&blip);
                    }

                    break;
                }

                if (missionData.helicopterStolen && MISC::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(missionData.vehicles[0], true), {3557.105f, 3919.986f, 711.1465f}, false) < 100) {
                    Quit(true);
                    SCREEN::ShowSubtitle("~r~Mission failed, a target escaped!", 8000);
                }
                else if (!missionData.helicopterStolen && PED::IS_PED_IN_COMBAT(missionData.enemies[10].ped, PLAYER::PLAYER_ID())) {
                    TASK::TASK_HELI_MISSION(missionData.enemies[10].ped, missionData.vehicles[0], 0, 0, {3557.105f, 3919.986f, 711.1465f}, 4, 50, 10, 0, -1, -1, -1, 32);
                    BLIPS::CreateForEntity(missionData.vehicles[0], BlipColorRed, BlipSpriteHelicopterAnimated, "Enemy Helicopter");
                    SCREEN::ShowSubtitle("A ~r~target ~w~is trying to escape in a ~r~helicopter~w~!", 8000);
                    missionData.helicopterStolen = true;
                }
            }
            break;
        }
        case 2: {
            SCREEN::ShowSubtitle("Lose the cops.", 100);

            if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 1) {
                Quit(false);
                return;
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

    switch (missionData.target) {
        case TonyMussolini: {
            STREAMING::REMOVE_IPL("smboat");
            STREAMING::REMOVE_IPL("apa_smboat_lodlights");
            break;
        }
    }
}

void MOST_WANTED_SIMPLE::Quit(const bool playerDied) {
    MissionState::active = false;

    if (playerDied) {
        MUSIC::StopTrack();
        MUSIC::MissionFailedSound();
    } else {
        MUSIC::MissionCompletedSound();
    }

    AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", false);

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

        SCREEN::ShowTextMessage("CHAR_LESTER", "Lester", "Wanted Suspect", "Good job, your cut of the reward is already in your account.");
    }

    ResetState();
}