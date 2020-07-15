#pragma, once
const char default_config[] =
R"(# GTA III Rainbomizer Configuration #

#####################################
# Script Vehicles Randomizer
ScriptVehiclesRandomizer = true

# Allow certain side missions to be activated by any vehicle

OffroadMissions = true # (Patriot Playground, A Ride In the Park, Multistorey Mayhem, Gripped!)
RCMissions = true # (Diablo Destruction, Mafia Massacre, Casino Calamity, Rumpo Rampage)

#####################################
# RC Vehicles Randomizer
RandomizeRCVehicles = true

#####################################
# Parked Vehicles Randomizer
ParkedVehiclesRandomizer = true

#####################################
# Colour Randomizer

RandomizeVehicleColours = true
RandomizeHUDColours = true
RandomizeMarkerColours = true

RandomizePickupColours = true
RandomizeExplosionColours = true

RainbowHUDColours = false

#####################################
# Traffic Randomizer
TrafficRandomizer = true

RandomizeRoadblocks = true

# Additional vehicles
DeadDodo = true
Train = true
AirTrain = true

#####################################
# Weapon Randomizer
WeaponRandomizer = true

###########################################
# Pickups Randomizer

# Randomizes weapons, health, armour, adrenaline, bribe star and mission pickups
# This feature is safe to use, though pickups are saved to the save file
 
PickupsRandomizer = true

# Randomizes the weapons dropped by dead peds
RandomizePedWeaponDrops = true

# Allowed pickup types
Weapons = true
Health = true
Armour = true
Adrenaline = true
Bribes = true
Briefcase = true

#####################################
# Pager Randomizer

# Randomizes the messages received through the pager
PagerRandomizer = true

# Allows any subtitle to be randomized - if false, it will only randomize from pager messages
AllowSubtitleMessages = true

#####################################
# Voice Line Randomizer
VoiceLineRandomizer = true

# Matches the subtitles to the randomized voice line
MatchSubtitles = true

#####################################
# Autosave
Autosave = true
Slot = 8)";