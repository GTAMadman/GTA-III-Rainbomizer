#include "Missions.h"
#include "plugin.h"
#include "Config.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include <map>
#include <CFileMgr.h>
#include <iostream>
#include <CFont.h>

std::map<int, int> gMissionEndOffsets
    = {{15, 4382},  {16, 4704},  {17, 3528}, {18, 3719}, {20, 3506}, {21, 5700},
       {22, 1988},  {23, 12927}, {24, 5245}, {25, 4673}, {26, 2782}, {28, 3047},
       {30, 2028},  {32, 8479},  {33, 3892}, {34, 3206}, {36, 8206}, {37, 912},
       {38, 12278}, {40, 10326}, {41, 3435}, {42, 1787}, {43, 2776}, {45, 3543},
       {46, 7186},  {47, 3113},  {48, 2586}, {49, 4083}, {50, 3478}, {51, 6565},
       {52, 4055},  {54, 3038},  {56, 4641}, {57, 9684}, {58, 3403}, {59, 9079},
       {60, 5867},  {61, 4385},  {62, 3932}, {63, 5680}, {65, 1598}, {66, 3406},
       {67, 9999},  {68, 11393}, {69, 2965}, {70, 347},  {71, 5145}, {72, 7362},
       {73, 8201},  {74, 1568},  {75, 1978}, {76, 2160}, {77, 1364}, {78, 5087},
       {79, 6818}};

std::map<int, CVector> gMissionEndCoords = {{15, {0.0, 0.0, 0.0}}};
std::map<int, CVector> gMissionStartCoords = {{15, {0.0, 0.0, 0.0}}};

const int START_MISSIONS      = 15;
const int END_MISSIONS        = 79;
const int SIZE_MAIN_SCRIPT    = 0x20000;

int Missions::GetRandomMission ()
{
	do
		{
			mRandomizedMission = Functions::RandomNumber(START_MISSIONS, END_MISSIONS);
		}
	while (!gMissionEndOffsets.count(mRandomizedMission));
	mStoreNextScript = true;
	return mRandomizedMission;
}

void __fastcall Missions::RandomizeMissionToStart (CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& missionId = CTheScripts::ScriptParams[0].iParam;

        if (missionId >= START_MISSIONS && missionId <= END_MISSIONS &&
	    gMissionEndOffsets.count(missionId))
		{
			mOriginalMission = missionId;
			missionId = GetRandomMission ();
			std::cout << "Storing mission: " <<  missionId << std::endl;
		}
}

CRunningScript *Missions::StoreRandomizedScript (uint32_t ip)
{
	CRunningScript* sc = plugin::CallAndReturn<CRunningScript*, 0x439000>(ip);
	if (std::exchange(mStoreNextScript, false)) {
		mRandomizedScript = sc;
		std::cout << "Storing randomized script" << std::endl;
	}

	return sc;
}

void Missions::HandleReturnOpcode (CRunningScript* thread, short opcode)
{
	const int COMMAND_RETURN = 81;
	if (opcode != COMMAND_RETURN || !mScriptReplaced)
		return;

	thread->ProcessOneCommand();
	
	memcpy ((char*)&CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		mTempMissionData.get (),
		SIZE_MISSION_SCRIPT);
	
	mScriptReplaced = false;
	mRandomizedScript = nullptr;
}

void Missions::HandleEndThreadOpcode (CRunningScript* thread, short opcode)
{
	const int COMMAND_TERMINATE_THIS_SCRIPT = 78;
	if (opcode != COMMAND_TERMINATE_THIS_SCRIPT)
		return;
	
	mRandomizedScript = nullptr;
}

bool Missions::ShouldJump (CRunningScript* thread)
{
	int currentOffset = thread->m_nIp - SIZE_MAIN_SCRIPT;

        short opcode = *reinterpret_cast<uint16_t *> (
            &CTheScripts::ScriptSpace[thread->m_nIp]);
	
	HandleReturnOpcode(thread, opcode);
	HandleEndThreadOpcode(thread, opcode);

        if (currentOffset == gMissionEndOffsets.at(mRandomizedMission))
		return true;

	return false;
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
	
	thread->m_nIp = gMissionEndOffsets.at(mOriginalMission) + SIZE_MAIN_SCRIPT;
	mScriptReplaced = true;
}

void Missions::TeleportPlayerAfterMission ()
{
	
}

char __fastcall Missions::JumpOnMissionEnd (CRunningScript* thread)
{
	if (mRandomizedScript == thread && ShouldJump (thread))
		MoveScriptToOriginalOffset (thread);
	
	return thread->ProcessOneCommand();
}

void
Missions::Initialise()
{
	plugin::patch::RedirectCall(0x588DE8, RandomizeMissionToStart);
	plugin::patch::RedirectCall(0x588E47, StoreRandomizedScript);
	plugin::patch::RedirectCall(0x439485, JumpOnMissionEnd);
	
	mTempMissionData = std::make_unique<unsigned char[]>(SIZE_MISSION_SCRIPT);
	mLocalVariables = std::make_unique<unsigned int[]>(16);
	//0x439485
}
