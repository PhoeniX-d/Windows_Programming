#include <windows.h>
#include "ContainmentInnerComponentWithRegFile.h"

// Class declaration
class CMultiplicationDivision : public IMultiplication, IDivision
{
private:
	long m_cRef;
public:

	// Constructor 
	CMultiplicationDivision();

	// Destructor
	~CMultiplicationDivision();

	// IUnknowm specific method declaration (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// IMultiplication specific method declaration (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision specific method declaration (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:

	// Constructor 
	CMultiplicationDivisionClassFactory();

	// Destructor
	~CMultiplicationDivisionClassFactory();

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

// Implementaion of CMultiplicationDivision's constructor
CMultiplicationDivision::CMultiplicationDivision()
{
	// code
	m_cRef = 1;	/* Harcoded innitialization to anticipate possible failure of QueryInterface */
	InterlockedIncrement(&glNumberOfActiveComponents); 	/* increment global counter */
}

// Implementation of CMultiplicationDivision's destructor
CMultiplicationDivision::~CMultiplicationDivision()
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);	/* decrement global counter */
}

// Implementaion of CMultiplicationDivision's IUnknown methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IDivision)
	{
		*ppv = static_cast<IDivision*>(this);
	}
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

// Implementaion of IMultiplication methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	// code
	*pMultiplication = num1 * num2;
	return (S_OK);
}

// Implementaion of IDivision methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	// code
	*pSubtract = num1 / num2;
	return (S_OK);
}

// Implementation of CMultiplicationDivisionClassFactory's constructor
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory()
{
	// code
	m_cRef = 1;	/* Harcoded innitialization to anticipate possible failure of QueryInterface */
}

// Implementation of CMultiplicationDivisionClassFactory's destructor
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory()
{
	// code
}

// Implementation of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
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

// Implementaion of CMultiplicationDivisionClassFactory's IClassFactory's methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	// variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;
	pCMultiplicationDivision = new CMultiplicationDivision();
	if (NULL == pCMultiplicationDivision)
	{
		return (E_OUTOFMEMORY);
	}

	// get the required interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();	/* anticipate possible failure of QueryInterface() */
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

// Implementation of Exported functions form this Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	if (rclsid != CLSID_MultiplicationDivision)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	// variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory();
	if (NULL == pCMultiplicationDivisionClassFactory)
	{
		return (E_OUTOFMEMORY);
	}

	// get the required interface
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();	/* anticipate possible failure of QueryInterface() */
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
