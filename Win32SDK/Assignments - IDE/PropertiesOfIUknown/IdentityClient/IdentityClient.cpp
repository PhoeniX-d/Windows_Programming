#include <windows.h>
#include <stdio.h>
#include "IdentityServer.h"

ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IUnknown* pIUnknownFromISum = NULL;
IUnknown* pIUnknownFromISubtract = NULL;

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

	pISum->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISum);
	pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	pISubtract->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISubtract);
	if (pIUnknownFromISum == pIUnknownFromISubtract)
	{
		printf("\nIUnknown\'s Identity property checked its TRUE\n");
	}
	else
	{
		printf("\nIUnknown's Identity property check failed its FALSE\n");
	}

	pIUnknownFromISubtract->Release();
	pIUnknownFromISubtract = NULL;
	
	pIUnknownFromISum->Release();
	pIUnknownFromISum = NULL;

	pISubtract->Release();
	pISubtract = NULL;

	pISum->Release();
	pISum = NULL;
	
	
	CoUninitialize();
	return (0);
}
