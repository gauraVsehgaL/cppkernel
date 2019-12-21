#include <ntddk.h>
#include "testsvec.hpp"

extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING);

void
Unload(PDRIVER_OBJECT)
{
	TestDeInitVector();
	return;
}



NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING)
{
	TestInitVector();
	DriverObject->DriverUnload = Unload;
	return STATUS_SUCCESS;
}

