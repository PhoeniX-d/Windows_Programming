#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

// Class declaration
class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
public:
	
	// Constructor 
	CSumSubtract();

	// Destructor
	~CSumSubtract();

	// IUnknowm specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// ISum specific method declaration (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declaration (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	
	// Constructor 
	CSumSubtractClassFactory();

	// Destructor
	~CSumSubtractClassFactory();

	// IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// IClassFactory specific method declaration (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//Global declarations
long glNumberOfActiveComponents = 0;		/* Number of active components*/
long glNumberOfServerLocks = 0;			/* Number of locks on this dll*/

// DllMain
BOOL WINAPI DllMain(HMODULE hdll, DWORD dwReason, LPVOID lpReserved)
{
	// code
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

// Implementaion of CSumSubtract's constructor
CSumSubtract::CSumSubtract()
{
	// code
	m_cRef = 1;	/* Harcoded innitialization to anticipate possible failure of QueryInterface */
	InterlockedIncrement(&glNumberOfActiveComponents); 	/* increment global counter */
}

// Implementation of CSumSubtract's destructor
CSumSubtract::~CSumSubtract()
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);	/* decrement global counter */
}

// Implementaion of CSumSubtract's IUnknown methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract *>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtract::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release()
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

// Implementaion of ISum methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	// code
	*pSum = num1 + num2;
	return (S_OK);
}

// Implementaion of ISubtract methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	// code
	*pSubtract = num1 - num2;
	return (S_OK);
}

// Implementation of CSumSubtractClassFactory's constructor
CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	// code
	m_cRef = 1;	/* Harcoded innitialization to anticipate possible failure of QueryInterface */
}

// Implementation of CSumSubtractClassFactory's destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	// code
}

// Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
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

// Implementaion of CSumSubtractClassFactory's IClassFactory's methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	
	// variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;
	pCSumSubtract = new CSumSubtract();
	if (NULL == pCSumSubtract)
	{
		return (E_OUTOFMEMORY);
	}

	// get the required interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();	/* anticipate possible failure of QueryInterface() */
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

// Implementation of Exported functions form this Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	if (rclsid != CLSID_SumSubtract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	// variable declarations
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	pCSumSubtractClassFactory = new CSumSubtractClassFactory();
	if (NULL == pCSumSubtractClassFactory)
	{
		return (E_OUTOFMEMORY);
	}

	// get the required interface
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();	/* anticipate possible failure of QueryInterface() */
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
