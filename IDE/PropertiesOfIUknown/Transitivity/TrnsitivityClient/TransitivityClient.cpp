#include <windows.h>
#include <stdio.h>
#include "TransitivityServer.h"

ISum* pISum = NULL;
ISum* pISumAgain = NULL;
ISubtract* pISubtract = NULL;
IMultiply* pIMultiply = NULL;

int main()
{
	HRESULT hr;
	printf("\n*****This program checks Transitivity property of IUnknown*****\n");

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("Error code %d : COM library cannot be initialized\n", GetLastError());
		return (0);
	}

	hr = CoCreateInstance(CLSID_SumSubtractMultiply, NULL, CLSCTX_INPROC_SERVER, IID_ISubtract, (void**)&pISubtract);
	if (FAILED(hr))
	{
		printf("Error code %d : ISubtract interface cannot be obtained\n", GetLastError());
		return (0);
	}

	/*
	pISubtract->QueryInterface(IID_IMultiply, (void**)&pIMultiply);
	pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	pIMultiply->QueryInterface(IID_ISum, (void**)&pISumAgain);

	if (pISum == pISumAgain)
	{
		printf("\nIUnknown\'s Transitivity property prooved true\n");
	}
	else
	{
		printf("\nIUnknown\'s Transitivity property failed\n");
	}
	*/
	pIMultiply->Release();
	pIMultiply = NULL;

	pISumAgain->Release();
	pISumAgain = NULL;

	pISubtract->Release();
	pISubtract = NULL;

	pISum->Release();
	pISum = NULL;

	CoUninitialize();
	return (0);
}
