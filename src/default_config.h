#pragma, once
const char default_config[] =
R"(# GTA III Rainbomizer Configuration #

###########################################
# General Configuration

DisableReplays = false
ModifyCredits = true
EnableEasterEggs = true

###########################################
# Script Vehicles Randomizer
ScriptVehiclesRandomizer = true

# Allow certain side missions to be activated by any vehicle

OffroadMissions = true # (Patriot Playground, A Ride In the Park, Multistorey Mayhem, Gripped!)
RCMissions = true # (Diablo Destruction, Mafia Massacre, Casino Calamity, Rumpo Rampage)

# Force a script vehicle
ForcedScriptVehicle = 0

###########################################
# RC Vehicles Randomizer
RandomizeRCVehicles = true

###########################################
# Parked Vehicles Randomizer
ParkedVehiclesRandomizer = true

# Force a parked vehicle
ForcedParkedVehicle = 0

###########################################
# Colour Randomizer

# Vehicles
RandomizeVehicleColours = true

# HUD
RandomizeHUDColours = true
RainbowHUDColours = false

# Markers
RandomizeMarkerColours = true
StaticMarkerColours = false

# Pickups
RandomizePickupColours = true
StaticPickupColours = false

# Explosions
RandomizeExplosionColours = true
StaticExplosionColours = false

###########################################
# Traffic Randomizer
TrafficRandomizer = true

RandomizeRoadblocks = true

# Vehicle types allowed to spawn in traffic
EnableCars = true
EnableBoats = true
EnableDodo = true
EnableRCBandit = true

# Additional vehicles
EnableDeadDodo = true
EnableTrain = true
EnableAirTrain = true

# Force a traffic vehicle
ForcedTrafficVehicle = 0

###########################################
# Weapon Randomizer
WeaponRandomizer = true

# Gives the player random weapons
RandomizePlayerWeapons = true

# Gives the player random weapons for rampages
RandomizeRampageWeapons = true

# Force a weapon
ForcedWeapon = 0

###########################################
# Pickups Randomizer

# Randomizes weapons, health, armour, adrenaline, bribe star and mission pickups
# This feature is safe to use, though pickups are saved to the save file
 
PickupsRandomizer = true

# Randomizes the weapons dropped by dead peds
RandomizePedWeaponDrops = true

# Allowed pickup types
EnableWeapons = true
EnableHealth = true
EnableArmour = true
EnableAdrenaline = true
EnableBribes = true
EnableBriefcase = true

# Randomize a small amount of money given by a briefcase pickup
MoneyInBriefcase = true

# Enter your own seed - if empty, the seed will be random
PickupsCustomSeed = ""

# Force a pickup
ForcedPickup = 0

###########################################
# Cutscene Randomizer
CutsceneRandomizer = true

###########################################
# Player Randomizer
PlayerRandomizer = true

RandomizePlayerOutfits = true
IncludeSpecialModels = true

# Force a player model
ForcedPlayerModel = ""

###########################################
# Ped Randomizer
PedRandomizer = true

# Randomizes generic peds on the streets, in vehicles and some missions
RandomizeGenericPeds = true

# Randomizes cops on the streets, in vehicles and at roadblocks
RandomizeCopPeds = true

# Force a ped model
ForcedPedModel = -1

###########################################
# Mission Randomizer
MissionRandomizer = true

# Enter your own seed - if empty, the seed will be random
MissionCustomSeed = ""

# Force a specific mission
ForcedMission = 0

###########################################
# Pager Randomizer

# Randomizes the messages received through the pager
PagerRandomizer = true

# Allows any subtitle to be randomized - if false, it will only randomize from pager messages
AllowSubtitleMessages = true

###########################################
# Voice Line Randomizer
VoiceLineRandomizer = true

# Matches the subtitles to the randomized voice line
MatchSubtitles = true

###########################################
# Autosave
Autosave = true
Slot = 8)";