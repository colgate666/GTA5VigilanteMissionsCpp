#include "pch.h"

#include "RandomMission.h"

#include <unordered_set>
#include <vector>
#include "SHV SDK/main.h"

enum eLocationType
{
    Foot,
    Car
};

static const std::vector<Vector3> LOCATIONS_FOOT = {
    Vector3(958.3557f, -141.5549f, 75.50748f),
    Vector3(1164.845f, -334.2931f, 69.74226f),
    Vector3(1214.709f, -420.8012f, 68.62407f),
    Vector3(1155.659f, -473.3027f, 67.51048f),
    Vector3(788.7799f, -738.5971f, 28.53819f),
    Vector3(415.7993f, -804.9828f, 30.36194f),
    Vector3(-115.3424f, -426.6558f, 36.8196f),
    Vector3(-318.0066f, 224.781f, 88.75639f),
    Vector3(-235.7711f, 276.5725f, 93.04496f),
    Vector3(439.0587f, 133.8473f, 101.1775f),
    Vector3(432.2224f, 225.0025f, 104.1669f),
    Vector3(-686.5708f, 273.3582f, 82.44141f),
    Vector3(-1223.188f, -264.502f, 39.41944f),
    Vector3(-1096.87f, -801.2212f, 19.64473f),
    Vector3(-1227.51f, -1171.697f, 8.635307f),
    Vector3(-841.7546f, -1204.689f, 7.395357f),
    Vector3(157.1279f, -967.2166f, 31.09192f),
    Vector3(237.4271f, -390.4071f, 47.30567f),
    Vector3(66.69101f, 113.9236f, 80.11262f),
    Vector3(-564.027f, 327.2527f, 85.40903f),
    Vector3(-219.9077f, -1957.957f, 27.75663f),
    Vector3(-325.6057f, -1462.222f, 30.51306f),
    Vector3(-172.0509f, -1436.433f, 31.2634f),
    Vector3(-105.1376f, -1094.589f, 26.06644f),
    Vector3(-63.15568f, -1107.807f, 26.32477f),
    Vector3(-208.8304f, -631.2042f, 48.22083f),
    Vector3(-175.8562f, -156.3028f, 43.62122f),
    Vector3(325.5165f, -211.5939f, 54.08629f),
    Vector3(458.5976f, -753.1367f, 27.35779f),
    Vector3(423.4489f, -1286.861f, 30.25341f),
    Vector3(286.4246f, -1584.264f, 30.53215f),
    Vector3(102.1467f, -1943.0f, 20.80371f),
    Vector3(-1020.126f, -2701.373f, 13.75664f),
    Vector3(-1641.421f, -1108.605f, 13.02085f),
    Vector3(-1836.245f, -1219.252f, 13.01726f),
    Vector3(-1820.584f, -862.6905f, 4.100582f),
    Vector3(-1660.969f, -900.475f, 8.538025f),
    Vector3(-1296.6f, -1501.365f, 4.344109f),
    Vector3(-1165.643f, -1514.781f, 4.383816f),
    Vector3(-331.8909f, -911.0989f, 31.08062f),
    Vector3(-739.7289f, -66.36839f, 41.75113f),
    Vector3(-844.1396f, -108.4216f, 28.18535f),
    Vector3(-425.4473f, 1128.7f, 325.8547f),
    Vector3(-105.5424f, 911.351f, 236.1674f),
    Vector3(958.9243f, -1742.755f, 31.12148f),
    Vector3(1208.936f, -1756.755f, 39.63063f),
    Vector3(971.1397f, -1457.827f, 31.34114f),
    Vector3(987.2574f, -1409.128f, 31.26411f),
    Vector3(264.4848f, -1278.07f, 29.16894f),
    Vector3(-231.7598f, -1165.854f, 22.90478f),
    Vector3(-603.5284f, -877.6115f, 25.35468f),
    Vector3(-931.6569f, -796.4459f, 15.92116f),
    Vector3(-1378.364f, 47.46008f, 53.68186f),
    Vector3(-1237.991f, 485.7172f, 93.16705f),
    Vector3(-1888.959f, 2028.161f, 140.7174f),
    Vector3(-2551.821f, 2322.683f, 33.05998f),
    Vector3(-3156.103f, 1068.687f, 20.67572f),
    Vector3(-2980.058f, 75.9231f, 11.6085f),
    Vector3(-2202.769f, 4261.527f, 47.83957f),
    Vector3(-212.3218f, 6198.221f, 31.48867f),
    Vector3(160.8905f, 6618.127f, 31.92143f),
    Vector3(1688.108f, 4780.192f, 41.92149f),
    Vector3(1660.526f, 4827.077f, 42.01349f),
    Vector3(1711.821f, 3761.432f, 34.20344f),
    Vector3(1420.286f, 3621.922f, 34.87617f),
    Vector3(1992.391f, 3768.693f, 32.1808f),
    Vector3(2488.09f, 4116.335f, 38.0647f),
    Vector3(2499.898f, 4086.932f, 38.37713f),
    Vector3(2752.527f, 3456.097f, 55.94258f),
    Vector3(2704.049f, 3447.708f, 55.80101f),
    Vector3(1998.903f, 3060.598f, 47.04928f),
    Vector3(1210.369f, 2702.171f, 38.00581f),
    Vector3(1177.054f, 2653.476f, 37.93536f),
    Vector3(1123.178f, 2655.729f, 37.99691f),
    Vector3(1050.356f, 2667.707f, 39.55112f),
    Vector3(616.5576f, 2734.069f, 42.01853f)
};

