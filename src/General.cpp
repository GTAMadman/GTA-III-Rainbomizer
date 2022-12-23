#include "General.h"

char* aWelcomeToLiber = reinterpret_cast<char*>(0x5FC5D8);
char* aFollow1ForLong = reinterpret_cast<char*>(0x5FC6DC);
char* aGta3OutNow___ = reinterpret_cast<char*>(0x5FC898);
char* aAppearingInSho = reinterpret_cast<char*>(0x5FC8F8);
char* aHttpRockstarga = reinterpret_cast<char*>(0x5FCF4C);
char* aWww_rockstar_0 = reinterpret_cast<char*>(0x5FCF88);
char* aWww_rockstarga = reinterpret_cast<char*>(0x5FCFC0);

std::vector<std::string> credits = { "GTA MADMAN", "PARIK", "123ROBOT", "FRYTERP23",
"HUGO ONE", "SPEEDYFOLF", "VOD CRACK" };

void General::Initialise()
{
	if (Config::general.easterEggs)
	{
		memcpy(aWelcomeToLiber, "WELCOME TO RAINBOMIZER CITY . . .   ", 37);
		memcpy(aGta3OutNow___, "GTA3 RAINBOMIZER V2.1   OUT NOW . . . ", 39);
		memcpy(aHttpRockstarga, "WWW.RAINBOMIZER.COM    ", 24);
		memcpy(aWww_rockstar_0, "WWW.RAINBOMIZER.COM    ", 24);
		memcpy(aWww_rockstarga, "WWW.RAINBOMIZER.COM    ", 24);

		std::string follow = "FOLLOW " + credits[RandomNumber(0, credits.size() - 1)]
			+ " FOR LONG AND SHORT TERM PARKING  ";
		std::string appearing = "APPEARING IN SHOP SOON, )" 
			+ credits[RandomNumber(0, credits.size() - 1)] + "), WITH THEIR NEW ALBUM, )IS THAT MY DAUGHTER?) ";

		memcpy(aFollow1ForLong, follow.c_str(), follow.size());
		memcpy(aAppearingInSho, appearing.c_str(), appearing.size());
	}

	if (Config::general.replays)
		plugin::patch::Nop(0x48C975, 5);
}