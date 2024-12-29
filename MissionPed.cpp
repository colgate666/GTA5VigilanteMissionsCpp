#include "pch.h"

#include <array>
#include "MissionPed.h"

constexpr std::array<const char*, 9> SCENARIOS = {
    "WORLD_HUMAN_SMOKING",
    "WORLD_HUMAN_GUARD_STAND",
    "WORLD_HUMAN_DRINKING",
    "WORLD_HUMAN_AA_SMOKE",
    "WORLD_HUMAN_STAND_IMPATIENT",
    "WORLD_HUMAN_DRUG_DEALER",
    "WORLD_HUMAN_STAND_MOBILE",
    "WORLD_HUMAN_STAND_MOBILE_UPRIGHT",
    "PATROL"
};

eWeapon GetRandomWeapon() {
    switch (MISC::GET_RANDOM_INT_IN_RANGE(1, 11)) {
        case 1:
            return WeaponAPPistol;
        case 2:
            return WeaponSpecialCarbine;
        case 3:
            return WeaponMicroSMG;
        case 4:
            return WeaponAssaultRifle;
        case 5:
            return WeaponPumpShotgun;
        case 6:
            return WeaponMG;
        case 7:
            return WeaponSMG;
        case 8:
            return WeaponSawnOffShotgun;
        case 9:
            return WeaponBullpupRifle;
        case 10:
            return WeaponCombatPistol;
        default:
            return WeaponPistol;
    }
}

MissionPed::MissionPed(const Ped ped, Hash relGroup, const bool civilian, const bool track): isFollowing(false), isInScenario(false), timerStarted(false), timerStart(0) {
    this->ped = ped;
    this->track = !civilian && track && PED::GET_RELATIONSHIP_BETWEEN_PEDS(this->ped, PLAYER::PLAYER_PED_ID()) == RelationshipNeutral;
    this->originalPosition = ENTITY::GET_ENTITY_COORDS(ped, true);
    this->originalRotation = ENTITY::GET_ENTITY_HEADING(ped);

    if (civilian) {
        return;
    }

    WEAPON::GIVE_WEAPON_TO_PED(this->ped, WeaponMicroSMG, 500, false, true);
    WEAPON::GIVE_WEAPON_TO_PED(this->ped, GetRandomWeapon(), 500, false, true);
    PED::SET_PED_ACCURACY(this->ped, 6);
}

void MissionPed::Process() {
    if (!this->track) {
        return;
    }

    if (IsDead() || PED::IS_PED_IN_COMBAT(this->ped, PLAYER::PLAYER_PED_ID())) {
        this->track = false;
        return;
    }

    const Vector3 pedCoords = ENTITY::GET_ENTITY_COORDS(this->ped, true);
    const Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);

    if (!this->isFollowing && SYSTEM::VDIST2(pedCoords, playerCoords) <= 8.5f) {
        Hash currentWeapon;

        if (const bool gotWeapon = WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &currentWeapon, true); gotWeapon && currentWeapon != WeaponUnarmed) {
            this->track = false;
            TASK::CLEAR_PED_TASKS(this->ped);
            TASK::TASK_COMBAT_PED(this->ped, PLAYER::PLAYER_PED_ID(), 0, 16);
            return;
        }

        AUDIO::PLAY_PED_AMBIENT_SPEECH_NATIVE(this->ped, "GENERIC_INSULT_MED", "SPEECH_PARAMS_STANDARD", true);
        TASK::CLEAR_PED_TASKS(this->ped);
        TASK::TASK_GOTO_ENTITY_AIMING(this->ped, PLAYER::PLAYER_PED_ID(), 4, 25);
        this->isFollowing = true;
        this->isInScenario = false;
        this->timerStarted = true;
        this->timerStart = MISC::GET_GAME_TIMER();
    }
    else if (this->isFollowing && SYSTEM::VDIST2(pedCoords, playerCoords) >= 12) {
        TASK::CLEAR_PED_TASKS(this->ped);
        const char* scenario = SCENARIOS[MISC::GET_RANDOM_INT_IN_RANGE(0, 8)];
        TASK::TASK_START_SCENARIO_AT_POSITION(this->ped, scenario, this->originalPosition, this->originalRotation, -1, false, false);
        this->isInScenario = true;
        this->isFollowing = false;
        this->timerStarted = false;
    }

    if (this->isFollowing && this->timerStarted && MISC::GET_GAME_TIMER() - this->timerStart > 5000) {
        this->track = false;
        TASK::CLEAR_PED_TASKS(this->ped);
        TASK::TASK_COMBAT_PED(this->ped, PLAYER::PLAYER_PED_ID(), 0, 16);
    }
}

void MissionPed::GiveRandomScenario() const {
    if (const char* scenario = SCENARIOS[MISC::GET_RANDOM_INT_IN_RANGE(0, 8)]; scenario == "PATROL") {
        TASK::TASK_GUARD_CURRENT_POSITION(this->ped, 15, 10, true);
    } else {
        TASK::TASK_START_SCENARIO_IN_PLACE(this->ped, scenario, 0, true);
    }
}

void MissionPed::Delete() {
    this->track = false;
    ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&this->ped);
}

bool MissionPed::IsDead() const {
    return PED::IS_PED_DEAD_OR_DYING(this->ped, true);
}

void MissionPed::ShowBlip(const char* name, eBlipSprite sprite) const {
    BLIPS::CreateForEnemyPed(this->ped, sprite, name);
}

void MissionPed::RemoveBlip() const {
    BLIPS::DeleteBlipForEntity(this->ped);
}

