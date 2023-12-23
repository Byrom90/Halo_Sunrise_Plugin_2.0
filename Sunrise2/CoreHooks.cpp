#include "stdafx.h"
#include "Sunrise2.h"
#include "Utilities.h"

XTITLE_SERVER_INFO activeServer;
WORD activeServerPort;

int NetDll_socketHook(XNCALLER_TYPE n, int af, int type, int protocol)
{
	int s = NetDll_socket(n, af, type, protocol);
	if (n == 1 && protocol == 6) {
		BOOL b = TRUE;
		NetDll_setsockopt(n, s, SOL_SOCKET, 0x5801, (char*)&b, sizeof(BOOL));
	}

	return s;
}

int NetDll_connectHook(XNCALLER_TYPE n, SOCKET s, const sockaddr* name, int namelen)
{
	if (n == 1) {
		((SOCKADDR_IN*)name)->sin_addr.S_un.S_addr = activeServer.inaServer.S_un.S_addr;
		((SOCKADDR_IN*)name)->sin_port = activeServerPort;
	}

	return NetDll_connect(n, s, name, namelen);;
}

int NetDll_XNetStartupHook(XNCALLER_TYPE xnc, XNetStartupParams* xnsp)
{
	xnsp->cfgFlags |= XNET_STARTUP_BYPASS_SECURITY;
	return NetDll_XNetStartup(xnc, xnsp);
}

int NetDll_XNetUnregisterInAddrHook(XNCALLER_TYPE xnc, IN_ADDR address) {
	if (address.S_un.S_addr == activeServer.inaServer.S_un.S_addr
	) {
		return 0;
	}

	return NetDll_XNetUnregisterInAddr(xnc, address);
}

int NetDll_XNetServerToInAddrHook(XNCALLER_TYPE n, IN_ADDR address_in, DWORD title_id, IN_ADDR* address_out) {
	if (n == 1 && address_in.S_un.S_addr == activeServer.inaServer.S_un.S_addr
		) {
		// Skip the actual bollocks, assume sockpatch is enabled and just copy the IP.
		// If the game manually checks for a secure 0. address, this will die.
		// We'll solve that if it happens.
		address_out->S_un.S_addr = address_in.S_un.S_addr;
		return 0;
	}

	return NetDll_XNetServerToInAddr(n, address_in, title_id, address_out);
}

HANDLE lsp_enum_handle;
int enumeration_index;

int XamCreateEnumeratorHandleHook(DWORD user_index, HXAMAPP app_id, DWORD open_message, DWORD close_message, DWORD extra_size, DWORD item_count, DWORD flags, PHANDLE out_handle)
{
	int result = XamCreateEnumeratorHandle(user_index, app_id, open_message, close_message, extra_size, item_count, flags, out_handle);

	if (open_message == 0x58039) {
		lsp_enum_handle = *out_handle;
		enumeration_index = 0;
	}

	return result;

}


struct halo_log_event
{
	int level;
	long category;
	int flags;
};

halo_log_event sunrise_event = {
	// It's not important, but the category here is wrong. I don't know what it should be.
	4, 1, 0
};


// Idk wtf im doing
typedef LONG
(WINAPI* p_halo_log_func)(
	__in    halo_log_event*    thisEvent,
	__in    char*              message,
	...
	); 

p_halo_log_func halo_logger;

