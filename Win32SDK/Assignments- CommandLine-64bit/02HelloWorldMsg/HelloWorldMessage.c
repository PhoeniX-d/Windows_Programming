/* Headers */

#include<Windows.h>

/* Global declarations */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* WinMain()*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    /* code */
    WNDCLASSEX wndclass;
    MSG msg;
    HWND hwnd;
    TCHAR szAppName[] = TEXT("Win32 Desktop Window");

    /* zero-out memory */
    memset((void *)&wndclass, 0, sizeof(WNDCLASSEX));

    /* Initialize structure variable */
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = (WNDPROC)WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    /* Register Class */
    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(szAppName,
                        TEXT("Hello-Win"),
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);


    if(hwnd == NULL)
    {
        MessageBox(NULL, TEXT("Cannot Create Proper Window"), TEXT("Error"), MB_OK);
        exit(0);
    }

    /* Show Window */
    ShowWindow(hwnd, iCmdShow);
    
    /* UpdateWidow */
    UpdateWindow(hwnd);

    /* Message Loop */
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /* code */
    HDC hdc;
    RECT rc;
    PAINTSTRUCT ps;
    TCHAR str[255];

    switch(iMsg)
    {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rc);
            SetTextColor(hdc, RGB(0, 255, 0));
            SetBkColor(hdc, RGB(0, 0, 0));
            DrawText(hdc, TEXT("Hello, World"), -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
