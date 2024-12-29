#pragma once

#include "inc/natives.h"
#include "inc/enums.h"
#include "inc/types.h"

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
	Blip CreateForEntity(Entity ped, eBlipColor color, int sprite, const char* name);
	Blip CreateForEntity(Entity ped, eBlipColor color, const char* name);
}
