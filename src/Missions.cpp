#include "Missions.h"
#include "plugin.h"
#include "Config.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include <map>
#include <CFileMgr.h>
#include <iostream>
#include <CFont.h>
#include <extensions/ScriptCommands.h>
#include <CPedType.h>
#include <random>
#include <fstream>

std::map<int, std::vector<Missions::MissionEndOffset>> gMissionEndOffsets
= { {15, {{4382}}},
{16, {{4704}}},
{17, {{3528}}},
{18, {{3719}}},
{19, {{15165, 15195}, {15693, 16722}, {15548, 15553}, {15439}}},
{20, {{3506}}},
{21, {{5700}}},
{22, {{1988}}},
{23, {{12927}}},
{24, {{5161, 5191}, {5245, 5252}, {5307}}},
{25, {{4673}}},
{26, {{2782, 2838}, {2847}}},
{27, {{7612, 7647}, {7810}}},
{28, {{3047}}},
{29, {{9887, 9894}, {9981}}},
{30, {{2028}}},
{31, {{2320, 2355}, {2584}}},
{32, {{8479}}},
{33, {{3892}}},
{34, {{3206}}},
{35, {{16822}}},
{36, {{8206}}},
{37, {{912}}},
{38, {{12278}}},
{39, {{4260}}},
{40, {{10326, 10352}, {10375}}},
{41, {{3435}}},
{42, {{1787}}},
{43, {{2776}}},
{44, {{18645, 18652}, {18988}}},
{45, {{3543}}},
{46, {{7186}}},
{47, {{3113}}},
{48, {{2586}}},
{49, {{4083}}},
{50, {{3478}}},
{51, {{6565}}},
{52, {{4055}}},
{53, {{12315, 12348}, {12436}}},
{54, {{3038}}},
{55, {{6285}}},
{56, {{4641}}},
{57, {{9684}}},
{58, {{3403}}},
{59, {{9079}}},
{60, {{5867}}},
{61, {{4385}}},
{62, {{3932}}},
{63, {{5680, 5727}, {5743, 5765}, {5783, 5788}}},
{64, {{4631, 4638}, {4791}}},
{65, {{1598}}},
{66, {{3406}}},
{67, {{9999}}},
{68, {{11393}}},
{69, {{2965}}},
{70, {{347}}},
{71, {{5145}}},
{72, {{7362}}},
{73, {{8201}}},
{74, {{1568}}},
{75, {{1978}}},
{76, {{2160}}},
{77, {{1364}}},
{78, {{5087}}},
{79, {{6818, 6865}, {7115}}} };

