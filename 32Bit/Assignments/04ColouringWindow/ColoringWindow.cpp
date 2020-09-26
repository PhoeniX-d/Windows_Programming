// Headers
#include <windows.h>
#include "MyHeader.h"

// Global declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASSEX wndclass = {};
    TCHAR szAppName[] = TEXT("Colouring Window");

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_VREDRAW | CS_HREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_HAND);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpfnWndProc = WndProc;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(
        szAppName,
        TEXT("Coloured Window"),
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
    static char keyPressed;
    HBRUSH hNewBrush, hOldBrush;
    HDC hdc;
    RECT rc;
    PAINTSTRUCT ps;

    switch (iMsg)
    {
    case WM_PAINT:

        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rc);
        switch (keyPressed)
        {
        case 'R':
            hNewBrush = CreateSolidBrush(RGB(255, 0, 0));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'G':
            hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'B':
            hNewBrush = CreateSolidBrush(RGB(0, 0, 255));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'C':
            hNewBrush = CreateSolidBrush(RGB(0, 255, 255));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'M':
            hNewBrush = CreateSolidBrush(RGB(255, 0, 255));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'Y':
            hNewBrush = CreateSolidBrush(RGB(255, 255, 0));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'K':
            hNewBrush = CreateSolidBrush(RGB(0, 0, 0));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        case 'W':
            hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
            break;

        default:
            hNewBrush = CreateSolidBrush(RGB(128, 64, 0));
            hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
        }
        FillRect(hdc, &rc, hNewBrush);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hNewBrush);
        EndPaint(hwnd, &ps);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {

        case 'R': /* Red */
            keyPressed = 'R';
            break;

        case 'G': /* Green */
            keyPressed = 'G';
            break;

        case 'B': /* Blue */
            keyPressed = 'B';
            break;

        case 'C': /* Cyan */
            keyPressed = 'C';
            break;

        case 'M': /* Magenta */
            keyPressed = 'M';
            break;

        case 'Y': /* Yellow */
            keyPressed = 'Y';
            break;

        case 'K': /* Black */
            keyPressed = 'K';
            break;

        case 'W': /* White */
            keyPressed = 'W';
            break;

        default: /* other key pressed */
            keyPressed = wParam;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
