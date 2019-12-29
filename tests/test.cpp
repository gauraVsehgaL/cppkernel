#include <ntddk.h>
#include "testsvec.hpp"
#include "testwstring.hpp"

extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING);

void
Unload(PDRIVER_OBJECT)
{
	//TestDeInitVector();
	TestDeInitWstring();
	return;
}


NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING)
{
	//TestInitVector();
	TestInitWstring();
	DriverObject->DriverUnload = Unload;
	return STATUS_SUCCESS;
}

