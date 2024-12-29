#include "pch.h"

#include "Music.hpp"

void MUSIC::StopTrack()
{
    AUDIO::TRIGGER_MUSIC_EVENT("MP_MC_STOP");
}

void MUSIC::StartTrack()
{
    AUDIO::TRIGGER_MUSIC_EVENT("BIKER_SYG_START");
}

void MUSIC::LowIntensityTrack()
{
    AUDIO::TRIGGER_MUSIC_EVENT("BIKER_SYG_CALM");
}

void MUSIC::MidIntensityTrack()
{
    AUDIO::TRIGGER_MUSIC_EVENT("BIKER_SYG_ATTACKED");
}

void MUSIC::HighIntensityTrack()
{
    AUDIO::TRIGGER_MUSIC_EVENT("BIKER_DEFEND_CRASH_DEAL_DELIVERING");
}

void MUSIC::MissionCompletedSound()
{
    AUDIO::TRIGGER_MUSIC_EVENT("MP_DM_COUNTDOWN_KILL");
}

void MUSIC::MissionFailedSound()
{
    AUDIO::PLAY_SOUND_FRONTEND(-1, "Survival_Failed", "DLC_VW_AS_Sounds", true);
}
