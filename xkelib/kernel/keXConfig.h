// xconfig.h currently updated to 17150
#ifndef _XCONFIG_H
#define _XCONFIG_H

#ifndef __cplusplus
	// disable: warning C4214: nonstandard extension used : bit field types other than int
	#pragma warning(disable:4214)
#endif
/* these settings are located in mobile files and flash config as follows:
XCONFIG_STATIC_SETTINGS					smc config
XCONFIG_STATISTIC_SETTINGS				statistics.settings 0x0 for 0x600
XCONFIG_SECURED_SETTINGS				follows smc config for 0x200
XCONFIG_USER_SETTINGS					mobileB.dat at 0x0 for 0x1FD
XCONFIG_XNET_MACHINE_ACCOUNT_SETTINGS	mobileC.dat at 0x0 for 0x1F0
XCONFIG_XNET_PARAMETERS_SETTINGS		mobileB.dat at 0x400 for 0x1F0
XCONFIG_MEDIA_CENTER_SETTINGS			mobileD.dat at 0x0 for 0x74c
XCONFIG_CONSOLE_SETTINGS				mobileB.dat at 0x200 for 0x1ed
XCONFIG_DVD_SETTINGS					mobileE.dat at 0x0 for 0x298
XCONFIG_IPTV_SETTINGS					mobileB.dat at 0x600 for 0x200
XCONFIG_SYSTEM_SETTINGS					mobileE.dat at 0x400 for 0x20
XCONFIG_DEVKIT_SETTINGS					mobileE.dat at 0x600 for 0x1a
*/
//char* XConfigNames[] = { // names of categories
//	"XCONFIG_STATIC_CATEGORY", 
//	"XCONFIG_STATISTIC_CATEGORY", 
//	"XCONFIG_SECURED_CATEGORY", 
//	"XCONFIG_USER_CATEGORY", 
//	"XCONFIG_XNET_MACHINE_ACCOUNT_CATEGORY", 
//	"XCONFIG_XNET_PARAMETERS_CATEGORY", 
//	"XCONFIG_MEDIA_CENTER_CATEGORY", 
//	"XCONFIG_CONSOLE_CATEGORY", 
//	"XCONFIG_DVD_CATEGORY", 
//	"XCONFIG_IPTV_CATEGORY", 
//	"XCONFIG_SYSTEM_CATEGORY",
//	"XCONFIG_DEVKIT_CATEGORY"
//};

enum { // category enumerator
	//XCONFIG_CATEGORY_TYPES
	XCONFIG_STATIC_CATEGORY = 0x0,					//_XCONFIG_STATIC_SETTINGS
	XCONFIG_STATISTIC_CATEGORY = 0x1,				//_XCONFIG_STATISTIC_SETTINGS
	XCONFIG_SECURED_CATEGORY = 0x2,					//_XCONFIG_SECURED_SETTINGS
	XCONFIG_USER_CATEGORY = 0x3,					//_XCONFIG_USER_SETTINGS
	XCONFIG_XNET_MACHINE_ACCOUNT_CATEGORY = 0x4,	//_XCONFIG_XNET_SETTINGS
	XCONFIG_XNET_PARAMETERS_CATEGORY = 0x5,			//_XCONFIG_XNET_SETTINGS
	XCONFIG_MEDIA_CENTER_CATEGORY = 0x6,			//_XCONFIG_MEDIA_CENTER_SETTINGS
	XCONFIG_CONSOLE_CATEGORY = 0x7, 				//_XCONFIG_CONSOLE_SETTINGS
	XCONFIG_DVD_CATEGORY = 0x8, 					//_XCONFIG_DVD_SETTINGS
	XCONFIG_IPTV_CATEGORY = 0x9, 					//_XCONFIG_IPTV_SETTINGS
	XCONFIG_SYSTEM_CATEGORY = 0xa,					//_XCONFIG_SYSTEM_SETTINGS
	XCONFIG_DEVKIT_CATEGORY = 0xb,					//_XCONFIG_DEVKIT_SETTINGS
	XCONFIG_CATEGORY_MAX
};


#pragma warning(push)
#pragma warning(disable: 4201)  // unnamed struct/union
#pragma pack(push, 1)

/* **************************** _XCONFIG_SECURED_SETTINGS **************************** */
//XCONFIG_SECURED_ENTRIES
enum{
	XCONFIG_SECURED_DATA = 0x0,
	XCONFIG_SECURED_MAC_ADDRESS = 0x1,
	XCONFIG_SECURED_AV_REGION = 0x2,
	XCONFIG_SECURED_GAME_REGION = 0x3,
	XCONFIG_SECURED_DVD_REGION = 0x4,
	XCONFIG_SECURED_RESET_KEY = 0x5,
	XCONFIG_SECURED_SYSTEM_FLAGS = 0x6,
	XCONFIG_SECURED_POWER_MODE = 0x7,
	XCONFIG_SECURED_ONLINE_NETWORK_ID = 0x8,
	XCONFIG_SECURED_POWER_VCS_CONTROL = 0x9,
	XCONFIG_SECURED_MANUFACTURING_SERIAL_NUMBER = 0xA,
	XCONFIG_SECURED_ENTRIES_MAX
};

// _XCONFIG_SECURED_SETTINGS macros for key pointers
#define XK_SECURED_1(x) &x.MACAddress					// key 0x1 6 bytes
#define XK_SECURED_2(x) &x.AVRegion						// key 0x2 4 bytes
#define XK_SECURED_3(x) &x.GameRegion					// key 0x3 2 bytes
#define XK_SECURED_4(x) &x.DVDRegion					// key 0x4 4 bytes
#define XK_SECURED_5(x) &x.ResetKey						// key 0x5 4 bytes
#define XK_SECURED_6(x) &x.OnlineNetworkID				// key 0x8 4 bytes
#define XK_SECURED_7(x) &x.PowerMode					// key 0x7 2 bytes
#define XK_SECURED_8(x) &x.SystemFlags					// key 0x6 4 bytes
#define XK_SECURED_9(x) &x.PowerVcsControl				// key 0x9 2 bytes
#define XK_SECURED_A(x) &x.ManufacturingSerialNumber	// key 0xA 16 bytes

typedef struct _XCONFIG_POWER_MODE{ // used by _XCONFIG_SECURED_SETTINGS
	BYTE VIDDelta;
	BYTE Reserved;
} XCONFIG_POWER_MODE, *PXCONFIG_POWER_MODE;

typedef struct _XCONFIG_POWER_VCS_CONTROL{ // used by _XCONFIG_SECURED_SETTINGS
	USHORT Configured : 1;
	USHORT Reserved : 3;
	USHORT Full : 4;
	USHORT Quiet : 4;
	USHORT Fuse : 4;
} XCONFIG_POWER_VCS_CONTROL, *PXCONFIG_POWER_VCS_CONTROL; // 2 bytes

