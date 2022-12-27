#ifndef __KERNEL_DEFINES_H
#define __KERNEL_DEFINES_H

#pragma comment(lib, "kernelext")

#include "keFileInfo.h"
#include "keXexInfo.h"
#include "kePrivateStructs.h"
#include "keDriver.h"
#include "keXeCrypt.h"
#include "keXeKeys.h"
#include "keXConfig.h"
#include "keSmc.h"
#include "keNand.h"
#include "kernelExpEnum.h"

#define OBJ_SYS_STRING	"\\System??\\%s"
#define OBJ_USR_STRING	"\\??\\%s"
#define OBJ_SYS_PATH	"\\System??\\"
#define OBJ_USR_PATH	"\\??\\"

// common modules
#define MODULE_KERNEL	"xboxkrnl.exe"
#define MODULE_XAM		"xam.xex"
#define MODULE_SIGNIN	"signin.xex"
#define MODULE_HUD		"hud.xex"
#define MODULE_XBDM		"xbdm.xex"

// some handy intrinsics and macros that are left out...
#define __isync()		__emit(0x4C00012C)

#define doSync(addr) \
	do { \
	__dcbst(0, addr); \
	__sync(); \
	__isync(); \
	} while (0)

#define doLightSync(addr) \
	do { \
	__dcbst(0, addr); \
	__sync(); \
	} while (0)

// debug serial port register
#define DBG_SERIAL_RCV		(DWORD volatile*)0x7FEA1010
#define DBG_SERIAL_XMIT		(DWORD volatile*)0x7FEA1014
#define DBG_SERIAL_STS		(DWORD volatile*)0x7FEA1018
#define DBG_SERIAL_CNTRL	(DWORD volatile*)0x7FEA101C

#define FILE_DIRECTORY_FILE                     0x00000001
#define FILE_WRITE_THROUGH                      0x00000002
#define FILE_SEQUENTIAL_ONLY                    0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define FILE_CREATE_TREE_CONNECTION             0x00000080

#define FILE_COMPLETE_IF_OPLOCKED               0x00000100
#define FILE_NO_EA_KNOWLEDGE                    0x00000200
//UNUSED                                        0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

// Valid values for object Attributes field
#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_VALID_ATTRIBUTES    0x000001F2L

// Directory Stuff
#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

#define SYMBOLIC_LINK_QUERY (0x0001)

// object type strings
#define OBJ_TYP_SYMBLINK	0x626d7953 // Symb
#define OBJ_TYP_DIRECTORY	0x65726944 // Dire
#define OBJ_TYP_DEVICE		0x69766544 // Devi
#define OBJ_TYP_EVENT		0x76657645 // Evev
#define OBJ_TYP_DEBUG		0x63706d64 // dmpc

// flags for xex load image dwModuleTypeFlags
#define XEX_LOADIMG_FLAG_TITLE_PROCESS   0x00000001
#define XEX_LOADIMG_FLAG_TITLE_IMPORTS   0x00000002
#define XEX_LOADIMG_FLAG_DEBUGGER        0x00000004
#define XEX_LOADIMG_FLAG_DLL             0x00000008
#define XEX_LOADIMG_FLAG_PATCH           0x00000010
#define XEX_LOADIMG_FLAG_PATCH_FULL      0x00000020
#define XEX_LOADIMG_FLAG_PATCH_DELTA     0x00000040
#define XEX_LOADIMG_FLAG_BOUND_PATH      0x40000000
#define XEX_LOADIMG_FLAG_SILENT_LOAD     0x80000000
#define XEX_LOADIMG_TYPE_TITLE 			(XEX_LOADIMG_FLAG_TITLE_PROCESS)
#define XEX_LOADIMG_TYPE_TITLE_DLL 		(XEX_LOADIMG_FLAG_TITLE_PROCESS | XEX_LOADIMG_FLAG_DLL)
#define XEX_LOADIMG_TYPE_SYSTEM_APP 	(XEX_LOADIMG_FLAG_DLL)
#define XEX_LOADIMG_TYPE_SYSTEM_DLL 	(XEX_LOADIMG_FLAG_DLL | XEX_LOADIMG_FLAG_TITLE_IMPORTS)

// flags used by ExCreateThread
#define EX_CREATE_FLAG_SUSPENDED		0x00000001 // thread created suspended
#define EX_CREATE_FLAG_SYSTEM			0x00000002 // create a system thread
#define EX_CREATE_FLAG_TLS_STATIC		0x00000008 // allocates more object memory, KPROCESS.SizeOfTlsSlots+KPROCESS.SizeOfTlsStaticData
#define EX_CREATE_FLAG_PRIORITY1		0x00000020 // sets priority class for the thread to 1 via KeSetPriorityClassThread - foreground
#define EX_CREATE_FLAG_PRIORITY0		0x00000040 // sets priority class for the thread to 0 via KeSetPriorityClassThread - background
#define EX_CREATE_FLAG_RETURN_KTHREAD	0x00000080 // puts PKTHREAD into pHandle instead of the thread HANDLE
#define EX_CREATE_FLAG_TITLE_EXEC		0x00000100 // title execution thread
#define EX_CREATE_FLAG_HIDDEN			0x00000400 // hides the thread from debugger thread list
// { more in here in regards to thread scheduler }
#define EX_CREATE_FLAG_CORE0			0x01000000 // threads starts on 1st cpu core
#define EX_CREATE_FLAG_CORE1			0x02000000 // threads starts on 2nd cpu core
#define EX_CREATE_FLAG_CORE2			0x04000000 // threads starts on 3rd cpu core
#define EX_CREATE_FLAG_CORE3			0x08000000 // threads starts on 4th cpu core
#define EX_CREATE_FLAG_CORE4			0x10000000 // threads starts on 5th cpu core
#define EX_CREATE_FLAG_CORE5			0x20000000 // threads starts on 6th cpu core

// Can be used instead of module name to get module address where XexGetModuleHandle() is called
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS	(PSZ)(-1)

typedef enum _POOL_TYPE {
	PoolTypeThread = 0x0,
	PoolTypeTitle = 0x1,
	PoolTypeSystem = 0x2,
	PoolTypeTitleDebug = 0x3,
	PoolTypeSystemDebug = 0x4,
} POOL_TYPE;

typedef enum { // effects on jtag noted in comment
	HalHaltRoutine = 0x0, // hard poweroff (used by hotplug HDD) HalpPowerDownSystemNow
	HalRebootRoutine = 0x1, // hard reset (video error) HalpRebootSystem
	HalKdRebootRoutine = 0x2, // hard reset (used for dumpwritedump/frozen processor) HalpRebootSystem
	HalFatalErrorRebootRoutine = 0x3, // hard reset HalpRebootSystem
	HalResetSMCRoutine = 0x4, // power off (hard) HalpRebootSystem
	HalPowerDownRoutine = 0x5, // power off (nice) HalpPowerDownSystem
	HalRebootQuiesceRoutine = 0x6, // E79 (lost settings) HalpRebootQuiesceSystem
	HalForceShutdownRoutine = 0x7, // frozen console HalpRequestPowerDownDpc
	HalPowerCycleQuiesceRoutine = 0x8,
	HalMaximumRoutine = 0x9,
} FIRMWARE_REENTRY;

/* description about xex exe headers in memory */
typedef struct _XBOX_HARDWARE_INFO {
	DWORD Flags;
	unsigned char NumberOfProcessors;
	unsigned char PCIBridgeRevisionID;
	unsigned char Reserved[6];
	unsigned short BldrMagic;
	unsigned short BldrFlags;
} XBOX_HARDWARE_INFO, *PXBOX_HARDWARE_INFO;

typedef struct _EX_TITLE_TERMINATE_REGISTRATION
{
	void* NotificationRoutine; // function pointer
	u32 Priority; // xam uses 0x7C800000 for early and 0x0 for late
	LIST_ENTRY ListEntry; // already defined in winnt.h
} EX_TITLE_TERMINATE_REGISTRATION, *PEX_TITLE_TERMINATE_REGISTRATION;

