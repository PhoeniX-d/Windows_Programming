#include <windows.h>
#include "TransitivityServer.h"

// Class declaration
class CSumSubtractMultiply : public ISum, ISubtract, IMultiply
{
private:
	long m_cRef;
public:

	// Constructor 
	CSumSubtractMultiply();

	// Destructor
	~CSumSubtractMultiply();

	// IUnknowm specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// ISum specific method declaration (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declaration (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// IMultiply specific method declaration (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
};

class CSumSubtractMultiplyClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:

	// Constructor 
	CSumSubtractMultiplyClassFactory();

	// Destructor
	~CSumSubtractMultiplyClassFactory();

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

// Implementaion of CSumSubtractMultiply's constructor
CSumSubtractMultiply::CSumSubtractMultiply()
{
	// code
	m_cRef = 1;	/* Harcoded innitialization to anticipate possible failure of QueryInterface */
	InterlockedIncrement(&glNumberOfActiveComponents); 	/* increment global counter */
}

// Implementation of CSumSubtractMultiply's destructor
CSumSubtractMultiply::~CSumSubtractMultiply()
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);	/* decrement global counter */
}

// Implementaion of CSumSubtractMultiply's IUnknown methods
HRESULT CSumSubtractMultiply::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract*>(this);
	}
	else if (riid == IID_IMultiply)
	{
		*ppv = static_cast<IMultiply*>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtractMultiply::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractMultiply::Release()
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
HRESULT CSumSubtractMultiply::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	// code
	*pSum = num1 + num2;
	return (S_OK);
}

// Implementaion of ISubtract methods
HRESULT CSumSubtractMultiply::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	// code
	*pSubtract = num1 - num2;
	return (S_OK);
}

// Implementaion of IMultiply methods
HRESULT CSumSubtractMultiply::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiply)
{
	// code
	*pMultiply = num1 * num2;
	return (S_OK);
}

// Implementation of CSumSubtractMultiplyClassFactory's constructor
CSumSubtractMultiplyClassFactory::CSumSubtractMultiplyClassFactory()
{
	// code
	m_cRef = 1;	/* Harcoded innitialization to anticipate possible failure of QueryInterface */
}

// Implementation of CSumSubtractMultiplyClassFactory's destructor
CSumSubtractMultiplyClassFactory::~CSumSubtractMultiplyClassFactory()
{
	// code
}

// Implementation of CSumSubtractMultiplyClassFactory's IClassFactory's IUnknown's methods
HRESULT CSumSubtractMultiplyClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CSumSubtractMultiplyClassFactory::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractMultiplyClassFactory::Release()
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

// Implementaion of CSumSubtractMultiplyClassFactory's IClassFactory's methods
HRESULT CSumSubtractMultiplyClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	// variable declarations
	CSumSubtractMultiply* pCSumSubtractMultiply = NULL;
	HRESULT hr;
	pCSumSubtractMultiply = new CSumSubtractMultiply();
	if (NULL == pCSumSubtractMultiply)
	{
		return (E_OUTOFMEMORY);
	}

	// get the required interface
	hr = pCSumSubtractMultiply->QueryInterface(riid, ppv);
	pCSumSubtractMultiply->Release();	/* anticipate possible failure of QueryInterface() */
	return (hr);
}

HRESULT CSumSubtractMultiplyClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractMultiplyClassFactory* pCSumSubtractMultiplyClassFactory = NULL;
	HRESULT hr;
	pCSumSubtractMultiplyClassFactory = new CSumSubtractMultiplyClassFactory();
	if (NULL == pCSumSubtractMultiplyClassFactory)
	{
		return (E_OUTOFMEMORY);
	}

	// get the required interface
	hr = pCSumSubtractMultiplyClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractMultiplyClassFactory->Release();	/* anticipate possible failure of QueryInterface() */
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
