#pragma once

#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>

#ifndef _Addy64_H

DWORD_PTR baseAddress;
HANDLE    pHandle;
DWORD     pID;
HWND      hGameWindow;

void GetModuleBaseAddress(TCHAR* lpszModuleName);

void getWindowInfo64(char _moduleName[], char _windowName[]);

class Addy64
{

public:
	DWORD_PTR address{ 0 };

private:
	unsigned int size{ 0 };
	DWORD_PTR aux_address;
	DWORD_PTR aux_address2;
	std::vector<unsigned int> offsets;

public:

	Addy64(std::vector<unsigned int> _offsets)
	{
		size = _offsets.size();
		offsets = _offsets;
		getAddress();
	};
	double getDouble();
	float  getFloat();
	int    getInt();

	void   writeFloat(float value);
	void   writeDouble(double value);
	void   writeInt(int value);

private:

	DWORD_PTR getAddress();
};

void GetModuleBaseAddress(TCHAR* lpszModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32))
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
			{
				baseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));

	}
	CloseHandle(hSnapshot);
}

void getWindowInfo64(char _moduleName[], char _windowName[])
{
	GetWindowThreadProcessId(FindWindow(NULL, _windowName), &pID);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	GetModuleBaseAddress(_T(_moduleName));
}

DWORD_PTR Addy64::getAddress()
{
	if (size == 1)
	{
		return baseAddress + offsets[0];
	}
	else if (size > 1)
	{
		ReadProcessMemory(pHandle, (LPCVOID)(baseAddress + offsets[0]), &aux_address, sizeof(aux_address), NULL);
		for (int i = 1; i < size - 1; i++)
		{
			ReadProcessMemory(pHandle, (LPCVOID)(aux_address + offsets[i]), &aux_address2, sizeof(aux_address2), NULL);
			aux_address = aux_address2;		
			address = aux_address2 + offsets[i + 1];
		}
		return address;
		aux_address = 0;
	}
}

double    Addy64::getDouble()
{
	ReadProcessMemory(pHandle, (LPCVOID)(address), &aux_address, 8, NULL);
	return *((double*)&aux_address);
}
float     Addy64::getFloat()
{
	ReadProcessMemory(pHandle, (LPCVOID)(address), &aux_address, 4, NULL);
	return *((float*)&aux_address);
}
int       Addy64::getInt()
{
	ReadProcessMemory(pHandle, (LPCVOID)(address), &aux_address, 4, NULL);
	return *((int*)&aux_address);
}

void	  Addy64::writeDouble(double value)
{
	WriteProcessMemory(pHandle, (LPVOID)(address), &value, sizeof(double), 0);
}
void	  Addy64::writeFloat(float value)
{
	WriteProcessMemory(pHandle, (LPVOID)(address), &value, sizeof(float), 0);
}
void	  Addy64::writeInt(int value)
{
	WriteProcessMemory(pHandle, (LPVOID)(address), &value, sizeof(int), 0);
}
#endif