std::map<int, CVector> gMissionEndCoords
= { {15, {1189.36, -40.4975, 9.97308}}, {16, {1199.29, -787.255, 14.6357}},
{17, {1331.08, -1034.28, 14.8164}}, {18, {1214.71, -791.163, 14.6876}},
{19, {905.944, -424.867, 14.8228}}, {20, {1089.3, -577.442, 14.7335}},
{21, {1194.76, -873.102, 14.9727}}, {22, {986.887, -69.8014, 7.47254}},
{23, {999.939, -879.78, 14.5457}},  {24, {1349.98, -459.49, 50.0701}},
{25, {983.637, -756.24, 14.9727}},  {26, {1436.51, -810.011, 11.8263}},
{27, {1219.33, -328.821, 26.074}},  {28, {1188.48, -39.5632, 9.97308}},
{29, {1086.82, -224.075, 8.90723}}, {30, {812.929, -631.481, 14.4702}},
{31, {1220.02, -324.571, 26.169}},  {32, {1454.94, -188.311, 55.4429}},
{33, {948.693, -1074.14, 13.173}},  {34, {953.4178, -1134.1697, 13.173}},
{35, {1447.64, -188.018, 55.6244}}, {36, {1469.84, -891.621, 11.4162}},
{37, {1449.92, -190.721, 55.5715}}, {38, {1529.41, -881.984, 11.4131}},
{39, {511.38, -649.858, 16.1011}},  {40, {1050.61, -931.457, 14.4359}},
{41, {1286.37, -1050.17, 14.8164}}, {42, {908.851, -828.69, 14.9727}},
{43, {976.39, -443.011, 14.9734}},  {44, {886.256, -425.206, 14.917}},
{45, {419.078, -1408.07, 26.1335}}, {46, {535.0825, -648.3719, 16.2156}},
{47, {38.6844, -723.011, 22.7562}}, {48, {415.038, -1383.88, 26.1682}},
{49, {109.437, -1294.39, 26.1681}}, {50, {373.586, -507.435, 26.1748}},
{51, {427.449, -1487.1, 18.641}},   {52, {427.449, -1487.1, 18.641}},
{53, {41.6044, -880.019, 34.2102}}, {54, {333.208, -451.617, 23.0175}},
{55, {136.562, 179.578, 11.5317}},  {56, {48.2645, -1548.34, 26.0181}},
{57, {1606.01, -616.299, 12.1514}}, {58, {113.082, -56.1878, 16.0181}},
{59, {197.032, -996.545, 26.1647}}, {60, {52.3952, -1547.92, 26.1681}},
{61, {79.4832, -1548.46, 28.2945}}, {62, {79.4832, -1548.46, 28.2945}},
{63, {46.4881, 69.6748, 16.1681}},  {64, {232.056, -530.438, 25.6575}},
{65, {260.7568, -789.0242, 27.9702}}, {66, {-72.3884, -1463.71, 26.1442}},
{67, {80.9688, -1548.67, 28.2945}}, {68, {-1025.87, -73.337, 38.8984}},
{69, {53.6893, -1548.53, 26.1681}}, {70, {80.9688, -1548.67, 28.2945}},
{71, {-1184.33, 73.268, 68.7311}},  {72, {-1275.17, -108.19, 58.8301}},
{73, {372.389, -327.871, 18.235}},  {74, {-427.297, -60.7034, 3.71128}},
{75, {-680.396, 75.9628, 18.8404}}, {76, {-680.396, 75.9628, 18.8404}},
{77, {-848.162, -168.21, 33.8565}}, {78, {-236.119, 269.261, 3.48417}},
{79, {-666.75, -1.75, 18.8614}} };

