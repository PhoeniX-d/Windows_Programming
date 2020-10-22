#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

// Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global variables
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // Declaration of variables
    WNDCLASSEX wndclass;
    MSG msg;
    HWND hWnd;
    TCHAR szAppName[] = TEXT("COM Dll Server");
    HRESULT hr;

    ZeroMemory((void *)&wndclass, sizeof(WNDCLASSEX));

    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("COM Library can\'t be initialized"), TEXT("Program Error"), MB_OK);
        exit(0);
    }

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

    CoUninitialize();
    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // code
    void SafeInterfaceRelease();
    TCHAR str[255];
    HRESULT hr;
    int iNum1 = 75, iNum2 = 25, iSum = 0, iSubtract = 0;

    switch (iMsg)
    {
    case WM_CREATE:
        hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
        if (FAILED(hr))
        {
            MessageBox(hwnd, TEXT("ISum interface can\'t be obtained"), TEXT("Program Error"), MB_OK);
            DestroyWindow(hwnd);
        }

        pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
        wsprintf(str, TEXT("Summation of %d and %d is %d"), iNum1, iNum2, iSum);
        MessageBox(hwnd, str, TEXT("Result"), MB_OK);

        hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
        if (FAILED(hr))
        {
            MessageBox(hwnd, TEXT("ISubtract interface can\'t be obtained"), TEXT("Program Error"), MB_OK);
            DestroyWindow(hwnd);
        }

        pISum->Release();
        pISum = NULL;

        pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
        wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSubtract);
        MessageBox(hwnd, str, TEXT("Result"), MB_OK);

        pISubtract->Release();
        pISubtract = NULL;

        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease()
{
    // code
    if (pISubtract)
    {
        pISubtract->Release();
        pISubtract = NULL;
    }
    if (pISum)
    {
        pISum->Release();
        pISum = NULL;
    }
}
