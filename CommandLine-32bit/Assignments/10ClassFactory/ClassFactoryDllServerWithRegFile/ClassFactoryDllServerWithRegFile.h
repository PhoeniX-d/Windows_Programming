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

// CLSID of CSumSubtract component {DC305656-B849-4BDE-BB95-F7FCC9155A59}
const CLSID CLSID_SumSubtract =
{ 0xDC305656, 0xB849, 0x4BDE, 0xBB, 0x95, 0xF7, 0xFC, 0xC9, 0x15, 0x5A, 0x59 };

// IID of ISum interface {6C6F1873-5493-488F-B246-5DBD7A4E7C07}
const IID IID_ISum =
{ 0x6c6f1873, 0x5493, 0x488f, 0xb2, 0x46, 0x5d, 0xbd, 0x7a, 0x4e, 0x7c, 0x7 };

// IID of ISubtract interface {3E65F05A-A19D-4236-9594-96B7538F7DDB}
const IID IID_ISubtract =
{ 0x3e65f05a, 0xa19d, 0x4236, 0x95, 0x94, 0x96, 0xb7, 0x53, 0x8f, 0x7d, 0xdb };