std::map<int, CVector> gMissionStartCoords = {
{15, {1226.6371, -841.9783, 14.9727}}, {16, {1226.6371, -841.9783, 14.9727}},
	{17, {1226.6371, -841.9783, 14.9727}}, {18, {1226.6371, -841.9783, 14.9727}},
	{19, {811.875, -939.9375, 35.75}},     {20, {895.346, -425.75, 13.875}},
	{21, {895.346, -425.75, 13.875}},	{22, {895.346, -425.75, 13.875}},      
	{23, {895.346, -425.75, 13.875}},	{24, {1193.143, -871.367, 13.992}},
	{25, {1193.143, -871.367, 13.992}},	{26, {1193.143, -871.367, 13.992}},       
	{27, {1193.143, -871.367, 13.992}}, {28, {1193.143, -871.367, 13.992}},      
	{29, {1193.143, -871.367, 13.992}},	{30, {1219.75, -322.793, 25.933}},   
	{31, {1219.75, -322.793, 25.933}},	{32, {1219.75, -322.793, 25.933}},  
	{33, {1219.75, -322.793, 25.933}},	{34, {1219.75, -322.793, 25.933}},   
	{35, {1455.688, -189.011, 54.449}}, {36, {1455.688, -189.011, 54.449}},   
	{37, {1455.688, -189.011, 54.449}},	{38, {1272.188, -93.674, 13.75}},     
	{39, {1455.688, -189.011, 54.449}}, {40, {938.5688, -233.8231, 4.9399}}, 
	{41, {938.5688, -233.8231, 4.9399}}, {42, {938.5688, -233.8231, 4.9399}}, 
	{43, {938.5688, -233.8231, 4.9399}}, {44, {523.6875, -645.071, 15.155}},    
	{45, {523.6875, -645.071, 15.155}}, {46, {523.6875, -645.071, 15.155}},    
	{47, {523.6875, -645.071, 15.155}}, {48, {523.6875, -645.071, 15.155}},    
	{49, {457.482, -1414.902, 25.149}}, {50, {457.482, -1414.902, 25.149}},   
	{51, {457.482, -1414.902, 25.149}}, {52, {457.482, -1414.902, 25.149}},   
	{53, {457.482, -1414.902, 25.149}}, {54, {38.928, -722.7512, 22.7562}},       
	{55, {38.928, -722.7512, 22.7562}}, {56, {38.928, -722.7512, 22.7562}},       
	{57, {38.928, -722.7512, 22.7562}}, {58, {38.928, -722.7512, 22.7562}},       
	{59, {38.928, -722.7512, 22.7562}}, {60, {83.359, -1548.563, 27.313}},      
	{61, {83.359, -1548.563, 27.313}}, {62, {83.359, -1548.563, 27.313}},      
	{63, {117.4897, -271.9755, 16.1682}}, {64, {117.4897, -271.9755, 16.1682}}, 
	{65, {117.4897, -271.9755, 16.1682}}, {66, {117.4897, -271.9755, 16.1682}}, 
	{67, {83.359, -1548.563, 27.313}}, {68, {83.359, -1548.563, 27.313}},     
	{69, {83.359, -1548.563, 27.313}}, {70, {83.359, -1548.563, 27.313}},      
	{71, {369.035, -327.973, 18.462}}, {72, {369.035, -327.973, 18.462}},      
	{73, {369.035, -327.973, 18.462}}, {74, {-440.726, -6.1465, 3.8614}},  
	{75, {-440.726, -6.1465, 3.8614}}, {76, {-440.726, -6.1465, 3.8614}}, 
	{77, {-440.726, -6.1465, 3.8614}}, {78, {-440.726, -6.1465, 3.8614}},  
	{79, {-362.75, 241.802, 59.645}} };

const int SIZE_MAIN_SCRIPT = 0x20000;
bool replacedByFirstMission = false;

template<typename T = int>
T &
GetGlobalVariable(uint32_t index) {
	return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[index * 4]);
}

int Missions::GetRandomMission()
{
	if (Config::mission.forcedMission >= START_MISSIONS && Config::mission.forcedMission <= END_MISSIONS)
		mRandomizedMission = Config::mission.forcedMission;
	else
	mRandomizedMission = mMissionOrder[mOriginalMission];

	mStoreNextScript = true;
	return mRandomizedMission;
}

void __fastcall Missions::RandomizeMissionToStart(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& missionId = CTheScripts::ScriptParams[0].iParam;

	if (missionId == 0) // InitAtNewGame
		InitShuffledMissionOrder(nullptr);

	if (missionId >= START_MISSIONS && missionId <= END_MISSIONS
		&& gMissionEndOffsets.count(missionId)
		)
	{
		mOriginalMission = missionId;
		if (mOriginalMission == 19)
		{
			strcpy(CModelInfo::GetModelInfo(0)->m_szName, "player");
		}
		missionId = GetRandomMission();
		if (mRandomizedMission == 19 && mOriginalMission != 19)
		{
			GetGlobalVariable(8) = 0;
			GetGlobalVariable(245) = 0;
			GetGlobalVariable(431) = 0;
			replacedByFirstMission = true;
		}
		if (mRandomizedMission == 19 && mOriginalMission == 19 && GetGlobalVariable(8) == 1)
		{
			GetGlobalVariable(8) = 0;
			GetGlobalVariable(431) = 0;
		}
		if (mRandomizedMission == 29)
			CClock::SetGameClock(7, 0);

		std::cout << "Storing mission: " << missionId
			<< std::endl;

		try
		{
			TeleportPlayer(gMissionStartCoords.at(
				mRandomizedMission), GetIslandFromMission(missionId));
		}
		catch (...)
		{
		}
		StoreGangThreatStates();
		SetGangHostilityBasedOnNewMission(missionId);
		mLastOriginalMissionStarted = mOriginalMission;
	}
}

