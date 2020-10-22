class ISum : public IUnknown
{
public:
    // ISum specific method declaration
    virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};

class ISubtract : public IUnknown
{
public:
    // ISum specific method declaration
    virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

// CLSID of SumSubtract {BB652BA4-CEB9-4374-984F-1568A3FF59F4}
const CLSID CLSID_SumSubtract =
    {0xbb652ba4, 0xceb9, 0x4374, 0x98, 0x4f, 0x15, 0x68, 0xa3, 0xff, 0x59, 0xf4};

// IID of ISum {53F7B29A-6284-4AF6-ABC7-DA7666242A98}
const IID IID_ISum =
    {0x53f7b29a, 0x6284, 0x4af6, 0xab, 0xc7, 0xda, 0x76, 0x66, 0x24, 0x2a, 0x98};

// IID of ISubtract {7A9B87BA-8C0A-4063-8A4B-3AA17347A3C9}
const IID IID_ISubtract =
    {0x7a9b87ba, 0x8c0a, 0x4063, 0x8a, 0x4b, 0x3a, 0xa1, 0x73, 0x47, 0xa3, 0xc9};
