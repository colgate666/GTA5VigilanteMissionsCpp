#pragma once

#include "SHV SDK/natives.h"
#include "SHV SDK/enums.h"
#include "SHV SDK/types.h"

namespace BLIPS
{
    Blip Create(float x, float y, float z, int sprite, eBlipColor color, const char* name);
	Blip CreateObjectiveBlip(const Vector3& position, const char* name);
	void CreateForEnemyPed(Ped ped);
	void CreateForEnemyVehicle(Vehicle vehicle);
	Blip GetBlipForEntity(Entity entity);
	void DeleteBlipForEntity(Entity entity);
	void CreateForEnemyPed(Ped ped, int sprite, const char* name);
	void SetBlipName(Blip blip, const char* name);
}
