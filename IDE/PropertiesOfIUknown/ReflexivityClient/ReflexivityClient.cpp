#include <windows.h>
#include <stdio.h>
#include "ReflexivityServer.h"

ISum* pISum = NULL;
ISum* pISumAgain= NULL;

int main()
{
	HRESULT hr;
	printf("\n*****This program checks Reflexivity property of IUnknown*****\n");

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("Error code %d : COM library cannot be initialized\n", GetLastError());
		return (0);
	}

	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
	if (FAILED(hr))
	{
		printf("Error code %d : ISum interface cannot be obtained\n", GetLastError());
		return (0);
	}
	
	pISum->QueryInterface(IID_ISum, (void**)&pISumAgain);

	if(pISum == pISumAgain)
		printf("\nIUnknown\'s Reflexivity property proved\n");
	else
		printf("\nIUnknown\'s Reflexivity property failed to prove\n");

	pISumAgain->Release();
	pISumAgain = NULL;

	pISum->Release();
	pISum = NULL;
	
	CoUninitialize();
	return (0);
}
