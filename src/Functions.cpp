#include "Functions.h"

int* Functions::ms_vehiclesLoaded = reinterpret_cast<int*>(0x773560);
/* Initialised the random engine and given it a seed */
std::mt19937 Functions::rngEngine{ (unsigned int)time(0) };

bool Functions::DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (x1 == x2 && y1 == y2 && z1 == z2)
		return true;
	return false;
}
void Functions::LoadModel(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState != 1)
	{
		CStreaming::RequestModel(modelID, 1);
		CStreaming::LoadAllRequestedModels(false);
	}
}
bool Functions::IsModelLoaded(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState == 1)
		return true;
	return false;
}
int Functions::RandomNumber(unsigned int min, unsigned int max)
{
	std::uniform_int_distribution<int> random(min, max);
	return random(rngEngine);
}