typedef struct _EX_THREAD_REGISTRATION {
	void* NotificationRoutine;
	DWORD Priority;
	LIST_ENTRY ListEntry;
} EX_THREAD_REGISTRATION, *PEX_THREAD_REGISTRATION;

typedef struct _VD_NOTIFICATION_REGISTRATION {
	PVOID NotificationRoutine; // 0x0 sz:0x4 void(*)()
	long Priority; // 0x4 sz:0x4
	LIST_ENTRY ListEntry; // 0x8 sz:0x8
} VD_NOTIFICATION_REGISTRATION, *PVD_NOTIFICATION_REGISTRATION; // size 16
C_ASSERT(sizeof(VD_NOTIFICATION_REGISTRATION) == 0x10);

typedef void (*pfnThreadNotificationRoutine)(PEX_THREAD_REGISTRATION ThisRegistration, PKTHREAD Thread, BOOL Creating);
typedef int (*LP_VD_NOTIFICATION_CALLBACK)(const PVD_NOTIFICATION_REGISTRATION vdReg, DWORD type, void * buf);

typedef struct _XBOX_KRNL_VERSION{
	WORD Major; // for 360 this is always 2
	WORD Minor; // usually 0
	WORD Build; // current version, for example 9199
	WORD Qfe;
} XBOX_KRNL_VERSION, *PXBOX_KRNL_VERSION;

typedef struct _KTIME_STAMP_BUNDLE {
	LARGE_INTEGER InterruptTime; // 0
	LARGE_INTEGER SystemTime; // 8
	DWORD TickCount; // 10
} KTIME_STAMP_BUNDLE, *PKTIME_STAMP_BUNDLE;

typedef struct _LZX_DECOMPRESS {
	LONG WindowSize;
	LONG CpuType;
} LZX_DECOMPRESS, *PLZX_DECOMPRESS;

typedef struct _TIME_FIELDS { 
	SHORT Year; // 0x0 sz:0x2
	SHORT Month; // 0x2 sz:0x2
	SHORT Day; // 0x4 sz:0x2
	SHORT Hour; // 0x6 sz:0x2
	SHORT Minute; // 0x8 sz:0x2
	SHORT Second; // 0xA sz:0x2
	SHORT Milliseconds; // 0xC sz:0x2
	SHORT Weekday; // 0xE sz:0x2
} TIME_FIELDS, *PTIME_FIELDS; // size 16
C_ASSERT(sizeof(TIME_FIELDS) == 0x10);

