#include <ntddk.h>
#include "vector.hpp"
#include "testclass.hpp"

extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING);

ktd::vector<int, PagedPool, 'cdtd'> *vec = nullptr;

void
Unload(PDRIVER_OBJECT)
{
	if (!vec)
		return;

	for (auto i = 0UL; i < vec->size(); i++)
	{
		DbgPrint("%d\n", (*vec)[i]);
	}

	delete vec;//calls size_t variant of delete.
	return;
}

void Test_VecInit()
{
	vec = new(PagedPool) ktd::vector<int, PagedPool, 'cdtd'>(10);
	vec->push_back(1);
	vec->push_back(2);
	vec->push_back(3);
	vec->push_back(4);
	vec->push_back(5);
	vec->push_back(6);
	(*vec)[5] = 98;
}

void Test_Random()
{
	ktd::vector<int, PagedPool, 'tset'> *vect = new(PagedPool) ktd::vector<int, PagedPool, 'tset'>(10);
	delete vect;

	test *ptr = new(PagedPool) test[2];
	delete[] ptr;
}

void Test_Copypod()
{
	ktd::vector<int, PagedPool, 'cdtd'> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	ktd::vector<int, PagedPool, 'cdtd'> vec2 = v1;
	vec2;
}

void Test_Copynonpod()
{
	ktd::vector<test, PagedPool, 'cdtd'> somevec;
	test obj;
	somevec.push_back(obj);
	somevec.push_back(test());
	somevec.push_back(test());
	somevec.push_back(test());
	somevec.push_back(obj);
	somevec.push_back(obj);
	somevec.push_back(test());
	somevec.push_back(test());

	ktd::vector<test, PagedPool, 'cdtd'> vec2 = somevec;
	//vec2.push_back(obj);
}

void Test_VecClass()
{	
	ktd::vector<test, NonPagedPool, 'tset'> vectest;
	DbgPrint("test size %lu", sizeof(test));
	vectest.push_back(test());

	test obj;
	vectest.push_back(obj);
	vectest.push_back(obj);
	vectest.push_back(obj);
	vectest.push_back(obj);
}


void Test_Movepod()
{
	ktd::vector<int, PagedPool, 'cdtd'> somevec;
	somevec.push_back(1);
	somevec.push_back(2);
	somevec.push_back(3);
	somevec.push_back(4);
	somevec.push_back(5);

	ktd::vector<int, PagedPool, 'cdtd'> vec2 = move(somevec);
}

void Test_Movenonpod()
{
	ktd::vector<test, PagedPool, 'cdtd'> somevec;
	test obj;
	somevec.push_back(test());
	somevec.push_back(test());
	somevec.push_back(test());
	somevec.push_back(test());
	somevec.push_back(obj);
	somevec.push_back(obj);
	somevec.push_back(test());
	somevec.push_back(test());

	ktd::vector<test, PagedPool, 'cdtd'> vec2 = move(somevec);
}

void Test_Push()
{
	ktd::vector<anothertestclass, PagedPool, 'tset'> v1;
	v1.push_back(1);	//should call constructor and then a move assignment operator.
}

void Test_Emplace()
{
	ktd::vector<anothertestclass, PagedPool, 'tset'> v2;
	v2.emplace_back(1);	//should call constructor.
}

void Test_PushVsEmplace()
{
	Test_Push();
	Test_Emplace();
}

void Test_Reserve()
{
	ktd::vector<anothertestclass, PagedPool, 'tset'> v;
	v.Reserve(15);	//should not call construcotrs.
}

void Test_Default()
{
	ktd::vector<test, PagedPool, 'tset'> vect2(2);
}

NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING)
{	
	Test_Default();
	Test_Reserve();
	Test_PushVsEmplace();

	Test_Movepod();
	Test_Movenonpod();

	Test_Copypod();
	Test_Copynonpod();

	int *i = new(PagedPool) int; i;
	delete i;
	
	Test_VecInit();
	Test_Random();
	Test_VecClass();
	
	DriverObject->DriverUnload = Unload;
	return STATUS_SUCCESS;
}

