#include "voices.h"

static int GetRandomizedMissionAudioSfx (const char* name)
{
	const int STREAMED_SOUND_MISSION_LIB_A1 = 0x5F;
	const int STREAMED_SOUND_MISSION_C1 = 0xC3;

	return RandomNumber(STREAMED_SOUND_MISSION_LIB_A1,
			    STREAMED_SOUND_MISSION_C1);
}

void voices::Initialise()
{
	if (Config::VoiceLineRandomizer::Enabled)
		plugin::patch::RedirectCall(0x57955D, GetRandomizedMissionAudioSfx);
}
