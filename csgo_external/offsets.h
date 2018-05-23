#pragma once

#include <Windows.h>

//Player Related Stuff
extern DWORD LocalPlayer;
extern DWORD EntityList;

extern DWORD m_iTeamNum;
extern DWORD m_iHealth;
extern DWORD m_vecOrigin;

//Matrixes
extern DWORD BoneMatrix;//<- Is also player related, lol.
extern DWORD ViewMatrix;

void initOffsets();