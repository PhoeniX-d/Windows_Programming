#include<Windows.h>
#include <stdio.h>
#include "AutomationDllServerWithRegFile.h"

/* global declarations */

IMyMath* pIMyMath = NULL;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/* code */
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ComClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if(FAILED(hr))
	{ 
		MessageBox(NULL, TEXT("COM Library Cannot be Initialized. \nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Client of COM Dll Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	/* code */
	void ComErrorDescriptionString(HWND, HRESULT);
	void SafeInterfaceRelease();

	HRESULT hr;
	int n1, n2, iSum, iSubtract;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void**)&pIMyMath);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hwnd, hr);
			DestroyWindow(hwnd);
		}

		n1 = 123;
		n2 = 121;

		pIMyMath->SumOfTwoIntegers(n1, n2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, iSum);
		MessageBox(hwnd, str, TEXT("SumOfTwoIntegers"), MB_OK);

		pIMyMath->SubtractionOfTwoIntegers(n1, n2, &iSubtract);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, iSubtract);
		MessageBox(hwnd, str, TEXT("SubtractionOfTwoIntegers"), MB_OK);

		pIMyMath->Release();
		pIMyMath = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	/* code */
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
		swprintf_s(str, TEXT("%#X : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(str, TEXT("[Could not find a description for error # % #X.]\n"), hr);
	}
	MessageBox(hwnd, str, TEXT("COM's ERROR"), MB_OK);
}

void SafeInterfaceRelease()
{
	/* code */
	if (pIMyMath)
	{
		pIMyMath->Release();
		pIMyMath = NULL;
	}
}
