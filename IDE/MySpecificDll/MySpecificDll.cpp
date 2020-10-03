// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include "MySpecificDll.h"

// DllMain()
BOOL WINAPI DllMain(HMODULE hdll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

__declspec(dllexport) int MakeSqare(int iNum)
{
	return iNum * iNum;
}
