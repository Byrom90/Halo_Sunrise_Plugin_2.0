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

const char* SunriseVers = "2.1.0";

in_addr sunrise_ip = { 174, 136, 231, 17 };
INT sunrise_port = 8000;
const char sunrise_description[XTITLE_SERVER_MAX_SERVER_INFO_LEN] = "required,mass_storage,other,ttl,usr,shr,web,dbg,upl,prs,std";


HANDLE hXam;
BOOL bRunContinuous = TRUE;
BOOL bLoopHasComplete = FALSE;
BOOL bIsDevkit; // Set on plugin load. Skips doing xnotify on devkits
DWORD LastTitleId;

DWORD Halo3InternalBeta = 0x4D53883A;
DWORD Halo3ExternalBeta = 0x4D53880C;
DWORD Halo3 = 0x4D5307E6;
DWORD Halo3ODST = 0x4D530877;
DWORD HaloReach = 0x4D53085B;

BOOL bAllowRetailPlayers = TRUE;
BOOL bIgnoreTrueskill = FALSE;

DWORD Halo3_Retail_XUserReadStats_Addr = 0x825B6358;
DWORD Halo3_Epsilon_XUserReadStats_Addr = 0x826E77E8;


VOID AllowRetailPlayers_HALO3_RETAIL()
{
	Sunrise_Dbg("Allowing Retail players");
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
	*((DWORD*)(0x823F8B04)) = 0x60000000;
	*((DWORD*)(0x822BB77C)) = 0x60000000;
	*((DWORD*)(0x822BB788)) = 0x60000000;
	*((DWORD*)(0x822BB794)) = 0x60000000;
	*((DWORD*)(0x822BB7A0)) = 0x60000000;
}

VOID AllowRetailPlayers_HALOREACH_RETAIL()
{
	Sunrise_Dbg("Allowing Retail players");
	// allow MM to start with offline players
	*((DWORD*)(0x82290744)) = 0x60000000;
	*((DWORD*)(0x82290750)) = 0x60000000;

	// disable host migration before map/game variants are downloaded.
	*((DWORD*)(0x82287B20)) = 0x60000000;
	*((DWORD*)(0x82287B24)) = 0x60000000;
	*((DWORD*)(0x82287B28)) = 0x60000000;
	*((DWORD*)(0x82287B2C)) = 0x60000000;
	*((DWORD*)(0x82287B30)) = 0x60000000;
	*((DWORD*)(0x82287B38)) = 0x60000000;
	*((DWORD*)(0x82287B40)) = 0x60000000;
	*((DWORD*)(0x82287B60)) = 0x60000000;
}

