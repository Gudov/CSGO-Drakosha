//#include "memory.h"
#include "offsets.h"
#include "classes.h"

#define XOR(a) a // WTF, я не знаю что это за ересь, это просто было

DWORD ClientDLL;
DWORD ClientDLL_Size;
DWORD EngineDLL;
DWORD EngineDLL_Size;

CPlayer* pEntity[32];
CLocalPlayer* pLocal;

void initMemory()
{
	initOffsets();

	mem->Process(XOR("csgo.exe"));
	ClientDLL = mem->Module(XOR("client.dll"));
	EngineDLL = mem->Module(XOR("engine.dll"));
	ClientDLL_Size = mem->ModuleSize(XOR("client.dll"));
	EngineDLL_Size = mem->ModuleSize(XOR("engine.dll"));

	pLocal = new CLocalPlayer();

	for (int i = 0; i < 32; i++)//2Lazy4RealPlayercount
	{
		pEntity[i] = new CPlayer();
	}
}