CRunningScript* Missions::StoreRandomizedScript(uint32_t ip)
{
	CRunningScript* sc = plugin::CallAndReturn<CRunningScript*, 0x439000>(ip);
	if (std::exchange(mStoreNextScript, false)) {
		mRandomizedScript = sc;
		mPostReplaceEndOffsets = gMissionEndOffsets[mOriginalMission];
		mPreReplaceEndOffsets = gMissionEndOffsets[mRandomizedMission];
		std::cout << "Storing randomized script" << std::endl;
	}

	return sc;
}

bool Missions::ProcessPreReplaceMissionEndOffsets(CRunningScript* thread, short opcode)
{
	if (mScriptReplaced)
		return false;

	for (int i = 0; i < mPreReplaceEndOffsets.size(); i++)
	{
		auto it = mPreReplaceEndOffsets[i];
		if (thread->m_nIp - SIZE_MAIN_SCRIPT == it.Start)
		{
			thread->m_nIp = it.End + SIZE_MAIN_SCRIPT;

			if (i == mPreReplaceEndOffsets.size() - 1)
				return true;

			continue;
		}
	}

	return false;
}

bool Missions::ProcessPostReplaceMissionEndOffsets(CRunningScript* thread, uint16_t& opcode)
{
	if (!mScriptReplaced)
		return false;

	if (opcode == eScriptCommands::COMMAND_RETURN ||
		thread->m_nIp - SIZE_MAIN_SCRIPT == mPostReplaceEndOffsets.front().End)
	{
		mPostReplaceEndOffsets.erase(mPostReplaceEndOffsets.begin());

		if (!mPostReplaceEndOffsets.size())
		{
			opcode = eScriptCommands::COMMAND_RETURN;
			thread->ProcessOneCommand();

			return true;
		}
		else
			thread->m_nIp = mPostReplaceEndOffsets.front().Start + SIZE_MAIN_SCRIPT;
	}
	return false;
}

void Missions::RestoreOriginalScriptForCleanup()
{
	memcpy((char*)& CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		mTempMissionData.get(),
		SIZE_MISSION_SCRIPT);

	mScriptReplaced = false;
	mRandomizedScript = nullptr;
}

void Missions::HandleEndThreadOpcode(CRunningScript* thread, short opcode)
{
	if (opcode != eScriptCommands::COMMAND_TERMINATE_THIS_SCRIPT)
		return;

	if (GetGlobalVariable(246) == 1)
	{
		if (mOriginalMission == 19 && mRandomizedMission != 19 && mRandomizedScript != nullptr)
		{
			GetGlobalVariable(246) = 0;
			plugin::Command<eScriptCommands::COMMAND_RESTART_CRITICAL_MISSION>(
				811.875, -939.9375, 35.75, 180.0);
			plugin::Command<eScriptCommands::COMMAND_OVERRIDE_NEXT_RESTART>(
				811.875, -939.9375, 35.75, 180.0);
		}

		if (mOriginalMission == 19 && mRandomizedMission == 38 && GetGlobalVariable(6) == 0)
			plugin::Command<eScriptCommands::COMMAND_ADD_SCORE>(CWorld::PlayerInFocus, 100000);
	}

	if (mRandomizedMission == 19 && mOriginalMission != 19)
	{
		GetGlobalVariable(245) = 1;
		replacedByFirstMission = false;
	}

	if (mOriginalMission != 19 && mOriginalMission != 38 && mRandomizedMission == 38
		&& GetGlobalVariable(275) == 1 && GetGlobalVariable(6) == 0)
	{
		TeleportPlayer(gMissionStartCoords.at(
			mOriginalMission), GetIslandFromMission(mOriginalMission));
	}

	ResetGangThreatStates();
	mRandomizedScript = nullptr;
}