#ifdef __cplusplus
extern "C" {
#endif

	NTSYSAPI
	EXPORTNUM(3)
	VOID
	NTAPI
	DbgPrint(
		IN		const char* s,
		...
	);

	NTSYSAPI
	EXPORTNUM(7)
	VOID
	NTAPI
	ExAcquireReadWriteLockExclusive(
		IN OUT	PERWLOCK pExReadWriteLock
	);

	// http://msdn.microsoft.com/en-us/library/ff544520%28v=vs.85%29.aspx
	// pool functions return NULL if there is insufficient memory
	// uses POOL_TYPE NonPagedPool
	// uses tag 'enoN' (None)
	NTSYSAPI
	EXPORTNUM(9)
	PVOID
	NTAPI
	ExAllocatePool(
		IN  	DWORD NumberOfBytes
	);

	// uses POOL_TYPE NonPagedPool
	NTSYSAPI
	EXPORTNUM(10)
	PVOID
	NTAPI
	ExAllocatePoolWithTag(
		IN  DWORD NumberOfBytes,
		IN  DWORD Tag
	);

	NTSYSAPI
	EXPORTNUM(11)
	PVOID
	NTAPI
	ExAllocatePoolTypeWithTag(
		IN  DWORD NumberOfBytes,
		IN  DWORD Tag,
		IN  POOL_TYPE PoolType
	);

	EXPORTNUM(12)
	extern PDWORD ExConsoleGameRegion;

	NTSYSAPI
	EXPORTNUM(13)
	DWORD
	NTAPI
	ExCreateThread(
		IN		PHANDLE pHandle,
		IN		DWORD dwStackSize,
		IN		LPDWORD lpThreadId,
		IN		PVOID apiThreadStartup,
		IN		LPTHREAD_START_ROUTINE lpStartAddress,
		IN		LPVOID lpParameter,
		IN		DWORD dwCreationFlagsMod
	);

	EXPORTNUM(14)
	extern POBJECT_TYPE ExEventObjectType;

	NTSYSAPI
	EXPORTNUM(15)
	VOID
	NTAPI
	ExFreePool(
		IN PVOID  pPool
	);

	NTSYSAPI
	EXPORTNUM(16)
	NTSTATUS
	NTAPI
	ExGetXConfigSetting(
		IN		WORD dwCategory,
		IN		WORD dwSetting,
		OUT		PVOID pBuffer,
		IN		WORD cbBuffer,
		OUT		PWORD szSetting
	);
	
	NTSYSAPI
	EXPORTNUM(17)
	VOID
	NTAPI
	ExInitializeReadWriteLock(
		IN OUT	PERWLOCK pExReadWriteLock
	);
	
	EXPORTNUM(18)
	extern POBJECT_TYPE ExMutantObjectType;

	NTSYSAPI
	EXPORTNUM(20)
	VOID
	NTAPI
	ExRegisterThreadNotification(
		IN OUT	PEX_THREAD_REGISTRATION threadNotification,
		IN		BOOL Create
	);

	NTSYSAPI
	EXPORTNUM(21)
	VOID
	NTAPI
	ExRegisterTitleTerminateNotification(
		IN OUT	PEX_TITLE_TERMINATE_REGISTRATION pTermStruct,
		IN		BOOL bCreate // true create, false destroy existing
	);

	EXPORTNUM(23)
	extern POBJECT_TYPE ExSemaphoreObjectType;

	NTSYSAPI
	EXPORTNUM(24)
	NTSTATUS
	NTAPI
	ExSetXConfigSetting(
		IN		WORD dwCategory,
		IN		WORD dwSetting,
		IN		PVOID pBuffer,
		IN		WORD szSetting
	);

	NTSYSAPI
	EXPORTNUM(25)
	VOID
	NTAPI
	ExTerminateThread(
		IN DWORD  exitCode
	);

	EXPORTNUM(27)
	extern POBJECT_TYPE ExThreadObjectType;

	EXPORTNUM(28)
	extern POBJECT_TYPE ExTimerObjectType;

	NTSYSAPI
	EXPORTNUM(31)
	VOID
	NTAPI
	XeKeysGetConsoleCertificate(
		OUT		PXE_CONSOLE_CERTIFICATE pConsoleCert
	);

	NTSYSAPI
	EXPORTNUM(36)
	VOID
	NTAPI
	HalOpenCloseODDTray(
		IN		DWORD setTray
	);

	NTSYSAPI
	EXPORTNUM(37)
	VOID
	NTAPI
	HalReadWritePCISpace(
		IN		BYTE Bus,
		IN		BYTE Device,
		IN		BYTE Function,
		IN		DWORD offset, // offset from 0 in pci bus+device+function
		IN OUT	PVOID pBuffer,
		IN      DWORD cbBuffer,
		OUT     BOOL isWrite // true if writing, false if reading
	);

	NTSYSAPI
	EXPORTNUM(39)
	VOID
	NTAPI
	HalRegisterSMCNotification(
		IN OUT	PHAL_SMC_REGISTRATION pSmcRegistration,
		IN		BOOL bUnk // seems to be 1 for create and 0 for remove?
	);

	NTSYSAPI
	EXPORTNUM(40)
	VOID
	NTAPI
	HalReturnToFirmware(
		IN		FIRMWARE_REENTRY powerDownMode
	);

	// buffers are 0x10 bytes in length, on cmd that recv no response send NULL for recv
	NTSYSAPI
	EXPORTNUM(41)
	VOID
	NTAPI
	HalSendSMCMessage(
		IN		LPVOID pCommandBuffer,
		OUT		LPVOID pRecvBuffer
	);

	// similar to KfAcquireSpinLock, but acquires lock in kernel on IopDeviceObjectLock
	NTSYSAPI
	EXPORTNUM(46)
	BYTE
	NTAPI
	IoAcquireDeviceObjectLock(
		VOID
	);

	NTSYSAPI
	EXPORTNUM(47)
	PIRP
	NTAPI
	IoAllocateIrp(
		IN		BYTE StackSize
	);

	NTSYSAPI
	EXPORTNUM(48)
	PIRP
	NTAPI
	IoBuildAsynchronousFsdRequest(
		IN		DWORD MajorFunction,
		IN		PDEVICE_OBJECT pDeviceObject,
		IN OUT	PVOID Buffer,
		IN		DWORD Length OPTIONAL,
		IN		PLARGE_INTEGER StartingOffset OPTIONAL,
		IN		PIO_STATUS_BLOCK IoStatusBlock OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(49)
	PIRP
	NTAPI
	IoBuildDeviceIoControlRequest(
		IN		DWORD IoControlCode,
		IN		PDEVICE_OBJECT pDeviceObject,
		IN		PVOID InputBuffer OPTIONAL,
		IN		DWORD InputBufferLength,
		IN		PVOID OutputBuffer OPTIONAL,
		IN		DWORD OutputBufferLength,
		IN		PKEVENT pEvent OPTIONAL,
		IN OUT	PIO_STATUS_BLOCK pIoStatusBlock
	);

	NTSYSAPI
	EXPORTNUM(50)
	PIRP
	NTAPI
	IoBuildSynchronousFsdRequest(
		IN		DWORD MajorFunction,
		IN		PDEVICE_OBJECT pDeviceObject,
		IN OUT	PVOID Buffer,
		IN		DWORD Length OPTIONAL,
		IN		PLARGE_INTEGER StartingOffset OPTIONAL,
		IN		PKEVENT pEvent,
		IN		PIO_STATUS_BLOCK IoStatusBlock OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(51)
	NTSTATUS
	NTAPI
	IoCallDriver(
		IN		PDEVICE_OBJECT pDeviceObject,
		IN OUT	PIRP pIrp
	);

	NTSYSAPI
	EXPORTNUM(52)
	NTSTATUS
	NTAPI
	IoCheckShareAccess(
		IN		DWORD DesiredAccess,
		IN		DWORD DesiredShareAccess,
		IN OUT	PFILE_OBJECT  FileObject,
		IN OUT	PSHARE_ACCESS ShareAccess,
		IN		BOOL Update
	);

	NTSYSAPI
	EXPORTNUM(53)
	VOID
	NTAPI
	IoCompleteRequest(
		IN OUT		void* pIrp, // PIRP
		IN OUT		DWORD unk // CHAR PriorityBoost?
	);

	EXPORTNUM(54)
	extern POBJECT_TYPE IoCompletionObjectType;

	NTSYSAPI
	EXPORTNUM(55)
	NTSTATUS
	NTAPI
	IoCreateDevice(
		IN		PDRIVER_OBJECT DriverObject,
		IN		DWORD DeviceExtensionSize, // ??
		IN		PSTRING DeviceName, // opt
		IN		DWORD DeviceType,
		IN		DWORD DeviceCharacteristics,
	//	IN		BOOL Exclusive,
		OUT		PDEVICE_OBJECT *DeviceObject
	);

	NTSYSAPI
	EXPORTNUM(57)
	VOID
	NTAPI
	IoDeleteDevice(
		IN		PDEVICE_OBJECT pDeviceObject
	);

	EXPORTNUM(58)
	extern POBJECT_TYPE IoDeviceObjectType;

	EXPORTNUM(62)
	extern POBJECT_TYPE IoFileObjectType;

	NTSYSAPI
	EXPORTNUM(63)
	VOID
	NTAPI
	IoFreeIrp(
		IN		PIRP pIrp
	);

	NTSYSAPI
	EXPORTNUM(64)
	VOID
	NTAPI
	IoInitializeIrp(
		IN OUT	PIRP pIrp,
		IN		BYTE StackSize
	);

	NTSYSAPI
	EXPORTNUM(65)
	NTSTATUS
	NTAPI
	IoInvalidDeviceRequest(
		IN OUT		void* pDeviceObject, // PDEVICE_OBJECT
		IN OUT		void* pIrp // PIRP
	);

	// returns STATUS_ACCESS_DENIED if not called by a system thread
	NTSYSAPI
	EXPORTNUM(66)
	BOOL
	NTAPI
	ExSetBetaFeaturesEnabled(
		IN		DWORD dwBetaFeature
	);

	NTSYSAPI
	EXPORTNUM(67)
	VOID
	NTAPI
	IoQueueThreadIrp(
		IN		PIRP pIrp
	);

	// use this to release IopDeviceObjectLock aquired with IoAcquireDeviceObjectLock
	NTSYSAPI
	EXPORTNUM(68)
	VOID
	NTAPI
	IoReleaseDeviceObjectLock(
		IN		BYTE oldIrql
	);

	NTSYSAPI
	EXPORTNUM(71)
	VOID
	NTAPI
	IoSetShareAccess(
		IN		DWORD DesiredAccess,
		IN		DWORD DesiredShareAccess,
		IN OUT	PFILE_OBJECT  FileObject,
		OUT		PSHARE_ACCESS ShareAccess
	);

	NTSYSAPI
	EXPORTNUM(72)
	VOID
	NTAPI
	IoStartNextPacket(
		IN		PDEVICE_OBJECT DeviceObject
	);

	NTSYSAPI
	EXPORTNUM(73)
	VOID
	NTAPI
	IoStartNextPacketByKey(
		IN		PDEVICE_OBJECT DeviceObject,
		IN		DWORD key
	);

	NTSYSAPI
	EXPORTNUM(74)
	VOID
	NTAPI
	IoStartPacket(
		IN		PDEVICE_OBJECT DeviceObject,
		IN		PIRP pIrp,
		IN		DWORD key OPTIONAL
	);
	
	NTSYSAPI
	EXPORTNUM(75)
	NTSTATUS
	NTAPI
	IoSynchronousDeviceIoControlRequest(
		IN		DWORD IoControlCode,
		IN		PDEVICE_OBJECT pDeviceObject,
		IN		PVOID InputBuffer OPTIONAL,
		IN		DWORD InputBufferLength,
		IN		PVOID OutputBuffer OPTIONAL,
		IN		DWORD OutputBufferLength,
		IN OUT	PDWORD pIoStatusInfo OPTIONAL // the result from iostatus.information is placed here if present
	);

	NTSYSAPI
	EXPORTNUM(76)
	PIRP
	NTAPI
	IoSynchronousFsdRequest(
		IN		DWORD MajorFunction,
		IN		PDEVICE_OBJECT pDeviceObject,
		IN OUT	PVOID Buffer,
		IN		DWORD Length,
		IN		PLARGE_INTEGER StartingOffset
	);

	NTSYSAPI
	EXPORTNUM(77)
	VOID
	NTAPI
	KeAcquireSpinLockAtRaisedIrql(
		IN OUT	PDWORD spinVar
	);

	NTSYSAPI
	EXPORTNUM(82)
	VOID
	NTAPI
	KeBugCheck(
		IN		DWORD BugCheckCode
	);

	NTSYSAPI
	EXPORTNUM(83)
	VOID
	NTAPI
	KeBugCheckEx(
		IN		DWORD BugCheckCode,
		IN		DWORD BugCheckParameter1,
		IN		DWORD BugCheckParameter2,
		IN		DWORD BugCheckParameter3,
		IN		DWORD BugCheckParameter4 
	);

	NTSYSAPI
	EXPORTNUM(86)
	VOID
	NTAPI
	KeContextFromKframes(
		IN 		PKTRAP_FRAME pktf,
		OUT 	PCONTEXT pctx
	);

	NTSYSAPI
	EXPORTNUM(90)
	NTSTATUS
	NTAPI
	KeDelayExecutionThread(
		IN		KPROCESSOR_MODE WaitMode,
		IN		BOOL Alertable,
		IN		PLARGE_INTEGER Interval
	);

	NTSYSAPI
	EXPORTNUM(95)
	VOID
	NTAPI
	KeEnterCriticalRegion(
		VOID
	);

	// untested
	NTSYSAPI
	EXPORTNUM(97)
	VOID
	NTAPI
	KeFlushCacheRange(
		IN		PVOID address,
		IN		DWORD size
	);

	NTSYSAPI
	EXPORTNUM(102)
	UCHAR // enum _KPROC_TYPE
	NTAPI
	KeGetCurrentProcessType(
		VOID
	);

	NTSYSAPI
	EXPORTNUM(109)
	VOID
	NTAPI
	KeInitializeApc(
		IN		PKAPC Apc,
		IN		PKTHREAD Thread,
		IN		PKKERNEL_ROUTINE KernelRoutine,
		IN		PKRUNDOWN_ROUTINE RundownRoutine OPTIONAL,
		IN		PKNORMAL_ROUTINE NormalRoutine OPTIONAL, // UserApcRoutine
		IN		KPROCESSOR_MODE Mode,
		IN		PVOID Context 
	);
	
	NTSYSAPI
	EXPORTNUM(112)
	VOID
	NTAPI
	KeInitializeEvent(
		IN OUT		PKEVENT Event,
		IN			DWORD Type,
		IN			BOOL State
	);

	NTSYSAPI
	EXPORTNUM(118)
	BOOL
	NTAPI
	KeInsertByKeyDeviceQueue(
		IN OUT		PKDEVICE_QUEUE DeviceQueue,
		IN OUT		PKDEVICE_QUEUE_ENTRY DeviceQueueEntry, // part of IRP overlay
		IN			DWORD key
	);

	NTSYSAPI
	EXPORTNUM(119)
	BOOL
	NTAPI
	KeInsertDeviceQueue(
		IN OUT		PKDEVICE_QUEUE DeviceQueue,
		IN OUT		PKDEVICE_QUEUE_ENTRY DeviceQueueEntry // part of IRP overlay
	);

	NTSYSAPI
	EXPORTNUM(122)
	BOOL
	NTAPI
	KeInsertQueueApc(
		IN		PKAPC Apc,
		IN		PVOID SystemArgument1,
		IN		PVOID SystemArgument2,
		IN		DWORD PriorityBoost // KPRIORITY
	);

	NTSYSAPI
	EXPORTNUM(123)
	BOOL
	NTAPI
	KeInsertQueueDpc(
		IN		PKDPC Dpc,
		IN		PVOID SystemArgument1 OPTIONAL,
		IN		PVOID SystemArgument2 OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(124)
	PDWORD
	NTAPI
	KeIpiGenericCall(
		IN  	PKIPI_BROADCAST_WORKER BroadcastFunction,
		IN  	PDWORD Context
	);

	NTSYSAPI
	EXPORTNUM(125)
	VOID
	NTAPI
	KeLeaveCriticalRegion(
		VOID
	);
	
	NTSYSAPI
	EXPORTNUM(132)
	NTSTATUS
	NTAPI
	KeQuerySystemTime(
		OUT		PFILETIME CurrentTime // LARGE_INTEGER
	);

	// lower with KfLowerIrql - DPC IRQL is 2
	NTSYSAPI
	EXPORTNUM(133)
	BYTE
	NTAPI
	KeRaiseIrqlToDpcLevel(
		VOID
	);
	
	NTSYSAPI
	EXPORTNUM(134)
	VOID
	NTAPI
	KeRegisterDriverNotification(
		IN OUT	PKDRIVER_NOTIFICATION_REGISTRATION pDriverNotification,
		IN		KDRIVER_NOTIFICATION_TYPE dwNotificationType // _KDRIVER_NOTIFICATION_TYPE
	);

	NTSYSAPI
	EXPORTNUM(137)
	VOID
	NTAPI
	KeReleaseSpinLockFromRaisedIrql(
		IN OUT	PDWORD spinVar
	);

	NTSYSAPI
	EXPORTNUM(138)
	PKDEVICE_QUEUE_ENTRY
	NTAPI
	KeRemoveByKeyDeviceQueue(
		IN OUT		PKDEVICE_QUEUE DeviceQueue,
		IN OUT		DWORD key
	);

	NTSYSAPI
	EXPORTNUM(139)
	PKDEVICE_QUEUE_ENTRY
	NTAPI
	KeRemoveDeviceQueue(
		IN OUT		PKDEVICE_QUEUE DeviceQueue
	);
	
	NTSYSAPI
	EXPORTNUM(143)
	VOID
	NTAPI
	KeResetEvent(
		IN OUT		PKEVENT Event
	);

	NTSYSAPI
	EXPORTNUM(146)
	VOID
	NTAPI
	KeResumeThread(
		IN	PKTHREAD thread
	);

	NTSYSAPI
	EXPORTNUM(153)
	LONG
	NTAPI
	KeSetBasePriorityThread(
		IN OUT	PKTHREAD Thread,
		IN		LONG Increment
	);

	NTSYSAPI
	EXPORTNUM(154)
	VOID
	NTAPI
	KeSetCurrentProcessType(
		IN		DWORD ProcessType
	);

	NTSYSAPI
	EXPORTNUM(157)
	HRESULT
	NTAPI
	KeSetEvent(
		IN 		PKEVENT Event,
		IN		DWORD Increment,
		IN		BOOL Wait
	);

	NTSYSAPI
	EXPORTNUM(168)
	BYTE
	NTAPI
	KeStallExecutionProcessor(
		IN		DWORD period
	);

	NTSYSAPI
	EXPORTNUM(169)
	VOID
	NTAPI
	KeSuspendThread(
		IN	PKTHREAD thread
	);

	EXPORTNUM(173)
	extern PKTIME_STAMP_BUNDLE KeTimeStampBundle;

	NTSYSAPI
	EXPORTNUM(176)
	NTSTATUS
	NTAPI
	KeWaitForSingleObject(
		IN		PVOID Object,
		IN		KWAIT_REASON WaitReason,
		IN		WAIT_MODE WaitMode,
		IN		BOOL Alertable,
		IN		PLARGE_INTEGER Timeout OPTIONAL
	);

	/* spinlock example:
	DWORD g_spinvar;
	{
		BYTE irql;
		irql = KfAcquireSpinLock(&g_spinvar);
		... some code
		KfReleaseSpinLock(&g_spinvar, irql);
	}*/
	NTSYSAPI
	EXPORTNUM(177)
	BYTE
	NTAPI
	KfAcquireSpinLock(
		IN OUT	PDWORD spinVar
	);

	NTSYSAPI
	EXPORTNUM(178)
	BYTE
	NTAPI
	KfRaiseIrql(
		IN		BYTE irql
	);
	
	NTSYSAPI
	EXPORTNUM(179)
	VOID
	NTAPI
	KfLowerIrql(
		IN		BYTE irql
	);

	NTSYSAPI
	EXPORTNUM(180)
	VOID
	NTAPI
	KfReleaseSpinLock(
		IN OUT	PDWORD spinVar,
		IN		BYTE oldIrql
	);

	NTSYSAPI
	EXPORTNUM(182)
	HRESULT
	NTAPI
	LDICreateDecompression(
		IN		PVOID pcbDataBlockMax,
		IN		PLZX_DECOMPRESS pvConfiguration,
		IN		PVOID pfn_dec_malloc, // void * (__cdecl *)(unsigned long) dec_malloc,
		IN		PVOID pfn_dec_free, // void (__cdecl *)(void *) dec_free,
		IN		PVOID dec_memory,
		IN		PVOID pcbSrcBufferMin,
		OUT		PHANDLE pmdhHandle
	);

	NTSYSAPI
	EXPORTNUM(183)
	HRESULT
	NTAPI
	LDIDecompress(
		IN		HANDLE hmd,
		IN		PVOID pbSrc,
		IN		DWORD cbSrc,
		IN OUT	PVOID pbDst,
		IN OUT	PDWORD pcbResult
	);
	
	NTSYSAPI
	EXPORTNUM(184)
	HRESULT
	NTAPI
	LDIDestroyDecompression(
		IN		HANDLE hmd
	);

	//  - INCOMPLETE!!
	NTSYSAPI
	EXPORTNUM(185)
	PVOID
	NTAPI
	MmAllocatePhysicalMemory(
		IN		DWORD type, // 0 (2 for system?)
		IN		DWORD size, // 1
		IN		DWORD accessFlags //0x20000004 - gives 1 64k phy alloc
	);

	NTSYSAPI
	EXPORTNUM(190)
	PVOID
	NTAPI
	MmGetPhysicalAddress(
		IN		PVOID Address
	);

	NTSYSAPI
	EXPORTNUM(191)
	BOOL
	NTAPI
	MmIsAddressValid(
		IN		PVOID Address
	);

	NTSYSAPI
	EXPORTNUM(196)
	DWORD
	NTAPI
	MmQueryAddressProtect(
		IN		PVOID Address
	);

	NTSYSAPI
	EXPORTNUM(197)
	DWORD
	NTAPI
	MmQueryAllocationSize(
		IN		PVOID Address
	);

	NTSYSAPI
	EXPORTNUM(198)
	DWORD
	NTAPI
	MmQueryStatistics(
		OUT		PMMSTATISTICS pMmStat
	);

	NTSYSAPI
	EXPORTNUM(199)
	DWORD
	NTAPI
	MmSetAddressProtect(
		IN		PVOID Address,
		IN		DWORD Size,
		IN		DWORD Type
	);// PAGE_READWRITE

	NTSYSAPI
	EXPORTNUM(204)
	PVOID
	NTAPI
	NtAllocateVirtualMemory(
		IN OUT 	LPVOID* lpAddress,
		IN		SIZE_T* dwSize,
		IN		DWORD flAllocationType,
		IN		DWORD flProtect,
		IN		DWORD dwMemoryRegionType
	);

	NTSYSAPI
	EXPORTNUM(207)
	NTSTATUS
	NTAPI
	NtClose(
		IN		HANDLE Handle
	);

	 NTSYSAPI
	 EXPORTNUM(208)
	 NTSTATUS
	 NTAPI
	 NtCreateDirectoryObject(
		 OUT		PHANDLE DirectoryHandle,
		 IN			POBJECT_ATTRIBUTES ObjectAttributes
	 );

	NTSYSAPI
	EXPORTNUM(210)
	NTSTATUS
	NTAPI
	NtCreateFile(
		OUT		PHANDLE FileHandle,
		IN		ACCESS_MASK DesiredAccess,
		IN		POBJECT_ATTRIBUTES ObjectAttributes,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		IN		PLARGE_INTEGER AllocationSize OPTIONAL,
		IN		DWORD FileAttributes,
		IN		DWORD ShareAccess,
		IN		DWORD CreateDisposition,
		IN		DWORD CreateOptions
	);

	//  UNTESTED
	NTSYSAPI
	EXPORTNUM(216)
	NTSTATUS
	NTAPI
	NtDeleteFile(
		IN 		POBJECT_ATTRIBUTES ObjectAttributes
	);

	NTSYSAPI
	EXPORTNUM(217)
	NTSTATUS
	NTAPI
	NtDeviceIoControlFile(
		IN		HANDLE FileHandle,
		IN		HANDLE Event OPTIONAL,
		IN		PIO_APC_ROUTINE ApcRoutine OPTIONAL,
		IN		PVOID ApcContext OPTIONAL,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		IN		DWORD IoControlCode,
		IN		PVOID InputBuffer OPTIONAL,
		IN		DWORD InputBufferLength,
		OUT		PVOID OutputBuffer OPTIONAL,
		IN		DWORD OutputBufferLength
	);
	
	NTSYSAPI
	EXPORTNUM(218)
	NTSTATUS
	NTAPI
	NtDuplicateObject(
		IN		HANDLE hSourceHandle,
		OUT		HANDLE* lpTargetHandle,
		IN		DWORD dwOptions
	);

	NTSYSAPI
	EXPORTNUM(222)
	NTSTATUS
	NTAPI
	NtOpenDirectoryObject(
		OUT		PHANDLE DirectoryHandle,
		IN		POBJECT_ATTRIBUTES ObjectAttributes
	);

	NTSYSAPI
	EXPORTNUM(223)
	NTSTATUS
	NTAPI
	NtOpenFile(
		OUT		PHANDLE FileHandle,
		IN		ACCESS_MASK DesiredAccess,
		IN		POBJECT_ATTRIBUTES ObjectAttributes,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		IN		DWORD ShareAccess,
		IN		DWORD OpenOptions
	);

	NTSYSAPI
	EXPORTNUM(224)
	NTSTATUS
	NTAPI
	NtOpenSymbolicLinkObject(
		OUT		PHANDLE LinkHandle,
		IN		POBJECT_ATTRIBUTES ObjectAttributes
	);

	// UNTESTED!!
	NTSYSAPI
	EXPORTNUM(227)
	NTSTATUS
	NTAPI
	NtQueueApcThread(
		IN		HANDLE ThreadHandle,
		IN		PIO_APC_ROUTINE ApcRoutine,
		IN		PVOID ApcRoutineContext OPTIONAL,
		IN		PIO_STATUS_BLOCK ApcStatusBlock OPTIONAL,
		IN		DWORD ApcReserved OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(228)
	NTSTATUS
	NTAPI
	NtQueryDirectoryFile(
		IN		HANDLE FileHandle,
		IN		HANDLE Event OPTIONAL,
		IN		PIO_APC_ROUTINE ApcRoutine OPTIONAL,
		IN		PVOID ApcContext OPTIONAL,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		OUT		PVOID FileInformation,
		IN		DWORD Length,
		IN		PSTRING FileMask OPTIONAL,
		IN		DWORD Unk // usually 0
	);

	NTSYSAPI
	EXPORTNUM(229)
	NTSTATUS
	NTAPI
	NtQueryDirectoryObject(
		IN		HANDLE DirectoryHandle,
		OUT		PVOID Buffer OPTIONAL,
		IN		DWORD Length,
		IN		BOOL RestartScan,//__in       BOOL  ReturnSingleEntry,
		IN OUT	PDWORD Context,
		OUT		PDWORD ReturnLength OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(231)
	NTSTATUS
	NTAPI
	NtQueryFullAttributesFile(
		IN		POBJECT_ATTRIBUTES ObjectAttributes,
		OUT		PFILE_NETWORK_OPEN_INFORMATION Attributes
	);

	NTSYSAPI
	EXPORTNUM(232)
	NTSTATUS
	NTAPI
	NtQueryInformationFile(
		IN		HANDLE FileHandle,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		OUT		PVOID FileInformation,
		IN		DWORD Length,
		IN		FILE_INFORMATION_CLASS FileInformationClass
	);

	NTSYSAPI
	EXPORTNUM(236)
	NTSTATUS
	NTAPI
	NtQuerySymbolicLinkObject(
		IN		HANDLE LinkHandle,
		IN OUT	PSTRING LinkTarget,
		OUT		PULONG ReturnedLength OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(239)
	NTSTATUS
	NTAPI
	NtQueryVolumeInformationFile(
		IN 		HANDLE FileHandle,
		OUT 	PIO_STATUS_BLOCK IoStatusBlock,
		OUT 	PVOID FileSystemInformation,
		IN 		DWORD Length,
		IN 		FSINFOCLASS FileSystemInformationClass
	);

	//  UNTESTED
	NTSYSAPI
	EXPORTNUM(240)
	NTSTATUS
	NTAPI
	NtReadFile(
		IN		HANDLE FileHandle,
		IN		HANDLE Event OPTIONAL,
		IN		PIO_APC_ROUTINE ApcRoutine OPTIONAL,
		IN		PVOID ApcContext OPTIONAL,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		OUT		PVOID Buffer,
		IN		DWORD Length,
		IN		PLARGE_INTEGER ByteOffset OPTIONAL
	);

	//  UNTESTED
	NTSYSAPI
	EXPORTNUM(241)
	NTSTATUS
	NTAPI
	NtReadFileScatter(
		IN 		HANDLE FileHandle,
		IN 		HANDLE Event OPTIONAL,
		IN 		PIO_APC_ROUTINE ApcRoutine OPTIONAL,
		IN 		PVOID ApcContext OPTIONAL,
		OUT 	PIO_STATUS_BLOCK IoStatusBlock,
		IN 		FILE_SEGMENT_ELEMENT SegmentArray,
		IN 		DWORD Length,
		IN 		PLARGE_INTEGER ByteOffset,
		IN 		PDWORD Key OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(246)
	NTSTATUS
	NTAPI
	NtSetEvent(
		IN		HANDLE EventHandle,
		OUT		PLONG PreviousState OPTIONAL 
	);	

	NTSYSAPI
	EXPORTNUM(247)
	NTSTATUS
	NTAPI
	NtSetInformationFile(
		IN		HANDLE FileHandle,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		IN		PVOID FileInformation,
		IN		DWORD Length,
		IN		FILE_INFORMATION_CLASS FileInformationClass
	);

	NTSYSAPI
	EXPORTNUM(249)
	NTSTATUS
	NTAPI
	NtSetSystemTime(
		IN		PFILETIME SystemTime,  // LARGE_INTEGER
		OUT		PFILETIME PreviousTime // LARGE_INTEGER
	);

	NTSYSAPI
	EXPORTNUM(253)
	NTSTATUS
	NTAPI
	NtWaitForSingleObjectEx(
		IN		HANDLE Handle,
		IN		DWORD WaitMode,
		IN		BOOL Alertable,
		IN		PLARGE_INTEGER Timeout
	);

	NTSYSAPI
	EXPORTNUM(255)
	NTSTATUS
	NTAPI
	NtWriteFile(
		IN		HANDLE FileHandle,
		IN		HANDLE Event OPTIONAL,
		IN		PIO_APC_ROUTINE ApcRoutine OPTIONAL,
		IN		PVOID ApcContext OPTIONAL,
		OUT		PIO_STATUS_BLOCK IoStatusBlock,
		IN		PVOID Buffer,
		IN		DWORD Length,
		IN		PLARGE_INTEGER ByteOffset OPTIONAL
	);


	NTSYSAPI
	EXPORTNUM(258)
	NTSTATUS
	NTAPI
	ObCreateObject(
		IN			POBJECT_TYPE ObjectType,
		IN			POBJECT_ATTRIBUTES ObjectAttributes,
		IN			DWORD ObjectBodySize,
		OUT			PVOID *Object
	);

	NTSYSAPI
	EXPORTNUM(259)
	HRESULT
	NTAPI
	ObCreateSymbolicLink(
		IN		PSTRING SymbolicLinkName,
		IN		PSTRING DeviceName
	);

	NTSYSAPI
	EXPORTNUM(260)
	HRESULT
	NTAPI
	ObDeleteSymbolicLink(
		IN		PSTRING SymbolicLinkName
	);

	NTSYSAPI
	EXPORTNUM(261)
	VOID
	NTAPI
	ObDereferenceObject(
		IN		PVOID Object
	);

	EXPORTNUM(262)
	extern POBJECT_TYPE ObDirectoryObjectType;

	NTSYSAPI
	EXPORTNUM(264)
	NTSTATUS
	NTAPI
	ObInsertObject(
		IN			PVOID Object,
		IN			POBJECT_ATTRIBUTES ObjectAttributes, // not sure, seems it's fed this from ObCreateObject
		IN			DWORD AdditionalReferences, // not sure on this one, could be a bool
		OUT			PHANDLE Handle
	);

	NTSYSAPI
	EXPORTNUM(265)
	BOOL
	NTAPI
	ObIsTitleObject(
		IN		PFILE_OBJECT pFileObject
	);

	NTSYSAPI
	EXPORTNUM(266)
	HRESULT
	NTAPI
	ObLookupAnyThreadByThreadId(
		IN		DWORD dwThreadId,
		OUT		PKTHREAD *pthr
	);

	NTSYSAPI
	EXPORTNUM(271)
	VOID
	NTAPI
	ObReferenceObject(
		IN		PVOID Object
	);

	NTSYSAPI
	EXPORTNUM(272)
	NTSTATUS
	NTAPI
	ObReferenceObjectByHandle(
		IN			HANDLE Handle,
		IN			POBJECT_TYPE ObjectType,
		OUT			PVOID *Object
	);

	NTSYSAPI
	EXPORTNUM(273)
	NTSTATUS
	NTAPI
	ObReferenceObjectByName(
		IN			PSTRING ObjectName,
		IN			DWORD Attributes, // PACCESS_STATE AccessState, ACCESS_MASK DesiredAccess
		IN			POBJECT_TYPE ObjectType,
		IN			PVOID ParseContext OPTIONAL, // KPROCESSOR_MODE AccessMode
		OUT			PVOID* Object
	);

	EXPORTNUM(274)
	extern POBJECT_TYPE ObSymbolicLinkObjectType;

	NTSYSAPI
	EXPORTNUM(275)
	NTSTATUS
	NTAPI
	ObTranslateSymbolicLink(
		IN		PVOID,
		OUT		PANSI_STRING
	);

	NTSYSAPI
	EXPORTNUM(283)
	int
	NTAPI
	RtlCompareMemoryUlong(
		IN   	void* Source,
		IN   	DWORD Length,
		IN   	DWORD Pattern
	);

	// just fake this one and cast to the winnt.h types to avoid conflicts
	//NTSYSAPI
	//EXPORTNUM(293)
	//VOID
	//NTAPI
	//RtlEnterCriticalSection(
	//	IN OUT		void* pMutex
	//);

	NTSYSAPI
	EXPORTNUM(298)
	VOID
	NTAPI
	RtlGetStackLimits(
		IN OUT	PDWORD LimitA,
		IN OUT	PDWORD LimitB
	);

	NTSYSAPI
	EXPORTNUM(299)
	PVOID
	NTAPI
	RtlImageXexHeaderField(
		IN		PVOID XexHeaderBase,
		IN		DWORD ImageField
	);

	NTSYSAPI
	EXPORTNUM(300)
	VOID
	NTAPI
	RtlInitAnsiString(
		IN OUT	PANSI_STRING DestinationString,
		IN		PCSZ  SourceString
	);

	// just fake this one and cast to the winnt.h types to avoid conflicts
	//NTSYSAPI
	//EXPORTNUM(304)
	//VOID
	//NTAPI
	//RtlLeaveCriticalSection(
	//	IN OUT		void* pMutex
	//);

	NTSYSAPI
	EXPORTNUM(305)
	PVOID
	NTAPI
	RtlLookupFunctionEntry(
		IN		PVOID pvOffset
	);

	NTSYSAPI
	EXPORTNUM(313)
	int
	NTAPI
	RtlScprintf(
		IN		const CHAR* Format,
		...
	);

	NTSYSAPI
	EXPORTNUM(314)
	int
	NTAPI
	RtlSnprintf(
		IN		CHAR* Buffer,
		IN		int SizeInBytes,
		IN		const CHAR* Format,
		...
	);
	
	NTSYSAPI
	EXPORTNUM(315)
	int
	NTAPI
	RtlSprintf(
		IN		CHAR* Buffer,
		IN		const CHAR* Format,
		...
	);
	
	NTSYSAPI
	EXPORTNUM(316)
	int
	NTAPI
	RtlScwprintf(
		IN		const WCHAR* Format,
		...
	);

	NTSYSAPI
	EXPORTNUM(317)
	int
	NTAPI
	RtlSnwprintf(
		IN		WCHAR * Buffer,
		IN		DWORD MaxLength,
		IN		LPCWSTR Format,
		...
	);	

	NTSYSAPI
	EXPORTNUM(318)
	int
	NTAPI
	RtlSwprintf(
		IN		WCHAR * Buffer,
		IN		LPCWSTR Format,
		...
	);

	NTSYSAPI
	EXPORTNUM(320)
	NTSTATUS
	NTAPI
	RtlTimeToTimeFields(
		IN		PFILETIME Time, // feed with result from KeQuerySystemTime
		OUT		PTIME_FIELDS TimeFields
	);

	NTSYSAPI
	EXPORTNUM(332)
	int
	NTAPI
	RtlVscprintf(
		IN		const CHAR* Format, 
		IN		va_list va
	);

	NTSYSAPI
	EXPORTNUM(333)
	int
	NTAPI
	RtlVsnprintf(
		IN		CHAR* Buffer, 
		IN		int SizeInBytes, 
		IN		const CHAR* Format, 
		IN		va_list va
	);
	
	NTSYSAPI
	EXPORTNUM(334)
	int
	NTAPI
	RtlVsprintf(
		IN		CHAR* Buffer, 
		IN		const CHAR* Format, 
		IN		va_list va
	);

	NTSYSAPI
	EXPORTNUM(335)
	int
	NTAPI
	RtlVscwprintf(
		IN		const WCHAR* Format, 
		IN		va_list va
	);

	NTSYSAPI
	EXPORTNUM(336)
	int
	NTAPI
	RtlVsnwprintf(
		IN		WCHAR* Buffer,
		IN		int SizeInBytes,
		IN		const WCHAR* Format,
		IN		va_list va
	);

	NTSYSAPI
	EXPORTNUM(337)
	int
	NTAPI
	RtlVswprintf(
		IN		WCHAR* Buffer,
		IN		const WCHAR* Format,
		IN		va_list va
	);

	EXPORTNUM(342)
	extern PXBOX_HARDWARE_INFO XboxHardwareInfo;

	EXPORTNUM(343)
	extern PXBOX_KRNL_VERSION XboxKrnlBaseVersion;

	EXPORTNUM(344)
	extern PXBOX_KRNL_VERSION XboxKrnlVersion;

	//dword pointer in kernel space to current title exe handle
	// PLDR_DATA_TABLE_ENTRY ent = (PLDR_DATA_TABLE_ENTRY)(*XexExecutableModuleHandle);
	//extern PHANDLE XexExecutableModuleHandle;
	EXPORTNUM(403)
	extern PLDR_DATA_TABLE_ENTRY* XexExecutableModuleHandle;

	NTSYSAPI
	EXPORTNUM(404)
	BOOL
	NTAPI
	XexCheckExecutablePrivilege(
		IN		DWORD priviledge
	);

	// ie XexGetModuleHandle("xam.xex", &hand), returns 0 on success
	NTSYSAPI
	EXPORTNUM(405)
	NTSTATUS
	NTAPI
	XexGetModuleHandle(
		IN		PSZ moduleName,
		IN OUT	PHANDLE hand
	);

	// ie XexGetProcedureAddress(hand ,0x50, &addr) returns 0 on success
	NTSYSAPI
	EXPORTNUM(407)
	NTSTATUS
	NTAPI
	XexGetProcedureAddress(
		IN		HANDLE hand,
		IN		DWORD dwOrdinal,
		IN		PVOID pvAddress
	);

	NTSYSAPI
	EXPORTNUM(408)
	NTSTATUS
	NTAPI
	XexLoadExecutable(
		IN		PCHAR szXexName,
		IN OUT	PHANDLE pHandle,
		IN		DWORD dwModuleTypeFlags,
		IN		DWORD dwMinimumVersion
	);

	NTSYSAPI
	EXPORTNUM(409)
	NTSTATUS
	NTAPI
	XexLoadImage(
		IN		LPCSTR szXexName,
		IN		DWORD dwModuleTypeFlags,
		IN		DWORD dwMinimumVersion,
		IN OUT	PHANDLE pHandle
	);

	NTSYSAPI
	EXPORTNUM(410)
	NTSTATUS
	NTAPI
	XexLoadImageFromMemory(
		IN		PVOID pvXexBuffer,
		IN		DWORD dwSize,
		IN		LPCSTR szXexName,
		IN		DWORD dwModuleTypeFlags,
		IN		DWORD dwMinimumVersion,
		IN OUT	PHANDLE pHandle
	);

	NTSYSAPI
	EXPORTNUM(412)
	PVOID // returns pointer to NT header
	NTAPI
	XexPcToFileHeader(
		IN		PVOID address,
		OUT		PLDR_DATA_TABLE_ENTRY* ldatOut // puts pointer to LDR_DATA_TABLE_ENTRY in the address pointer here
	);

	NTSYSAPI
	EXPORTNUM(416)
	HRESULT
	NTAPI
	XexStartExecutable(
		IN		FARPROC TitleProcessInitThreadProc
	);

	NTSYSAPI
	EXPORTNUM(417)
	VOID
	NTAPI
	XexUnloadImage(
		IN		HANDLE moduleHandle
	);

	NTSYSAPI
	EXPORTNUM(418)
	VOID
	NTAPI
	XexUnloadImageAndExitThread(
		IN		HANDLE moduleHandle,
		IN		HANDLE threadHandle
	);

	NTSYSAPI
	EXPORTNUM(420)
	NTSTATUS
	NTAPI
	XexVerifyImageHeaders(
		IN		PIMAGE_XEX_HEADER XexHeader,
		IN		DWORD SizeOfHeaders
	);

	NTSYSAPI
	EXPORTNUM(424)
	PVOID
	NTAPI
	RtlImageDirectoryEntryToData(
		IN		PVOID Base,
		IN		BOOL MappedAsImage,
		IN		WORD DirectoryEntry,
		IN OUT	PDWORD size
	);

	EXPORTNUM(430)
	extern PCHAR ExLoadedCommandLine; // max size 0x200 ie: "default.xex"
	
	EXPORTNUM(431)
	extern PCHAR ExLoadedImageName; // max size 0x100 ie: "\Device\Mass0\xexloader_testing\default.xex"

	NTSYSAPI
	EXPORTNUM(434)
	VOID
	NTAPI
	VdDisplayFatalError(
		IN		DWORD dwErrorCode
	);

	NTSYSAPI
	EXPORTNUM(442)
	VOID
	NTAPI
	VdGetCurrentDisplayInformation(
		IN OUT	PDISPLAY_INFO dispInfo
	);

	EXPORTNUM(446)
	extern D3DDevice* VdGlobalDevice;

	EXPORTNUM(447)
	extern D3DDevice* VdGlobalXamDevice;

	NTSYSAPI
	EXPORTNUM(461)
	PVOID // seems to return RTL_CRITICAL_SECTION VdpNotificationRegistrationListLock
	NTAPI
	VdRegisterGraphicsNotification(
		IN		LP_VD_NOTIFICATION_CALLBACK VdpXamNotificationCallback,
		IN		BOOL unk // seems to be insert/delete toggle
	);

	// when notification is called from kernel, PVD_NOTIFICATION_REGISTRATION is always NULL
	NTSYSAPI
	EXPORTNUM(462)
	VOID
	NTAPI
	VdRegisterXamGraphicsNotification(
		IN		LP_VD_NOTIFICATION_CALLBACK VdpXamNotificationCallback
	);

	NTSYSAPI
	EXPORTNUM(486)
	NTSTATUS
	NTAPI
	XInputdReadState(
		IN		DWORD dwDeviceContext,
		OUT		PDWORD pdwPacketNumber,
		OUT		PXINPUT_GAMEPAD pInputData,
		IN OUT	PBOOL pbUnknown OPTIONAL
	);

	NTSYSAPI
	EXPORTNUM(487)
	NTSTATUS
	NTAPI
	XInputdWriteState(
		IN		DWORD DeviceContext,
		IN		DWORD dwVibrationLevel,
		IN		VOID* pInputData, // PXINPUT_GAMEPAD PXINPUT_OUTPUT_DATA
		IN 		BYTE bAmplitude,
		IN 		BYTE bFrequency,
		IN 		BYTE bOffset
	);

	NTSYSAPI
	EXPORTNUM(569)
	BOOL
	NTAPI
	ExIsBetaFeatureEnabled(
		IN		DWORD dwBetaFeature
	);

	NTSYSAPI
	EXPORTNUM(570)
	VOID
	NTAPI
	XeKeysGetFactoryChallenge(
		IN		PVOID buf
	);

	NTSYSAPI
	EXPORTNUM(571)
	DWORD
	NTAPI
	XeKeysSetFactoryResponse(
		IN		PVOID buf
	);

	NTSYSAPI
	EXPORTNUM(575)
	DWORD
	NTAPI
	XeKeysGetStatus(
		IN OUT	PDWORD sta
	);

	NTSYSAPI
	EXPORTNUM(576)
	NTSTATUS
	NTAPI
	XeKeysGeneratePrivateKey(
		IN		WORD KeyId
	);
	
	// returns the size of the given key number for use with get/set
	NTSYSAPI
	EXPORTNUM(577)
	WORD
	NTAPI
	XeKeysGetKeyProperties(
		IN		DWORD KeyId
	);

	NTSYSAPI
	EXPORTNUM(578)
	NTSTATUS
	NTAPI
	XeKeysSetKey(
		IN		WORD KeyId,
		IN		PVOID KeyBuffer,
		IN		WORD keyLength
	);

	NTSYSAPI
	EXPORTNUM(579)
	NTSTATUS
	NTAPI
	XeKeysGenerateRandomKey(
		IN		WORD KeyId,
		OUT		PVOID KeyBuffer
	);

	NTSYSAPI
	EXPORTNUM(580)
	NTSTATUS
	NTAPI
	XeKeysGetKey(
		IN		WORD KeyId,
		OUT		PVOID KeyBuffer,
		IN OUT	PDWORD keyLength
	);

	NTSYSAPI
	EXPORTNUM(582)
	DWORD
	NTAPI
	XeKeysGetConsoleID(
		OUT		PBYTE databuffer OPTIONAL, // optional, will copy the console ID to this if it's sent
		OUT		char* szBuffer OPTIONAL // optional, will sprintf the data to this if it's sent
	);

	NTSYSAPI
	EXPORTNUM(583)
	NTSTATUS
	NTAPI
	XeKeysGetConsoleType(
		IN OUT	PDWORD ConsoleType
	);

	NTSYSAPI
	EXPORTNUM(585)
	BOOL
	NTAPI
	XeKeysHmacSha(
		IN		XEKEY_INDEX keySel,
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		IN		const PBYTE pbInp3,
		IN		DWORD cbInp3,
		IN OUT	PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(596)
	BOOL
	NTAPI
	XeKeysObfuscate(
		IN		XEKEY_OBFUSCATE keySel,
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN OUT	PBYTE pbOut,
		IN		PDWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(597)
	BOOL
	NTAPI
	XeKeysUnObfuscate(
		IN		XEKEY_OBFUSCATE keySel,
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN OUT	PBYTE pbOut,
		IN		PDWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(598)
	VOID
	NTAPI
	XeKeysConsolePrivateKeySign(
		IN		BYTE* pbHash,
		OUT		PXE_CONSOLE_SIGNATURE pConsoleSignature
	);

	NTSYSAPI
	EXPORTNUM(599)
	BOOL
	NTAPI
	XeKeysConsoleSignatureVerification(
		IN		PBYTE pbHash, // 0x14 byte hash
		IN		XE_CONSOLE_SIGNATURE sig,
		IN OUT	PDWORD localCertCompareResult // result of comparing the cert to the console cert
	);

	NTSYSAPI
	EXPORTNUM(607)
	DWORD
	NTAPI
	XeKeysExecute(
		IN		PVOID pvPhyBuffer, // must be 0x80 byte aligned
		IN		DWORD len, // code block must be > 0x120 and no larger than 0x10000
		IN OUT	PVOID arg1, // args depend on the code block sent
		IN OUT	PVOID arg2,
		IN OUT	PVOID arg3,
		IN OUT	PVOID arg4
	);

	NTSYSAPI
	EXPORTNUM(609)
	VOID
	NTAPI
	XInputdPowerDownDevice(
		IN		DWORD flag // or the user index with 0x10000000
	);

	NTSYSAPI
	EXPORTNUM(611)
	VOID
	NTAPI
	AniTerminateAnimation(
		VOID
	);
	
	NTSYSAPI
	EXPORTNUM(620)
	VOID
	NTAPI
	HalGetPowerUpCause(
		OUT		PBYTE 	reply
	);

	NTSYSAPI
	EXPORTNUM(629)
	NTSTATUS
	NTAPI
	XexTransformImageKey(
		IN OUT	PVOID pBuf,
		IN		DWORD cbLength
	);

	NTSYSAPI
	EXPORTNUM(650)
	NTSTATUS
	NTAPI
	NtAllocateEncryptedMemory(
		IN   	DWORD memoryRegionType, // 0= auto/thread type, 1= title, 2=system, 3=debug, 4=??
		IN  	SIZE_T Size,
		OUT		LPVOID* pBuffer
	);	

	NTSYSAPI
	EXPORTNUM(690)
	NTSTATUS
	NTAPI
	XeKeysGetMediaID(
		IN OUT	PBYTE pMediaID, // 0x10 bytes
		IN		BOOL fCheckHvAuth // if true checks if dvd auth data is valid first?
	);

	EXPORTNUM(731)
	extern PVOID* UsbdBootEnumerationDoneEvent;

	NTSYSAPI
	EXPORTNUM(738)
	HRESULT
	NTAPI
	LDIResetDecompression(
		IN		HANDLE hmd
	);

	NTSYSAPI
	EXPORTNUM(793)
	NTSTATUS
	NTAPI
	HalReadArgonEeprom(
		IN		ARGON_EEPROM_FIELD field,
		IN OUT	PVOID pvBuffer,
		IN		DWORD dwCbbuf,
		OUT		PWORD pwBufUsed OPTIONAL
	);

	// NTSYSAPI
	// EXPORTNUM(111)
	// VOID
	// NTAPI
	// KeInitializeDpc(
		// OUT		PKDPC Dpc,
		// IN		PVOID DeferredRoutine,
		// IN		PVOID DeferredContext OPTIONAL
	// );

	// NTSYSAPI
	// EXPORTNUM(113)
	// VOID
	// NTAPI
	// KeInitializeInterrupt(
		// OUT		PKINTERRUPT InterruptObject,
		// IN		PVOID ServiceRoutine,
		// IN		PVOID ServiceContext,
		// IN		BYTE Irql,
		// IN		BYTE InterruptMode,
		// IN		BYTE bProcTargetNumber // KAFFINITY ProcessorEnableMask
	// );

	// NTSYSAPI
	// EXPORTNUM(45)
	// NTSTATUS
	// NTAPI
	// KeConnectInterrupt(
		// IN		PKINTERRUPT InterruptObject
	// );


	

// haven't had any reason to touch on these Io functions as of yet
// IoSetIoCompletion @70
// IoCreateFile @56
// IoDismountVolume @59
// IoDismountVolumeByFileHandle @60
// IoDismountVolumeByName @61
// IoCheckShareAccess @52
// IoRemoveShareAccess @69
// IoSetShareAccess @71
	



#ifdef __cplusplus
}
#endif


#endif	//__KERNEL_DEFINES_H