static const std::vector<Vector3> LOCATIONS_VEHICLE = {
    Vector3(-1326.338f, 5136.826f, 61.98092f),
    Vector3(-337.7497f, 6069.629f, 31.73389f),
    Vector3(-180.8488f, 6465.757f, 31.20587f),
    Vector3(172.2699f, 6579.066f, 32.53137f),
    Vector3(1727.338f, 6398.668f, 35.22195f),
    Vector3(2547.849f, 5319.684f, 44.95111f),
    Vector3(2544.552f, 2621.24f, 38.3621f),
    Vector3(2666.361f, 1673.555f, 25.20385f),
    Vector3(2580.545f, 441.4199f, 109.0808f),
    Vector3(408.2307f, -2070.269f, 21.63659f),
    Vector3(-86.95599f, -2115.876f, 17.26918f),
    Vector3(-556.7122f, -2136.262f, 6.531339f),
    Vector3(-1187.478f, -1495.184f, 5.097012f),
    Vector3(-1651.682f, -923.522f, 9.012685f),
    Vector3(-1476.117f, -501.9565f, 33.09459f),
    Vector3(-188.0657f, -149.6397f, 44.20177f),
    Vector3(230.8618f, -789.9957f, 30.94275f),
    Vector3(-195.1992f, 282.343f, 93.2417f),
    Vector3(-1394.672f, 58.78949f, 54.4501f),
    Vector3(-1949.325f, -335.7829f, 46.1995f),
    Vector3(208.6546f, 226.1538f, 105.6051f),
    Vector3(100.5251f, -20.41864f, 68.01024f),
    Vector3(61.86081f, -301.5036f, 47.17083f),
    Vector3(467.2407f, -532.9135f, 35.98397f),
    Vector3(423.3599f, -607.2281f, 28.49987f),
    Vector3(323.2897f, -850.3389f, 29.34249f),
    Vector3(501.5409f, -994.3605f, 27.74894f),
    Vector3(531.5969f, -1036.542f, 37.50127f),
    Vector3(726.5676f, -1190.626f, 44.8922f),
    Vector3(573.3943f, -1428.351f, 29.6075f),
    Vector3(190.251f, -1774.328f, 29.17102f),
    Vector3(-64.03038f, -2054.813f, 21.7747f),
    Vector3(-90.87307f, -2020.987f, 18.01695f),
    Vector3(-405.5422f, -1809.907f, 21.50559f),
    Vector3(-581.2361f, -1956.833f, 27.20109f),
    Vector3(-710.875f, -2122.791f, 42.36239f),
    Vector3(-713.8049f, -1950.05f, 27.14961f),
    Vector3(-983.3277f, -2616.08f, 13.8295f),
    Vector3(-1170.747f, -1460.43f, 4.957169f),
    Vector3(-1213.78f, -1197.595f, 7.694859f),
    Vector3(-1156.907f, -825.1862f, 14.44065f),
    Vector3(-1394.662f, -579.5674f, 30.26363f),
    Vector3(-1554.632f, -326.2013f, 46.85171f),
    Vector3(-1786.169f, 90.07755f, 76.46387f),
    Vector3(-1612.345f, 375.1869f, 89.97917f),
    Vector3(-1882.838f, 699.646f, 128.3672f),
    Vector3(-2010.467f, 705.9418f, 145.5211f),
    Vector3(-2621.259f, 1127.152f, 162.2988f),
    Vector3(-2302.596f, 449.2766f, 174.4667f),
    Vector3(-1998.635f, -162.3358f, 29.56968f),
    Vector3(-2022.341f, -476.3376f, 11.368f),
    Vector3(-2182.905f, -337.427f, 13.20371f),
    Vector3(-2526.534f, -193.4347f, 19.31018f),
    Vector3(-3025.761f, 105.4377f, 11.62844f),
    Vector3(-3106.848f, 1096.672f, 20.47231f),
    Vector3(-3024.62f, 1874.819f, 29.89819f),
    Vector3(-2545.359f, 1906.313f, 168.9719f),
    Vector3(-1898.068f, 2016.655f, 140.9769f),
    Vector3(-1593.878f, 2352.143f, 43.58834f),
    Vector3(-1142.753f, 2662.476f, 18.0209f),
    Vector3(-516.3898f, 2840.728f, 33.98786f),
    Vector3(847.5055f, 2846.733f, 58.57842f),
    Vector3(1211.186f, 2715.805f, 38.00459f),
    Vector3(1230.549f, 2684.057f, 37.6313f),
    Vector3(2052.189f, 3018.868f, 45.46199f),
    Vector3(2254.444f, 3194.383f, 48.69269f),
    Vector3(2642.698f, 3116.496f, 49.37523f),
    Vector3(2623.745f, 3129.004f, 49.28777f),
    Vector3(2757.665f, 3450.729f, 55.9211f),
    Vector3(2429.007f, 3963.394f, 36.57501f),
    Vector3(2486.238f, 4118.029f, 38.0647f),
    Vector3(1800.934f, 4586.852f, 37.10669f),
    Vector3(78.46184f, 3627.929f, 39.6853f),
    Vector3(337.3323f, 3422.375f, 36.39695f),
    Vector3(748.8038f, 3595.673f, 32.978f),
    Vector3(-2201.213f, 4261.719f, 47.933f)
};

