#pragma once

#include <Windows.h>
#include <iostream>

#include "offsets.h"
#include "memory.h"

bool getAliveStatus(int health);

class CBoneMatrix
{
public:
	void GetBonePos(DWORD boneBase, int boneID, float * bonePos);
};

class CLocalPlayer
{
public:
	uintptr_t Player;//reason why I'm using unintptr_t instead of DWORD is because BuFFy told me to do so :).
	float Pos[3];

	int Health;
	int Team;
	int Weapon;
	bool isAlive;

	void ReadData();
};

class CPlayer
{
public:
	uintptr_t Player;

	float Pos[3];
	float HeadPos[3];

	int Health;
	int Team;
	int Weapon;
	bool isAlive;

	uintptr_t BoneBase;

	void ReadData(int i);
};