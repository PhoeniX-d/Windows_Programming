#include <windows.h>
#include "AggregationInnerComponentWithRegFile.h"

/* interface declaration for internal use only (not to be included in .h file )*/
interface INoAggregationIUnknown /* new */
{
    virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **) = 0;
    virtual ULONG _stdcall AddRef_NoAggregation() = 0;
    virtual ULONG _stdcall Release_NoAggregation() = 0;
};
class CMultiplicationDivision : public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
    long m_cRef;
    IUnknown *m_pIUnknownOuter;

public:
    /* constructor declaration */
    CMultiplicationDivision(IUnknown *);

    /* destructor declaration */
    ~CMultiplicationDivision();

    /* Aggregation supported IUnknown supported methods declaration (inherited) */
    HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

    /* Aggregation non-supported IUnknown supported methods declaration (inherited) */
    HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **);
    ULONG __stdcall AddRef_NoAggregation();
    ULONG __stdcall Release_NoAggregation();

    /* IMultiplication specific methods declaration inherited */
    HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);

    /* IDivision specific methods declaration inherited */
    HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);
};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
private:
    long m_cRef;

public:
    /* constructor decl'n */
    CMultiplicationDivisionClassFactory();

    /* destructor decl'n */
    ~CMultiplicationDivisionClassFactory();

    /* IUnknown specific methods declaration (inherited) */
    HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

    /* IClassFactory specific methods declaration (inherited) */
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

/* implementation of CMultiplicationDivision methods */
CMultiplicationDivision::CMultiplicationDivision(IUnknown *pUnknownOuter)
{
    /* code */
    m_cRef = 1;
    InterlockedIncrement(&glNumberOfActiveComponents);
    if (pUnknownOuter != NULL)
    {
        this->m_pIUnknownOuter = pUnknownOuter;
    }
    else
    {
        this->m_pIUnknownOuter = reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));
    }
}

CMultiplicationDivision::~CMultiplicationDivision()
{
    /* code */
    InterlockedDecrement(&glNumberOfActiveComponents);
}

/* implementation of CMultiplicationDivision's Aggregation supported IUnknown's methods */
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
    return (m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CMultiplicationDivision::AddRef()
{
    return (m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release()
{
    return (m_pIUnknownOuter->Release());
}

/* implementation of CMultiplicationDivision's Aggregation non-supported IUnknown's methods */
HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
    /* code */
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<INoAggregationIUnknown *>(this);
    }
    else if (riid == IID_IMultiplication)
    {
        *ppv = static_cast<IMultiplication *>(this);
    }
    else if (riid == IID_IDivision)
    {
        *ppv = static_cast<IDivision *>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
    return (S_OK);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation()
{
    /* code */
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation()
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

/* implementation of IMultiplication's method */
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
    *pMultiplication = num1 * num2;
    return (S_OK);
}

/* implementation of IDivision's method */
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
    *pDivision = num1 / num2;
    return (S_OK);
}

/* implementation of CMultiplicationDivisionClassFactory's methods */
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory()
{
    /* code */
    m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory()
{
    /* code */
}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
    /* code */
    if (riid == IID_IUnknown)
    {
        *ppv = static_cast<IClassFactory *>(this);
    }
    else if (riid == IID_IClassFactory)
    {
        *ppv = static_cast<IClassFactory *>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
    return (S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef()
{
    /* code */
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release()
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

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    /* code */
    if (pUnkOuter != NULL && riid != IID_IUnknown)
    {
        return (CLASS_E_NOAGGREGATION);
    }
    CMultiplicationDivision *pCMultiplicationDivision = NULL;
    HRESULT hr;
    pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
    if (pCMultiplicationDivision == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
    pCMultiplicationDivision->Release_NoAggregation();
    return (hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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
/* Exported dll function */
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    /* code */
    if (rclsid != CLSID_MultiplicationDivision)
    {
        return (CLASS_E_CLASSNOTAVAILABLE);
    }
    CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
    HRESULT hr;
    pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory();
    if (pCMultiplicationDivisionClassFactory == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
    pCMultiplicationDivisionClassFactory->Release();
    return hr;
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
