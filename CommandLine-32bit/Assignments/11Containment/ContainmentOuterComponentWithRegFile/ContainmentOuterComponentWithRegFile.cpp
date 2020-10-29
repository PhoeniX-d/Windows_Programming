#include <windows.h>
#include "ContainmentInnerComponentWithRegFile.h"
#include "ContainmentOuterComponentWithRegFile.h"

/* class declaration */
class CSumSubtract : public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;

public:
	/* constructor declaration */
	CSumSubtract();

	/* destructor declaration */
	~CSumSubtract();

	/* IUnknown specific methods declaration (inherited) */
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* ISum specific methods declaration (inherited) */
	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);

	/* ISubtraction specific methods declaration (inherited) */
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);

	/* IMultiplication specific methods declaration (inherited) */
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);

	/* IDivision specific methods declaration (inherited) */
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);

	/* custome method to initialize inner component */
	HRESULT __stdcall InitializeInnerComponent();
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	/* constructor declaration */
	CSumSubtractClassFactory();

	/* destructor declaration */
	~CSumSubtractClassFactory();

	/* IUnknown specific methods declaration (inherited) */
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* CSumSubtractClassFactory specific method declaration */
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

/* global variable */
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

/* DllMain */
BOOL WINAPI DllMain(HMODULE hdll, DWORD dwReason, LPVOID lpReserved)
{
	/* code */
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return (TRUE);
}

/* implementation of CSumSutract methods */
CSumSubtract::CSumSubtract()
{
	/* code */
	m_cRef = 1;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
	/* code */
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	else
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	/* code */
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtract::AddRef()
{
	/* code */
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release()
{
	/* code */
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	/* code */
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	/* code */
	*pSubtract = num1 - num2;
	return (S_OK);
}

HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	/* code */
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return (S_OK);
}

HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	/* code */
	if (num2 != 0)
		m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	else
	{
		MessageBox(NULL, TEXT("Divide By Zero"), TEXT("ERROR"), MB_OK);
		return (S_FALSE);
	}
	return (S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent()
{
	/* code */
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER,
						  IID_IMultiplication, (void **)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication interface cannot be obtained"), TEXT("Program Error"), MB_OK);
		m_pIMultiplication = NULL;
		return (E_FAIL);
	}

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void **)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision interface cannot be obtained"), TEXT("Program Error"), MB_OK);
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
		m_pIDivision = NULL;
		return (E_FAIL);
	}
	return (S_OK);
}

/* implementation of CSumSubtractClassFactory specific methods  */
CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	// code
	m_cRef = 1; /* hardcoded to anticipate possible failure of QueryInterface */
}

CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	// code
}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtractClassFactory::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release()
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	// code
	if (NULL != pUnkOuter)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;
	pCSumSubtract = new CSumSubtract();
	if (pCSumSubtract == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to initialize inner component"), TEXT("ERROR"), MB_OK);
		pCSumSubtract->Release();
		return (hr);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// code
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return (S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	// code
	if (rclsid != CLSID_SumSubtract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	pCSumSubtractClassFactory = new CSumSubtractClassFactory();
	if (pCSumSubtractClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow()
{
	// code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
	{
		return (S_OK);
	}
	else
	{
		return (S_FALSE);
	}
}
