#include <windows.h>
#include <TlHelp32.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <math.h>
#include <random>
#include <conio.h>
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <process.h>
#include <unordered_map>

class CMemory
{
public:
	CMemory();
	~CMemory();

	DWORD PID;
	HANDLE hProcess;

	template <class cData>
	cData ReadMem(DWORD dwAddress)
	{
		cData cRead;
		ReadProcessMemory(hProcess, (LPVOID)dwAddress, &cRead, sizeof(cData), NULL);
		return cRead;
	}

	template <class cData>
	cData WriteMem(DWORD dwAddress, cData write)
	{
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &write, sizeof(cData), NULL);
		return 0;
	}

	template <class cData>
	void WriteMemNRET(DWORD dwAddress, cData write)
	{
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &write, sizeof(cData), NULL);
		return;
	}

	virtual void  Process(char* ProcessName);
	virtual DWORD Module(char* ModuleName);
	virtual DWORD ModuleSize(char* ModuleName);
	virtual bool  DataCompare(BYTE* data, BYTE* sign, char* mask);
	virtual DWORD FindSignature(DWORD base, DWORD size, BYTE* sign, char* mask);
};

extern CMemory* mem;