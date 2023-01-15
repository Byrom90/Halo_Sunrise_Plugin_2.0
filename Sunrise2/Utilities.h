#pragma once

#ifndef UTIL_H
#define UTIL_H
#include "stdafx.h"


FARPROC ResolveFunction(HMODULE hHandle, DWORD Ordinal);
FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal);
VOID PatchInJump(DWORD* addr, DWORD dest, BOOL linked);
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
BOOL IsTrayOpen();
VOID ThreadMe(LPTHREAD_START_ROUTINE lpStartAddress);
VOID XNotify(LPCWSTR pwszStringParam);

DWORD MountPath(PCHAR Drive, PCHAR Device);
PCHAR GetMountPath();

// DO NOT CALL DIRECTLY. USE DEFINE Sunrise_Dbg instead
VOID Sunrise_Print(const CHAR* fmt, ...);

// Prints are only enabled is DO_PRINTS is defined below
#define DO_PRINTS // Comment out to disable prints

#ifdef DO_PRINTS
#define Sunrise_Dbg(x, ...) { do { Sunrise_Print("[Sunrise2] "  x "\n", __VA_ARGS__); } while(0); }
#else
#define Sunrise_Dbg
#endif

#pragma region Sunrise2 ini
#define BASE_ADDR 0x91A00000
#define MOUNT_POINT	 "SR2:"
#define PATH_INI	MOUNT_POINT "\\Sunrise2.ini"

VOID Writeini(BOOL GenerateNew);
VOID Readini();
#pragma endregion

#endif