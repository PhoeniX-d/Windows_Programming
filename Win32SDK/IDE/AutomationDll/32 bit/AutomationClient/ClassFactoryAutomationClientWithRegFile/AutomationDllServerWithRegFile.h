/* class declaration */
class IMyMath : public IDispatch
{
public:

	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;/* pure virtual */
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;/* pure virtual */
};

/* CLSID of MyMath component {28DD1A38-635C-41F6-843F-59B951417791} */
const CLSID CLSID_MyMath = 
{ 0x28dd1a38, 0x635c, 0x41f6, 0x84, 0x3f, 0x59, 0xb9, 0x51, 0x41, 0x77, 0x91 };

/* IID of IMyMath interface {349BB164-9B46-4F39-A0DB-CD5670553AE1} */
const IID IID_IMyMath = 
{ 0x349bb164, 0x9b46, 0x4f39, 0xa0, 0xdb, 0xcd, 0x56, 0x70, 0x55, 0x3a, 0xe1 };