typedef struct _XCONFIG_SECURED_SETTINGS { 
	DWORD CheckSum; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	char OnlineNetworkID[0x4]; // key 0x8 0x8 sz:0x4
	char Reserved1[0x4]; // 0xC sz:0x4
	char ManufacturingSerialNumber[0x10]; // key 0xA 0x10 sz:0x10
	UCHAR MACAddress[0x6]; // key 0x1 0x20 sz:0x6
	char Reserved3[0x2]; // 0x26 sz:0x2
	DWORD AVRegion; // key 0x2 0x28 sz:0x4
	USHORT GameRegion; // key 0x3 0x2C sz:0x2
	char Reserved4[0x6]; // 0x2E sz:0x6
	DWORD DVDRegion; // key 0x4 0x34 sz:0x4
	DWORD ResetKey; // key 0x5 0x38 sz:0x4
	DWORD SystemFlags; // key 0x6 0x3C sz:0x4
	XCONFIG_POWER_MODE PowerMode; // key 0x7 0x40 sz:0x2
	XCONFIG_POWER_VCS_CONTROL PowerVcsControl; // key 0x9 0x42 sz:0x2
	char ReservedRegion[0x1BC]; // 0x44 sz:0x1BC
} XCONFIG_SECURED_SETTINGS, *PXCONFIG_SECURED_SETTINGS; // size 512
C_ASSERT(sizeof(XCONFIG_SECURED_SETTINGS) == 0x200);


/* **************************** _XCONFIG_CONSOLE_SETTINGS **************************** */
//XCONFIG_CONSOLE_ENTRIES
enum _XCONFIG_CONSOLE_ENTRIES {
	XCONFIG_CONSOLE_DATA = 0x0,
	XCONFIG_CONSOLE_SCREEN_SAVER = 0x1,
	XCONFIG_CONSOLE_AUTO_SHUT_OFF = 0x2,
	XCONFIG_CONSOLE_WIRELESS_SETTINGS = 0x3,
	XCONFIG_CONSOLE_CAMERA_SETTINGS = 0x4,
	XCONFIG_CONSOLE_PLAYTIMERDATA = 0x5,
	XCONFIG_CONSOLE_MEDIA_DISABLEAUTOLAUNCH = 0x6,
	XCONFIG_CONSOLE_KEYBOARD_LAYOUT = 0x7,
	XCONFIG_CONSOLE_PC_TITLE_EXEMPTIONS = 0x8,
	XCONFIG_CONSOLE_NUI = 0x9,
	XCONFIG_CONSOLE_VOICE = 0xA,
	XCONFIG_CONSOLE_RETAIL_EX_FLAGS = 0xB,
	XCONFIG_CONSOLE_UNUSED_2 = 0xC, // previously was XCONFIG_CONSOLE_DASH_FIRST_USE_TUTORIAL_FLAGS = 0xC
	XCONFIG_CONSOLE_TV_DIAGONAL_SIZE_IN_CM = 0xD,
	XCONFIG_CONSOLE_NETWORKSTORAGEDEVICE_SERIALNUMBER = 0xE,
	XCONFIG_CONSOLE_DISCOVERABLE = 0xF,
	XCONFIG_CONSOLE_LIVE_TV_PROVIDER = 0x10,
	XCONFIG_CONSOLE_UNUSED_1 = 0x11, // unknown what this was
	XCONFIG_CONSOLE_CLOSEDCAPTIONINGSTATE = 0x12,
	XCONFIG_CONSOLE_CLOSEDCAPTIONINGSETTINGS = 0x13,
	XCONFIG_CONSOLE_ENCRYPTEDCONTRACTDATA = 0x14,
	XCONFIG_CONSOLE_MAX
};

// _XCONFIG_CONSOLE_SETTINGS macros for key pointers
#define XK_CONSOLE_1(x) &x.ScreenSaver						// key 0x1 2 bytes
#define XK_CONSOLE_2(x) &x.AutoShutoff						// key 0x2 2 bytes
#define XK_CONSOLE_3(x) &x.WirelessSettings					// key 0x3 256 bytes
#define XK_CONSOLE_4(x) &x.CameraSettings					// key 0x4 4 bytes
#define XK_CONSOLE_5(x) &x.PlayTimerData					// key 0x5 20 bytes
#define XK_CONSOLE_6(x) &x.MediaDisableAutoLaunch			// key 0x6 2 bytes
#define XK_CONSOLE_7(x) &x.KeyboardLayout					// key 0x7 2 bytes
#define XK_CONSOLE_8(x) &x.ParentalControlTitleExemptions	// key 0x8 0x64 bytes
#define XK_CONSOLE_9(x) &x.Nui								// key 0x9 0x28 bytes
#define XK_CONSOLE_A(x) &x.VoiceVolumeDucking				// key 0xA 1 byte
#define XK_CONSOLE_B(x) &x.RetailExFlags					// key 0xB 4 bytes
#define XK_CONSOLE_C(x) &x.DashFirstUseTutorialFlags		// key 0xC 4 byte
#define XK_CONSOLE_D(x) &x.TVDiagonalSizeInCm				// key 0xD 2 byte
#define XK_CONSOLE_E(x) &x.NetworkStorageDeviceSerialNumber	// key 0xE 20 byte
#define XK_CONSOLE_F(x) &x.ConsoleDiscoverable				// key 0xF 1 byte
#define XK_CONSOLE_10(x) &x.LiveTVProvider					// key 0x10 4 byte
#define XK_CONSOLE_11(x) &x.Unused							// key 0x11 2 byte
#define XK_CONSOLE_12(x) &x.ClosedCaptioning				// key 0x12 1 byte
#define XK_CONSOLE_13(x) &x.ClosedCaptioningSettings		// key 0x13 4 byte
#define XK_CONSOLE_14(x) &x.EncryptedContractData			// key 0x14 26 byte

typedef struct _XCONFIG_PLAYTIMERDATA {  // used by _XCONFIG_CONSOLE_SETTINGS
	ULARGE_INTEGER uliResetDate; // 0x0 sz:0x8
	DWORD dwPlayTimerFrequency; // 0x8 sz:0x4
	DWORD dwTotalPlayTime; // 0xC sz:0x4
	DWORD dwRemainingPlayTime; // 0x10 sz:0x4
} XCONFIG_PLAYTIMERDATA, *PXCONFIG_PLAYTIMERDATA; // size 20
C_ASSERT(sizeof(XCONFIG_PLAYTIMERDATA) == 0x14);

typedef struct _XCONFIG_NUI { 
	DWORD Flags; // 0x0 sz:0x4
	float DistanceToPlayspace; // 0x4 sz:0x4
	s32 AutoTiltAngle; // 0x8 sz:0x4
	BYTE Reserved[0x10]; // 0xC sz:0x10
} XCONFIG_NUI, *PXCONFIG_NUI; // size 28
C_ASSERT(sizeof(XCONFIG_NUI) == 0x1C);

typedef struct _XCONFIG_PC_TITLE_EXEMPTIONS { 
	DWORD TitleIDs[0x19]; // 0x0 sz:0x64
} XCONFIG_PC_TITLE_EXEMPTIONS, *PXCONFIG_PC_TITLE_EXEMPTIONS; // size 100
C_ASSERT(sizeof(XCONFIG_PC_TITLE_EXEMPTIONS) == 0x64);

