#pragma once
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

	// IMultiply specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; // Pure virtual
};


// CLSID of CSumSubtract component {3D39B9BC-D679-4B32-9B23-2D41211A8335}
const CLSID CLSID_SumSubtract =
{ 0x3d39b9bc, 0xd679, 0x4b32, 0x9b, 0x23, 0x2d, 0x41, 0x21, 0x1a, 0x83, 0x35 };

// IID of ISum interface {54BA8AD9-EAF8-48B3-BADA-187411985BD7}
const IID IID_ISum =
{ 0x54ba8ad9, 0xeaf8, 0x48b3, 0xba, 0xda, 0x18, 0x74, 0x11, 0x98, 0x5b, 0xd7 };

// IID of ISubtract interface {35B24746-FCF1-45A5-803C-64082B339E62}
const IID IID_ISubtract =
{ 0x35b24746, 0xfcf1, 0x45a5, 0x80, 0x3c, 0x64, 0x8, 0x2b, 0x33, 0x9e, 0x62 };

// IID of IMultiply interface {9A893725-5AB5-4DE3-96D2-9E59565C78B8}
const IID IID_IMultiply =
{ 0x9a893725, 0x5ab5, 0x4de3, 0x96, 0xd2, 0x9e, 0x59, 0x56, 0x5c, 0x78, 0xb8 };
