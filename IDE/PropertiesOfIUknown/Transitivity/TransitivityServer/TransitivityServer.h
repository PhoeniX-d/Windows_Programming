class ISum : public IUnknown
{
public:

	// ISum  specific method declaration
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;	// Pure virual
};

class ISubtract : public IUnknown
{
public:

	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // Pure virtual
};

class IMultiply : public IUnknown
{
public:

	// ISubtract specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; // Pure virtual
};

// CLSID of CSumSubtractMultiply component {FE3A2BD7-2D35-4F8E-B299-B74C01ECD750}
const CLSID CLSID_SumSubtractMultiply =
{ 0xfe3a2bd7, 0x2d35, 0x4f8e, 0xb2, 0x99, 0xb7, 0x4c, 0x1, 0xec, 0xd7, 0x50 };

// IID of ISum interface {B4B44286-0F15-47EC-ABE2-4634F14F7D3A}
const IID IID_ISum =
{ 0xb4b44286, 0xf15, 0x47ec, 0xab, 0xe2, 0x46, 0x34, 0xf1, 0x4f, 0x7d, 0x3a };

// IID of ISubtract interface {30694B12-7948-49AF-AC4B-0103864928C5}
const IID IID_ISubtract =
{ 0x30694b12, 0x7948, 0x49af, 0xac, 0x4b, 0x1, 0x3, 0x86, 0x49, 0x28, 0xc5 };

// IID of IMultiply interface {E3938242-999A-49E8-BF7C-FEC4716E319F}
const IID IID_IMultiply =
{ 0xe3938242, 0x999a, 0x49e8, 0xbf, 0x7c, 0xfe, 0xc4, 0x71, 0x6e, 0x31, 0x9f};
