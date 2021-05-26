#pragma once
#include "plugin.h"
#include "Config.h"
#include "CFileMgr.h"
#include "CRunningScript.h"

class Autosave
{
public:
	static void Initialise();
private:
	static void __fastcall RequestAutosave(CRunningScript* script, void* edx, int opcode);
	static void __fastcall IncreaseMissionsPassed(CRunningScript* script, void* edx, int* arg0, short count);
	static void FixSavingAfterKingdomCome();
	static bool ShouldSave;
	static char* MakeValidSaveName(int slot);
	static void GenericSave(int fileHandle);
	static char ProcessCommands0to99(CRunningScript* script, int opcode);
};