#define write_to_halo_logs(f_, ...)                                 \
{                                                                   \
    if (halo_logger) {                                              \
    	halo_logger(&sunrise_event, (f_), ##__VA_ARGS__);           \
    }                                                               \
};

void RegisterHaloLogger(DWORD address) {
	halo_logger = (p_halo_log_func)address;
}

void RegisterActiveServer(in_addr address, WORD port, const char description[XTITLE_SERVER_MAX_SERVER_INFO_LEN]) {
	activeServer.inaServer.S_un.S_addr = address.S_un.S_addr;
	activeServerPort = port;
	memcpy(activeServer.szServerInfo, description, XTITLE_SERVER_MAX_SERVER_INFO_LEN);
}

int XamEnumerateHook(
	HANDLE hEnum,
	DWORD dwFlags,
	PDWORD pvBuffer,
	DWORD cbBuffer,
	PDWORD pcItemsReturned,
	PXOVERLAPPED pOverlapped
)
{
	if (
		hEnum == lsp_enum_handle
	) {
		write_to_halo_logs("networking:sunrise: XamEnumerateHook(%d, %d, %d, %d, %d, %d)", hEnum, dwFlags, pvBuffer, cbBuffer, pcItemsReturned, pOverlapped);
		write_to_halo_logs("networking:sunrise: XamEnumerateHook with handle %d", hEnum);
		write_to_halo_logs("networking:sunrise: This is enumeration %d", enumeration_index);

		if (cbBuffer < sizeof(XTITLE_SERVER_INFO)) {
			write_to_halo_logs("networking:sunrise: XamEnumerateHook The buffer is too small! %d < %d", cbBuffer, sizeof(XTITLE_SERVER_INFO));
			return ERROR_INSUFFICIENT_BUFFER;
		}

		write_to_halo_logs("networking:sunrise: Copying LSP info from %d to buffer %d", &activeServer, pvBuffer);
		write_to_halo_logs("networking:sunrise: Our server info has IP %d description %s", activeServer.inaServer.S_un.S_addr, activeServer.szServerInfo);
		memcpy(pvBuffer, &activeServer, sizeof(XTITLE_SERVER_INFO));

		int errorCode = enumeration_index == 0 ? 0 : ERROR_NO_MORE_FILES;

		enumeration_index = 1;

		if (pOverlapped) {
			write_to_halo_logs("networking:sunrise: overlapped with low = %d, high = %d, context = %d, error = %d, event = %d",
				pOverlapped->InternalLow,
				pOverlapped->InternalHigh,
				pOverlapped->InternalContext,
				pOverlapped->dwExtendedError,
				pOverlapped->hEvent
			);

			pOverlapped->InternalLow = errorCode;
			pOverlapped->InternalHigh = 1;
			pOverlapped->InternalContext = (ULONG_PTR)GetCurrentThread();
			pOverlapped->dwExtendedError = 0;

			write_to_halo_logs("networking:sunrise: Set overlapped to low = %d, high = %d, context = %d, error = %d, event = %d",
				pOverlapped->InternalLow,
				pOverlapped->InternalHigh,
				pOverlapped->InternalContext,
				pOverlapped->dwExtendedError,
				pOverlapped->hEvent
			);


			if (pOverlapped->hEvent) {
				write_to_halo_logs("networking:sunrise Resetting event...");

				ResetEvent(pOverlapped->hEvent);
			}


			if (pOverlapped->hEvent) {
				write_to_halo_logs("networking:sunrise Setting event...");

				SetEvent(pOverlapped->hEvent);
			}

			write_to_halo_logs("networking:sunrise XamEnumerateHook finished. Hold onto your helmets.");

			return ERROR_IO_PENDING;
		}

		return errorCode;
	}

	return XamEnumerate(hEnum, dwFlags, pvBuffer, cbBuffer, pcItemsReturned, pOverlapped);
}

VOID SetupNetDllHooks()
{
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 12, (DWORD)NetDll_connectHook); // connect
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 3, (DWORD)NetDll_socketHook); // socket
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 51, (DWORD)NetDll_XNetStartupHook);
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 58, (DWORD)NetDll_XNetServerToInAddrHook);
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 63, (DWORD)NetDll_XNetUnregisterInAddrHook);

	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 590, (DWORD)XamCreateEnumeratorHandleHook);
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 592, (DWORD)XamEnumerateHook);

}

DWORD __stdcall XUserReadStats_hook(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD* pcbResults, DWORD* pResults, void*)
{
	if (pcbResults)
		*pcbResults = 4;
	if (pResults)
		*pResults = 0;
	return 0;
}

VOID SetupXUserReadStatsHook(DWORD Address)
{
	Sunrise_Dbg("Ignoring true skill");
	PatchInJump((DWORD*)Address, (DWORD)&XUserReadStats_hook, false);
}
