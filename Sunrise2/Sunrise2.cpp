//-----------------------------------------------------------------------------
//  Sunrise 2.0
//
//  Dev:
//			Byrom
// 
//  Credits:
//			craftycodie - Halo hooks and address
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "CoreHooks.h"
#include "Utilities.h"

FLOAT SunriseVers = 2.00;

CHAR ip[4] = { 174, 136, 231, 17 };
INT port = 8000;


HANDLE hXam;
BOOL bRunContinuous = TRUE;
BOOL bLoopHasComplete = FALSE;
BOOL bIsDevkit; // Set on plugin load. Skips doing xnotify on devkits
DWORD LastTitleId;
DWORD Halo3 = 0x4D5307E6;
DWORD Halo3Pimps = 0x4D53880C;
DWORD HaloReach = 0x4D53085B;
DWORD Halo3Epsilon = 0x4D53883A;

BOOL bAllowRetailPlayers = TRUE;
BOOL bIgnoreTrueskill = TRUE;

DWORD Halo3_Beta_LSP_Addr = 0x820DE740;
DWORD Halo3_Pimps_LSP_Addr = 0x821A7768;
DWORD Halo3_Epsilon_LSP_Addr = 0x8248E820;
DWORD Halo3_Retail_LSP_Addr = 0x823B8EF0;

DWORD Halo3_Retail_XUserReadStats_Addr = 0x825B6358;
DWORD Halo3_Epsilon_XUserReadStats_Addr = 0x826E77E8;


VOID AllowRetailPlayers_HALO3_RETAIL()
{
	// allow MM to start with offline peers
	*((DWORD*)(0x822BA37C)) = 0x60000000;
	// disable host migration before map/game variants are downloaded.
	*((DWORD*)(0x824004BC)) = 0x60000000;
	*((DWORD*)(0x824004C0)) = 0x60000000;
	*((DWORD*)(0x824004C4)) = 0x60000000;
	*((DWORD*)(0x824004C8)) = 0x60000000;
	*((DWORD*)(0x824004CC)) = 0x60000000;
	*((DWORD*)(0x824004D0)) = 0x60000000;
	*((DWORD*)(0x824004D4)) = 0x60000000;
	*((DWORD*)(0x824004D8)) = 0x60000000;

	// Allow MM to start with peers who don't have exp loaded
	// Doesn't work fully yet.
	*((DWORD*)(0x823F8B04)) = 0x60000000;

	*((DWORD*)(0x822BB77C)) = 0x60000000;
	*((DWORD*)(0x822BB788)) = 0x60000000;
	*((DWORD*)(0x822BB794)) = 0x60000000;
	*((DWORD*)(0x822BB7A0)) = 0x60000000;
}

VOID Initialise()
{
	hXam = GetModuleHandle(MODULE_XAM);

	while (bRunContinuous)
	{

		DWORD TitleID = XamGetCurrentTitleId();

		if (TitleID != LastTitleId) 
		{
			LastTitleId = TitleID; // Set the last title id  to the current title id so we don't loop rechecking

			if (TitleID == Halo3 || TitleID == Halo3Pimps || TitleID == Halo3Epsilon) // Check for both regular and alpha/beta title ids
			{
				PLDR_DATA_TABLE_ENTRY PLDR_Halo3xex = (PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle;
				//XexPcToFileHeader((PVOID)0x82000000, &PLDR_Halo3xex);

				switch (PLDR_Halo3xex->TimeDateStamp) // Detects the exact xex by timestamp. Prevents patching static addresses in the wrong xex.
				{
				case 0x48C1FB10: // Halo 3 Retail latest TU 
				{
					printf("[Sunrise2] Halo 3 Retail detected! Initialising hooks...\n");
					SetupNetDllHooks();
					SetupLSPHook(Halo3_Retail_LSP_Addr);
					if (bAllowRetailPlayers)
						AllowRetailPlayers_HALO3_RETAIL();

					if (bIgnoreTrueskill)
						SetupXUserReadStatsHook(Halo3_Retail_XUserReadStats_Addr);

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x46CA8883: // Halo 3 Epsilon Aug 20th 2007
				{
					printf("[Sunrise2] Halo 3 Epsilon (Aug 20th) detected! Initialising hooks...\n");
					SetupNetDllHooks();
					SetupLSPHook(Halo3_Epsilon_LSP_Addr);

					if (bIgnoreTrueskill)
						SetupXUserReadStatsHook(Halo3_Epsilon_XUserReadStats_Addr);

					// Enable debug logs.
					*((DWORD*)(0x82236154)) = 0x60000000;

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x4637C172: // Halo 3 Beta May 1st 2007
				{
					printf("[Sunrise2] Halo 3 Beta (May 1st) detected! Initialising hooks...\n");
					SetupNetDllHooks();
					SetupLSPHook(Halo3_Beta_LSP_Addr);

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x455E2AC3: // Halo 3 Pimps at sea (Alpha)
				{
					printf("[Sunrise2] Halo 3 Pimps at sea (Alpha) detected! Initialising hooks...\n");
					SetupNetDllHooks();
					SetupLSPHook(Halo3_Pimps_LSP_Addr);
					
					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				default:
				{
					printf("[Sunrise2] Unsupported Halo 3 xex! TimeDateStamp: 0x%X\n", PLDR_Halo3xex->TimeDateStamp); // Print the timestamp so we can support this xex later if required.
					break;
				}

				}
			}
			else if (TitleID == HaloReach) // Future Reach support
			{
				PLDR_DATA_TABLE_ENTRY PLDR_HaloReachxex = (PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle;
				switch (PLDR_HaloReachxex->TimeDateStamp)
				{
				default:
				{
					printf("[Sunrise2] Unsupported Halo Reach xex! TimeDateStamp: 0x%X\n", PLDR_HaloReachxex->TimeDateStamp); // Print the timestamp so we can support this xex later if required.
					break;
				}
				}
			}
		}
		Sleep(500); // Add a slight delay to the check loop
	}
	bLoopHasComplete = TRUE;
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (IsTrayOpen())
		{
			printf("[Sunrise2] Plugin load aborted! Disc tray is open\n");
			HANDLE hSunrise = hModule;
			bLoopHasComplete = TRUE; // Make sure we set this so we don't get stuff in a sleep loop when we unload (DLL_PROCESS_DETACH) in a sec.
			*(WORD*)((DWORD)hSunrise + 64) = 1;
			return FALSE;
		}
		
		bIsDevkit = *(DWORD*)0x8E038610 & 0x8000 ? FALSE : TRUE; // Simple devkit check
		printf("[Sunrise2] v%.02f loaded! Running on %s kernel\n", SunriseVers, bIsDevkit ? "Devkit" : "Retail");
		ThreadMe((LPTHREAD_START_ROUTINE)Initialise);
		
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		bRunContinuous = FALSE; // Exit the continuous loop
		while (!bLoopHasComplete) // Wait for loop to complete
			Sleep(100);

		Sleep(500);
		printf("[Sunrise2] Unloaded!\n", SunriseVers);
		break;

	}
	return TRUE;
}
