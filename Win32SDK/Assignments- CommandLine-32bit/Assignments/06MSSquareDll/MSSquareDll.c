// Headers
#include<windows.h>
#include "MSSquareDll.h"

// DllMain()
BOOL WINAPI DllMain(HMODULE hdll, DWORD dwReason, LPVOID lpResrved)
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
__declspec(dllexport) int MakeSquare(int iNum)
{
	return iNum * iNum;
}
