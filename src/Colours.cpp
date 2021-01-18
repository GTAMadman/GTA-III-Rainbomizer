#include "Colours.h"

std::vector<Colours::Pattern> Colours::Patterns;
std::vector<Colours::Pattern> Colours::PickupPatterns;
int Colours::GetColour(int pattern, int rgb)
{
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (Patterns[i].ID == pattern)
		{
			if (rgb == 0)
				return Patterns[i].colours[0];
			if (rgb == 1)
				return Patterns[i].colours[1];
			if (rgb == 2)
				return Patterns[i].colours[2];
		}
	}
	return 0;
}
int Colours::GetPickupsColour(int pattern, int rgb)
{
	for (int i = 0; i < PickupPatterns.size(); i++)
	{
		if (PickupPatterns[i].ID == pattern)
		{
			if (rgb == 0)
				return PickupPatterns[i].colours[0];
			if (rgb == 1)
				return PickupPatterns[i].colours[1];
			if (rgb == 2)
				return PickupPatterns[i].colours[2];
		}
	}
	return 0;
}
void* __fastcall Colours::RandomizeColours(CRGBA* colour, void* edx, int r, int g, int b, int a)
{
	if (Config::colours.rainbowTextEnabled)
	{
		CRGBA rainbow = GetRainbowColour(r, g, b);
		if (r != g && g != b)
		{
			colour->r = rainbow.r;
			colour->g = rainbow.g;
			colour->b = rainbow.b;
			colour->a = a;
		}
		else
		{
			colour->r = r;
			colour->g = g;
			colour->b = b;
			colour->a = a;
		}
		return colour;
	}
	else
	{
		int pattern = r + g + b;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern pat = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(pat);
		}

		if (r != g && g != b)
		{
			colour->r = GetColour(pattern, 0);
			colour->g = GetColour(pattern, 1);
			colour->b = GetColour(pattern, 2);
			colour->a = a;
		}
		else
		{
			colour->r = r;
			colour->g = g;
			colour->b = b;
			colour->a = a;
		}
		return colour;
	}
}
/* Had to put armour into it's own hooked function due to some issues with it */
void* __fastcall Colours::RandomizeMiscColours(CRGBA* colour, void* edx, int r, int g, int b, int a)
{
	if (Config::colours.rainbowTextEnabled)
	{
		CRGBA rainbow = GetRainbowColour(r, g, b);
		colour->r = rainbow.r;
		colour->g = rainbow.g;
		colour->b = rainbow.b;
		colour->a = a;
	}
	else
	{
		int pattern = r + g + b;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		colour->r = GetColour(pattern, 0);
		colour->g = GetColour(pattern, 1);
		colour->b = GetColour(pattern, 2);
		colour->a = a;

		return colour;
	}
}
void __fastcall Colours::RandomizeMarkerColours(C3dMarker* marker)
{
	CRGBA original = marker->m_colour;

	if (Config::colours.staticMarkerColours)
	{
		int pattern = marker->m_colour.r + marker->m_colour.g + marker->m_colour.b;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		marker->m_colour.r = GetColour(pattern, 0);
		marker->m_colour.g = GetColour(pattern, 1);
		marker->m_colour.b = GetColour(pattern, 2);
	}
	else
	{
		marker->m_colour = GetRainbowColour(marker->m_colour.r, marker->m_colour.g, marker->m_colour.b);
		marker->m_colour.a = original.a;
	}

	marker->Render();
	marker->m_colour = original;
}
void Colours::RandomizePickupColours(int ID, char r, char g, char b, char a, CVector& posn, float radius, 
	float farClip, char coronaType, char flareType, char refl, char obstacles, char arg12, float normalAngle)
{
	CRGBA colour;
	if (Config::colours.staticPickupColours)
	{
		int pattern = ID;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		colour.r = GetColour(pattern, 0);
		colour.g = GetColour(pattern, 1);
		colour.b = GetColour(pattern, 2);
	}
	else
	{
		int pattern = ID;
		if (GetPickupsColour(pattern, 0) == 0)
		{
			Pattern col = { pattern, {r, g, b} };
			PickupPatterns.push_back(col);
		}
		int origR = GetPickupsColour(pattern, 0);
		int origG = GetPickupsColour(pattern, 1);
		int origB = GetPickupsColour(pattern, 2);

		colour = GetRainbowColour(origR, origG, origB);
	}

	CCoronas::RegisterCorona(ID, colour.r, colour.g, colour.b, a, posn, radius, farClip, coronaType, flareType, refl, obstacles, arg12, normalAngle);
}
void Colours::RandomizeRaceMarkerColours(int ID, char r, char g, char b, char a, CVector& posn, float radius,
	float farClip, char coronaType, char flareType, char refl, char obstacles, char arg12, float normalAngle)
{
	CRGBA colour;
	if (Config::colours.staticMarkerColours)
	{
		int pattern = r + g + b;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		r = GetColour(pattern, 0);
		g = GetColour(pattern, 1);
		b = GetColour(pattern, 2);
	}
	else
	{
		static int origR = 200;
		static int origG = 0;
		static int origB = 0;

		colour = GetRainbowColour(origR, origG, origB);
	}

	CCoronas::RegisterCorona(ID, colour.r, colour.g, colour.b, a, posn, radius, farClip, coronaType, flareType, refl, obstacles, arg12, normalAngle);
}
void Colours::RandomizeExplosionColours(int ID, char r, char g, char b, char a, CVector& posn, float radius,
	float farClip, RwTexture* texture, char flareType, char refl, char obstacles, char arg12, float normalAngle)
{
	CRGBA colour;
	if (Config::colours.staticExplosionColours)
	{
		int pattern = r + g + b;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		colour.r = GetColour(pattern, 0);
		colour.g = GetColour(pattern, 1);
		colour.b = GetColour(pattern, 2);
	}
	else
		colour = GetRainbowColour(r, g, b);

	CCoronas::RegisterCorona(ID, colour.r, colour.g, colour.b, a, posn, radius, farClip, texture, flareType, refl, obstacles, arg12, normalAngle);
}
CRGBA Colours::GetRainbowColour(int r, int g, int b)
{
	CRGBA colour;
	int colours[3];

	float time = 1000.0 * clock() / CLOCKS_PER_SEC;
	int hash = (r * 255 + g) * 255 + b;
	HSVtoRGB((int)(time / 10 + hash) % 360, 0.7, 0.7, colours);

	colour.r = colours[0];
	colour.g = colours[1];
	colour.b = colours[2];

	return colour;
}
void Colours::HSVtoRGB(int H, double S, double V, int output[3])
{
	double C = S * V;
	double X = C * (1 - std::abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60)
	{
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120)
	{
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180)
	{
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240)
	{
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300)
	{
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else
	{
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	output[0] = (Rs + m) * 255;
	output[1] = (Gs + m) * 255;
	output[2] = (Bs + m) * 255;
}
void __fastcall Colours::ChooseVehicleColour(CVehicleModelInfo* thisInfo, void* edx, int* prim, int* sec)
{
	*prim = RandomNumber(0, 94);
	*sec = RandomNumber(0, 94);
}
int Colours::RandomizeColourTable()
{
	CVehicleModelInfo::LoadVehicleColours();
	for (int i = 0; i < 95; i++)
	{
		CVehicleModelInfo::ms_colourTextureTable[i].r = RandomNumber(0, 255);
		CVehicleModelInfo::ms_colourTextureTable[i].g = RandomNumber(0, 255);
		CVehicleModelInfo::ms_colourTextureTable[i].b = RandomNumber(0, 255);
	}
	// No idea why re-calling this fixes the crashes
	CVehicleModelInfo::LoadVehicleColours();

	return 0;
}
/* I've only left this in as a sort of "cheat" to get vehicle colours re-randomizing at the start of a new game */
void __fastcall Colours::ScriptVehicleColourRandomizer(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);

	CTheScripts::ScriptParams[1].iParam = RandomNumber(0, 94);
	CTheScripts::ScriptParams[2].iParam = RandomNumber(0, 94);
}
void Colours::Initialise()
{
	if (Config::colours.vehicleEnabled)
	{
		// Vehicle Colours
		plugin::patch::RedirectCall(0x48C04A, RandomizeColourTable);
		plugin::patch::RedirectJump(0x520FD0, ChooseVehicleColour);
		// Using this as a sort of workaround due to a fix
		plugin::patch::RedirectCall(0x443B1E, ScriptVehicleColourRandomizer);
	}
	if (Config::colours.textEnabled)
	{
		// Text Colours
		plugin::patch::RedirectJump(0x4F8C20, RandomizeColours);
		for (int textColourAddresses : {0x506332, 0x506BF2}) // Ammo, Faded Wanted Stars
			plugin::patch::RedirectCall(textColourAddresses, RandomizeMiscColours);
	}
	if (Config::colours.markersEnabled)
	{
		plugin::patch::RedirectCall(0x51B441, RandomizeMarkerColours);
		plugin::patch::RedirectCall(0x4448B3, RandomizeRaceMarkerColours);
	}
	if (Config::colours.pickupsEnabled)
	{
		for (int addr : {0x43196C, 0x431E7C, 0x4320FC, 0x43237C})
			plugin::patch::RedirectCall(addr, RandomizePickupColours);
	}
	if (Config::colours.explosionsEnabled)
	{
		for (int addr : {0x55A574, 0x55A5AD, 0x55A6A9, 0x55A6E2})
			plugin::patch::RedirectCall(addr, RandomizeExplosionColours);
	}
}