bool Missions::ShouldJump(CRunningScript* thread)
{
	int currentOffset = thread->m_nIp - SIZE_MAIN_SCRIPT;

	uint16_t& opcode = *reinterpret_cast<uint16_t*> (
		&CTheScripts::ScriptSpace[thread->m_nIp]);

	if (ProcessPostReplaceMissionEndOffsets(thread, opcode))
		RestoreOriginalScriptForCleanup();

	HandleEndThreadOpcode(thread, opcode);

	return ProcessPreReplaceMissionEndOffsets(thread, opcode);
}

void Missions::MoveScriptToOriginalOffset(CRunningScript* thread)
{
	int* missionOffsets = (int*)0x6F0558;

	memcpy(mTempMissionData.get(),
		(char*)& CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		SIZE_MISSION_SCRIPT);

	int offset = missionOffsets[mOriginalMission];
	CFileMgr::ChangeDir("\\");
	int handle = CFileMgr::OpenFile("data\\main.scm", "rb");
	CFileMgr::Seek(handle, offset, 0);
	CFileMgr::Read(handle, (char*)& CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT], SIZE_MISSION_SCRIPT);
	CFileMgr::CloseFile(handle);

	TeleportPlayerAfterMission();
	ResetGangThreatStates();
	FixEndOfMissions();
	mLastOriginalMissionStarted = -1;

	thread->m_nIp = mPostReplaceEndOffsets.front().Start + SIZE_MAIN_SCRIPT;
	mScriptReplaced = true;
}

void Missions::TeleportPlayerAfterMission()
{
	try
	{
		TeleportPlayer(gMissionEndCoords.at(mOriginalMission), GetIslandFromMission(mOriginalMission));
	}
	catch (...) {}
}

char __fastcall Missions::JumpOnMissionEnd(CRunningScript* thread)
{
	if (mRandomizedScript == thread && ShouldJump(thread))
		MoveScriptToOriginalOffset(thread);

	return thread->ProcessOneCommand();
}

void Missions::LoadMissionData(uint8_t* data, uint32_t size)
{
	CPedType::Load(data, size);
	SaveStructure* save
		= reinterpret_cast<SaveStructure*> (
			data + size - sizeof(SaveStructure));

	if (std::string(save->signature, 11) != "RAINBOMIZER")
		return InitShuffledMissionOrder(nullptr);
	return InitShuffledMissionOrder(save);
}

void Missions::InitShuffledMissionOrder(Missions::SaveStructure* structure)
{
	uint32_t seed = RandomNumber(INT_MIN, INT_MAX);
	if (structure)
		seed = structure->randomSeed;

	if (!structure && Config::mission.usingSeed)
		seed = std::hash<std::string>{}(Config::mission.seed);

	std::mt19937 engine{ seed };
	std::uniform_int_distribution<int> d(START_MISSIONS, END_MISSIONS);

	mMissionOrder.Reset();
	for (int i = START_MISSIONS; i <= END_MISSIONS; i++)
		std::swap(mMissionOrder[i], mMissionOrder[d(engine)]);

	mSaveStructure.randomSeed = seed;
}

void Missions::MissionOrder::Reset()
{
	for (int i = 0; i < TOTAL_MISSIONS; i++)
		Missions[i] = START_MISSIONS + i;
}

void Missions::SaveMissionData(uint8_t* data, uint32_t& outSize)
{
	CPedType::Save(data, &outSize);

	memcpy(data + outSize, &mSaveStructure, sizeof(SaveStructure));
	outSize += sizeof(SaveStructure);
}