//found in xconfig.h of sdk
/*typedef struct _XCLOSEDCAPTIONING_SETTINGS {
	DWORD UseDefaults : 1; // 0x0 bfo:0x0
	DWORD EdgeAttribute : 3; // 0x0 bfo:0x1
	DWORD FontColor : 4; // 0x0 bfo:0x4
	DWORD FontSize : 2; // 0x0 bfo:0x8
	DWORD FontStyle : 4; // 0x0 bfo:0x10
	DWORD FontOpacity : 2; // 0x0 bfo:0x14
	DWORD BackgroundColor : 4; // 0x0 bfo:0x16
	DWORD BackgroundOpacity : 2; // 0x0 bfo:0x20
	DWORD WindowOpacity : 2; // 0x0 bfo:0x22
	DWORD WindowColor : 4; // 0x0 bfo:0x24
	DWORD PreferredLanguage : 4; // 0x0 bfo:0x28
} XCLOSEDCAPTIONING_SETTINGS, *PXCLOSEDCAPTIONING_SETTINGS; // size 4
C_ASSERT(sizeof(XCLOSEDCAPTIONING_SETTINGS) == 0x4);*/


typedef struct _XCONFIG_CONSOLE_SETTINGS { 
	DWORD CheckSum; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	SHORT ScreenSaver; // key 0x1 0x8 sz:0x2
	SHORT AutoShutOff; // key 0x2 0xA sz:0x2
	UCHAR WirelessSettings[0x100]; //key 0x3 0xC sz:0x100
	DWORD CameraSettings; // key 0x4 0x10C sz:0x4
	XCONFIG_NUI Nui; // key 0x9 12625 0x110 sz:0x1C
	XCONFIG_PLAYTIMERDATA PlayTimerData; // key 0x5 0x12C sz:0x14
	SHORT MediaDisableAutoLaunch; // key 0x6 0x140 sz:0x2
	SHORT KeyboardLayout; // key 0x7 0x142 sz:0x2
	XCONFIG_PC_TITLE_EXEMPTIONS ParentalControlTitleExemptions; // key 0x8 0x144 sz:0x64
	UCHAR VoiceVolumeDucking; // key 0xA 0x1A8 sz:0x1
	DWORD RetailExFlags; // key 0xB 0x1A9 sz:0x4
	DWORD DashFirstUseTutorialFlags; // key 0xC 0x1AD sz:0x4 *depreciated as of 164## dash*
	USHORT TVDiagonalSizeInCm; // key 0xD 0x1B1 sz:0x2
	UCHAR NetworkStorageDeviceSerialNumber[0x14]; // key 0xE 0x1B3 sz:0x14
	UCHAR ConsoleDiscoverable; // key 0xF 0x1C7 sz:0x1
	DWORD LiveTVProvider; // key 0x10 0x1C8 sz:0x4
	UCHAR Unused[0x2]; // key 0x11 0x1CC sz:0x2
	UCHAR ClosedCaptioning; // key 0x12 0x1CE sz:0x1
	XCLOSEDCAPTIONING_SETTINGS ClosedCaptioningSettings; // key 0x13 0x1CF sz:0x4
	UCHAR EncryptedContractData[0x1A]; // key 0x14 0x1D3 sz:0x1A
} XCONFIG_CONSOLE_SETTINGS, *PXCONFIG_CONSOLE_SETTINGS; // size 493
C_ASSERT(sizeof(XCONFIG_CONSOLE_SETTINGS) == 0x1ED);



/* **************************** _XCONFIG_DVD_SETTINGS **************************** */
//XCONFIG_DVD_ENTRIES
enum{
	XCONFIG_DVD_ALL = 0x0,
	XCONFIG_DVD_VOLUME_ID = 0x1,
	XCONFIG_DVD_BOOKMARK = 0x2,
	XCONFIG_DVD_ENTRIES_MAX
};

// _XCONFIG_DVD_SETTINGS macros for key pointers
#define XK_DVD_1(x) &x.VolumeId	// key 0x1 20 bytes
#define XK_DVD_2(x) &x.Data		// key 0x2 640 bytes

typedef struct _XCONFIG_DVD_SETTINGS { 
	DWORD Version; // 0x0 sz:0x4
	BYTE VolumeId[0x14]; // 0x4 sz:0x14 key 0x1
	BYTE Data[0x280]; // 0x18 sz:0x280 key 0x2
} XCONFIG_DVD_SETTINGS, *PXCONFIG_DVD_SETTINGS; // size 664
C_ASSERT(sizeof(XCONFIG_DVD_SETTINGS) == 0x298);


/* **************************** _XCONFIG_IPTV_SETTINGS **************************** */
//XCONFIG_IPTV_ENTRIES
enum{
	XCONFIG_IPTV_DATA = 0x0,
	XCONFIG_IPTV_SERVICE_PROVIDER_NAME = 0x1,
	XCONFIG_IPTV_PROVISIONING_SERVER_URL = 0x2,
	XCONFIG_IPTV_SUPPORT_INFO = 0x3,
	XCONFIG_IPTV_BOOTSTRAP_SERVER_URL = 0x4,
	XCONFIG_IPTV_ENTRIES_MAX
};

// _XCONFIG_IPTV_SETTINGS macros for key pointers
#define XK_IPTV_1(x) &x.ServiceProviderName		// key 0x1 120 bytes
#define XK_IPTV_2(x) &x.ProvisioningServerURL	// key 0x2 128 bytes
#define XK_IPTV_3(x) &x.SupportInfo				// key 0x3 128 bytes
#define XK_IPTV_4(x) &x.BootstrapServerURL		// key 0x4 128 bytes

typedef struct _XCONFIG_IPTV_SETTINGS { 
	DWORD CheckSum; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	wchar_t ServiceProviderName[0x3C]; // 0x8 sz:0x78 key 0x1
	wchar_t ProvisioningServerURL[0x40]; // 0x80 sz:0x80 key 0x2
	wchar_t SupportInfo[0x40]; // 0x100 sz:0x80 key 0x3
	wchar_t BootstrapServerURL[0x40]; // 0x180 sz:0x80 key 0x4
} XCONFIG_IPTV_SETTINGS, *PXCONFIG_IPTV_SETTINGS; // size 512
C_ASSERT(sizeof(XCONFIG_IPTV_SETTINGS) == 0x200);


/* **************************** _XCONFIG_MEDIA_CENTER_SETTINGS **************************** */
//XCONFIG_MEDIA_CENTER_ENTRIES
enum{
	XCONFIG_MEDIA_CENTER_DATA = 0x0,
	XCONFIG_MEDIA_CENTER_MEDIA_PLAYER = 0x1,
	XCONFIG_MEDIA_CENTER_XESLED_VERSION = 0x2,
	XCONFIG_MEDIA_CENTER_XESLED_TRUST_SECRET = 0x3,
	XCONFIG_MEDIA_CENTER_XESLED_TRUST_CODE = 0x4,
	XCONFIG_MEDIA_CENTER_XESLED_HOST_ID = 0x5,
	XCONFIG_MEDIA_CENTER_XESLED_KEY = 0x6,
	XCONFIG_MEDIA_CENTER_XESLED_HOST_MAC_ADDRESS = 0x7,
	XCONFIG_MEDIA_CENTER_SERVER_UUID = 0x8,
	XCONFIG_MEDIA_CENTER_SERVER_NAME = 0x9,
	XCONFIG_MEDIA_CENTER_SERVER_FLAG = 0xa,
	XCONFIG_MEDIA_ENTRIES_MAX
};

