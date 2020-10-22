#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

class CSumSubtract : public ISum, ISubtract
{
private:
    long m_cRef;

public:
    CSumSubtract();
    ~CSumSubtract();

    // IUnknown specific method declaration(inherited)
    HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

    // ISum, ISubtract method declaration(inherited)
    HRESULT __stdcall SumOfTwoIntegers(int, int, int *);
    HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);
};

class CSumSubtractIClassFactory : public IClassFactory
{
private:
    long m_cRef;

public:
    CSumSubtractIClassFactory();
    ~CSumSubtractIClassFactory();

    // IClassFActory's IUnknown's specific method declaration(inherited)
    HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

    // IClassFactory's method declaration(inherited)
    HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
    HRESULT __stdcall LockServer(BOOL);
};

// global variable
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// DllMain
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
//Implementation of CSumSubtract methods
CSumSubtract::CSumSubtract()
{
    // code
    m_cRef = 1; /* harcoded to anticipate posiible failure of QueryInterface booz of late late binding */
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
    // code
    InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
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

    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
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

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
    // code
    *pSum = num1 + num2;
    return (S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
    // code
    *pSubtract = num1 - num2;
    return (S_OK);
}

// Implementation of IClassFactory methods
CSumSubtractIClassFactory::CSumSubtractIClassFactory()
{
    // code
    m_cRef = 1; /* harcoded to anticipate possible failure of QueryInterface bcoz of late late binding */
}

CSumSubtractIClassFactory::~CSumSubtractIClassFactory()
{
    // code
}

HRESULT CSumSubtractIClassFactory::QueryInterface(REFIID riid, void **ppv)
{
    // code
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

ULONG CSumSubtractIClassFactory::AddRef()
{
    // code
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CSumSubtractIClassFactory::Release()
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

HRESULT CSumSubtractIClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    // code
    if (NULL != pUnkOuter)
    {
        return (CLASS_E_NOAGGREGATION);
    }

    HRESULT hr;
    CSumSubtract *pCSumSubtract = new CSumSubtract();
    if (NULL == pCSumSubtract)
    {
        return (E_OUTOFMEMORY);
    }

    hr = pCSumSubtract->QueryInterface(riid, ppv);
    pCSumSubtract->Release();
    return (hr);
}

HRESULT CSumSubtractIClassFactory::LockServer(BOOL fLock)
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

// Implementation of exported functions from dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    // code
    if (rclsid != CLSID_SumSubtract)
    {
        return (CLASS_E_CLASSNOTAVAILABLE);
    }

    HRESULT hr;
    CSumSubtractIClassFactory *pCSumSubtractIClassFactory = new CSumSubtractIClassFactory();
    if (NULL == pCSumSubtractIClassFactory)
    {
        return (E_OUTOFMEMORY);
    }

    pCSumSubtractIClassFactory->QueryInterface(riid, ppv);
    pCSumSubtractIClassFactory->Release();
    return (S_OK);
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