static const std::vector<Vector3> FLEECA_LOCATIONS = {
    Vector3(-2969.897f, 483.3021f, 14.46835f),
    Vector3(-349.3697f, -44.89134f, 48.04182f),
    Vector3(314.4158f, -281.3477f, 54.16473f),
    Vector3(-1215.664f, -325.0962f, 36.68665f),
    Vector3(151.6956f, -1035.145f, 28.33931f),
    Vector3(1175.124f, 2701.105f, 37.17781f)
};

static const auto PACIFIC_LOCATION = Vector3(224.4161f, 208.0313f, 104.5419f);

static auto BANK_ROBBER_NAME = "MP_G_M_Pros_01";

static const std::vector<const char*> CRIMINALS = {
    "G_M_M_ArmGoon_01",
    "G_M_Y_MexGang_01",
    "G_M_Y_MexGoon_01",
    "G_M_Y_PoloGoon_01",
    "G_M_Y_SalvaGoon_01",
    "A_M_Y_MethHead_01",
    "A_M_M_Hillbilly_01",
    "G_F_Y_Lost_01",
    "G_M_Y_Lost_01",
    "S_M_Y_Robber_01",
    "G_M_M_ChiGoon_01"
};

static const std::vector<const char*> VICTIMS = {
    "A_F_Y_Vinewood_01",
    "A_M_Y_Vinewood_01",
    "A_F_Y_Vinewood_04",
    "A_F_M_Tourist_01",
    "A_F_Y_Tourist_01",
    "S_F_Y_Hooker_01",
    "A_F_Y_Hipster_01",
    "A_F_Y_Hipster_03",
    "A_M_Y_Hipster_02",
    "A_M_Y_Hiker_01",
    "A_M_Y_Runner_01",
    "A_F_M_FatWhite_01"
};

static const std::vector<const char*> VEHICLES = {
    "zentorno",
    "sultanrs",
    "sultan",
    "sentinel",
    "sabregt",
    "phoenix",
    "pfister811",
    "penumbra",
    "cyclone",
    "ruiner",
    "jb700",
    "cheetah",
    "comet2",
    "banshee",
    "bullet"
};