// _XCONFIG_MEDIA_CENTER_SETTINGS macros for key pointers
#define XK_MC_1(x) &x.MediaPlayer			// key 0x1 20 bytes
#define XK_MC_2(x) &x.XeSledVersion			// key 0x2 10 bytes
#define XK_MC_3(x) &x.XeSledTrustSecret		// key 0x3 20 bytes
#define XK_MC_4(x) &x.XeSledTrustCode		// key 0x4 8 bytes
#define XK_MC_5(x) &x.XeSledHostID			// key 0x5 20 bytes
#define XK_MC_6(x) &x.XeSledKey				// key 0x6 1628 bytes
#define XK_MC_7(x) &x.XeSledHostMACAddress	// key 0x7 6 bytes
#define XK_MC_8(x) &x.ServerUUID			// key 0x8 16 bytes
#define XK_MC_9(x) &x.ServerName			// key 0x9 128 bytes
#define XK_MC_A(x) &x.ServerFlag			// key 0xa 4 bytes

typedef struct _XCONFIG_MEDIA_CENTER_SETTINGS { 
	DWORD CheckSum; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	char MediaPlayer[0x14]; // 0x8 sz:0x14 key 0x1
	BYTE XeSledVersion[0xA]; // 0x1C sz:0xA key 0x2
	BYTE XeSledTrustSecret[0x14]; // 0x26 sz:0x14 key 0x3 
	BYTE XeSledTrustCode[0x8]; // 0x3A sz:0x8 key 0x4
	BYTE XeSledHostID[0x14]; // 0x42 sz:0x14 key 0x5
	BYTE XeSledKey[0x65C]; // 0x56 sz:0x65C key 0x6
	BYTE XeSledHostMACAddress[0x6]; // 0x6B2 sz:0x6 key 0x7
	char ServerUUID[0x10]; // 0x6B8 sz:0x10 key 0x8
	char ServerName[0x80]; // 0x6C8 sz:0x80 key 0x9
	char ServerFlag[0x4]; // 0x748 sz:0x4 key 0xa
} XCONFIG_MEDIA_CENTER_SETTINGS, *PXCONFIG_MEDIA_CENTER_SETTINGS; // size 1868
C_ASSERT(sizeof(XCONFIG_MEDIA_CENTER_SETTINGS) == 0x74C);


/* **************************** _XCONFIG_SYSTEM_SETTINGS **************************** */
//XCONFIG_SYSTEM_ENTRIES
enum{
	XCONFIG_SYSTEM_ALL = 0x0,
	XCONFIG_SYSTEM_ALARM_TIME = 0x1,
	XCONFIG_SYSTEM_PREVIOUS_FLASH_VERSION = 0x2,
	XCONFIG_SYSTEM_RGC_AUTH_DELAY = 0x3,
	XCONFIG_SYSTEM_ENTRIES_MAX
};

// _XCONFIG_SYSTEM_SETTINGS macros for key pointers
#define XK_SYSTEM_1(x) &x.AlarmTime				// key 0x1 8 bytes
#define XK_SYSTEM_2(x) &x.PreviousFlashVersion	// key 0x2 4 bytes
#define XK_SYSTEM_3(x) &x.RgcAuthDelay			// key 0x3 16 bytes

typedef struct _XCONFIG_SYSTEM_SETTINGS{
	DWORD Version; // 0x0 sz:0x4
	LARGE_INTEGER AlarmTime; // key 0x1 0x4 sz:0x8
	DWORD PreviousFlashVersion; // key 0x2 0xC sz:0x4
	ULARGE_INTEGER RgcAuthDelay[2]; // 0x10 sz:0x10
} XCONFIG_SYSTEM_SETTINGS, *PXCONFIG_SYSTEM_SETTINGS; // XConfigSystemSettings; 16 bytes
C_ASSERT(sizeof(XCONFIG_SYSTEM_SETTINGS) == 0x20);


/* **************************** _XCONFIG_USER_SETTINGS **************************** */
//XCONFIG_USER_ENTRIES
enum{
	XCONFIG_USER_DATA = 0x0,
	XCONFIG_USER_TIME_ZONE_BIAS = 0x1,
	XCONFIG_USER_TIME_ZONE_STD_NAME = 0x2,
	XCONFIG_USER_TIME_ZONE_DLT_NAME = 0x3,
	XCONFIG_USER_TIME_ZONE_STD_DATE = 0x4,
	XCONFIG_USER_TIME_ZONE_DLT_DATE = 0x5,
	XCONFIG_USER_TIME_ZONE_STD_BIAS = 0x6,
	XCONFIG_USER_TIME_ZONE_DLT_BIAS = 0x7,
	XCONFIG_USER_DEFAULT_PROFILE = 0x8,
	XCONFIG_USER_LANGUAGE = 0x9,
	XCONFIG_USER_VIDEO_FLAGS = 0xa,
	XCONFIG_USER_AUDIO_FLAGS = 0xb,
	XCONFIG_USER_RETAIL_FLAGS = 0xc,
	XCONFIG_USER_DEVKIT_FLAGS = 0xd,
	XCONFIG_USER_COUNTRY = 0xe,
	XCONFIG_USER_PC_FLAGS = 0xf,
	XCONFIG_USER_SMB_CONFIG = 0x10,
	XCONFIG_USER_LIVE_PUID = 0x11,
	XCONFIG_USER_LIVE_CREDENTIALS = 0x12,
	XCONFIG_USER_AV_COMPOSITE_SCREENSZ = 0x13,
	XCONFIG_USER_AV_COMPONENT_SCREENSZ = 0x14,
	XCONFIG_USER_AV_VGA_SCREENSZ = 0x15,
	XCONFIG_USER_PC_GAME = 0x16,
	XCONFIG_USER_PC_PASSWORD = 0x17,
	XCONFIG_USER_PC_MOVIE = 0x18,
	XCONFIG_USER_PC_GAME_RATING = 0x19,
	XCONFIG_USER_PC_MOVIE_RATING = 0x1a,
	XCONFIG_USER_PC_HINT = 0x1b,
	XCONFIG_USER_PC_HINT_ANSWER = 0x1c,
	XCONFIG_USER_PC_OVERRIDE = 0x1d,
	XCONFIG_USER_MUSIC_PLAYBACK_MODE = 0x1e,
	XCONFIG_USER_MUSIC_VOLUME = 0x1f,
	XCONFIG_USER_MUSIC_FLAGS = 0x20,
	XCONFIG_USER_ARCADE_FLAGS = 0x21,
	XCONFIG_USER_PC_VERSION = 0x22,
	XCONFIG_USER_PC_TV = 0x23,
	XCONFIG_USER_PC_TV_RATING = 0x24,
	XCONFIG_USER_PC_EXPLICIT_VIDEO = 0x25,
	XCONFIG_USER_PC_EXPLICIT_VIDEO_RATING = 0x26,
	XCONFIG_USER_PC_UNRATED_VIDEO = 0x27,
	XCONFIG_USER_PC_UNRATED_VIDEO_RATING = 0x28,
	XCONFIG_USER_VIDEO_OUTPUT_BLACK_LEVELS = 0x29,
	XCONFIG_USER_VIDEO_PLAYER_DISPLAY_MODE = 0x2a,
	XCONFIG_USER_ALTERNATE_VIDEO_TIMING_ID = 0x2b,
	XCONFIG_USER_VIDEO_DRIVER_OPTIONS = 0x2c,
	XCONFIG_USER_MUSIC_UI_FLAGS = 0x2d,
	XCONFIG_USER_VIDEO_MEDIA_SOURCE_TYPE = 0x2e,
	XCONFIG_USER_MUSIC_MEDIA_SOURCE_TYPE = 0x2f,
	XCONFIG_USER_PHOTO_MEDIA_SOURCE_TYPE = 0x30,
	XCONFIG_USER_ENTRIES_MAX
};

