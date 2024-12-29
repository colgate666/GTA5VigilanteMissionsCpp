#pragma once

#include "inc/natives.h"
#include "inc/types.h"
#include "inc/enums.h"
#include "Blip.hpp"

struct MissionPed {
private:
    Vector3 originalPosition;
    float originalRotation;
    bool isFollowing;
    bool isInScenario;
    bool timerStarted;
    bool track;
    int timerStart;
public:
    Ped ped;

    MissionPed(Ped ped, Hash relGroup, bool civilian, bool track);
    void Process();
    void GiveRandomScenario() const;
    void Delete();
    bool IsDead() const;
    void ShowBlip(const char* name = "Wanted Criminal", eBlipSprite sprite = BlipSpriteEnemy) const;
    void RemoveBlip() const;
};