static const std::vector<const char*> BANK_HOSTAGES = {
    "A_F_Y_Vinewood_04",
    "A_M_Y_Vinewood_04",
    "S_F_M_Fembarber",
    "IG_Old_Man2",
    "U_M_M_BankMan",
    "A_F_Y_Vinewood_01",
    "A_F_Y_Vinewood_02",
    "A_M_Y_Vinewood_01",
    "S_M_M_Security_01"
};

static const std::vector<const char*> BANK_POLICE = {
    "S_M_Y_Swat_01",
    "MP_M_FIBSec_01"
};

static const std::vector<const char*> BANK_VEHICLES = {
    "RIOT",
    "FBI",
    "FBI2"
};

struct MissionData {
    RANDOM_MISSION::eMissionType missionType;
    int currentObjective = 0;
    int currentBank = 0;
    Blip objectiveBlip = 0;
    Vector3 objectiveLocation;
    std::vector<MissionPed> enemies = {};
    std::vector<MissionPed> hostages = {};
    std::vector<Vehicle> vehicles = {};
};

auto missionData = MissionData();

Vector3 GetRandomLocation(const eLocationType type) {
    if (type == Foot) {
        return LOCATIONS_FOOT[MISC::GET_RANDOM_INT_IN_RANGE(0, LOCATIONS_FOOT.size() - 1)];
    }

    return LOCATIONS_VEHICLE[MISC::GET_RANDOM_INT_IN_RANGE(0, LOCATIONS_VEHICLE.size() - 1)];
}

const char* GetRandomModel(const std::vector<const char*>& models) {
    return models[MISC::GET_RANDOM_INT_IN_RANGE(0, models.size() - 1)];
}

Ped CreateMissionEntity(const std::vector<const char*>& modelPool, const Vector3& location) {
    const char* modelName = GetRandomModel(modelPool);
    const Hash model = MISC::GET_HASH_KEY(modelName);

    STREAMING::REQUEST_MODEL(model);

    while (!STREAMING::HAS_MODEL_LOADED(model)) {
        WAIT(1);
    }

    const Vector3 approximateLocation = VECTORS::Around(location, 2);
    const Ped ped = PED::CREATE_PED(0, model, approximateLocation.x, approximateLocation.y, approximateLocation.z, 0, false, true);

    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

    return ped;
}

Ped CreateVictim(const Vector3 &location) {
    return CreateMissionEntity(VICTIMS, location);
}

Ped CreateCriminal(const Vector3& location) {
    return CreateMissionEntity(CRIMINALS, location);
}

Vehicle CreateVehicle(const Vector3& location) {
    const char* modelName = GetRandomModel(VEHICLES);
    const Hash model = MISC::GET_HASH_KEY(modelName);

    STREAMING::REQUEST_MODEL(model);

    while (!STREAMING::HAS_MODEL_LOADED(model)) {
        WAIT(1);
    }

    const Vector3 approximateLocation = VECTORS::Around(location, 2);
    const Vehicle vehicle = VEHICLE::CREATE_VEHICLE(model, approximateLocation.x, approximateLocation.y, approximateLocation.z, 0, false, true, false);

    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

    return vehicle;
}

std::vector<Ped> CreateGroupOfCriminals(const Vector3& location) {
    const int groupSize = MISC::GET_RANDOM_INT_IN_RANGE(4, 13);

    std::vector<Ped> peds;
    std::unordered_set<Hash> models = {};

    peds.reserve(groupSize);

    for (size_t c = 0; c < groupSize; c++) {
        const char* modelName = GetRandomModel(CRIMINALS);
        const Hash model = MISC::GET_HASH_KEY(modelName);

        if (!models.contains(model)) {
            models.insert(model);

            STREAMING::REQUEST_MODEL(model);

            while (!STREAMING::HAS_MODEL_LOADED(model)) {
                WAIT(1);
            }
        }

        const Vector3 approximateLocation = VECTORS::Around(location, 5);
        const Ped ped = PED::CREATE_PED(0, model, approximateLocation.x, approximateLocation.y, approximateLocation.z, 0, false, true);

        peds.push_back(ped);
    }

    for (const Hash& model : models) {
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
    }

    return peds;
}