VOID Initialise()
{
	hXam = GetModuleHandle(MODULE_XAM);

	if (MountPath(MOUNT_POINT, GetMountPath()) != 0)
	{
		Sunrise_Dbg("Failed to set mount point!");
		return;
	}

	while (bRunContinuous)
	{

		DWORD TitleID = XamGetCurrentTitleId();

		if (TitleID != LastTitleId)
		{
			LastTitleId = TitleID; // Set the last title id  to the current title id so we don't loop rechecking

			if (TitleID == Halo3 || TitleID == Halo3ExternalBeta || TitleID == Halo3InternalBeta) // Check for both regular and alpha/beta title ids
			{
				RegisterActiveServer(sunrise_ip, sunrise_port, sunrise_description);

				Readini(); // Read the ini each time Halo is loaded to avoid having to reload the plugin

				PLDR_DATA_TABLE_ENTRY PLDR_Halo3xex = (PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle;
				//XexPcToFileHeader((PVOID)0x82000000, &PLDR_Halo3xex);

				switch (PLDR_Halo3xex->TimeDateStamp) // Detects the exact xex by timestamp. Prevents patching static addresses in the wrong xex.
				{
				case 0x48C1FB10: // Halo 3 Retail TU2
				{
					Sunrise_Dbg("Halo 3 Retail detected! Initialising hooks...");
					SetupNetDllHooks();

					if (bAllowRetailPlayers)
						AllowRetailPlayers_HALO3_RETAIL();

					if (bIgnoreTrueskill)
						SetupXUserReadStatsHook(Halo3_Retail_XUserReadStats_Addr);

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x46CA8883: // Halo 3 Epsilon Aug 20th 2007
				{
					Sunrise_Dbg("Halo 3 Epsilon (Aug 20th) detected! Initialising hooks...");
					SetupNetDllHooks();

					if (bIgnoreTrueskill)
						SetupXUserReadStatsHook(Halo3_Epsilon_XUserReadStats_Addr);

					// Enable debug logs.
					*((DWORD*)(0x82236154)) = 0x60000000;

					// Add Sunrise to the debug logs.
					RegisterHaloLogger(0x82237920);

					XNotify(L"Halo Sunrise Initialised!");
					break;
				}
				case 0x4637C172: // Halo 3 Beta May 1st 2007
				{
					Sunrise_Dbg("Halo 3 Beta (May 1st) detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x4649437B: // Halo 3 Beta May 15th 2007
				{
					Sunrise_Dbg("Halo 3 Beta (May 15th) detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x455E2AC3: // Halo 3 Pimps at sea (Alpha)
				{
					Sunrise_Dbg("Halo 3 Pimps at sea (Alpha) detected! Initialising hooks...");
					SetupNetDllHooks();

					// Fix a bug where high rank players can't enter matchmaking.
					*((DWORD*)(0x82457578)) = 0x3960000C;
					// Fix another stats bug.
					*((WORD*)(0x82454BAC)) = 0x4800;
					// Force the game to save settings even if a newer file is present.
					*((WORD*)(0x82970B30)) = 0x4800;

					// Enable debug logs.
					*((DWORD*)(0x823b23d0)) = 0x60000000;
					// Move them from cache:\\ to d:\\ 
					const char* reports_path = "d:\\reports\\";
					memcpy(((char*)(0x820B934C)), reports_path, strlen(reports_path) + 1);

					// Add Sunrise to the debug logs.
					RegisterHaloLogger(0x823B2CE8);

					XNotify(L"Halo Sunrise Initialised!");
					break;
				}
				case 0x45F10275: // Halo 3 Delta cache_test
				{
					Sunrise_Dbg("Halo 3 Delta (cache_test, Mar 9th) detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x45F1026C: // Halo 3 Delta cache_release
				{
					Sunrise_Dbg("Halo 3 Delta (cache_release, Mar 9th) detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x45EF61A8: // Halo 3 Delta cache_release
				{
					Sunrise_Dbg("Halo 3 Delta (cache_release, Mar 7th) detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				default:
				{
					Sunrise_Dbg("Unrecognized Halo 3 xex! TimeDateStamp: 0x%X", PLDR_Halo3xex->TimeDateStamp); // Print the timestamp so we can support this xex later if required.
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}

				}
			}
			else if (TitleID == Halo3ODST)
			{
				RegisterActiveServer(sunrise_ip, sunrise_port, sunrise_description);

				Readini(); // Read the ini each time Halo is loaded to avoid having to reload the plugin

				PLDR_DATA_TABLE_ENTRY PLDR_Halo3ODSTxex = (PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle;
				switch (PLDR_Halo3ODSTxex->TimeDateStamp) // Detects the exact xex by timestamp. Prevents patching static addresses in the wrong xex.
				{
				case 0x49F68EC3: // Halo 3 ODST
				{
					Sunrise_Dbg("Halo 3 ODST detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				default:
				{
					Sunrise_Dbg("Unrecognized Halo 3 ODST xex! TimeDateStamp: 0x%X", PLDR_Halo3ODSTxex->TimeDateStamp); // Print the timestamp so we can support this xex later if required.
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}

				}
			}
			else if (TitleID == HaloReach) // Future Reach support
			{
				RegisterActiveServer(sunrise_ip, sunrise_port, sunrise_description);

				Readini(); // Read the ini each time Halo is loaded to avoid having to reload the plugin

				PLDR_DATA_TABLE_ENTRY PLDR_HaloReachxex = (PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle;
				switch (PLDR_HaloReachxex->TimeDateStamp)
				{
				case 0x4C4AAE66:
				{
					Sunrise_Dbg("Halo: Reach detected! Initialising hooks...");
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x4E559FF8: //reach tu
				{
					Sunrise_Dbg("Halo: Reach TU detected! Initialising hooks...");
					SetupNetDllHooks();

					if (bAllowRetailPlayers) {
						AllowRetailPlayers_HALOREACH_RETAIL();
					}

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				case 0x4CC5E691:
				{
					Sunrise_Dbg("Halo: Reach detected! Initialising hooks...");
					SetupNetDllHooks();

					// Load retail maps.
					*((DWORD*)(0x823C0244)) = 0x60000000;
					*((DWORD*)(0x823C01E4)) = 0x60000000;
					// Havok Patch
					*((DWORD*)(0x8305C000)) = 0x60000000;
					*((DWORD*)(0x8305C010)) = 0x60000000;

					XNotify(L"Halo Sunrise Intialised!");
					break;
				}
				default:
				{
					Sunrise_Dbg("Unrecognized Halo Reach xex! TimeDateStamp: 0x%X", PLDR_HaloReachxex->TimeDateStamp); // Print the timestamp so we can support this xex later if required.
					SetupNetDllHooks();

					XNotify(L"Halo Sunrise Intialised!");
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
			Sunrise_Dbg("Plugin load aborted! Disc tray is open");
			HANDLE hSunrise = hModule;
			bLoopHasComplete = TRUE; // Make sure we set this so we don't get stuck in a sleep loop when we unload (DLL_PROCESS_DETACH) in a sec.
			*(WORD*)((DWORD)hSunrise + 64) = 1;
			return FALSE;
		}

		bIsDevkit = *(DWORD*)0x8E038610 & 0x8000 ? FALSE : TRUE; // Simple devkit check
		Sunrise_Dbg("v%s loaded! Running on %s kernel", SunriseVers, bIsDevkit ? "Devkit" : "Retail");
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
		Sunrise_Dbg("Unloaded!");
		break;

	}
	return TRUE;
}
