// Header
#include<windows.h>
#include "MySpecificDll.h"
#include "MyHeader.h"

// Global declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Code
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyDllDemo");

	// ZeroOutMemory
	ZeroMemory((LPVOID)&wndclass, sizeof(WNDCLASSEX));

	// Initialize members of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register class
	RegisterClassEx(&wndclass);

	// Create Window
	hwnd = CreateWindow(
		szAppName,
		TEXT("DllDemo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// Display Window
	ShowWindow(hwnd, iCmdShow);

	// Paint window
	UpdateWindow(hwnd);

	// Start MessageLoop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR szStr[255];
	static int iNum = 0;
	int iRes = 0;
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 1:iNum = 1;
			break;
		case 2:iNum = 2;
			break;
		case 3:iNum = 3;
			break;
		case 4:iNum = 4;
			break;
		case 5:iNum = 5;
			break;
		case 6:iNum = 6;
			break;
		case 7:iNum = 7;
			break;
		case 8:iNum = 8;
			break;
		case 9:iNum = 9;
			break;
		case 'S':
			iRes = MakeSquare(iNum);
			wsprintf(szStr, TEXT("Square of %d is %d"), iNum, iRes);
			MessageBox(hwnd, szStr, TEXT("MakeSquare"), MB_OK);
			break;
		}
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

