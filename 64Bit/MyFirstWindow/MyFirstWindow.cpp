// Headers
#include<Windows.h>

// Global declation
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Variable declarations
	WNDCLASSEX 	wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My Application");
	
	//ZeroOut Memory
	memset((void *)&wndclass, NULL, sizeof(WNDCLASSEX));
	/* OR
	*	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));
	*/
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	//Register structure to OS
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(
		szAppName,				 /* Name of Application */
		TEXT("My First Window"), /* Name of Caption of window */
		WS_OVERLAPPEDWINDOW,	 /* Style of window */
		CW_USEDEFAULT,			 /* x coordinate of window - lefttop */
		CW_USEDEFAULT,			 /* y coordinate of windows - lefttop */
		CW_USEDEFAULT,			 /* width of window */
		CW_USEDEFAULT,			 /* height of window */
		NULL,					 /* Handle of Parent process (HW_DESKTOP)*/
		NULL,					 /* Handle of Menu */
		hInstance,				 /* Handle of window */
		NULL					 /* Extra parameter for CreateWindow */
	);

	//Show window stored in memory
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam , LPARAM lParam)
{
	//Code
	switch(iMsg)
	{
		case WM_DESTROY :
			PostQuitMessage(0);
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
