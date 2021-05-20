#include "Credits.h"

std::vector<wchar_t*> lead_developers = { L"GTAMADMAN", L"PARIK" };
std::vector<wchar_t*> contributors = { L"123ROBOT", L"FRYTERP23" };
std::vector<wchar_t*> beta_testers = { L"HUGOONE", L"SPEEDYFOLF", L"VODCRACK" };

void Credits::PrintCredits(float x, float y, const wchar_t* text, int* position, float offset)
{
	plugin::Call<0x4FE620>(x, y, text, position, offset);
}
void Credits::PrintGroup(wchar_t* title, std::vector<wchar_t*> list, int* position, float offset)
{
	PrintCredits(1.1, 1.1, title, position, offset);

	for (auto item : list)
	{
		PrintCredits(1.7, 1.7, item, position, offset);
	}
	*position += 37.5;
}
void Credits::ModifyCredits(float x, float y, wchar_t* text, int* position, float offset)
{
	PrintCredits(1.7, 1.0, L"RAINBOMIZER", position, offset);
	*position += 37.5;

	PrintGroup(L"LEAD DEVELOPERS", lead_developers, position, offset);
	PrintGroup(L"CONTRIBUTORS", contributors, position, offset);
	PrintGroup(L"BETA TESTERS", beta_testers, position, offset);

	PrintCredits(1.7, 1.0, L"ROCKSTAR GAMES", position, offset);

	*position += 37.5;
	PrintCredits(x, y, text, position, offset);
}
void Credits::Initialise()
{
	if (Config::general.credits)
		plugin::patch::RedirectCall(0x4FAEEC, ModifyCredits);
}