// _XCONFIG_USER_SETTINGS macros for key pointers
#define XK_USER_1(x) &x.TimeZoneBias				// key 0x1 4 bytes
#define XK_USER_2(x) &x.TimeZoneStdName				// key 0x2 4 bytes
#define XK_USER_3(x) &x.TimeZoneDltName				// key 0x3 4 bytes
#define XK_USER_4(x) &x.TimeZoneStdDate				// key 0x4 4 bytes
#define XK_USER_5(x) &x.TimeZoneDltDate				// key 0x5 4 bytes
#define XK_USER_6(x) &x.TimeZoneStdBias				// key 0x6 4 bytes
#define XK_USER_7(x) &x.TimeZoneDltBias				// key 0x7 4 bytes
#define XK_USER_8(x) &x.DefaultProfile				// key 0x8 8 bytes
#define XK_USER_9(x) &x.Language					// key 0x9 4 bytes
#define XK_USER_A(x) &x.VideoFlags					// key 0xa 4 bytes
#define XK_USER_B(x) &x.AudioFlags					// key 0xb 4 bytes
#define XK_USER_C(x) &x.RetailFlags					// key 0xc 4 bytes
#define XK_USER_D(x) &x.DevkitFlags					// key 0xd 4  bytes
#define XK_USER_E(x) &x.Country						// key 0xe 1 bytes
#define XK_USER_F(x) &x.ParentalControlFlags		// key 0xf 1 bytes
#define XK_USER_10(x) &x.SMBConfig					// key 0x10 256 bytes
#define XK_USER_11(x) &x.LivePUID					// key 0x11 8 bytes
#define XK_USER_12(x) &x.LiveCredentials			// key 0x12 16 bytes
#define XK_USER_13(x) &x.AvPackHDMIScreenSz			// key 0x13 4 bytes
#define XK_USER_14(x) &x.AvPackComponentScreenSz	// key 0x14 4 bytes
#define XK_USER_15(x) &x.AvPackVGAScreenSz			// key 0x15 4 bytes
#define XK_USER_16(x) &x.ParentalControlGame		// key 0x16 4 bytes
#define XK_USER_17(x) &x.ParentalControlPassword	// key 0x17 4 bytes
#define XK_USER_18(x) &x.ParentalControlMovie		// key 0x18 4 bytes
#define XK_USER_19(x) &x.ParentalControlGameRating	// key 0x19 4 bytes
#define XK_USER_1A(x) &x.ParentalControlMovieRating	// key 0x1a 4 bytes
#define XK_USER_1B(x) &x.ParentalControlHint		// key 0x1b 1 bytes
#define XK_USER_1C(x) &x.ParentalControlHintAnswer	// key 0x1c 32 bytes
#define XK_USER_1D(x) &x.ParentalControlOverride	// key 0x1d 32  bytes
#define XK_USER_1E(x) &x.MusicPlaybackMode			// key 0x1e 4 bytes
#define XK_USER_1F(x) &x.MusicVolume				// key 0x1f 4 bytes
#define XK_USER_20(x) &x.MusicFlags					// key 0x20 4 bytes
#define XK_USER_21(x) &x.ArcadeFlags				// key 0x21 4 bytes
#define XK_USER_22(x) &x.ParentalControlVersion		// key 0x22 4 bytes
#define XK_USER_23(x) &x.ParentalControlTV			// key 0x23 4 bytes
#define XK_USER_24(x) &x.ParentalControlTVRating	// key 0x24 4 bytes
#define XK_USER_25(x) &x.ParentalControlExplicitVideo// key 0x25 4 bytes
#define XK_USER_26(x) &x.ParentalControlExplicitVideoRating// key 0x26 4 bytes
#define XK_USER_27(x) &x.ParentalControlUnratedVideo// key 0x27 4 bytes
#define XK_USER_28(x) &x.ParentalControlUnratedVideoRating// key 0x28 4 bytes
#define XK_USER_29(x) &x.VideoOutputBlackLevels		// key 0x29 4 bytes
#define XK_USER_2A(x) &x.VideoPlayerDisplayMode		// key 0x2a 1 bytes
#define XK_USER_2B(x) &x.AlternateVideoTimingIDs	// key 0x2b 4 bytes
#define XK_USER_2C(x) &x.VideoDriverOptions			// key 0x2c 4 bytes
#define XK_USER_2D(x) &x.MusicUIFlags				// key 0x2d 4 bytes
#define XK_USER_2E(x) &x.VideoMediaSourceType		// key 0x2e 1 bytes
#define XK_USER_2F(x) &x.MusicMediaSourceType		// key 0x2f 1 bytes
#define XK_USER_30(x) &x.PhotoMediaSourceType		// key 0x30 1 bytes

// parental control password stored as hex
// I set it to all X and the value was 01010101, then I set it to all Y and the value was 02020202
// the reset query answer I used was "aaa" which it stored in mobileB as wchar in plaintext
// X 01, Y 02, L 03, R 04, U 05, D 06, LT 09, RT 0A, LB 0B, RB 0C
// numerically in the dash... LT 1, LB 2, RB 3, RT 4, L 5, U 6, D 7, R 8, X 9, Y 0

// These flags are stored in the retail flags (XCONFIG_USER_RETAIL_FLAGS).
//

#define XC_MISC_FLAG_AUTOPOWERDOWN      0x00000001
#define XC_MISC_FLAG_DONT_USE_DST       0x00000002
#define XC_MISC_FLAG_CONNECTIONNOTICE   0x00000004
#define XC_MISC_FLAG_24HCLOCK           0x00000008
#define XC_MISC_FLAG_NO_NOTIFY_DISPLAY  0x00000010
#define XC_MISC_FLAG_NO_NOTIFY_SOUND    0x00000020
#define XC_MISC_FLAG_OOBE_HAS_RUN       0x00000040

#define XC_MISC_FLAG_ALL_MASK           ((XC_MISC_FLAG_AUTOPOWERDOWN) | (XC_MISC_FLAG_DONT_USE_DST) | (XC_MISC_FLAG_CONNECTIONNOTICE) | \
										 (XC_MISC_FLAG_24HCLOCK) | (XC_MISC_FLAG_NO_NOTIFY_DISPLAY) | (XC_MISC_FLAG_NO_NOTIFY_SOUND) | \
										 (XC_MISC_FLAG_OOBE_HAS_RUN))

typedef struct _XCONFIG_TIMEZONE_DATE { // used by _XCONFIG_USER_SETTINGS
	BYTE Month; // 0x0 sz:0x1
	BYTE Day; // 0x1 sz:0x1
	BYTE DayOfWeek; // 0x2 sz:0x1
	BYTE Hour; // 0x3 sz:0x1
} XCONFIG_TIMEZONE_DATE, *PXCONFIG_TIMEZONE_DATE; // size 4
C_ASSERT(sizeof(XCONFIG_TIMEZONE_DATE) == 0x4);

