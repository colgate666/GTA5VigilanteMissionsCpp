#pragma once

#include "inc/main.h"
#include "inc/natives.h"
#include "Screen.hpp"

namespace UIScript
{
    enum class ScaleformType: int {
        PLAYER_DIED
    };

	struct Data
	{
		static bool showScaleform;
		static ScaleformType scaleformType;
		static bool pendingNoti;
	};

    void Clean();
	void ScriptMain();
	void OnAbort();
}
