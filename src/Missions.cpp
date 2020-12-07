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
#include <CWaterCannons.h>

std::map<int, std::vector<Missions::MissionEndOffset>> gMissionEndOffsets
	= {{15, {{4382}}},
	{16, {{4704}}},
	{17, {{3528}}},
	{18, {{3719}}},
	{20, {{3506}}},
	{21, {{5700}}},
	{22, {{1988}}},
	{23, {{12927}}},
	{24, {{5161, 5191}, {5307}}},
	{25, {{4673}}},
	{26, {{2782, 2838}, {2847}}},
	{28, {{3047}}},
	{30, {{2028}}},
	{32, {{8479}}},
	{33, {{3892}}},
	{34, {{3206}}},
	{36, {{8206}}},
	{37, {{912}}},
	{38, {{12278}}},
	{40, {{10326, 10352}, {10375}}},
	{41, {{3435}}},
	{42, {{1787}}},
	{43, {{2776}}},
	{45, {{3543}}},
	{46, {{7186}}},
	{47, {{3113}}},
	{48, {{2586}}},
	{49, {{4083}}},
	{50, {{3478}}},
	{51, {{6565}}},
	{52, {{4055}}},
	{54, {{3038}}},
	{56, {{4641}}},
	{57, {{9684}}},
	{58, {{3403}}},
	{59, {{9079}}},
	{60, {{5867}}},
	{61, {{4385}}},
	{62, {{3932}}},
	{63, {{5680}}},
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
	{79, {{6818}}},
	{19, {{15165, 15195}, {15439}, {15693}}},
	{27, {{7612, 7647}, {7810}}},
	{29, {{9887, 9894}, {9981}}},
	{31, {{2320, 2355}, {2584}}},
	{35, {{16822}}},
	{39, {{4260}}},
	{44, {{18645, 18652}, {18988}}},
	{53, {{12315}}},
	{64, {{4664, 4668}, {4791}}}};

std::map<int, CVector> gMissionEndCoords
	= {{15, {1189.36, -40.4975, 9.97308}}, {16, {1199.29, -787.255, 14.6357}},
	{17, {1331.08, -1034.28, 14.8164}}, {18, {1214.71, -791.163, 14.6876}},
	{19, {905.944, -424.867, 14.8228}}, {20, {1089.3, -577.442, 14.7335}},
	{21, {1194.76, -873.102, 14.9727}}, {22, {986.887, -69.8014, 7.47254}},
	{23, {999.939, -879.78, 14.5457}},  {24, {1349.98, -459.49, 50.0701}},
	{25, {983.637, -756.24, 14.9727}},  {26, {1436.51, -810.011, 11.8263}},
	{27, {1219.33, -328.821, 26.074}},  {28, {1188.48, -39.5632, 9.97308}},
	{29, {1086.82, -224.075, 8.90723}}, {30, {812.929, -631.481, 14.4702}},
	{31, {1220.02, -324.571, 26.169}},  {32, {1454.94, -188.311, 55.4429}},
	{33, {948.693, -1074.14, 13.173}},  {34, {967.018, -1125.41, 13.173}},
	{35, {1447.64, -188.018, 55.6244}}, {36, {1469.84, -891.621, 11.4162}},
	{37, {1449.92, -190.721, 55.5715}}, {38, {1529.41, -881.984, 11.4131}},
	{39, {511.38, -649.858, 16.1011}},  {40, {1050.61, -931.457, 14.4359}},
	{41, {1286.37, -1050.17, 14.8164}}, {42, {908.851, -828.69, 14.9727}},
	{43, {976.39, -443.011, 14.9734}},  {44, {886.256, -425.206, 14.917}},
	{45, {419.078, -1408.07, 26.1335}}, {46, {588.767, -654.78, 1.79896}},
	{47, {38.6844, -723.011, 22.7562}}, {48, {333.208, -451.617, 23.0175}},
	{49, {109.437, -1294.39, 26.1681}}, {50, {373.586, -507.435, 26.1748}},
	{51, {427.449, -1487.1, 18.641}},   {52, {427.449, -1487.1, 18.641}},
	{53, {41.6044, -880.019, 34.2102}}, {54, {415.038, -1383.88, 26.1682}},
	{55, {136.562, 179.578, 11.5317}},  {56, {48.2645, -1548.34, 26.0181}},
	{57, {1606.01, -616.299, 12.1514}}, {58, {113.082, -56.1878, 16.0181}},
	{59, {197.032, -996.545, 26.1647}}, {60, {52.3952, -1547.92, 26.1681}},
	{61, {79.4832, -1548.46, 28.2945}}, {62, {79.4832, -1548.46, 28.2945}},
	{63, {372.488, -624.01, 18.4508}},  {64, {232.056, -530.438, 25.6575}},
	{65, {372.353, -506.441, 26.1748}}, {66, {-72.3884, -1463.71, 26.1442}},
	{67, {80.9688, -1548.67, 28.2945}}, {68, {-1025.87, -73.337, 38.8984}},
	{69, {53.6893, -1548.53, 26.1681}}, {70, {80.9688, -1548.67, 28.2945}},
	{71, {-1184.33, 73.268, 68.7311}},  {72, {-1275.17, -108.19, 58.8301}},
	{73, {372.389, -327.871, 18.235}},  {74, {-427.297, -60.7034, 3.71128}},
	{75, {-680.396, 75.9628, 18.8404}}, {76, {-680.396, 75.9628, 18.8404}},
	{77, {-848.162, -168.21, 33.8565}}, {78, {-236.119, 269.261, 3.48417}},
	{79, {-666.75, -1.75, 18.8614}}};

