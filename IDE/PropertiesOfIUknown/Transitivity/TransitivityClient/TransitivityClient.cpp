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
	printf("\n*****This program checks Identity property of IUnknown*****\n");

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

	pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	pISubtract->QueryInterface(IID_IMultiply, (void**)&pIMultiply);
	pIMultiply->QueryInterface(IID_ISum, (void**)&pISumAgain);

	if (pISum == pISumAgain)
	{
		printf("\nIUnknown\'s Transitivity property checked its TRUE\n");
	}
	else
	{
		printf("\nIUnknown's Transitivity property check failed its FALSE\n");
	}

	pISumAgain->Release();
	pISumAgain = NULL;

	pIMultiply->Release();
	pIMultiply = NULL;

	pISubtract->Release();
	pISubtract = NULL;

	pISum->Release();
	pISum = NULL;

	CoUninitialize();
	return (0);
}
