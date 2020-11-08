#include <Windows.h>
#include <stdio.h>
#include "AutomationDllServerWithRegFile.h"

/* global function declaration */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* WinMain() */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	/* code */
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("COM Automation Dll");

	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hInstance = hInstance;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		szAppName,
		TEXT("Client Of COM Automation Dll"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	/* code */
	void ComErrorDescriptionString(HWND, HRESULT);
	IDispatch* pIDispatch = NULL;
	HRESULT hr;
	DISPID dispid;
	const OLECHAR* szFunctionName1 = L"SumOfTwoIntegers";
	const OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS param = {vArg, 0, 2, NULL};
	int n1, n2;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:

		/* COM initialize */
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("COM library cannot be initialized"),
				TEXT("COM Error"), MB_OK);
			DestroyWindow(hwnd);
			exit(0);
		}

		hr = CoCreateInstance(CLSID_MyMath,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IDispatch,
			(void**)&pIDispatch);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Component cannot be created"),
				TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}
		/* common code for IMyMath->SumOfTwoIntegers and IMyMath->SubtrctionOfTwoInteges */
		n1 = 75;
		n2 = 25;

		/* as DISPPARAMS rgvarg recieves parameter in reverse order */
		VariantInit(vArg);

		vArg[0].vt = VT_INT;
		vArg[0].intVal = n2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = n1;

		param.cArgs = 2;
		param.cNamedArgs = 0;
		param.rgdispidNamedArgs = NULL;
		param.rgvarg = vArg;

		VariantInit(&vRet);

		/* code for IMyMath->SumOfTwoIntegers */
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			(LPOLESTR*)&szFunctionName1,
			1,
			GetUserDefaultLCID(),
			&dispid
		);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot get ID of SumOfTwoIntegers"),
				TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		/* Invoke() for IMyMath->SumOfTwoIntegers */
		hr = pIDispatch->Invoke(
			dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL
		);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot Invoke function"),
				TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else
		{
			wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		}

		/* code of IMyMath->SubtractionOfTwoIntegers */
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			(LPOLESTR*)&szFunctionName2,
			1,
			GetUserDefaultLCID(),
			&dispid
		);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot get ID of SubtractionOfTwoIntegers"),
				TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		/* Invoke() for IMyMath->SubtractionOfTwoIntegers */
		hr = pIDispatch->Invoke(
			dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD,
			&param,
			&vRet,
			NULL,
			NULL
		);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Cannot Invoke function"),
				TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else
		{
			wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		}

		VariantClear(vArg);
		VariantClear(&vRet);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&szErrorMessage,
		0,
		NULL) != 0)
	{
		swprintf_s(str, TEXT("%s"), szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(str, TEXT("[Could not find description for error #%#x.\n]"), hr);
	}
	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
