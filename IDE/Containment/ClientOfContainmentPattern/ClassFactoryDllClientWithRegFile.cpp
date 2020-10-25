#include <windows.h>
#include "ClientContainmentInnerComponentWithRegFile.h"

// Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global variable declaration
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

// WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Declaration of variables
	WNDCLASSEX wndclass;
	MSG	msg;
	HWND hWnd;
	TCHAR szAppName[] = TEXT("ComClient");
	HRESULT hr;

	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

	// COM initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library can not be initialized.\n Program will now exit."),
			   TEXT("Program Error"), MB_OK);
		exit(0);
	}

	// WNDCLASSEX initialization
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
		TEXT("Client of Com Dll Server ClassFactory"),
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

	// COM Un-Initialization
	CoUninitialize();
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declaration
	void SafeInterfaceRelease();

	// variable delcaratioms
	HRESULT hr;
	int iNum1 = 0, iNum2 = 0, iSum = 0, iSubtract = 0, iMul = 0, iDiv = 0;
	TCHAR str[255] = { '\0' };

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER,
			IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("Interface cannot be obtained"), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// Initialize arguments harcoded
		iNum1 = 25;
		iNum2 = 75;
		// Call SumOfTwoIntegers() of iSum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);		
		// Display result
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);


		// Call QueryInterface on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}		
		// Again initialze aruments hardcoded
		iNum1 = 75;
		iNum2 = 25;
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);		
		// Display result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iSubtract);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		// Again initialze aruments hardcoded
		iNum1 = 5;
		iNum2 = 5;
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMul);		
		// Display result
		wsprintf(str, TEXT("Multiplication of %d and %d is %d"), iNum1, iNum2, iMul);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		// Again initialze aruments hardcoded
		iNum1 = 100;
		iNum2 = 5;
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDiv);
		// Display result
		wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iDiv);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);


		pIDivision->Release();
		pIDivision = NULL;

		pIMultiplication->Release();
		pIMultiplication = NULL;

		pISubtract->Release();
		pISubtract = NULL;

		pISum->Release();
		pISum = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterFaceRelease()
{
	// code
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
}