void InitFleecaPeds() {
    const Hash bankRobberModel = MISC::GET_HASH_KEY(BANK_ROBBER_NAME);
    const Hash firstHostage = MISC::GET_HASH_KEY(GetRandomModel(BANK_HOSTAGES));
    const Hash secondHostage = MISC::GET_HASH_KEY(GetRandomModel(BANK_HOSTAGES));

    STREAMING::REQUEST_MODEL(bankRobberModel);
    STREAMING::REQUEST_MODEL(firstHostage);
    STREAMING::REQUEST_MODEL(secondHostage);

    while (!STREAMING::HAS_MODEL_LOADED(bankRobberModel) || !STREAMING::HAS_MODEL_LOADED(firstHostage) || !STREAMING::HAS_MODEL_LOADED(secondHostage)) {
        WAIT(1);
    }

    switch (missionData.currentBank) {
        case 0: {
            Ped ped = PED::CREATE_PED(26, bankRobberModel, -2964.18f, 481.0777f, 15.69693f, 30, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -2963.857f, 484.278f, 15.697f, 126, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -2958.51f, 477.1414f, 15.69691f, 26, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -2957.031f, 480.7106f, 15.70944f, 9.649f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -2964.271f, 477.429f, 15.69697f, -7.861f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));

            ped = PED::CREATE_PED(26, firstHostage, -2960.853f, 481.0599f, 15.69693f, 95.13f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            ped = PED::CREATE_PED(26, secondHostage, -2960.613f, 483.9062f, 15.69703f, 94.10f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            break;
        }
        case 1: {
            Ped ped = PED::CREATE_PED(26, bankRobberModel, -348.1603f, -49.06974f, 49.03651f, 48.98949f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -352.2792f, -47.55939f, 49.03641f, -66.99968f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -355.5144f, -47.00598f, 49.03641f, -103.9994f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -357.8593f, -52.98608f, 49.0364f, -49.93279f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -353.8931f, -54.31932f, 49.04078f, -91.17307f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));

            ped = PED::CREATE_PED(26, firstHostage, -350.4429f, -51.97402f, 49.03652f, -3.043174f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            ped = PED::CREATE_PED(26, secondHostage, -352.5433f, -51.1286f, 49.03647f, 1.822526f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            break;
        }
        case 2: {
            Ped ped = PED::CREATE_PED(26, bankRobberModel, 311.6597f, -276.2448f, 54.1646f, -74.00441f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 316.7694f, -278.3633f, 54.16472f, 30.99782f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 307.5851f, -281.2281f, 54.16462f, -51.94263f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 309.4192f, -276.0536f, 54.16466f, -101.5581f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 310.9105f, -283.3813f, 54.17715f, -102.6255f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));

            ped = PED::CREATE_PED(26, firstHostage, 314.4158f, -281.3477f, 54.16473f, 21.91808f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            ped = PED::CREATE_PED(26, secondHostage, 312.0094f, -280.3156f, 54.16463f, -7.192459f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            break;
        }
        case 3: {
            Ped ped = PED::CREATE_PED(26, bankRobberModel, -1215.184f, -330.0213f, 37.78087f, -15.79769f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -1211.406f, -328.4123f, 37.78097f, 66.99969f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -1217.893f, -331.9763f, 37.78086f, -48.88696f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -1215.417f, -337.4013f, 37.78086f, -5.066119E-07f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, -1211.546f, -336.2029f, 37.79304f, -33.99992f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));

            ped = PED::CREATE_PED(26, firstHostage, -1210.526f, -331.9603f, 37.78099f, 36.9999f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            ped = PED::CREATE_PED(26, secondHostage, -1212.919f, -333.1217f, 37.78091f, 17.99998f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            break;
        }
        case 4: {
            Ped ped = PED::CREATE_PED(26, bankRobberModel, 152.3929f, -1039.924f, 29.36801f, 47.60934f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 147.5129f, -1038.305f, 29.36789f, -73.00114f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 143.2488f, -1043.078f, 29.3679f, -42.98598f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 145.0282f, -1037.781f, 29.36794f, -92.99951f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 146.5712f, -1045.173f, 29.38041f, -110.8552f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));

            ped = PED::CREATE_PED(26, firstHostage, 147.9353f, -1042.076f, 29.36794f, 0.0002265055f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            ped = PED::CREATE_PED(26, secondHostage, 149.421f, -1042.728f, 29.36801f, 1.072878f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            break;
        }
        default: {
            Ped ped = PED::CREATE_PED(26, bankRobberModel, 1173.477f, 2705.483f, 38.08796f, -119.4031f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 1177.076f, 2705.032f, 38.08787f, 120.9997f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 1180.469f, 2705.364f, 38.08789f, 79.99958f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 1180.707f, 2711.697f, 38.08786f, 104.9145f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));
            ped = PED::CREATE_PED(26, bankRobberModel, 1176.749f, 2711.792f, 38.10051f, 83.0192f, false, true);
            missionData.enemies.push_back(MissionPed(ped, RELATIONSHIP_MISSION_AGGRESSIVE, false, false));

            ped = PED::CREATE_PED(26, firstHostage, 1175.03f, 2708.574f, 38.08796f, 170.949f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            ped = PED::CREATE_PED(26, secondHostage, 1176.591f, 2708.643f, 38.08788f, -166.713f, false, true);
            missionData.hostages.push_back(MissionPed(ped, RELATIONSHIP_MISSION_PEDESTRIAN, true, false));
            break;
        }
    }

    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(bankRobberModel);
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(firstHostage);
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(secondHostage);
}

void SpawnMissionPeds() {
    switch (missionData.missionType) {
        case RANDOM_MISSION::FleecaBankRobbery: {
            InitFleecaPeds();

            for (const MissionPed& enemy : missionData.enemies) {
                PED::SET_PED_ACCURACY(enemy.ped, 65);
                PED::SET_PED_ARMOUR(enemy.ped ,100);
                PED::SET_PED_COMBAT_MOVEMENT(enemy.ped, 1);
                enemy.ShowBlip("Bank Robber");
                TASK::TASK_START_SCENARIO_IN_PLACE(enemy.ped, "WORLD_HUMAN_STAND_IMPATIENT", 0, true);
            }

            for (const MissionPed& hostage : missionData.hostages) {
                TASK::TASK_HANDS_UP(hostage.ped, 1800000, 0, -1, false);
                PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(hostage.ped, true);
            }
            break;
        }
    }
}

void RemoveDeadEnemies() {
    for (size_t i = 0; i < missionData.enemies.size(); i++)
    {
        const MissionPed enemy = missionData.enemies.at(i);

        if (!PED::IS_PED_DEAD_OR_DYING(enemy.ped, 1))
        {
            continue;
        }

        if (!PED::CAN_PED_RAGDOLL(enemy.ped))
        {
            PED::SET_PED_CAN_RAGDOLL(enemy.ped, true);
        }

        enemy.RemoveBlip();

        missionData.enemies.erase(missionData.enemies.begin() + i);
        break;
    }
}

void ResetState() {
    for (MissionPed& enemy : missionData.enemies) {
        enemy.Delete();
    }

    for (MissionPed& hostage : missionData.hostages) {
        hostage.Delete();
    }

    for (Vehicle& vehicle : missionData.vehicles) {
        ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);
    }

    missionData.enemies.clear();
    missionData.hostages.clear();
    missionData.vehicles.clear();
    missionData.currentBank = 0;
    missionData.currentObjective = 0;
}

void RANDOM_MISSION::Start(const eMissionType type) {
    missionData.missionType = type;
    missionData.currentObjective = 0;
    const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID());

    switch (missionData.missionType) {
        case FleecaBankRobbery: {
            missionData.currentBank = MISC::GET_RANDOM_INT_IN_RANGE(0, 5);

            do {
                missionData.objectiveLocation = FLEECA_LOCATIONS[missionData.currentBank];
            } while (SYSTEM::VDIST2(missionData.objectiveLocation.x, missionData.objectiveLocation.y, missionData.objectiveLocation.z, playerCoords.x, playerCoords.y, playerCoords.z) <= 200);

            break;
        }
    }

    missionData.objectiveBlip = BLIPS::CreateObjectiveBlip(missionData.objectiveLocation, "Crime Scene");
}

void RANDOM_MISSION::Process() {
    switch (missionData.currentObjective) {
        case 0: {
            if (const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID()); SYSTEM::VDIST2(missionData.objectiveLocation.x, missionData.objectiveLocation.y, missionData.objectiveLocation.z, playerCoords.x, playerCoords.y, playerCoords.z) <= 200) {
                SpawnMissionPeds();
                missionData.currentObjective = 1;
            } else {
                SCREEN::ShowSubtitle("Go to the ~y~crime scene~w~.", 1000);
            }

            break;
        }
        case 1: {
            RemoveDeadEnemies();

            if (missionData.enemies.size() > 0) {
                return;
            }


            break;
        }
    }
}
