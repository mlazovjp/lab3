// lab3keygenerator.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include "Windows.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")

void outputPassword1() {
	printf("\nPassword1:\tFGHIJK6789:;\n");
}


void outputPassword2() {
	printf("\nPassword2:\tAQAEE@GBDC;G\n");
}


void outputPassword3() {
	printf("\nPassword3:\tGN\"EH\\CU[(+*\n");
}


void outputPassword4() {

	TCHAR volumeName[MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;

	if (GetVolumeInformation(
		_T("C:\\"),
		volumeName,
		ARRAYSIZE(volumeName),
		& serialNumber,
		& maxComponentLen,
		& fileSystemFlags,
		fileSystemName,
		ARRAYSIZE(fileSystemName)))
	{
		_tprintf(_T("\nPassword4:\t%lu\n"), serialNumber);
	}

}

// https://gist.github.com/yoggy/1241986
void print_adapter(PIP_ADAPTER_ADDRESSES aa)
{
	char buf[BUFSIZ];
	memset(buf, 0, BUFSIZ);
	WideCharToMultiByte(CP_ACP, 0, aa->FriendlyName, wcslen(aa->FriendlyName), buf, BUFSIZ, NULL, NULL);
	printf("adapter_name:%s\n", buf);
}

// https://gist.github.com/yoggy/1241986
void print_addr(PIP_ADAPTER_UNICAST_ADDRESS ua)
{
	char buf[BUFSIZ];

	int family = ua->Address.lpSockaddr->sa_family;
	printf("\t%s ", family == AF_INET ? "IPv4" : "IPv6");

	memset(buf, 0, BUFSIZ);
	getnameinfo(ua->Address.lpSockaddr, ua->Address.iSockaddrLength, buf, sizeof(buf), NULL, 0, NI_NUMERICHOST);
	printf("%s\n", buf);
}


// https://gist.github.com/yoggy/1241986
bool print_ipaddress()
{
	DWORD rv, size;
	PIP_ADAPTER_ADDRESSES adapter_addresses, aa;
	PIP_ADAPTER_UNICAST_ADDRESS ua;

	rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &size);
	if (rv != ERROR_BUFFER_OVERFLOW) {
		fprintf(stderr, "GetAdaptersAddresses() failed...");
		return false;
	}
	adapter_addresses = (PIP_ADAPTER_ADDRESSES)malloc(size);

	rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);
	if (rv != ERROR_SUCCESS) {
		fprintf(stderr, "GetAdaptersAddresses() failed...");
		free(adapter_addresses);
		return false;
	}

	//aa = adapter_addresses + 1;		// jump ahead 376 bytes?	
	//printf("adapter_addresses = %d\n", adapter_addresses);
	//printf("aa = %d\n", aa);

	//printf("\nadapter_addresses.AdapterName=%d\n", (adapter_addresses)->AdapterName);
	//printf("adapter_addresses.AdapterName=%x\n", (adapter_addresses)->AdapterName);
	printf("adapter_addresses.AdapterName=%s\n", (adapter_addresses)->AdapterName);

	//printf("\nadapter_addresses.PhysicalAddress=%d\n", (adapter_addresses)->PhysicalAddress);
	//printf("adapter_addresses.PhysicalAddress=%x\n", (adapter_addresses)->PhysicalAddress);
	//printf("adapter_addresses.PhysicalAddress=%s\n", (adapter_addresses)->PhysicalAddress);

	for (aa = adapter_addresses; aa != NULL; aa = aa->Next) {
		print_adapter(aa);
		for (ua = aa->FirstUnicastAddress; ua != NULL; ua = ua->Next) {
			print_addr(ua);
		}
	}

	free(adapter_addresses);
}



void outputPassword5() {
	
	// ****************************************************
	// setup heap allocation - begin
	// ****************************************************
	// get handle to process heap
	HANDLE hProcessHeap = GetProcessHeap();

	DWORD dwFlags = 0;
	DWORD dwBytes = 0x178;

	// allocate heap of 376 bytes
	HANDLE hAllocatedHeap = HeapAlloc(hProcessHeap, dwFlags, dwBytes);

	


	// ****************************************************
	// setup heap allocation - end
	// ****************************************************

	/*
	// ****************************************************
	// setup get adapter addresses - begin
	// ****************************************************
	ULONG Family = AF_INET;		// Return only IPv4 addresses associated with adapters with IPv4 enabled.
	ULONG Flags = NULL;			// unicast, anycast, and multicast IP addresses will be returned.
	PVOID Reserved = NULL;
	PIP_ADAPTER_ADDRESSES AdapterAddresses;	// A pointer to a buffer that contains a linked list of IP_ADAPTER_ADDRESSES structures on successful return.
	//PULONG SizePointer;			// A pointer to a variable that specifies the size of the buffer pointed to by AdapterAddresses.
	DWORD SizePointer;

	DWORD rv = GetAdaptersAddresses(Family, Flags, Reserved, AdapterAddresses, &SizePointer);

	printf("\nrv=%d", rv);
	printf("\nERROR_ADDRESS_NOT_ASSOCIATED=%d", ERROR_ADDRESS_NOT_ASSOCIATED);
	printf("\nERROR_BUFFER_OVERFLOW=%d", ERROR_BUFFER_OVERFLOW);
	printf("\nERROR_INVALID_PARAMETER=%d", ERROR_INVALID_PARAMETER);
	printf("\nERROR_NOT_ENOUGH_MEMORY=%d", ERROR_NOT_ENOUGH_MEMORY);
	printf("\nERROR_NO_DATA=%d", ERROR_NO_DATA);

	
	for (PIP_ADAPTER_ADDRESSES aa = AdapterAddresses; aa != NULL; aa = aa->Next) {

		printf("\nPassword5:\tTBD\n");
		//print_adapter(aa);
		//for (ua = aa->FirstUnicastAddress; ua != NULL; ua = ua->Next) {
		//	print_addr(ua);
		//}
	}




	// ****************************************************
	// setup get adapter addresses - end
	// ****************************************************

	// free memory used by heap allocation
	HeapFree(hProcessHeap, dwFlags, hAllocatedHeap);


	*/

	print_ipaddress();

	printf("\nPassword5:\tTBD\n");
}









int main(int argc, char *argv[]) {

		outputPassword1();
		outputPassword2();
		outputPassword3();
		outputPassword4();
		outputPassword5();

    return 0;
}