/* class declaration */
class IMyMath : public IDispatch
{
public:

	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;/* pure virtual */
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;/* pure virtual */
};

/* CLSID of MyMath component {6D5FD802-4FC6-4B51-ABBC-1BC52707B8E1} */
const CLSID CLSID_MyMath = 
{ 0x6d5fd802, 0x4fc6, 0x4b51, 0xab, 0xbc, 0x1b, 0xc5, 0x27, 0x7, 0xb8, 0xe1 };

/* IID of IMyMath interface {D3172311-1903-46C8-948B-A03EE8DC58C7} */
const IID IID_IMyMath = 
{ 0xd3172311, 0x1903, 0x46c8, 0x94, 0x8b, 0xa0, 0x3e, 0xe8, 0xdc, 0x58, 0xc7 };
