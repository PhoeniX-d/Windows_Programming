// Headers
#include <windows.h>
#include <tchar.h>

// Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppname[] = TEXT("MultithreadingApp");

	// code
	ZeroMemory((LPVOID)&wndclass, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppname;

	// RegisterClassEx
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		szAppname,
		TEXT("Main Thread 1"),
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

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hThread1 = NULL, hThread2 = NULL;
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		if (hThread1 == NULL)
		{
			MessageBox(hwnd, TEXT("Caanot Create Thread 2"), TEXT("Program Error"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		if (hThread2 == NULL)
		{
			MessageBox(hwnd, TEXT("Caanot Create Thread 3"), TEXT("Program Error"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Thread - 4"), TEXT("Multithreading"), MB_OK | MB_ICONINFORMATION);
		break;

	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID lParam)
{
	// variable declaration
	HWND hwnd = (HWND)lParam;
	HDC hdc;
	int i = 0;
	TCHAR szStr[255];

	// code
	hdc = GetDC(hwnd);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	for (i = 0; i < 65536; i++)
	{
		wsprintf(szStr, TEXT("Thread Counting Increment:%d"), i);
		TextOut(hdc, 5, 5, szStr, (int)_tcslen(szStr));
	}
	ReleaseDC(hwnd, hdc);
	return (0);
}

DWORD WINAPI ThreadProcTwo(LPVOID lParam)
{
	// variable declaration
	HWND hwnd = (HWND)lParam;
	HDC hdc;
	int i = 0;
	TCHAR szStr[255];

	// code
	hdc = GetDC(hwnd);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	for (i = 65536; i >= 0; i--)
	{
		wsprintf(szStr, TEXT("Thread Counting Decrement:%d"), i);
		TextOut(hdc, 5, 30, szStr, (int)_tcslen(szStr));
	}
	ReleaseDC(hwnd, hdc);
	return (0);
}
