#include "stdafx.h"
#include "Utilities.h"
#include "SimpleIni.h"
#include "Sunrise2.h"

FARPROC ResolveFunction(HMODULE hHandle, DWORD Ordinal) {
	return (hHandle == NULL) ? NULL : GetProcAddress(hHandle, (LPCSTR)Ordinal);
}

FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal)
{
	HMODULE mHandle = GetModuleHandle(ModuleName);
	return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (LPCSTR)Ordinal);
}

VOID PatchInJump(DWORD* addr, DWORD dest, BOOL linked) {
	DWORD temp[4];

	if (dest & 0x8000) // If bit 16 is 1
		temp[0] = 0x3D600000 + (((dest >> 16) & 0xFFFF) + 1); // lis 	%r11, dest>>16 + 1
	else
		temp[0] = 0x3D600000 + ((dest >> 16) & 0xFFFF); // lis 	%r11, dest>>16

	temp[1] = 0x396B0000 + (dest & 0xFFFF); // addi	%r11, %r11, dest&0xFFFF
	temp[2] = 0x7D6903A6; // mtctr	%r11

	if (linked)
		temp[3] = 0x4E800421; // bctrl
	else
		temp[3] = 0x4E800420; // bctr

	memcpy(addr, temp, 0x10);
}

DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress)
{
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);
	if (address == NULL)
		return S_FALSE;

	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL)
		return S_FALSE;

	DWORD result = 2;

	CHAR* stringTable = (CHAR*)(importDesc + 1);

	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);

	for (DWORD x = 0; x < importDesc->ModuleCount; x++)
	{
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++)
		{
			DWORD value = *((DWORD*)importAdd[y]);
			if (value == address)
			{
				memcpy((DWORD*)importAdd[y], &PatchAddress, 4);
				DWORD newCode[4];
				PatchInJump(newCode, PatchAddress, FALSE);
				memcpy((DWORD*)importAdd[y + 1], newCode, 16);
				result = S_OK;
			}
		}
		importTable = (XEX_IMPORT_TABLE_ORG*)(((BYTE*)importTable) + importTable->TableSize);
	}
	return result;
}

DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress)
{
	LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	return (moduleHandle == NULL) ? S_FALSE : PatchModuleImport(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);
}


BOOL IsTrayOpen()
{
	unsigned char msg[0x10];
	unsigned char resp[0x10];
	memset(msg, 0x0, 0x10);
	msg[0] = 0xA;
	HalSendSMCMessage(msg, resp);

	if (resp[1] == 0x60) return TRUE;

	return FALSE;
}


VOID ThreadMe(LPTHREAD_START_ROUTINE lpStartAddress) {
	HANDLE handle;
	DWORD lpThreadId;
	ExCreateThread(&handle, 0, &lpThreadId, (PVOID)XapiThreadStartup, lpStartAddress, NULL, 0x2 | CREATE_SUSPENDED);
	XSetThreadProcessor(handle, 4);
	SetThreadPriority(handle, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(handle);
}

VOID XNotify(LPCWSTR pwszStringParam)
{
	if (bIsDevkit) // We don't need a stupid notify on Devkit. Smh...
		return;
	XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, XUSER_INDEX_ANY, XNOTIFYUI_PRIORITY_HIGH, (PWCHAR)pwszStringParam, NULL);
}


char SunriseFullPath[MAX_PATH];
DWORD MountPath(PCHAR Drive, PCHAR Device)
{
	CHAR Destination[MAX_PATH] = { 0 };
	sprintf_s(Destination, MAX_PATH, (KeGetCurrentProcessType() == PROC_SYSTEM) ? OBJ_SYS_STRING : OBJ_USR_STRING, Drive);
	ANSI_STRING LinkName, DeviceName;
	RtlInitAnsiString(&LinkName, Destination);
	RtlInitAnsiString(&DeviceName, Device);
	ObDeleteSymbolicLink(&LinkName);
	return (DWORD)ObCreateSymbolicLink(&LinkName, &DeviceName);
}

PCHAR GetMountPath() {
	std::wstring ws;
	PLDR_DATA_TABLE_ENTRY TableEntry;
	XexPcToFileHeader((PVOID)BASE_ADDR, &TableEntry);

	ws = TableEntry->FullDllName.Buffer;
	std::string FullDllName(ws.begin(), ws.end());

	ws = TableEntry->BaseDllName.Buffer;
	std::string BaseDllName(ws.begin(), ws.end());

	std::string::size_type i = FullDllName.find(BaseDllName);

	if (i != std::string::npos)
		FullDllName.erase(i, BaseDllName.length());

	memset(SunriseFullPath, 0x0, MAX_PATH);
	strcpy(SunriseFullPath, FullDllName.c_str());

	Sunrise_Dbg("Running from: %s", FullDllName.c_str());


	return SunriseFullPath;
}

BOOL CWriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size)
{
	// Open our file
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fHandle == INVALID_HANDLE_VALUE)
	{
		//DbgPrint("CWriteFile - CreateFile failed");
		return FALSE;
	}

	// Write our data and close
	DWORD writeSize = Size;
	if (WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE)
	{
		//DbgPrint("CWriteFile - WriteFile failed");
		return FALSE;
	}
	CloseHandle(fHandle);

	// All done
	return TRUE;
}

