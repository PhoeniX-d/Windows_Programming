// Headers
#include <windows.h>
#include "MyModuleDll.h"

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
	return (TRUE);
}

extern "C" int MakeSquare(int iNum)
{
	return iNum * iNum;
}
