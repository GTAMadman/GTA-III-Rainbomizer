#include "voices.h"
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <cctype>

struct MissionAudioData
{
	char* SoundName;
	uint32_t SoundId;
};


std::unordered_map<std::string, std::string> subtitles{{
	{"lib_a1", "ebal_a"},  {"lib_a2", "ebal_a1"}, {"lib_a", "ebal_b"},
	{"lib_b", "ebal_d"},   {"lib_c", "ebal_g"},  {"lib_d", "lm1_9"},
	{"l2_a", "lm3_5"},     {"j4t_1", "jm4_10"},  {"j4t_2", "jm4_11"},
	{"j4t_3", "jm4_12"},   {"j4t_4", "jm4_13"},  {"j4_a", "jm4_6"},
	{"j4_b", "jm4_2"},     {"j4_c", "jm4_3"},    {"j4_d", "jm4_4"},
	{"j4_e", "jm4_5"},     {"j4_f", "jm4_5"},    {"j6_a", "jm6_1"},
	{"j6_b", "jm6_2"},     {"j6_c", "jm6_3"},    {"s1_a", "fm1_q"},
	{"s1_a1", "fm1_q1"},   {"s1_b", "fm1_r"},    {"s1_c", "fm1_s"},
	{"s1_c1", "fm1_s1"},   {"s1_d", "fm1_t"},    {"s1_e", "fm1_u"},
	{"s1_f", "fm1_v"},     {"s1_g", "fm1_w"},    {"s1_h", "fm1_ss"},
	{"s1_i", "fm1_tt"},    {"s1_j", "fm1_x"},    {"s1_k", "fm1_y"},
	{"s1_l", "fm1_aa"},    {"s3_a", "fm3_8i"},   {"mf1_a", "mea1_b4"},
	{"mf2_a", "mea3_b4"},  {"mf3_a", "mea4_b4"}, {"mf3_b", "mea4_b5"},
	{"mf3_b1", "mea4_b7"}, {"mf3_c", "mea4_b6"}, {"a4_a", "am4_1a"},
	{"a4_b", "am4_1b"},    {"a4_c", "am4_1c"},   {"a4_d", "am4_1d"},
	{"k3_a", "km3_7"},     {"r2_a", "rm2_e"},    {"r2_b", "rm2_e1"},
	{"r2_c", "rm2_f"},     {"r2_d", "rm2_f1"},   {"r2_e", "rm2_k"},
	{"r2_f", "rm2_l"},     {"r2_g", "rm2_m"},    {"r2_h", "rm2_n"},
	{"r6_a", "rm6_1"},     {"r6_a1", "rm6_2"},   {"r6_b", "rm6_3"},
	{"yd2_a", "yd2_c"},    {"yd2_b", "yd2_d"},   {"yd2_c", "yd2_cc"},
	{"yd2_c1", "yd2_e"},   {"yd2_d", "yd2_m"},   {"yd2_e", "yd2_f"},
	{"yd2_f", "yd2_g1"},   {"yd2_g", "yd2_g2"},  {"yd2_h", "yd2_h"},
	{"yd2_ass", "yd2_n"},  {"yd2_ok", "yd2_l"},  {"h5_a", "hm5_1"},
	{"h5_b", "hm5_5"},     {"h5_c", "hm5_6"},    {"c_1", "cat2_j"},
}};

MissionAudioData* MissionAudioNameSfxAssoc = (MissionAudioData*) 0x607094;

const int STREAMED_SOUND_MISSION_LIB_A1 = 0x5F;
const int STREAMED_SOUND_MISSION_C1 = 0xC3;

int voices::GetRandomizedMissionAudioSfx (const char* name)
{	
	int sound = Functions::RandomNumber(STREAMED_SOUND_MISSION_LIB_A1,
				 STREAMED_SOUND_MISSION_C1);

	char* newName = MissionAudioNameSfxAssoc
		[sound - STREAMED_SOUND_MISSION_LIB_A1].SoundName;

	std::string subtitle = subtitles.count(name) ? subtitles[name] : name;
	std::transform(subtitle.begin(), subtitle.end(), subtitle.begin(),
		       [](unsigned char c){ return std::tolower(c); });
	
	voiceLines[subtitle] = newName;
	if (subtitles.count(newName))
		voiceLines[subtitle] = subtitles[newName];
	
	return sound;
}

char* __fastcall voices::FixSubtitles(CText* text, void* edx, char* key)
{
	std::string _key = key;
	std::transform(_key.begin(), _key.end(), _key.begin(),
		       [](unsigned char c){ return std::tolower(c); });
		
	if (voiceLines.count(_key)) {
		std::string newKey = voiceLines[_key];
		std::transform(newKey.begin(), newKey.end(), newKey.begin(),
		       [](unsigned char c){ return std::toupper(c); });
		memcpy(key, newKey.c_str(), newKey.size());
		key[newKey.size()] = '\0';
	}
	
	return plugin::CallMethodAndReturn<char*, 0x52C5A0, CText *>(text, key);
}
void voices::Initialise()
{
	if (Config::VoiceLineRandomizer::Enabled)
		{
			plugin::patch::RedirectCall(0x57955D, GetRandomizedMissionAudioSfx);
			plugin::patch::RedirectCall(0x43D119, voices::FixSubtitles);
		}
}

std::unordered_map<std::string, std::string> voices::voiceLines;
