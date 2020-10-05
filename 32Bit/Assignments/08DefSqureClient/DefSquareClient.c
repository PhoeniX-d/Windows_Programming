// Headers
#include <windows.h>
#include "MyHeader.h"
typedef int (*pfnMakeSquare)(int);
pfnMakeSquare pfn = NULL;

// Global Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // Declaration of used variables
    MSG msg;
    HWND hwnd;
    WNDCLASSEX wndclass;
    TCHAR szAppName[] = TEXT("DLLLoading");

    memset((void *)&wndclass, 0, sizeof(WNDCLASSEX));

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

    hwnd = CreateWindow(
        szAppName,
        TEXT("Explicit linking"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

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
    TCHAR szStr[255];
    static int iNum = 0;
    int iRes = 0;
    HMODULE hdll = NULL;
    switch (iMsg)
    {
    case WM_CREATE:
        hdll = LoadLibrary(TEXT("MSSquareDll.dll"));

        if (hdll == NULL)
        {
            MessageBox(hwnd, TEXT("Exiting"), TEXT("Error!!"), MB_OK);
            DestroyWindow(hwnd);
        }

        pfn = (pfnMakeSquare)GetProcAddress(hdll, "MakeSquare");
        iNum = 12;
        iRes = pfn(iNum);
        FreeLibrary(hdll);
        wsprintf(szStr, TEXT("Square of %d is %d"), iNum, iRes);
        MessageBox(hwnd, szStr, TEXT("Module Definition Dll"), MB_OK);
        break;

    case WM_DESTROY:
        PostQuitMessage(EXIT_SUCCESS);
        break;
    }

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
