#include "plugin.h"
#include "General.h"
#include "Script.h"
#include "Remote.h"
#include "Player.h"
#include "Ped.h"
#include "Parked.h"
#include "Traffic.h"
#include "Weapons.h"
#include "Colours.h"
#include "Voices.h"
#include "Pickups.h"
#include "Pager.h"
#include "Credits.h"
#include "Autosave.h"
#include "Missions.h"
#include "Cutscenes.h"
#include "Config.h"

class Rainbomizer {
public:
	Rainbomizer() {
		Config::Initialise();
		General::Initialise();
		Script::Initialise();
		Remote::Initialise();
		Parked::Initialise();
		Traffic::Initialise();
		Weapons::Initialise();
		Colours::Initialise();
		Voices::Initialise();
		Pickups::Initialise();
		Pager::Initialise();
		Player::Initialise();
		Ped::Initialise();
		Cutscenes::Initialise();
		Missions::Initialise();
		Credits::Initialise();
		Autosave::Initialise();
	}
} rainbomizer;