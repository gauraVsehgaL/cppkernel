#include <ntddk.h>
#include <wstring>

void TestDefault()
{
	ktd::wstring<PagedPool, 'test'> somestring(L"Hello");

	auto another = somestring;
}

void TestInitWstring()
{
	TestDefault();
}

void TestDeInitWstring()
{

}
