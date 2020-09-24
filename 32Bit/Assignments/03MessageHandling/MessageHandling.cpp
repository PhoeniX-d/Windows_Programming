// Headers
#include<windows.h>

// Global declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASSEX wndclass = { };
    TCHAR szAppName[] = TEXT("MessageHandling");

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_VREDRAW | CS_HREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_HAND);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpfnWndProc = WndProc;
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(
        szAppName,
        TEXT("Message Handling"),
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
        case WM_CREATE:
            MessageBox(hwnd, TEXT("WM_CREATE Message sent!"), TEXT("WM_CREATE"), MB_OK | MB_ICONEXCLAMATION);
            break;

        case WM_LBUTTONDOWN:
            MessageBox(hwnd, TEXT("WM_LBUTTONDOWN Message sent!"), TEXT("WM_LBUTTONDOWN"), MB_OK | MB_ICONASTERISK);
            break;

        case WM_MOVE:
            MessageBox(hwnd, TEXT("WM_MOVE Message sent!"), TEXT("WM_MOVE"), MB_OK | MB_ICONERROR);
            break;

        case WM_KEYDOWN:
            MessageBox(hwnd, TEXT("WM_KEYDOWN Message sent!"), TEXT("WM_KEYDOWN"), MB_OK | MB_ICONQUESTION);
            break;

        case WM_SIZE:
            MessageBox(hwnd, TEXT("WM_SIZE Message sent!"), TEXT("WM_SIZE"), MB_OK | MB_ICONWARNING);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
