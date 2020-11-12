class IMultiplication : public IUnknown
{
public:
    /* IMultiplication specific method declaraion */
    virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0; /* pure virtual */
};

class IDivision : public IUnknown
{
public:
    /* IDivision specific method declaraion */
    virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0; /* pure virtual */
};

/* CLSID of MultiplicationDivision component {33E9F880-7046-41FC-999C-405109392152} */
const CLSID CLSID_MultiplicationDivision =
    {0x33e9f880, 0x7046, 0x41fc, 0x99, 0x9c, 0x40, 0x51, 0x9, 0x39, 0x21, 0x52};

/* IID of IMultiplication interface {54504D5D-0C87-4CDF-A0D0-8D640832B81C} */
const IID IID_IMultiplication =
    {0x54504d5d, 0xc87, 0x4cdf, 0xa0, 0xd0, 0x8d, 0x64, 0x8, 0x32, 0xb8, 0x1c};

/* IID of IDivision interface {3BE850A9-C09C-44D0-82C9-8378906BA29C} */
const IID IID_IDivision =
    {0x3be850a9, 0xc09c, 0x44d0, 0x82, 0xc9, 0x83, 0x78, 0x90, 0x6b, 0xa2, 0x9c};
