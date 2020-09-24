// Headers
#include<windows.h>

// Global declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Declaration of variables
	WNDCLASSEX		wndclass;
	MSG			msg;
	HWND			hWnd;
	TCHAR			szAppName[] = TEXT("PhoeniXWindow");

	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	hWnd = CreateWindow(
		szAppName,
		TEXT("Pranav\'s Window"),
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

	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	RECT	rc;
	HDC		hdc;
	PAINTSTRUCT	ps;

	switch (iMsg)
	{
	case WM_PAINT:

		/* Get Specialist from OS */
		hdc = BeginPaint(hWnd, &ps);
		//hdc = GetDC(hWnd);
		/* Get area to be painted */
		GetClientRect(hWnd, &rc);
		/* Set color of text */
		SetTextColor(hdc, RGB(0, 255, 0));
		/* Set background color of text (default is white)*/
		SetBkColor(hdc, RGB(0, 0, 0));
		/* Draw text using Device Context specialist */
		DrawText(hdc, TEXT("Hello, World!!"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		/* As HDC is expensive resource of OS free after use */
		EndPaint(hWnd, &ps);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_DESTROY:
		
		PostQuitMessage(0);
		break;
	
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}