typedef struct _XCONFIG_USER_SETTINGS { 
	DWORD CheckSum; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	DWORD TimeZoneBias; // 0x8 sz:0x4 key 0x1
	char TimeZoneStdName[0x4]; // 0xC sz:0x4 key 0x2
	char TimeZoneDltName[0x4]; // 0x10 sz:0x4 key 0x3
	XCONFIG_TIMEZONE_DATE TimeZoneStdDate; // 0x14 sz:0x4 key 0x4
	XCONFIG_TIMEZONE_DATE TimeZoneDltDate; // 0x18 sz:0x4 key 0x5
	DWORD TimeZoneStdBias; // 0x1C sz:0x4 key 0x6
	DWORD TimeZoneDltBias; // 0x20 sz:0x4 key 0x7
	XUID DefaultProfile; // 0x24 sz:0x8 key 0x8
	DWORD Language; // 0x2C sz:0x4 key 0x9
	DWORD VideoFlags; // 0x30 sz:0x4 key 0xa
	DWORD AudioFlags; // 0x34 sz:0x4 key 0xb
	DWORD RetailFlags; // 0x38 sz:0x4 key 0xc
	DWORD DevkitFlags; // 0x3C sz:0x4 key 0xd
	char Country; // 0x40 sz:0x1 key 0xe
	char ParentalControlFlags; // 0x41 sz:0x1 key 0xf
	BYTE ReservedFlag[0x2]; // 0x42 sz:0x2
	char SMBConfig[0x100]; // 0x44 sz:0x100 key 0x10
	XUID LivePUID; // 0x144 sz:0x8 key 0x11
	char LiveCredentials[0x10]; // 0x14C sz:0x10 key 0x12
	SHORT AVPackHDMIScreenSz[2]; // 0x15C sz:0x4 key 0x13
	SHORT AVPackComponentScreenSz[2]; // 0x160 sz:0x4 key 0x14
	SHORT AVPackVGAScreenSz[2]; // 0x164 sz:0x4 key 0x15
	DWORD ParentalControlGame; // 0x168 sz:0x4 key 0x16
	DWORD ParentalControlPassword; // 0x16C sz:0x4 key 0x17
	DWORD ParentalControlMovie; // 0x170 sz:0x4 key 0x18
	DWORD ParentalControlGameRating; // 0x174 sz:0x4 key 0x19
	DWORD ParentalControlMovieRating; // 0x178 sz:0x4 key 0x1a
	char ParentalControlHint; // 0x17C sz:0x1 key 0x1b
	char ParentalControlHintAnswer[0x20]; // 0x17D sz:0x20 key 0x1c
	char ParentalControlOverride[0x20]; // 0x19D sz:0x20 key 0x1d
	DWORD MusicPlaybackMode; // 0x1BD sz:0x4 key 0x1e
	int MusicVolume; // 0x1C1 sz:0x4 (FLOAT) key 0x1f
	DWORD MusicFlags; // 0x1C5 sz:0x4 key 0x20
	DWORD ArcadeFlags; // 0x1C9 sz:0x4 key 0x21
	DWORD ParentalControlVersion; // 0x1CD sz:0x4 key 0x22
	DWORD ParentalControlTV; // 0x1D1 sz:0x4 key 0x23
	DWORD ParentalControlTVRating; // 0x1D5 sz:0x4 key 0x24
	DWORD ParentalControlExplicitVideo; // 0x1D9 sz:0x4 key 0x25
	DWORD ParentalControlExplicitVideoRating; // 0x1DD sz:0x4 key 0x26
	DWORD ParentalControlUnratedVideo; // 0x1E1 sz:0x4 key 0x27
	DWORD ParentalControlUnratedVideoRating; // 0x1E5 sz:0x4 key 0x28
	DWORD VideoOutputBlackLevels; // 0x1E9 sz:0x4 key 0x29
	BYTE VideoPlayerDisplayMode; // 0x1ED sz:0x1 key 0x2a
	DWORD AlternateVideoTimingIDs; // 0x1EE sz:0x4 key 0x2b
	DWORD VideoDriverOptions; // 0x1F2 sz:0x4 key 0x2c
	DWORD MusicUIFlags; // 0x1F6 sz:0x4 key 0x2d
	char VideoMediaSourceType; // 0x1FA sz:0x1 key 0x2e
	char MusicMediaSourceType; // 0x1FB sz:0x1 key 0x2f
	char PhotoMediaSourceType; // 0x1FC sz:0x1 key 0x30
} XCONFIG_USER_SETTINGS, *PXCONFIG_USER_SETTINGS; // size 509
C_ASSERT(sizeof(XCONFIG_USER_SETTINGS) == 0x1FD);


/* **************************** _XCONFIG_XNET_SETTINGS **************************** */
//XCONFIG_XNET_ENTRIES
enum{
	XCONFIG_XNET_ALL = 0x0,
	XCONFIG_XNET_DATA = 0x1,
	XCONFIG_XNET_ENTRIES_MAX
};

// _XCONFIG_XNET_SETTINGS macros for key pointers
#define XK_XNET_1(x) &x.Data // key 0x01 492 bytes

// decrypted xconfig machine account (mobilec.dat)
typedef struct _XNetConfigSectorHeader { 
	unsigned char abHash[0x14]; // 0x0 sz:0x14
	unsigned char abConfounder[0x8]; // 0x14 sz:0x8
} XNetConfigSectorHeader, *PXNetConfigSectorHeader; // size 28
C_ASSERT(sizeof(XNetConfigSectorHeader) == 0x1C);

typedef struct _NetLogonMachineAccount { 
	XNetConfigSectorHeader Header; // 0x0 sz:0x1C
	unsigned int dwServiceNetworkID; // 0x1C sz:0x4
	unsigned long long qwId; // 0x20 sz:0x8
	char szGamertag[0x10]; // 0x28 sz:0x10
	char szDomain[0x14]; // 0x38 sz:0x14
	char szKerberosRealm[0x18]; // 0x4C sz:0x18
	unsigned char abKey[0x10]; // 0x64 sz:0x10
	unsigned char bCountryIdOfLastLogon; // 0x74 sz:0x1
	unsigned char abReserved[0x177]; // 0x75 sz:0x177
} XNetLogonMachineAccount, *PXNetLogonMachineAccount; // size 492
C_ASSERT(sizeof(XNetLogonMachineAccount) == 0x1EC);

typedef struct _XCONFIG_XNET_SETTINGS{
	unsigned int version;
	union { // key 0x01 492 unsigned chars
		unsigned char abData[492];
		XNetLogonMachineAccount xnAccount; // applies only after decrypting this blob from category XCONFIG_XNET_MACHINE_ACCOUNT_CATEGORY
	} Data;
} XCONFIG_XNET_SETTINGS, *PXCONFIG_XNET_SETTINGS; // 496 unsigned chars
C_ASSERT(sizeof(XCONFIG_XNET_SETTINGS) == 0x1F0);

