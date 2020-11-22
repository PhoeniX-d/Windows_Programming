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

// CLSID of CSumSubtract component {AFF7FFDA-9540-4C8F-9754-95C3BCB3A843}
const CLSID CLSID_SumSubtract =
{ 0xaff7ffda, 0x9540, 0x4c8f, 0x97, 0x54, 0x95, 0xc3, 0xbc, 0xb3, 0xa8, 0x43 };

// IID of ISum interface {936B41EB-E3EC-42FB-B69D-8EB0CB0AD424}
const IID IID_ISum =
{ 0x936b41eb, 0xe3ec, 0x42fb, 0xb6, 0x9d, 0x8e, 0xb0, 0xcb, 0xa, 0xd4, 0x24 };

// IID of ISubtract interface {01351684-971D-41F6-85C7-F5F95D68104D}
const IID IID_ISubtract =
{ 0x1351684, 0x971d, 0x41f6, 0x85, 0xc7, 0xf5, 0xf9, 0x5d, 0x68, 0x10, 0x4d };
