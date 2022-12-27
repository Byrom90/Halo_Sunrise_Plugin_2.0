#include "stdafx.h"
#include "Sunrise2.h"
#include "Utilities.h"

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
		((SOCKADDR_IN*)name)->sin_addr.S_un.S_un_b.s_b1 = ip[0];
		((SOCKADDR_IN*)name)->sin_addr.S_un.S_un_b.s_b2 = ip[1];
		((SOCKADDR_IN*)name)->sin_addr.S_un.S_un_b.s_b3 = ip[2];
		((SOCKADDR_IN*)name)->sin_addr.S_un.S_un_b.s_b4 = ip[3];
		((SOCKADDR_IN*)name)->sin_port = port;
	}

	return NetDll_connect(n, s, name, namelen);;
}

int NetDll_XNetStartupHook(XNCALLER_TYPE xnc, XNetStartupParams* xnsp)
{
	xnsp->cfgFlags |= XNET_STARTUP_BYPASS_SECURITY;
	return NetDll_XNetStartup(xnc, xnsp);
}


VOID SetupNetDllHooks()
{
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 12, (DWORD)NetDll_connectHook); // connect
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 3, (DWORD)NetDll_socketHook); // socket
	PatchModuleImport((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle, "xam.xex", 51, (DWORD)NetDll_XNetStartupHook);
}


int __fastcall lsp_server_hook(char* lsp_manager, int service_type, DWORD* out_connection_token, DWORD* lsp_ip_address, unsigned __int16* lsp_port, char* Source)
{
	int result; // r3

	*lsp_ip_address = (int)ip;
	*lsp_port = port;
	*out_connection_token = 1;
	result = 1;
	return result;
}

VOID SetupLSPHook(DWORD Address)
{
	PatchInJump((DWORD*)Address, (DWORD)&lsp_server_hook, false);
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
	PatchInJump((DWORD*)Address, (DWORD)&XUserReadStats_hook, false);
}