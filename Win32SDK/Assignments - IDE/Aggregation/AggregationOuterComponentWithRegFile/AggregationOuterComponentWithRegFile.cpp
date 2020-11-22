#include <windows.h>
#include "AggregationInnerComponentWithRegFile.h"
#include "AggregationOuterComponentWithRegFile.h"

class CSumSubtract : public ISum, ISubtract
{
private:
    long m_cRef;
    IUnknown *m_pIUnknownInner;
    IMultiplication *m_pIMultiplication;
    IDivision *m_pIDivision;

public:
    /* constructor decl'n */
    CSumSubtract();

    /* destructor decl'n */
    ~CSumSubtract();

    /* IUnknown specific method declaration */
    HRESULT __stdcall QueryInterface(REFIID riid, void **ppv);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

    /* ISum specific method declaration */
    HRESULT __stdcall SumOfTwoIntegers(int, int, int *);

    /* ISubtract specific method declaration */
    HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);

    /* custom method for inner component creation */
    HRESULT __stdcall InitializeInnerComponent();
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
    long m_cRef;

public:
    /* contructor decl'n */
    CSumSubtractClassFactory();

    /* destructro decl'n */
    ~CSumSubtractClassFactory();

    /* IUnkown specific method declaration */
    HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

    /* IClassFactory specific methods declaration */
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

/* implementation of CSumSubtract specific methods */
CSumSubtract::CSumSubtract()
{
    /* code */
    m_pIMultiplication = NULL;
    m_pIDivision = NULL;
    m_pIUnknownInner = NULL;
    m_cRef = 1;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
    InterlockedDecrement(&glNumberOfActiveComponents);
    if (m_pIMultiplication)
    {
        m_pIMultiplication->Release();
        m_pIMultiplication = NULL;
    }
    else if (m_pIDivision)
    {
        m_pIDivision->Release();
        m_pIDivision = NULL;
    }
    else if (m_pIUnknownInner)
    {
        m_pIUnknownInner->Release();
        m_pIUnknownInner = NULL;
    }
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
    /* code */
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
    else if (riid == IID_IMultiplication)
    {
        return (m_pIUnknownInner->QueryInterface(riid, ppv));
    }
    else if (riid == IID_IDivision)
    {
        return (m_pIUnknownInner->QueryInterface(riid, ppv));
    }
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

HRESULT CSumSubtract::InitializeInnerComponent()
{
    /* code */
    HRESULT hr;
    hr = CoCreateInstance(CLSID_MultiplicationDivision, reinterpret_cast<IUnknown *>(this),
                          CLSCTX_INPROC_SERVER, IID_IUnknown, (void **)&m_pIUnknownInner);
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("IUnknown Interface cannot be obtained from Inner component"), TEXT("Program ERROR"), MB_OK);
        return (E_FAIL);
    }

    hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void **)&m_pIMultiplication);
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("IMultiplication Interface cannot be obtained from Inner component"), TEXT("Program ERROR"), MB_OK);
        m_pIUnknownInner->Release();
        m_pIUnknownInner = NULL;
        return (E_FAIL);
    }

    hr = m_pIUnknownInner->QueryInterface(IID_IDivision, (void **)&m_pIDivision);
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("IDivision Interface cannot be obtained from Inner component"), TEXT("Program ERROR"), MB_OK);
        m_pIUnknownInner->Release();
        m_pIUnknownInner = NULL;
        return (E_FAIL);
    }
    return (S_OK);
}

/* implementation of CSumSubtractClassFactory specific methods  */
CSumSubtractClassFactory::CSumSubtractClassFactory()
{
    /* code */
    m_cRef = 1; /* hardcoded to anticipate possible failure of QueryInterface */
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
        return (0);
    }
    return (m_cRef);
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    /* code */
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
