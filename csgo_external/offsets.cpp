#include "offsets.h"

DWORD LocalPlayer;
DWORD EntityList;

DWORD m_iTeamNum;
DWORD m_iHealth;
DWORD m_vecOrigin;

//Matrixes
DWORD BoneMatrix;//<- Is also player related, lol.
DWORD ViewMatrix;

void initOffsets()
{
	LocalPlayer		 = 0xAA9AB4;
	EntityList		 = 0x4A8473C;

	m_iTeamNum		 = 0xF0;
	m_iHealth		 = 0xFC;
	m_vecOrigin		 = 0x134;

	BoneMatrix		 = 0x2698;

	ViewMatrix		 = 0x4A76154;
}