/* **************************** _XCONFIG_STATISTIC_SETTINGS **************************** */
//XCONFIG_STATISTIC_ENTRIES
enum{
	XCONFIG_STATISTICS_DATA = 0x0,
	XCONFIG_STATISTICS_XUID_MAC_ADDRESS = 0x1,
	XCONFIG_STATISTICS_XUID_COUNT = 0x2,
	XCONFIG_STATISTICS_ODD_FAILURES = 0x3,
	XCONFIG_STATISTICS_HDD_SMART_DATA = 0x4,
	XCONFIG_STATISTICS_UEM_ERRORS = 0x5,
	XCONFIG_STATISTICS_FPM_ERRORS = 0x6,
	XCONFIG_STATISTICS_LAST_REPORT_TIME = 0x7,
	XCONFIG_STATISTICS_BUG_CHECK_DATA = 0x8,
	XCONFIG_STATISTICS_TEMPERATURE = 0x9,
	XCONFIG_STATISTICS_XEKEYS_WRITE_FAILURE = 0xA,
	XCONFIG_STATISTICS_ENTRIES_MAX
};

// _XCONFIG_STATISTIC_SETTINGS macros for key pointers
#define XK_STATISTIC_1(x) &x.XUIDMACAddress		// key 0x1 6 bytes
#define XK_STATISTIC_2(x) &x.XUIDCount			// key 0x2 4 bytes
#define XK_STATISTIC_3(x) &x.ODDFailures		// key 0x3 32 bytes
#define XK_STATISTIC_4(x) &x.HDDSmartData		// key 0x4 512 bytes
#define XK_STATISTIC_5(x) &x.UEMErrors			// key 0x5 100 bytes
#define XK_STATISTIC_6(x) &x.FPMErrors			// key 0x6 56 bytes - 9199 increased 0x38 to 0x60
#define XK_STATISTIC_7(x) &x.LastReportTime		// key 0x7 8 bytes
#define XK_STATISTIC_8(x) &x.BugCheckData		// key 0x8 101 bytes 
#define XK_STATISTIC_9(x) &x.TemperatureData	// key 0x9 200 bytes
#define XK_STATISTIC_A(x) &x.XeKeysWriteFailure	// key 0xa 16 bytes

typedef struct _XCONFIG_XEKEYS_WRITE_FAILURE { 
	LARGE_INTEGER DateTime; // 0x0 sz:0x8
	DWORD Status; // 0x8 sz:0x4
	char File; // 0xC sz:0x1
	char Reserved[0x3]; // 0xD sz:0x3
} XCONFIG_XEKEYS_WRITE_FAILURE, *PXCONFIG_XEKEYS_WRITE_FAILURE; // size 16
C_ASSERT(sizeof(XCONFIG_XEKEYS_WRITE_FAILURE) == 0x10);

typedef struct _XCONFIG_STATISTIC_SETTINGS { 
	DWORD CheckSum; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	char XUIDMACAddress[0x6]; // 0x8 sz:0x6 key 0x1
	char Reserved[0x2]; // 0xE sz:0x2
	DWORD XUIDCount; // 0x10 sz:0x4 key 0x2
	BYTE ODDFailures[0x20]; // 0x14 sz:0x20 key 0x3
	BYTE BugCheckData[0x65]; // 0x34 sz:0x65 key 0x8 
	BYTE TemperatureData[0xC8]; // 0x99 sz:0xC8 key 0x9
	XCONFIG_XEKEYS_WRITE_FAILURE XeKeysWriteFailure; // 0x161 sz:0x10 key 0xa
	char Unused[0x1C3]; // 0x171 sz:0x1C3
	char HDDSmartData[0x200]; // 0x334 sz:0x200 key 0x4
	char UEMErrors[0x64]; // 0x534 sz:0x64 key 0x5
	char FPMErrors[0x60]; // 0x598 sz:0x60 key 0x6
	LARGE_INTEGER LastReportTime; // 0x5F8 sz:0x8 key 0x7
} XCONFIG_STATISTIC_SETTINGS, *PXCONFIG_STATISTIC_SETTINGS; // size 1536
C_ASSERT(sizeof(XCONFIG_STATISTIC_SETTINGS) == 0x600);



/* **************************** _XCONFIG_STATIC_SETTINGS **************************** */
//XCONFIG_STATIC_ENTRIES
enum{
	XCONFIG_STATIC_DATA = 0x0,
	XCONFIG_STATIC_FIRST_POWER_ON_DATE = 0x1,
	XCONFIG_STATIC_SMC_CONFIG = 0x2,
	XCONFIG_STATIC_ENTRIES_MAX
};

// _XCONFIG_STATIC_SETTINGS macros for key pointers
#define XK_STATIC_1(x) &x.FirstPowerOnDate // key 0x1 5 bytes
#define XK_STATIC_2(x) &x.SMCConfig // key 0x2 256 bytes

typedef struct _FanOverride{ // used by _XCONFIG_STATIC_SETTINGS // 01111111 <- normally disabled as 0x7F
	BYTE Enable : 1; // says 7 is bit 0
	BYTE Speed : 7; // says 0 bit 7
} FanOverride, *PFanOverride; // 1 byte
C_ASSERT(sizeof(FanOverride) == 0x1);

typedef struct _Thermal{ // used by _XCONFIG_STATIC_SETTINGS
	BYTE Cpu;
	BYTE Gpu;
	BYTE Edram;
} Thermal, *PThermal; // 3 bytes
C_ASSERT(sizeof(Thermal) == 0x3);

typedef struct _ViperData{ // used by _XCONFIG_STATIC_SETTINGS
	BYTE GpuVoltageNotSetting : 1; // bit 7
	BYTE MemoryVoltageNotSetting : 1; // bit 6 (bit 5 thru 0 unused
	//BYTE unknown : 6; // 1 byte
	BYTE GpuTarget;
	BYTE MemoryTarget;
	BYTE CheckSum;	
} ViperData, *PViperData; // 4 bytes
C_ASSERT(sizeof(ViperData) == 0x4);

typedef struct _TempCalData{ // used by _XCONFIG_STATIC_SETTINGS
	WORD Gain; // 0 sz 2
	WORD Offset; // 2 sz 2
} TempCalData, *PTempCalData; // 4 bytes
C_ASSERT(sizeof(TempCalData) == 0x4);

typedef struct _TempSetting{ // used by _XCONFIG_STATIC_SETTINGS
	TempCalData Cpu;
	TempCalData Gpu;
	TempCalData Edram;
	TempCalData Board; 
} TempSetting, *PTempSetting; // 16 bytes
C_ASSERT(sizeof(TempSetting) == 0x10);

typedef struct _ThermalCalData{ // used by _XCONFIG_STATIC_SETTINGS
	TempSetting therm; // 16 bytes
	char AnaFuseValue;
	Thermal SetPoint; // 3 bytes
	Thermal Overload; // 3 bytes
} ThermalCalData, *PThermalCalData;
C_ASSERT(sizeof(ThermalCalData) == 0x17);

