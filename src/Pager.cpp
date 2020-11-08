#include "Pager.h"

std::vector<std::string> Pager::PagerKeys = {"DIAB1_A", "TONI_P", "YD_P", "HOOD1_A", "COLT_IN", "UZI_IN",
"IMPEXPP", "EMVHPUP", "VANHSTP", "PAGEB1", "PAGEB2", "PAGEB5", "PAGEB4", "PAGEB3", "PAGEB6", "PAGEB7",
"PAGEB8", "PAGEB9", "PAGEB10", "PAGEB11", "PAGEB12", "PAGEB13", "PAGEB14", "A_COMP3", "NEW_TAX", "FM4_1",
"RM6_666", "DIAB1_A"};
void __fastcall Pager::RandomizePagerMessages(CText* text, void* edx, char* key)
{
	if (Config::pager.allowSubtitlesEnabled)
	{
		if (PagerKeys.size() < 29)
			AddSubtitleKeys();
	}
	std::string newKey = PagerKeys[RandomNumber(0, PagerKeys.size() - 1)];

	memcpy(key, newKey.c_str(), newKey.size());
	key[newKey.size()] = '\0';

	text->GetText(key);
}
void Pager::AddSubtitleKeys()
{
	for (auto& key : voices::subtitles)
	{
		std::transform(key.second.begin(), key.second.end(), key.second.begin(),
			[](unsigned char c) { return std::toupper(c); });

		PagerKeys.push_back(key.second);
	}
}
void Pager::Initialise()
{
	if (Config::pager.Enabled)
		plugin::patch::RedirectCall(0x43F138, RandomizePagerMessages);
}