// DO NOT CALL DIRECTLY. USE DEFINE Sunrise_Dbg instead
VOID Sunrise_Print(const CHAR* fmt, ...)
{
#ifdef DO_PRINTS
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
#endif
}

#pragma region Sunrise2 ini
// Use an app or site to convert ini to byte array - https://tomeko.net/online_tools/file_to_hex.php
// Default ini with comments
BYTE INIDATA[213] = {
	0x5B, 0x4F, 0x50, 0x54, 0x49, 0x4F, 0x4E, 0x53, 0x5D, 0x0D, 0x0A, 0x3B, 0x20, 0x41, 0x6C, 0x6C,
	0x6F, 0x77, 0x73, 0x20, 0x6D, 0x61, 0x74, 0x63, 0x68, 0x6D, 0x61, 0x6B, 0x69, 0x6E, 0x67, 0x20,
	0x74, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6B, 0x20, 0x77, 0x68, 0x65, 0x6E, 0x20, 0x74, 0x68, 0x65,
	0x20, 0x6C, 0x65, 0x61, 0x64, 0x65, 0x72, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x20, 0x41, 0x50, 0x49,
	0x20, 0x69, 0x73, 0x20, 0x64, 0x6F, 0x77, 0x6E, 0x2F, 0x62, 0x72, 0x6F, 0x6B, 0x65, 0x6E, 0x0D,
	0x0A, 0x3B, 0x20, 0x4F, 0x6E, 0x6C, 0x79, 0x20, 0x77, 0x6F, 0x72, 0x6B, 0x73, 0x20, 0x66, 0x6F,
	0x72, 0x20, 0x6E, 0x6F, 0x6E, 0x2D, 0x72, 0x65, 0x74, 0x61, 0x69, 0x6C, 0x20, 0x70, 0x6C, 0x61,
	0x79, 0x65, 0x72, 0x73, 0x0D, 0x0A, 0x49, 0x67, 0x6E, 0x6F, 0x72, 0x65, 0x54, 0x72, 0x75, 0x65,
	0x73, 0x6B, 0x69, 0x6C, 0x6C, 0x20, 0x3D, 0x20, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x0D, 0x0A, 0x3B,
	0x20, 0x45, 0x6E, 0x61, 0x62, 0x6C, 0x65, 0x73, 0x20, 0x6D, 0x61, 0x74, 0x63, 0x68, 0x6D, 0x61,
	0x6B, 0x69, 0x6E, 0x67, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x52, 0x65, 0x74, 0x61, 0x69, 0x6C,
	0x20, 0x70, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x73, 0x0D, 0x0A, 0x41, 0x6C, 0x6C, 0x6F, 0x77, 0x52,
	0x65, 0x74, 0x61, 0x69, 0x6C, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x73, 0x20, 0x3D, 0x20, 0x74,
	0x72, 0x75, 0x65, 0x0D, 0x0A
};

// Save changes to (use false) or generate new (use true) Sunrise2.ini
VOID Writeini(BOOL GenerateNew)
{
	CSimpleIniA ini_Sunrise_W;
	ini_Sunrise_W.Reset();
	ini_Sunrise_W.SetSpaces(true);
	if (GenerateNew) {
		if (CWriteFile(PATH_INI, INIDATA, sizeof(INIDATA)) == TRUE)
		{
			Sunrise_Dbg("Sunrise2.ini created successfully!");
			Readini();
		}
		else
			Sunrise_Dbg("Failed to create Sunrise2.ini");

	}
	else {
		if (!ini_Sunrise_W.LoadFile(PATH_INI)) {
			ini_Sunrise_W.SetBoolValue("OPTIONS", "IgnoreTrueskill", bIgnoreTrueskill);
			ini_Sunrise_W.SetBoolValue("OPTIONS", "AllowRetailPlayers", bAllowRetailPlayers);
		}
	}

	if (!GenerateNew && !ini_Sunrise_W.SaveFile(PATH_INI))
	{
		//Sunrise_Dbg("Changes saved to Sunrise2.ini!");
		ini_Sunrise_W.Reset();
	}
	else if (!GenerateNew)
	{
		Sunrise_Dbg("Failed to save changes to Sunrise2.ini!");
	}
}

// Read ini values
VOID Readini()
{
	Sunrise_Dbg("Reading values from Sunrise2.ini");
	CSimpleIniA ini_Sunrise_R;
	ini_Sunrise_R.Reset();
	ini_Sunrise_R.SetSpaces(true);
	if (!ini_Sunrise_R.LoadFile(PATH_INI)) {
		
		bIgnoreTrueskill = ini_Sunrise_R.GetBoolValue("OPTIONS", "IgnoreTrueskill", FALSE);
		bAllowRetailPlayers = ini_Sunrise_R.GetBoolValue("OPTIONS", "AllowRetailPlayers", TRUE);
		ini_Sunrise_R.Reset();


		Writeini(FALSE); // This should ensure that any entries missing from the clients ini will be added with default value
	}
	else {
		Sunrise_Dbg("Error reading Sunrise2.ini. Generating new ini...");
		Writeini(TRUE);
	}
}
#pragma endregion