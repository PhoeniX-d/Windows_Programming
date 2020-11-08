#include <windows.h>
#include <stdio.h>
#include "AutomationDllServerWithRegFile.h"

/* CoClass declaration */
class CMyMath : public IMyMath
{
private :

	long m_cRef;
	ITypeInfo* m_pITypeInfo;

public:

	/* constructor declaration */
	CMyMath();

	/* desstructor declaration */
	~CMyMath();

	/* IUnknown specific method declaration (inherited)*/
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* IDispatch specific methods declaration (inherited)*/
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);;
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	/* IMyMath specific method declaration */
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	/* Custome methods */
	HRESULT __stdcall InitInstance();
};

/* ClassFactory class declaration */
class CMyMathClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	/* constructor declaration */
	CMyMathClassFactory();

	/* destructor declaration */
	~CMyMathClassFactory();

	/* IUnknown specific methods declaration (inherited) */
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	/* CMyMathClassFactory specific methods declaration (inherited) */
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

/* global variable */
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

/* {115D16ED-6EEB-4CD8-8DC1-9D76C413D11A} */
const GUID LIBID_AutomationServer =
{ 0x115d16ed, 0x6eeb, 0x4cd8, 0x8d, 0xc1, 0x9d, 0x76, 0xc4, 0x13, 0xd1, 0x1a };

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

/* CMyMath methods implementation */
CMyMath::CMyMath()
{
	/* code */
	m_cRef = 1;
	m_pITypeInfo = NULL;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMyMath::~CMyMath()
{
	/* code */
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pITypeInfo)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
}

HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv)
{
	/* code */
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMyMath::AddRef()
{
	/* code */
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMyMath::Release()
{
	/* code */
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete (this);
		return (0);
	}
	return (m_cRef);
}

HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	/* code */
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	/* code */
	*pSubtract = num1 - num2;
	return (S_OK);
}

HRESULT CMyMath::InitInstance()
{
	/* code */
	void ComErrorDescriptionString(HWND, HRESULT);
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return (hr);
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return (hr);
		}
		pITypeLib->Release();
	}
	return (S_OK);
}

HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	/* code */
	/* ar we have type library it is 1, else 0 */
	*pCountTypeInfo = 1;
	return (S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	/* code */
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
	{
		return (DISP_E_BADINDEX);
	}
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return (S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	/* code */
	return (DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	/* code */
	HRESULT hr;
	hr = DispInvoke(
		this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);
	return (hr);
}

/* CMyMathClassFactory methods implementation */
CMyMathClassFactory::CMyMathClassFactory()
{
	/* code */
	m_cRef = 1;
}

CMyMathClassFactory::~CMyMathClassFactory()
{
	/* code */
}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	/* code */
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMyMathClassFactory::AddRef()
{
	/* code */
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMyMathClassFactory::Release()
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

HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	 /* code */
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}
	CMyMath* pCMyMath = NULL;
	HRESULT hr;
	pCMyMath = new CMyMath();
	if (pCMyMath == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	/* call automation related init method */
	pCMyMath->InitInstance();

	/* get requested interface */
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return (hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
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

/* Dll Exported fuctions */
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	/* code */
	if (rclsid != CLSID_MyMath)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;
	pCMyMathClassFactory = new CMyMathClassFactory();
	if (pCMyMathClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	return (hr);
}

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

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	/* code */
	TCHAR* szErrorMessage = NULL;
	TCHAR szStr[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
	{
		hr = HRESULT_CODE(hr);
	}
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(szStr, TEXT("%#X  :  %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(szStr, TEXT("[Could not find description for error #% #x.]\n"), hr);
	}
	MessageBox(hwnd, szStr, TEXT("COM ERROR"), MB_OK);
}
