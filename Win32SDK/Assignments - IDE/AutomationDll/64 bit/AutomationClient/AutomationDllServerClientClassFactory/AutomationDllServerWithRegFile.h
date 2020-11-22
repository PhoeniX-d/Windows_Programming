class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

/* CLSID of MyMath component : {DABB2740-C7DB-43FF-A321-03039B49C189} */
const CLSID CLSID_MyMath =
{ 0xdabb2740, 0xc7db, 0x43ff, 0xa3, 0x21, 0x3, 0x3, 0x9b, 0x49, 0xc1, 0x89 };

/* IID of IMyMath Interface : {08BE5A89-D22B-4B2C-A02A-DB801147A596} */
const IID IID_IMyMath =
{ 0x8be5a89, 0xd22b, 0x4b2c, 0xa0, 0x2a, 0xdb, 0x80, 0x11, 0x47, 0xa5, 0x96 };