void __fastcall Missions::FixWalkingAfterChaperone(CPed* ped, void* edx, eObjective obj, float x, int a4, int a5)
{
	plugin::CallMethod<0x4D8A90>(ped, obj, x, a4, a5);

	if (ped == FindPlayerPed() && x == 1436.25 &&
		CTheScripts::pActiveScripts->m_szName == std::string("frank1"))
	{
		FindPlayerPed()->SetObjective(eObjective::OBJECTIVE_NONE);
	}
}
void __fastcall Missions::FixRemovingExchangeMoney(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int money = CTheScripts::ScriptParams[1].iParam;

	// Only remove the player money if the original mission is The Exchange
	if (mRandomizedMission == 79 && mOriginalMission != 79 &&
		script->m_szName == std::string("cat1") && money == -500000)
	{
		CTheScripts::ScriptParams[1].iParam = 0;
	}
}
char* __fastcall Missions::FixSAMLastMissionName(CText* text, void* edx, char* key)
{
	if (key == std::string("CAT2") && mRandomizedMission == 79 && mOriginalMission != 79)
	{
		std::string newKey = "AS3";

		memcpy(key, newKey.c_str(), newKey.size());
		key[newKey.size()] = '\0';

		injector::WriteMemory<int>(0x74B808, 0);
		return text->GetText(key);
	}
	return text->GetText(key);
}
void __fastcall Missions::FixGiveMeLibertyMovement(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	bool movementSetting = CTheScripts::ScriptParams[1].iParam;

	if (mRandomizedMission == 19 && mOriginalMission != 19 &&
		script->m_szName == std::string("eight") && movementSetting == 1)
	{
		injector::WriteMemory<int>(0x95CD95, 1);
		CCutsceneMgr::DeleteCutsceneData();
		FindPlayerPed()->SetObjective(eObjective::OBJECTIVE_NONE);
		CPad::GetPad(CWorld::PlayerInFocus)->Clear(true);
	}
}
void Missions::BlockExtraText(wchar_t* message, int time, short flag)
{
	if (mRandomizedMission != 19 || (mRandomizedMission == 19 && mOriginalMission == 19) ||
		!replacedByFirstMission)
	{
		CMessages::AddBigMessage(message, time, flag);
	}
	else
	{
		replacedByFirstMission = false;
	}
}
void Missions::OpenPortlandSafehouseDoor()
{
	for (int i = 0; i < 21; i++)
		plugin::Command<eScriptCommands::COMMAND_ROTATE_OBJECT>(1025, 210.0, 10.0, 0);
}
void Missions::ShouldOverrideRestart(CVector& point, float angle)
{
	if (mOriginalMission == 19)
		CRestart::OverrideNextRestart(point, angle);
}
void __fastcall Missions::ShouldRestartCritical(CPlayerInfo* player)
{
	if (mOriginalMission == 19)
		player->PlayerFailedCriticalMission();
}
void Missions::FixEndOfMissions()
{
	if (mOriginalMission == 79)
		PlayRandomRadioStation();

	if (mRandomizedMission == 79)
	{
		CCutsceneMgr::DeleteCutsceneData();
		plugin::CallMethod<0x46B3A0>(&TheCamera, 1500, 1);
		FindPlayerPed()->SetObjective(eObjective::OBJECTIVE_NONE);
	}

	if (mOriginalMission == 19 && mRandomizedMission != 19)
		plugin::Command<eScriptCommands::COMMAND_CANCEL_OVERRIDE_RESTART>();

	if (mRandomizedMission == 19)
		OpenPortlandSafehouseDoor();
}
void __fastcall Missions::RemoveCarCubes(CPathFind* path, void* edx, float x1, float y1,
	float z1, float x2, float y2, float z2, char a3)
{
	if (!ShouldRemoveCarCube(x1, x2))
		plugin::CallMethod<0x42D960>(path, x1, y1, z1, x2, y2, z2, a3);
}

