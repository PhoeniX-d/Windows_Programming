
////////////////////////////////////////////////
//											  //
//	Name		:MyFirstWindow				  //
//	Description	:My First Win32 Application   //
//	Author		:Pranav Choudhary			  //
//	Date		:20 Sept					  //
//											  //
////////////////////////////////////////////////

// Headers
#include <Windows.h>

// Global declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdLine, _In_ int iCmdShow)
{
	// Code
	// Declaration used of variables
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MyWin32App"); /* for UNICODE(wide char) convenience */

	// Before initializing clear memory of wndclass using either memset or ZeroMemory
	memset((void *)&wndclass, NULL, sizeof(WNDCLASSEX));

	// Now Initialize members
	wndclass.cbSize = sizeof(WNDCLASSEX);						  /* size of structure */
	wndclass.style = CS_HREDRAW | CS_VREDRAW;					  /* style of class */
	wndclass.cbClsExtra = 0;									  /* extra info to class */
	wndclass.cbWndExtra = 0;									  /* extra info to window */
	wndclass.lpfnWndProc = WndProc;								  /* where to go when even occurs */
	wndclass.hInstance = hInstance;								  /* which program window */
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			  /* loads default icon for window */
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);			  /* loads default minimize icon for window */
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);				  /* loads default cursor for window */
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); /* color of window background */
	wndclass.lpszClassName = szAppName;							  /*  name of class */
	wndclass.lpszMenuName = NULL;								  /* name of menu */

	// Register WNDCLASSEX object to OS
	RegisterClassEx(&wndclass);

	// Create a window in memory
	hwnd = CreateWindow(

		szAppName,						 /* Name of our Application */
		TEXT("MyFirstWin32Application"), /* Name of caption of our appliction*/
		WS_OVERLAPPEDWINDOW,			 /* Style of window */
		CW_USEDEFAULT,					 /* x coordinate of window (from leftop) */
		CW_USEDEFAULT,					 /* y coordinate of window (from leftop) */
		CW_USEDEFAULT,					 /* Height of our window in pexels */
		CW_USEDEFAULT,					 /* Width of our window in pixels */
		NULL,							 /* Handle of Parent Window(here NULL as Desktop is parent)*/
		NULL,							 /* Handle of Menu */
		hInstance,						 /* Handle of this program */
		NULL							 /* Creation paramter(extra) for more information*/
	);
	// Now Display window present in memory
	ShowWindow(hwnd, iCmdShow);

	// Update window which will paint our window
	UpdateWindow(hwnd);

	//Now start Message loop or Message pump ("The Heart of Fetus")
	while(GetMessage(
			&msg,		/* Pass empty msg object to message pool to get filled with msg */
			NULL,		/* We want all msgs from Parent as well as from all children */
			0,		/* No Message filter lower limit */
			0		/* No Message filter upper limit */		
			))
	{
		/* 	
		*	Our emptied msg will get filled with all information 
		*	now, translate message (low-level processing) 
		*/
		TranslateMessage(&msg);
		/* 	
		*	Now translated message will be dispatched to WndProc
		*	through DispatchMessage 
		*/
		DispatchMessage(&msg);
	}

	/* We want to return a value that is returned by PostQuitMessage */
	return ((int)msg.wParam);
}

/*
*	Callback function:called in two cases
*	1. When a Event occurs (Posting of Message)
*	2. Without an event by OS (Sending of Message)
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	/* Way 1 Win32 API */
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:			 //(VK) Virual Keycode
			DestroyWindow(hwnd); // API of Win32 ... sending of message
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0); /* EXIT_CODE i.e.0 gets stored in wParam of message */
		break;
	}

	/* Forward all msgs to DefWindowProc(i.e.to OS) which does not match with above case(s) */
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