typedef struct _SMCBlock { 
	BYTE StructureVersion; // 0x0 sz:0x1
	BYTE ConfigSource; // 0x1 sz:0x1
	char ClockSelect; // 0x2 sz:0x1
	FanOverride fanOrCpu; // 1 byte 0x3 sz:0x2
	FanOverride fanOrGpu; // 1 byte
	char EjectPressTimeout; // 0x5 sz:0x1
	
	BYTE unknownBits : 1; // 1 byte total for this bitfield
	BYTE MteErrorHandling : 1; // 0x6 bfo:0x6
	BYTE ScreenToolExecutionCount : 2; // 0x6 bfo:0x4
	BYTE ScreenToolFinished : 1; // 0x6 bfo:0x3
	BYTE ScreenToolStarted : 1; // 0x6 bfo:0x2
	BYTE UseTempCalDefaults : 1; // 0x6 bfo:0x1 (checked in smc, bit 1)
	BYTE RadioEnable : 1; // 0x6 bfo:0x0

	char DelayOverloadTimer; // 0x7 sz:0x1
	char MaxOverloadDelta; // 0x8 sz:0x1
	char DropDeadDelta; // 0x9 sz:0x1
	ThermalCalData Temperature; // 0xA sz:0x17
	char MinFanSpeed; // 0x21 sz:0x1
	ViperData Viper; // 0x22 sz:0x4
	BYTE pad4[0x98]; // 0x26 sz:0x98
	TempSetting ThermalSet0; // 0xBE sz:0x10
	BYTE pad5[4]; // 0xCE sz:0x4
	TempSetting ThermalSet1; // 0xD2 sz:0x10
	BYTE pad6[2]; // 0xE2 sz:0x2
	ThermalCalData BackupThermalCalData; // 0xE4 sz:0x17
	BYTE pad7[3]; // 0xFB sz:0x3
	BYTE DoNotUse[2]; // 0xFE sz:0x2
} SMCBlock, *PSMCBlock; // size 256
C_ASSERT(sizeof(SMCBlock) == 0x100);

typedef struct _XCONFIG_STATIC_SETTINGS{
	DWORD CheckSum; // 0x0 sz:0x4 *** see below ***
	DWORD Version; // 0x4 sz:0x4
	char FirstPowerOnDate[5]; // 0x8 sz:0x5 key 0x1
	char reserved; // 0xD sz:0x1
	SMCBlock SMCConfig;  // 0xE sz:0x100 key 0x2
} XCONFIG_STATIC_SETTINGS, *PXCONFIG_STATIC_SETTINGS; // XConfigStaticSettings; 270 bytes
C_ASSERT(sizeof(XCONFIG_STATIC_SETTINGS) == 0x10E);

/* **************************** _XCONFIG_DEVKIT_SETTINGS **************************** */
//XCONFIG_DEVKIT_ENTRIES
enum _XCONFIG_DEVKIT_ENTRIES {
	XCONFIG_DEVKIT_DATA = 0x0,
	XCONFIG_DEVKIT_USBD_ROOT_HUB_PORT_DISABLE_MASK = 0x1,
	XCONFIG_DEVKIT_XAM_FEATURE_ENABLE_DISABLE_MASK = 0x2,
	XCONFIG_DEVKIT_KIOSK_ID = 0x3,
	XCONFIG_DEVKIT_MAX
};

typedef struct _XCONFIG_DEVKIT_XAM_FEATURE_MASK { 
	DWORD DevkitEnableMask; // 0x0 sz:0x4
	DWORD ConsoleDisableMask; // 0x4 sz:0x4
	DWORD Reserved[2]; // 0x8 sz:0x8
} XCONFIG_DEVKIT_XAM_FEATURE_MASK, *PXCONFIG_DEVKIT_XAM_FEATURE_MASK; // size 16
C_ASSERT(sizeof(XCONFIG_DEVKIT_XAM_FEATURE_MASK) == 0x10);

typedef struct _XCONFIG_USBD_ROOT_HUB_PORT_MASK { 
	BYTE Mask[2]; // 0x0 sz:0x2
} XCONFIG_USBD_ROOT_HUB_PORT_MASK, *PXCONFIG_USBD_ROOT_HUB_PORT_MASK; // size 2
C_ASSERT(sizeof(XCONFIG_USBD_ROOT_HUB_PORT_MASK) == 0x2);

typedef struct _XCONFIG_DEVKIT_SETTINGS { 
	DWORD Version; // 0x0 sz:0x4
	XCONFIG_USBD_ROOT_HUB_PORT_MASK UsbdRootHubPortDisableMask; // 0x4 sz:0x2
	XCONFIG_DEVKIT_XAM_FEATURE_MASK XamFeatureMask; // 0x6 sz:0x10
	DWORD KioskId; // 0x16 sz:0x4
} XCONFIG_DEVKIT_SETTINGS, *PXCONFIG_DEVKIT_SETTINGS; // size 22
C_ASSERT(sizeof(XCONFIG_DEVKIT_SETTINGS) == 0x1A);



#pragma warning(pop)  // unnamed struct/union
#pragma pack(pop)


/*
USHORT XConfig_numEntr[XCONFIG_CATEGORY_MAX] = {
	XCONFIG_STATIC_ENTRIES_MAX,
	XCONFIG_STATISTICS_ENTRIES_MAX,
	XCONFIG_SECURED_ENTRIES_MAX,
	XCONFIG_USER_ENTRIES_MAX,
	XCONFIG_XNET_ENTRIES_MAX,
	XCONFIG_XNET_ENTRIES_MAX,
	XCONFIG_MEDIA_ENTRIES_MAX,
	XCONFIG_CONSOLE_MAX,
	XCONFIG_DVD_ENTRIES_MAX,
	XCONFIG_IPTV_ENTRIES_MAX,
	XCONFIG_SYSTEM_ENTRIES_MAX,
	XCONFIG_DEVKIT_ENTRIES_MAX,
}; // the number of entries in each category
*/
/*
// this and internal SMCBlock checksums seem to be the only ones used at this point
//
// use this to calculate XCONFIG_STATIC_SETTINGS.CheckSum
// where data is a BYTE pointer to the full XCONFIG_STATIC_SETTINGS struct
UINT XConfigStaticMainChecksumCalc(PBYTE data)
{
	UINT i, len, sum = 0;
	data += 0x10;
	for(i=0, len=252; i<len; i++)
		sum += data[i]&0xFF;
	sum = (~sum)&0xFFFF;
	return ((sum&0xFF00)<<8)+((sum&0xFF)<<24);
}

// EXAMPLE:
NTSTATUS SetTreshHolds(BYTE cpu, BYTE gpu, BYTE mem, BYTE cpuOff, BYTE gpuOff, BYTE memOff)
{
	XCONFIG_STATIC_SETTINGS xcss;
	DWORD sta;
	WORD sz;
	sta = ExGetXConfigSetting(XCONFIG_STATIC_CATEGORY, XCONFIG_STATIC_DATA, &xcss, sizeof(XCONFIG_STATIC_SETTINGS) , &sz);
	if((sta == 0)&&(sz == sizeof(XCONFIG_STATIC_SETTINGS)))
	{
		xcss.Temperature.SetPoint.Cpu = cpu;
		xcss.Temperature.SetPoint.Gpu = gpu;
		xcss.Temperature.SetPoint.Edram = mem;
		xcss.Temperature.Overload.Cpu = cpuOff;
		xcss.Temperature.Overload.Gpu = gpuOff;
		xcss.Temperature.Overload.Edram = memOff;
		xcss.CheckSum = XConfigStaticChecksumCalc((PBYTE)&xcss);
		sta = ExSetXConfigSetting(XCONFIG_STATIC_CATEGORY, XCONFIG_STATIC_DATA, &xcss, sz);
	}
	return sta;
}
*/

#endif // _XCONFIG_H