void __fastcall Missions::UnlockBridges(CBuilding* building, void* edx, int modelId)
{
	if (ShouldBuildingBeReplaced(building->m_nModelIndex, modelId))
		building->ReplaceWithNewModel(modelId);
}
void Missions::RemoveObjects(CEntity* entity)
{
	/* The Portland Subway Gate still gets added for some
	reason, so I just move it under the ground :P */
	if (entity->m_nModelIndex == 1280)
		entity->GetPosition().z -= 10;

	if (!ShouldObjectBeRemoved(entity->m_nModelIndex))
		CWorld::Add(entity);
}
void Missions::UnlockShoresideBridge()
{
	if (CStats::CommercialPassed != 1)
		CStats::CommercialPassed = 1;

	CBridge::Update();
}
bool Missions::ShouldRemoveCarCube(float x1, float x2)
{
	if (x1 == 619.5625 && x2 == -911.5)
		return true;

	if (x1 == 659.5625 && x2 == 200.0)
		return true;

	if (x1 == 529.5625 && x2 == 106.5)
		return true;

	if (x1 == 484.0 && x2 == 75.5)
		return true;

	if (x1 == -69.0625 && x2 == -614.0)
		return true;

	return false;
}
bool Missions::ShouldObjectBeRemoved(int model)
{
	int objects[] = { 1299, 1281, 855 };

	for (const int& obj : objects)
	{
		if (model == obj)
			return true;
	}
	return false;
}
bool Missions::ShouldBuildingBeReplaced(int origModel, int newModel)
{
	if (origModel == 855 && newModel == 218)
		return true;

	if (origModel == 419 && newModel == 418)
		return true;

	if (origModel == 952 && newModel == 218)
		return true;

	if (origModel == 1033 && newModel == 218)
		return true;

	if (origModel == 1332 && newModel == 1331)
		return true;

	if (origModel == 1331 && newModel == 1332)
		return true;

	if (origModel == 408 && newModel == 400)
		return true;

	return false;
}
void Missions::StoreGangThreatStates()
{
	gang_threats.mafia = CPedType::ms_apPedType[7]->m_Threat.bPlayer1;
	gang_threats.triads = CPedType::ms_apPedType[8]->m_Threat.bPlayer1;
	gang_threats.diablos = CPedType::ms_apPedType[9]->m_Threat.bPlayer1;
	gang_threats.yakuza = CPedType::ms_apPedType[10]->m_Threat.bPlayer1;
	gang_threats.yardies = CPedType::ms_apPedType[11]->m_Threat.bPlayer1;
	gang_threats.colombians = CPedType::ms_apPedType[12]->m_Threat.bPlayer1;
	gang_threats.hoods = CPedType::ms_apPedType[13]->m_Threat.bPlayer1;
}
void Missions::ResetGangThreatStates()
{
	SetGangHostility(gang_threats.mafia, gang_threats.triads, gang_threats.diablos,
		gang_threats.yardies, gang_threats.yakuza, gang_threats.hoods, gang_threats.colombians);
}
void Missions::SetGangHostility(int mafia, int triads, int diablos, int yardies, int yakuza, int hoods, int colombians)
{
	CPedType::ms_apPedType[7]->m_Threat.bPlayer1 = mafia;
	CPedType::ms_apPedType[8]->m_Threat.bPlayer1 = triads;
	CPedType::ms_apPedType[9]->m_Threat.bPlayer1 = diablos;
	CPedType::ms_apPedType[10]->m_Threat.bPlayer1 = yakuza;
	CPedType::ms_apPedType[11]->m_Threat.bPlayer1 = yardies;
	CPedType::ms_apPedType[12]->m_Threat.bPlayer1 = colombians;
	CPedType::ms_apPedType[13]->m_Threat.bPlayer1 = hoods;
}
void Missions::SetGangHostilityBasedOnNewMission(int mission)
{
	if (GetIslandFromMission(mission) == eLevelName::PORTLAND)
		SetGangHostility(0, 0, 0, gang_threats.yardies);

	if (GetIslandFromMission(mission) == eLevelName::STAUNTON_ISLAND)
		SetGangHostility(gang_threats.mafia,
			gang_threats.triads, gang_threats.diablos, 0);
}
void Missions::DoGameSpecificStuffAfterSucessLoad()
{
	plugin::Call<0x591A20>();

	if (FindPlayerPed())
		TeleportPlayer(FindPlayerPed()->GetPosition(), eLevelName::GENERIC);
}
void __fastcall Missions::FixSalvatoresGarage(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	if (script->m_szName == std::string("toni3"))
		CGarages::ChangeGarageType(CTheScripts::ScriptParams[0].iParam, 21, 0);
}
void Missions::FindClosestHospitalRestartPoint(CVector& point, CVector* storedPoint, float* angle)
{
	if (mLastOriginalMissionStarted != -1)
		if (gMissionStartCoords.count(mLastOriginalMissionStarted))
			point = gMissionStartCoords[mLastOriginalMissionStarted];

	CRestart::FindClosestHospitalRestartPoint(point, storedPoint, angle);
}
void Missions::FindClosestPoliceRestartPoint(CVector& point, CVector* storedPoint, float* angle)
{
	if (mLastOriginalMissionStarted != -1)
		if (gMissionStartCoords.count(mLastOriginalMissionStarted))
			point = gMissionStartCoords[mLastOriginalMissionStarted];

	CRestart::FindClosestPoliceRestartPoint(point, storedPoint, angle);
}
eLevelName Missions::GetIslandFromMission(int mission)
{
	if (mission >= 15 && mission <= 43)
		return eLevelName::PORTLAND;

	if (mission >= 44 && mission <= 73)
		return eLevelName::STAUNTON_ISLAND;

	if (mission >= 74 && mission <= 79)
		return eLevelName::SHORESIDE_VALE;

	return eLevelName::GENERIC;
}
void Missions::Initialise()
{
	if (Config::mission.Enabled)
	{
		plugin::patch::RedirectCall(0x588DE8, RandomizeMissionToStart);
		plugin::patch::RedirectCall(0x588E47, StoreRandomizedScript);
		plugin::patch::RedirectCall(0x439485, JumpOnMissionEnd);
		plugin::patch::RedirectCall(0x591883, LoadMissionData);
		plugin::patch::RedirectCall(0x59087A, SaveMissionData);

		plugin::patch::RedirectCall(0x44E72A, UnlockBridges);
		plugin::patch::RedirectCall(0x44FD27, UnlockBridges);
		plugin::patch::RedirectCall(0x453E80, UnlockBridges);
		plugin::patch::RedirectCall(0x444F02, RemoveObjects);
		plugin::patch::RedirectCall(0x4A297B, RemoveObjects);
		plugin::patch::RedirectCall(0x47899C, RemoveObjects);
		plugin::patch::RedirectCall(0x4787FE, RemoveObjects);
		plugin::patch::RedirectCall(0x48C9CD, UnlockShoresideBridge);

		plugin::patch::RedirectCall(0x44265A, RemoveCarCubes);
		plugin::patch::RedirectCall(0x44327A, FixWalkingAfterChaperone);
		plugin::patch::RedirectCall(0x43DF22, FixRemovingExchangeMoney);
		plugin::patch::RedirectCall(0x447FBD, FixSAMLastMissionName);
		plugin::patch::RedirectCall(0x441152, FixGiveMeLibertyMovement);
		plugin::patch::RedirectCall(0x43D0A8, BlockExtraText);
		plugin::patch::RedirectCall(0x44371C, FixSalvatoresGarage);
		plugin::patch::RedirectCall(0x5918E5, DoGameSpecificStuffAfterSucessLoad);
		plugin::patch::RedirectCall(0x42159D, FindClosestHospitalRestartPoint);
		plugin::patch::RedirectCall(0x4217BA, FindClosestPoliceRestartPoint);
		plugin::patch::RedirectCall(0x421966, FindClosestPoliceRestartPoint);

		plugin::patch::RedirectCall(0x43FDFC, ShouldOverrideRestart);
		plugin::patch::RedirectCall(0x444A7D, ShouldOverrideRestart);
		plugin::patch::RedirectCall(0x444AAD, ShouldRestartCritical);

		mTempMissionData = std::make_unique<unsigned char[]>(SIZE_MISSION_SCRIPT);
		mLocalVariables = std::make_unique<unsigned int[]>(16);
	}
}