std::map<int, CVector> gMissionStartCoords = {
	{15, {1224.563, -840.25, 15.0}},      {16, {1224.563, -840.25, 15.0}},
	{17, {1224.563, -840.25, 15.0}},      {18, {1224.563, -840.25, 15.0}},
	{19, {811.875, -939.9375, 15.0}},     {20, {892.75, -425.75, 13.875}},
	{21, {892.75, -425.75, 13.875}},      {21, {892.75, -425.75, 13.875}},
	{22, {892.75, -425.75, 13.875}},      {23, {892.75, -425.75, 13.875}},
	{24, {1191.688, -870.0, 15.0}},       {25, {1191.688, -870.0, 15.0}},
	{26, {1191.688, -870.0, 15.0}},       {27, {1191.688, -870.0, 15.0}},
	{28, {1191.688, -870.0, 15.0}},       {29, {1191.688, -870.0, 15.0}},
	{30, {1219.75, -319.6875, 27.375}},   {31, {1219.75, -319.6875, 27.375}},
	{32, {1219.75, -319.6875, 27.375}},   {33, {1219.75, -319.6875, 27.375}},
	{34, {1219.75, -319.6875, 27.375}},   {35, {1455.688, -187.25, 55.5625}},
	{36, {1455.688, -187.25, 55.5625}},   {37, {1455.688, -187.25, 55.5625}},
	{38, {1272.188, -92.875, 13.75}},     {39, {1455.688, -187.25, 55.5625}},
	{40, {938.375, -230.5, 3.875}},       {41, {938.375, -230.5, 3.875}},
	{42, {938.375, -230.5, 3.875}},       {43, {938.375, -230.5, 3.875}},
	{44, {523.6875, -639.0, 16.0625}},    {45, {523.6875, -639.0, 16.0625}},
	{46, {523.6875, -639.0, 16.0625}},    {47, {523.6875, -639.0, 16.0625}},
	{48, {523.6875, -639.0, 16.0625}},    {49, {459.0625, -1413.0, 26.0625}},
	{50, {459.0625, -1413.0, 26.0625}},   {51, {459.0625, -1413.0, 26.0625}},
	{52, {459.0625, -1413.0, 26.0625}},   {53, {459.0625, -1413.0, 26.0625}},
	{54, {38.75, -725.375, 22.75}},       {55, {38.75, -725.375, 22.75}},
	{56, {38.75, -725.375, 22.75}},       {57, {38.75, -725.375, 22.75}},
	{58, {38.75, -725.375, 22.75}},       {59, {38.75, -725.375, 22.75}},
	{60, {87.25, -1548.563, 28.25}},      {61, {87.25, -1548.563, 28.25}},
	{62, {87.25, -1548.563, 28.25}},      {63, {120.6875, -272.0625, 16.0625}},
	{64, {120.6875, -272.0625, 16.0625}}, {65, {120.6875, -272.0625, 16.0625}},
	{66, {120.6875, -272.0625, 16.0625}}, {67, {87.25, -1548.563, 28.25}},
	{68, {87.25, -1548.563, 28.25}},      {69, {87.25, -1548.563, 28.25}},
	{70, {87.25, -1548.563, 28.25}},      {71, {367.25, -328.0625, 19.5}},
	{72, {367.25, -328.0625, 19.5}},      {73, {367.25, -328.0625, 19.5}},
	{74, {-443.5, -6.0625, 3.75}},        {75, {-443.5, -6.0625, 3.75}},
	{76, {-443.5, -6.0625, 3.75}},        {77, {-443.5, -6.0625, 3.75}},
	{78, {-443.5, -6.0625, 3.75}},        {79, {-362.75, 246.5, 60.0}}};

const int SIZE_MAIN_SCRIPT    = 0x20000;

int Missions::GetRandomMission ()
{
	mRandomizedMission = mMissionOrder[mOriginalMission];
	mStoreNextScript = true;
	return mRandomizedMission;
}

void __fastcall Missions::RandomizeMissionToStart (CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& missionId = CTheScripts::ScriptParams[0].iParam;

	if (missionId >= START_MISSIONS && missionId <= END_MISSIONS
	    && gMissionEndOffsets.count (missionId))
		{
			mOriginalMission = missionId;
			missionId	 = GetRandomMission ();
			std::cout << "Storing mission: " << missionId
				  << std::endl;

			try
				{
					TeleportPlayer (gMissionStartCoords.at (
						mRandomizedMission));
				}
			catch (...)
				{
				}
		}
}

