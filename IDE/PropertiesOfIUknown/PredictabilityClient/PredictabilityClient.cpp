#include <windows.h>
#include <stdio.h>
#include "PredictabilityServer.h"

ISum* pISum = NULL;

int main()
{
	HRESULT hr;
	printf("\n*****This program checks Predictability property of IUnknown*****\n");

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

	pISum->Release();
	pISum = NULL;

	Sleep(1000);

	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
	if (FAILED(hr))
	{
		printf("Error code %d : ISum interface cannot be obtained\n", GetLastError());
		return (0);
	}
	
	pISum->Release();
	pISum = NULL;
	

	printf("\nIUnknown\'s Predictability property prooved\n");
	
	CoUninitialize();
	return (0);
}
