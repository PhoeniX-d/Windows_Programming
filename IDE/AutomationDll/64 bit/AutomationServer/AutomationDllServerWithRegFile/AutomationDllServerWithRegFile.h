/* class declaration */
class IMyMath : public IDispatch
{
public:

	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;/* pure virtual */
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;/* pure virtual */
};

/* CLSID of MyMath component {E2339B4A-387D-4C46-BE3B-667AC160B89C} */
const CLSID CLSID_MyMath = 
{ 0xe2339b4a, 0x387d, 0x4c46, 0xbe, 0x3b, 0x66, 0x7a, 0xc1, 0x60, 0xb8, 0x9c };

/* IID of IMyMath interface {97819FD8-05FB-496F-8A4A-404A56666374} */
const IID IID_IMyMath = 
{ 0x97819fd8, 0x5fb, 0x496f, 0x8a, 0x4a, 0x40, 0x4a, 0x56, 0x66, 0x63, 0x74 };
