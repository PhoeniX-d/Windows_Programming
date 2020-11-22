#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

/* class declration */
class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;

public:
	/* contructor declaration */
	CSumSubtract();

	/* destructor declaration */
	~CSumSubtract();

	/* IUnknown specific methods declaration (inherited) */
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* ISum specific method declaration (inherited) */
	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);

	/* ISubtract specific method declaration (inherited) */
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);
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

	/* CSumSubtractClassFactory's IClassFactory's IUnknown specific methods declaration */
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* CSumSubtractClassFactory specific methods declaration */
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

/* global variables */
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

/* DllMain() */
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

/* implementation of CSumSubtract methods */
CSumSubtract::CSumSubtract()
{
	/* code */
	m_cRef = 1; /* hardcoded to anticipate possible failure of QueryInterface due to late late bindings */
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
	/* code */
	InterlockedDecrement(&glNumberOfActiveComponents);
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
		return (m_cRef);
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

/* implementation of CSumSubtractClassFactory specific methods */
CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	/* code */
	m_cRef = 1; /* hardcoded to anticipate possible failure of QueryInterface due to late late binding */
}

CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	/* code */
}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	/* code */
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
	/* code */
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release()
{
	/* code */
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (m_cRef);
	}
	return (m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	/* code */
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	pCSumSubtract = new CSumSubtract();
	if (NULL == pCSumSubtract)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	/* code */
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

/* Dll exported function */
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	/* code */
	if (rclsid != CLSID_SumSubtract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	pCSumSubtractClassFactory = new CSumSubtractClassFactory();
	if (NULL == pCSumSubtractClassFactory)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return (hr);
}

/* funtion to unload dll */
extern "C" HRESULT __stdcall DllCanUnloadNow()
{
	/* code */
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
	{
		return (S_OK);
	}
	else
	{
		return (S_FALSE);
	}
}
