// Headers
#include<Windows.h>
#include "MyHeader.h"
#include "MSSquareDll.h"
#pragma comment(lib, "MSSquareDll.lib")

// Global Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Declaration of used variables
	MSG			msg;
	HWND		hWnd;
	WNDCLASSEX	wndclass;
	TCHAR		szAppName[] = TEXT("TheMessageBox");

	memset((void*)&wndclass, NULL, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndclass);

	hWnd = CreateWindow(
		szAppName,
		TEXT("Implicit linking"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR szStr[255];
	static int iNum = 0;
	int iRes = 0;

	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1': iNum = 1;
			break;
		case '2': iNum = 2;
			break;
		case '3': iNum = 3;
			break;
		case '4': iNum = 4;
			break;
		case '5': iNum = 5;
			break;
		case '6': iNum = 6;
			break;
		case '7': iNum = 7;
			break;
		case '8': iNum = 8;
			break;
		case '9': iNum = 9;
			break;
		}
		iRes = MakeSquare(iNum);
		wsprintf(szStr, TEXT("Square of %d is %d"), iNum, iRes);
		MessageBox(hWnd, szStr, TEXT("Microsoft Specific Dll"), MB_OK);
		break;

	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	}

	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}
