#pragma once

#include <Windows.h>
#include <iostream>

#include "offsets.h"
#include "memory.h"

bool getAliveStatus(int health)
{
	if (health < 1)//For some reason 1 hp = dead, lol
		return false;
	else
		return true;
}

class CBoneMatrix
{
public:
	void GetBonePos(DWORD boneBase, int boneID, float * bonePos)
	{
		bonePos[0] = mem->ReadMem<float>(boneBase + 0x30 * boneID + 0x1c);//x
		bonePos[1] = mem->ReadMem<float>(boneBase + 0x30 * boneID + 0x1C);//y
		bonePos[2] = mem->ReadMem<float>(boneBase + 0x30 * boneID + 0x2C);//z
	}
}CBoneMatrix;

class CLocalPlayer
{
public:
	uintptr_t Player;//reason why I'm using unintptr_t instead of DWORD is because BuFFy told me to do so :).
	float Pos[3];

	int Health;
	int Team;
	int Weapon;
	bool isAlive;

	void ReadData()
	{
		Player = mem->ReadMem<uintptr_t>(ClientDLL + LocalPlayer);//Get the local player
		Pos[0] = mem->ReadMem<float>(Player + (m_vecOrigin));//feetpos x
		Pos[1] = mem->ReadMem<float>(Player + (m_vecOrigin + 0x4));//feetpos y
		Pos[2] = mem->ReadMem<float>(Player + (m_vecOrigin + 0x8));//feetpos z
		Weapon = mem->ReadMem<int>(Player + 0x2EE8);

		Health = mem->ReadMem<int>(Player + m_iHealth);//health
		Team = mem->ReadMem<int>(Player + m_iTeamNum);//team
		isAlive = getAliveStatus(Health);//See if our playeer is alive
	}
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

	void ReadData(int i)
	{
		Player = mem->ReadMem<uintptr_t>(ClientDLL + EntityList + (i * 0x10));//Size of each entity is 10 Hex.
		Pos[0] = mem->ReadMem<float>(Player + (m_vecOrigin));//feetpos x
		Pos[1] = mem->ReadMem<float>(Player + (m_vecOrigin + 0x4));//feetpos y
		Pos[2] = mem->ReadMem<float>(Player + (m_vecOrigin + 0x8));//feetpos z
		Weapon = mem->ReadMem<char>(Player + 0x2EE8);

		Health = mem->ReadMem<int>(Player + m_iHealth);//health
		Team = mem->ReadMem<int>(Player + m_iTeamNum);//team
		isAlive = getAliveStatus(Health);//Get alive status of the player
		BoneBase = mem->ReadMem<uintptr_t>(Player + BoneMatrix);//Bone matrix, obv. not used for bone esp ;)

		CBoneMatrix.GetBonePos(BoneBase, 11, HeadPos);//Head position used for box height and width. (Since width = height / 2)
	}
};