CRunningScript *Missions::StoreRandomizedScript (uint32_t ip)
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

bool Missions::ProcessPreReplaceMissionEndOffsets (CRunningScript* thread, short opcode)
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

bool Missions::ProcessPostReplaceMissionEndOffsets (CRunningScript* thread, uint16_t &opcode)
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

void Missions::RestoreOriginalScriptForCleanup ()
{
	memcpy ((char*)&CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		mTempMissionData.get (),
		SIZE_MISSION_SCRIPT);
	
	mScriptReplaced = false;
	mRandomizedScript = nullptr;
}

void Missions::HandleEndThreadOpcode (CRunningScript* thread, short opcode)
{
	if (opcode != eScriptCommands::COMMAND_TERMINATE_THIS_SCRIPT)
		return;
	
	mRandomizedScript = nullptr;
}

bool Missions::ShouldJump (CRunningScript* thread)
{
	int currentOffset = thread->m_nIp - SIZE_MAIN_SCRIPT;

        uint16_t& opcode = *reinterpret_cast<uint16_t *> (
            &CTheScripts::ScriptSpace[thread->m_nIp]);
	
	if (ProcessPostReplaceMissionEndOffsets (thread, opcode))
		RestoreOriginalScriptForCleanup ();
	
	HandleEndThreadOpcode(thread, opcode);

        return ProcessPreReplaceMissionEndOffsets(thread, opcode);
}

void Missions::MoveScriptToOriginalOffset (CRunningScript* thread)
{
	int *missionOffsets = (int *) 0x6F0558;

	memcpy (mTempMissionData.get (),
		(char*)&CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		SIZE_MISSION_SCRIPT);
	
	int offset = missionOffsets[mOriginalMission];
	CFileMgr::ChangeDir("\\");
	int handle = CFileMgr::OpenFile("data\\main.scm", "rb");
	CFileMgr::Seek(handle, offset, 0);
	CFileMgr::Read(handle, (char*)&CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT], SIZE_MISSION_SCRIPT);
	CFileMgr::CloseFile(handle);

	TeleportPlayerAfterMission ();
	
	thread->m_nIp = mPostReplaceEndOffsets.front().Start + SIZE_MAIN_SCRIPT;
	mScriptReplaced = true;
}

void Missions::TeleportPlayerAfterMission ()
{
	try
		{
			TeleportPlayer(gMissionEndCoords.at(mOriginalMission));
		}
	catch (...) {}
}

char __fastcall Missions::JumpOnMissionEnd (CRunningScript* thread)
{
	if (mRandomizedScript == thread && ShouldJump (thread))
		MoveScriptToOriginalOffset (thread);
	
	return thread->ProcessOneCommand();
}

void Missions::LoadMissionData (uint8_t *data, uint32_t size)
{
	CPedType::Load (data, size);
	SaveStructure *save
		= reinterpret_cast<SaveStructure *> (
			data + size - sizeof (SaveStructure));

	if (std::string (save->signature, 11) != "RAINBOMIZER")
		return InitShuffledMissionOrder (nullptr);
	return InitShuffledMissionOrder (save);
}

void Missions::InitShuffledMissionOrder (Missions::SaveStructure* structure)
{
	uint32_t seed = RandomNumber (INT_MIN, INT_MAX);
	if (structure)
		seed = structure->randomSeed;

	std::mt19937 engine{seed};
	std::uniform_int_distribution<int> d(START_MISSIONS, END_MISSIONS);

	mMissionOrder.Reset ();
	for (int i = START_MISSIONS; i <= END_MISSIONS; i++)
		std::swap (mMissionOrder[i], mMissionOrder[d(engine)]);
		
	mSaveStructure.randomSeed = seed;
}

void Missions::MissionOrder::Reset ()
{
	for (int i = 0; i < TOTAL_MISSIONS; i++)
		Missions[i] = START_MISSIONS + i;
}

void Missions::InitAtNewGame ()
{
	CWaterCannons::Init();
	InitShuffledMissionOrder (nullptr);
}

void Missions::SaveMissionData (uint8_t* data, uint32_t& outSize)
{
	CPedType::Save(data, &outSize);

	memcpy (data + outSize, &mSaveStructure, sizeof(SaveStructure));
	outSize += sizeof(SaveStructure);
}

void
Missions::Initialise()
{
	plugin::patch::RedirectCall(0x588DE8, RandomizeMissionToStart);
	plugin::patch::RedirectCall(0x588E47, StoreRandomizedScript);
	plugin::patch::RedirectCall(0x439485, JumpOnMissionEnd);
	plugin::patch::RedirectCall(0x591883, LoadMissionData);
	plugin::patch::RedirectCall(0x59087A, SaveMissionData);
	plugin::patch::RedirectCall(0x48C5BC, InitAtNewGame);

	printf("%p\n", mSaveStructure);
	
	mTempMissionData = std::make_unique<unsigned char[]>(SIZE_MISSION_SCRIPT);
	mLocalVariables = std::make_unique<unsigned int[]>(16);
}
