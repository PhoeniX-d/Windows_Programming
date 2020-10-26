#include <windows.h>
#include "ContainmentInnerComponentWithRegFile.h"

/* class declaration */
class CMultiplicationDivision : public IMultiplication, IDivision
{
private:
	long m_cRef;

public:

	/* constructor declaration */
	CMultiplicationDivision();

	/* destructor declaration */
	~CMultiplicationDivision();

	/* IUnknown specific methods declarations */
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* IMultiplciation specific method declraration */
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	/* IDivision specific methods declaration */
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	long m_cRef;

public:

	/* constructor declaration */
	CMultiplicationDivisionClassFactory();

	/* destructor declaration */
	~CMultiplicationDivisionClassFactory();

	/* IUnknown specific methods declaration */
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* CMultiplicationDivisionClassFactory specific methods declaration */
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

/* global variable */
long glNumberOfActiveComponent = 0;
long glNumberOfServerLocks = 0;

/* DllMain */
BOOL WINAPI DllMain(HMODULE hdll, DWORD dwReason, LPVOID lpReserved)
{
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

/* Implementaion of CMultiplication  methods */
CMultiplicationDivision::CMultiplicationDivision()
{
	// code
	m_cRef = 1;	/* hardcoded to anticipate possible failure of QueryInterface */
	InterlockedIncrement(&glNumberOfActiveComponent);
}

CMultiplicationDivision::~CMultiplicationDivision()
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponent);
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMultiplicationDivision::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivision::Release()
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

HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	*pMultiplication = num1 * num2;
	return (S_OK);
}

HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	*pDivision= num1 / num2;
	return (S_OK);
}

/* implementation of CMultiplicationDivisionClassFactory methods declaration */
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory()
{
	// code
	m_cRef = 1; /* hardcoded to anticipate possible failure of QueryInterface */
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory()
{
	// code
}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release()
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

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// code
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	pCMultiplicationDivision = new CMultiplicationDivision();
	if (pCMultiplicationDivision == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();
	return (hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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

/* Exported Dll method */
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// code
	if (rclsid != CLSID_MultiplicationDivision)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory();
	if (pCMultiplicationDivisionClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return (S_OK);
}

extern "C" HRESULT __stdcall DllCanUnloadNow()
{
	/* code */
	if (glNumberOfActiveComponent == 0 && glNumberOfServerLocks == 0)
	{
		return (S_OK);
	}
	else
	{
		return (S_FALSE);
	}
}
