#include "pch.h"
#include "Blip.hpp"

void BLIPS::SetBlipName(const Blip blip, const char* name)
{
	HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(name);
	HUD::END_TEXT_COMMAND_SET_BLIP_NAME(blip);
}

Blip BLIPS::Create(const float x, const float y, const float z, const int sprite, const eBlipColor color, const char *name) {
    const Blip blipHandle = HUD::ADD_BLIP_FOR_COORD(x, y, z);
    HUD::SET_BLIP_SPRITE(blipHandle, sprite);
    HUD::SET_BLIP_COLOUR(blipHandle, color);
    SetBlipName(blipHandle, name);
    HUD::SET_BLIP_AS_SHORT_RANGE(blipHandle, true);

    return blipHandle;
}

Blip BLIPS::CreateObjectiveBlip(const Vector3 &position, const char *name) {
	const Blip blipHandle = HUD::ADD_BLIP_FOR_COORD(position.x, position.y, position.z);
	HUD::SET_BLIP_COLOUR(blipHandle, BlipColorYellow);
	SetBlipName(blipHandle, name);
	HUD::SET_BLIP_AS_SHORT_RANGE(blipHandle, true);
	HUD::SET_BLIP_ROUTE(blipHandle, true);

	return blipHandle;
}


void BLIPS::CreateForEnemyPed(const Ped ped)
{
	const Blip blipHandle = HUD::ADD_BLIP_FOR_ENTITY(ped);

	HUD::SET_BLIP_SCALE(blipHandle, 0.7f);
	HUD::SET_BLIP_SPRITE(blipHandle, BlipSpriteEnemy);
	HUD::SET_BLIP_COLOUR(blipHandle, BlipColorRed);
	SetBlipName(blipHandle, "Wanted Criminal");
}

void BLIPS::CreateForEnemyPed(const Ped ped, const int sprite, const char* name)
{
	const Blip blipHandle = HUD::ADD_BLIP_FOR_ENTITY(ped);
	HUD::SET_BLIP_SPRITE(blipHandle, sprite);
	HUD::SET_BLIP_SCALE(blipHandle, 0.8f);
	HUD::SET_BLIP_COLOUR(blipHandle, BlipColorRed);
	SetBlipName(blipHandle, name);
}

void BLIPS::CreateForEnemyVehicle(const Vehicle vehicle)
{
	Blip blipHandle = HUD::ADD_BLIP_FOR_ENTITY(vehicle);
	Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);

	if (VEHICLE::IS_THIS_MODEL_A_CAR(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, BlipSpritePersonalVehicleCar);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_BIKE(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, BlipSpritePersonalVehicleBike);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_HELI(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, BlipSpriteHelicopterAnimated);
	}
	else if (VEHICLE::IS_THIS_MODEL_A_PLANE(model))
	{
		HUD::SET_BLIP_SPRITE(blipHandle, BlipSpritePlane);
	} else if (VEHICLE::IS_THIS_MODEL_A_BOAT(model))
    {
        HUD::SET_BLIP_SPRITE(blipHandle, BlipSpriteBoat);
    }

	HUD::SET_BLIP_SCALE(blipHandle, 0.8f);
	HUD::SET_BLIP_COLOUR(blipHandle, BlipColorRed);
	SetBlipName(blipHandle, "Enemy vehicle");
}

Blip BLIPS::GetBlipForEntity(const Entity entity)
{
	return HUD::GET_BLIP_FROM_ENTITY(entity);
}

void BLIPS::DeleteBlipForEntity(const Entity entity)
{
	Blip blip = GetBlipForEntity(entity);
	HUD::REMOVE_BLIP(&blip);
}
