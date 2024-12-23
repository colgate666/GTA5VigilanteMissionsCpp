#include "pch.h"

#include "UIScript.hpp"

bool UIScript::Data::pendingNoti;
bool UIScript::Data::showScaleform;
UIScript::ScaleformType UIScript::Data::scaleformType;
std::vector<int> scaleformHandles = std::vector<int>();
int scaleformST;
bool scaleformRequested;
bool scaleformFading;

void UIScript::Clean() {
    Data::showScaleform = false;
    scaleformRequested = false;
    scaleformFading = false;

    for (const int& handle : scaleformHandles) {
        SCREEN::FreeScaleform(handle);
    }

    scaleformHandles.clear();
}

void UIScriptMain()
{
    while (DLC::GET_IS_LOADING_SCREEN_ACTIVE())
        WAIT(1);

	while (true)
	{
		if (UIScript::Data::pendingNoti)
		{
			if (CAM::IS_SCREEN_FADED_IN() && !PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()))
			{
				UIScript::Data::showScaleform = true;
				UIScript::Data::pendingNoti = false;
			}
		}

		if (UIScript::Data::showScaleform)
		{
			if (!scaleformRequested)
			{
				scaleformRequested = true;
				char title[150];
				char subtitle[100];

				switch (UIScript::Data::scaleformType)
				{
					case UIScript::ScaleformType::PLAYER_DIED: {
                        AUDIO::PLAY_SOUND_FRONTEND(-1, "Survival_Failed", "DLC_VW_AS_Sounds", true);
                        /*scaleformHandles = SCREEN::LoadWallStat(SURVIVAL::SurvivalData::earnedMoney,
                                                                SURVIVAL::SurvivalData::CurrentWave,
                                                                0,false,true,
                                                                false,false);*/
                        break;
                    }
				}

				scaleformST = MISC::GET_GAME_TIMER();
			}

            if (scaleformHandles.size() > static_cast<size_t>(1)) {
                for (const int& handle: scaleformHandles) {
                    GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(handle, 255, 255, 0, 255, 0);

                    if (MISC::GET_GAME_TIMER() - scaleformST >= 15000)
                    {
                        UIScript::Data::showScaleform = false;
                        scaleformRequested = false;
                        scaleformFading = false;
                        SCREEN::FreeScaleform(handle);
                    }
                }

                if (!UIScript::Data::showScaleform)
                    scaleformHandles.clear();
            } else {
                int handle = scaleformHandles.at(0);
                GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(handle, 255, 255, 0, 255, 0);

                if (MISC::GET_GAME_TIMER() - scaleformST >= 8000 && !scaleformFading)
                {
                    scaleformFading = true;
                    SCREEN::FadeOutScaleform(handle, 2000);
                    scaleformST = MISC::GET_GAME_TIMER();
                }
                else if (MISC::GET_GAME_TIMER() - scaleformST >= 2000 && scaleformFading)
                {
                    UIScript::Data::showScaleform = false;
                    scaleformRequested = false;
                    scaleformFading = false;
                    SCREEN::FreeScaleform(handle);
                    scaleformHandles.clear();
                }
            }
		}

		WAIT(0);
	}
}

void UIScript::ScriptMain()
{
	UIScriptMain();
}

void UIScript::OnAbort()
{
	SCREEN::UnloadSprites();
	Data::pendingNoti = false;

    for (const auto& scaleform : scaleformHandles) {
        if (scaleform != 0)
            SCREEN::FreeScaleform(scaleform);
    }
}
