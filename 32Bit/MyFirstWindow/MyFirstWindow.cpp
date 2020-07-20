// headers

#include<windows.h>

// global declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My Application");
	
	// zero-out wndclass members
	//memset((void*)&wndclass, NULL, sizeof(WNDCLASSEX));
						//OR
	ZeroMemory((void *)&wndclass, sizeof(WNDCLASSEX));
	
	// Initializations
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc; // this will register our callback function to WindowsOs
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);//Getting object from Windows Stock i.e. HBRUSH here
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	
	// register above class to OS
	RegisterClassEx(&wndclass);
	
	// Create Windows
	
	hwnd = CreateWindow
			(
					szAppName,
					TEXT("My Window"),
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
	
	// message loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
