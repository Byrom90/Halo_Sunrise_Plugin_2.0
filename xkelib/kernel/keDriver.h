#ifndef __KEDRIVER_H
#define __KEDRIVER_H

#define STATUS_BUFFER_OVERFLOW          ((NTSTATUS)0x80000005)
#define STATUS_NO_MORE_FILES			((NTSTATUS)0x80000006)
#define STATUS_VERIFY_REQUIRED          ((NTSTATUS)0x80000016)

#define STATUS_NOT_IMPLEMENTED			((NTSTATUS)0xC0000002)
#define STATUS_INVALID_PARAMETER		((NTSTATUS)0xC000000D)
#define STATUS_NO_SUCH_DEVICE			((NTSTATUS)0xC000000E)
#define STATUS_INVALID_DEVICE_REQUEST	((NTSTATUS)0xC0000010)
#define STATUS_NO_MEDIA_IN_DEVICE		((NTSTATUS)0xC0000013)
#define STATUS_UNRECOGNIZED_MEDIA		((NTSTATUS)0xC0000014)
#define STATUS_MORE_PROCESSING_REQUIRED	((NTSTATUS)0xC0000016)
#define STATUS_ACCESS_DENIED			((NTSTATUS)0xC0000022)
#define STATUS_BUFFER_TOO_SMALL         ((NTSTATUS)0xC0000023)
#define STATUS_OBJECT_NAME_INVALID		((NTSTATUS)0xC0000033)
#define STATUS_DELETE_PENDING			((NTSTATUS)0xC0000056)
#define STATUS_INSUFFICIENT_RESOURCES	((NTSTATUS)0xC000009A) // poolTypeWithTag fails
#define STATUS_DEVICE_NOT_READY         ((NTSTATUS)0xC00000A3)
#define STATUS_NOT_SUPPORTED			((NTSTATUS)0xC00000BB)
#define STATUS_INVALID_PARAMETER_1		((NTSTATUS)0xC00000EF)
#define STATUS_INVALID_PARAMETER_2		((NTSTATUS)0xC00000F0)
#define STATUS_INVALID_PARAMETER_3		((NTSTATUS)0xC00000F1)
#define STATUS_INVALID_PARAMETER_4		((NTSTATUS)0xC00000F2)
#define STATUS_INVALID_PARAMETER_5		((NTSTATUS)0xC00000F3)
#define STATUS_INVALID_PARAMETER_6		((NTSTATUS)0xC00000F4)
#define STATUS_INVALID_PARAMETER_7		((NTSTATUS)0xC00000F5)
#define STATUS_INVALID_PARAMETER_8		((NTSTATUS)0xC00000F6)
#define STATUS_INVALID_PARAMETER_9		((NTSTATUS)0xC00000F7)
#define STATUS_INVALID_PARAMETER_10		((NTSTATUS)0xC00000F8)
#define STATUS_INVALID_PARAMETER_11		((NTSTATUS)0xC00000F9)
#define STATUS_INVALID_PARAMETER_12		((NTSTATUS)0xC00000FA)
#define STATUS_FILE_CLOSED				((NTSTATUS)0xC0000128)
#define STATUS_IO_DEVICE_ERROR			((NTSTATUS)0xC0000185)

// more devices at http://msdn.microsoft.com/en-us/library/windows/hardware/ff544637%28v=vs.85%29.aspx
#define IO_NO_INCREMENT					0
#define IO_CD_ROM_INCREMENT				1	// FILE_DEVICE_CD_ROM, FILE_DEVICE_CD_ROM_FILE_SYSTEM
#define IO_NETWORK_INCREMENT			2	// FILE_DEVICE_NETWORK, FILE_DEVICE_NETWORK_BROWSER, FILE_DEVICE_NETWORK_FILE_SYSTEM, FILE_DEVICE_PHYSICAL_NETCARD

#define IO_TYPE_ADAPTER                 1
#define IO_TYPE_CONTROLLER              2
#define IO_TYPE_DEVICE                  3
#define IO_TYPE_DRIVER                  4
#define IO_TYPE_FILE                    5
#define IO_TYPE_IRP                     6
#define IO_TYPE_MASTER_ADAPTER          7
#define IO_TYPE_OPEN_PACKET             8
#define IO_TYPE_TIMER                   9
#define IO_TYPE_VPB                     10
#define IO_TYPE_ERROR_LOG               11
#define IO_TYPE_ERROR_MESSAGE           12
#define IO_TYPE_DEVICE_OBJECT_EXTENSION 13

// IRP_NOCACHE – data for this I/O request should be read from the actual backing media and not from cache.
// IRP_PAGING_IO – the I/O operation in question is performing paging I/O. This bit is used by the Memory Manager.
// IRP_MOUNT_COMPLETION – the I/O operation in question is performing a mount operation.
// IRP_SYNCHRONOUS_API – the API in question expects synchronous behavior. While synchronous behavior is advised when this bit is set, it is not required.
// IRP_ASSOCIATED_IRP – the IRP in question is associated with some larger I/O operation.
// IRP_BUFFERED_IO – the AssociatedIrp.SystemBuffer field is valid
// IRP_DEALLOCATE_BUFFER – the system buffer was allocated from pool and should be deallocated by the I/O Manager.
// IRP_INPUT_OPERATION – the I/O operation is for input. This is used by the Memory Manager to indicate a page in operation.
// IRP_SYNCHRONOUS_PAGING_IO – the paging operation should complete synchronously. This bit is used by the Memory Manager.
// IRP_CREATE_OPERATION – the IRP represents a file system create operation.
// IRP_READ_OPERATION – the IRP represents a read operation.
// IRP_WRITE_OPERATION – the IRP represents a write operation.
// IRP_CLOSE_OPERATION – the IRP represents a close operation.
// IRP_DEFER_IO_COMPLETION – the IRP should be processed asynchronously. While asynchronous behavior is advised when this bit is set, it is not required.

// Define I/O Request Packet (IRP) flags
#define IRP_NOCACHE                     0x00000001
#define IRP_SYNCHRONOUS_API             0x00000002
#define IRP_CREATE_OPERATION            0x00000004
#define IRP_CLOSE_OPERATION             0x00000008
#define IRP_DEFER_IO_COMPLETION         0x00000010
#define IRP_UNLOCK_USER_BUFFER          0x00000020
#define IRP_UNMAP_SEGMENT_ARRAY         0x00000040

#define IRP_IO_PRIORITY_MASK            0xFF000000
#define IRP_IO_PRIORITY_SHIFT           24

// Define I/O Request Packet (IRP) flags - windows
//#define IRP_NOCACHE                     0x00000001
//#define IRP_PAGING_IO                   0x00000002
//#define IRP_MOUNT_COMPLETION            0x00000002
//#define IRP_SYNCHRONOUS_API             0x00000004
//#define IRP_ASSOCIATED_IRP              0x00000008 // does KeSetEvent for IRP.UserEvent on complete
//#define IRP_BUFFERED_IO                 0x00000010 // checks PendingReturned on complete
//#define IRP_DEALLOCATE_BUFFER           0x00000020 // does MmLockUnlockBufferPages on complete
//#define IRP_INPUT_OPERATION             0x00000040 // does MmUnlockAndUnmapSegmentArray on complete
//#define IRP_SYNCHRONOUS_PAGING_IO       0x00000040
//#define IRP_CREATE_OPERATION            0x00000080
//#define IRP_READ_OPERATION              0x00000100
//#define IRP_WRITE_OPERATION             0x00000200
//#define IRP_CLOSE_OPERATION             0x00000400
//#define IRP_DEFER_IO_COMPLETION         0x00000800
//#define IRP_OB_QUERY_NAME               0x00001000
//#define IRP_HOLD_DEVICE_QUEUE           0x00002000
//#define IRP_UM_DRIVER_INITIATED_IO      0x00400000  
//// Define I/O request packet (IRP) alternate flags for allocation control.
//#define IRP_QUOTA_CHARGED               0x01
//#define IRP_ALLOCATED_MUST_SUCCEED      0x02
//#define IRP_ALLOCATED_FIXED_SIZE        0x04
//#define IRP_LOOKASIDE_ALLOCATION        0x08

/* IO_STACK_LOCATION.Control from wdm.h in ReactOS*/
#define SL_PENDING_RETURNED               0x01
#define SL_ERROR_RETURNED                 0x02
#define SL_INVOKE_ON_CANCEL               0x20
#define SL_INVOKE_ON_SUCCESS              0x40
#define SL_INVOKE_ON_ERROR                0x80

/* IO_STACK_LOCATION.flags */
// IRP_MJ_CREATE/IRP_MJ_CREATE_NAMED_PIPE
#define SL_OPEN_TARGET_DIRECTORY        0x04
#define SL_CASE_SENSITIVE               0x80 // only added by parse routine
// #define SL_FORCE_ACCESS_CHECK           0x01
// #define SL_OPEN_PAGING_FILE             0x02
// #define SL_STOP_ON_SYMLINK              0x08


// IRP_MJ_READ/IRP_MJ_WRITE
#define SL_FSCACHE_REQUEST              0x01 // for read this bit signals to check args
//#define SL_KEY_SPECIFIED                0x01 
//#define SL_OVERRIDE_VERIFY_VOLUME       0x02
//#define SL_WRITE_THROUGH                0x04
//#define SL_FT_SEQUENTIAL_WRITE          0x08
//#define SL_FORCE_DIRECT_WRITE           0x10
//#define SL_REALTIME_STREAM              0x20

// Device I/O Control
// Same SL_OVERRIDE_VERIFY_VOLUME as for read/write above.
#define SL_READ_ACCESS_GRANTED          0x01
#define SL_WRITE_ACCESS_GRANTED         0x04    // Gap for SL_OVERRIDE_VERIFY_VOLUME

// IRP_MJ_LOCK_CONTROL
#define SL_FAIL_IMMEDIATELY             0x01
#define SL_EXCLUSIVE_LOCK               0x02

// IRP_MJ_DIRECTORY_CONTROL/IRP_MJ_QUERY_EA/IRP_MJ_QUERY_QUOTA
#define SL_RESTART_SCAN                 0x01
//#define SL_RETURN_SINGLE_ENTRY          0x02
//#define SL_INDEX_SPECIFIED              0x04

// IRP_MJ_DIRECTORY_CONTROL
#define SL_WATCH_TREE                   0x01

// IRP_MJ_FILE_SYSTEM_CONTROL
#define SL_ALLOW_RAW_MOUNT              0x01

// IRP_MJ_SET_INFORMATION
#define SL_BYPASS_ACCESS_CHECK          0x01

#define METHOD_BUFFERED                   0
#define METHOD_IN_DIRECT                  1
#define METHOD_OUT_DIRECT                 2
#define METHOD_NEITHER                    3

#define METHOD_DIRECT_TO_HARDWARE       METHOD_IN_DIRECT
#define METHOD_DIRECT_FROM_HARDWARE     METHOD_OUT_DIRECT

// Device Object flags
#define DO_EXCLUSIVE                    0x00000002      
#define DO_DIRECT_IO                    0x00000004      
#define DO_DEVICE_HAS_NAME              0x00000008      
#define DO_DEVICE_INITIALIZING          0x00000010      

// Device Object flags - windows flags just in case
//#define DO_VERIFY_VOLUME                    0x00000002      
//#define DO_BUFFERED_IO                      0x00000004      
//#define DO_EXCLUSIVE                        0x00000008      
//#define DO_DIRECT_IO                        0x00000010      
//#define DO_MAP_IO_BUFFER                    0x00000020      
//#define DO_DEVICE_HAS_NAME                  0x00000040      
//#define DO_DEVICE_INITIALIZING              0x00000080      
//#define DO_SYSTEM_BOOT_PARTITION            0x00000100      
//#define DO_LONG_TERM_REQUESTS               0x00000200      
//#define DO_NEVER_LAST_DEVICE                0x00000400      
//#define DO_SHUTDOWN_REGISTERED              0x00000800      
//#define DO_BUS_ENUMERATED_DEVICE            0x00001000      
//#define DO_POWER_PAGABLE                    0x00002000      
//#define DO_POWER_INRUSH                     0x00004000      
//#define DO_LOW_PRIORITY_FILESYSTEM          0x00010000      
//#define DO_SUPPORTS_TRANSACTIONS            0x00040000      
//#define DO_FORCE_NEITHER_IO                 0x00080000      
//#define DO_VOLUME_DEVICE_OBJECT             0x00100000      
//#define DO_SYSTEM_SYSTEM_PARTITION          0x00200000      
//#define DO_SYSTEM_CRITICAL_PARTITION        0x00400000      
//#define DO_DISALLOW_EXECUTE                 0x00800000

#define FO_SYNCHRONOUS_IO               0x01
#define FO_NO_INTERMEDIATE_BUFFERING    0x04
#define FO_SEQUENTIAL_ONLY              0x08
#define FO_CLEANUP_COMPLETE             0x10
#define FO_HANDLE_CREATED               0x20
#define FO_RANDOM_ACCESS                0x40
#define FO_DISMOUNTED                   0x80

#define FO_SHARED_DELETE                0x02
#define FO_SHARED_WRITE                 0x04
#define FO_SHARED_READ                  0x08
#define FO_DELETE_ACCESS                0x10
#define FO_WRITE_ACCESS                 0x20
#define FO_READ_ACCESS                  0x40

// file object flags - windows flags just in case
//#define FO_FILE_OPEN						0x00000001
//#define FO_SYNCHRONOUS_IO					0x00000002
//#define FO_ALERTABLE_IO						0x00000004
//#define FO_NO_INTERMEDIATE_BUFFERING		0x00000008
//#define FO_WRITE_THROUGH					0x00000010
//#define FO_SEQUENTIAL_ONLY					0x00000020
//#define FO_CACHE_SUPPORTED					0x00000040
//#define FO_NAMED_PIPE						0x00000080
//#define FO_STREAM_FILE						0x00000100
//#define FO_MAILSLOT							0x00000200
//#define FO_GENERATE_AUDIT_ON_CLOSE			0x00000400
//#define FO_QUEUE_IRP_TO_THREAD				FO_GENERATE_AUDIT_ON_CLOSE
//#define FO_DIRECT_DEVICE_OPEN				0x00000800
//#define FO_FILE_MODIFIED					0x00001000
//#define FO_FILE_SIZE_CHANGED				0x00002000
//#define FO_CLEANUP_COMPLETE					0x00004000
//#define FO_TEMPORARY_FILE					0x00008000
//#define FO_DELETE_ON_CLOSE					0x00010000
//#define FO_OPENED_CASE_SENSITIVE			0x00020000
//#define FO_HANDLE_CREATED					0x00040000
//#define FO_FILE_FAST_IO_READ				0x00080000
//#define FO_RANDOM_ACCESS					0x00100000
//#define FO_FILE_OPEN_CANCELLED				0x00200000
//#define FO_VOLUME_OPEN						0x00400000
//#define FO_REMOTE_ORIGIN					0x01000000
//#define FO_DISALLOW_EXCLUSIVE				0x02000000
//#define FO_SKIP_COMPLETION_PORT				FO_DISALLOW_EXCLUSIVE
//#define FO_SKIP_SET_EVENT					0x04000000
//#define FO_SKIP_SET_FAST_IO					0x08000000
//#define FO_INDIRECT_WAIT_OBJECT				0x10000000
//#define FO_SECTION_MINSTORE_TREATMENT		0x20000000


// flags for characteristics of IoCreateDevice, most likely not valid for x360
#define FILE_REMOVABLE_MEDIA                        0x00000001
#define FILE_READ_ONLY_DEVICE                       0x00000002
#define FILE_FLOPPY_DISKETTE                        0x00000004
#define FILE_WRITE_ONCE_MEDIA                       0x00000008
#define FILE_REMOTE_DEVICE                          0x00000010
#define FILE_DEVICE_IS_MOUNTED                      0x00000020
#define FILE_VIRTUAL_VOLUME                         0x00000040
#define FILE_AUTOGENERATED_DEVICE_NAME              0x00000080
#define FILE_DEVICE_SECURE_OPEN                     0x00000100
#define FILE_CHARACTERISTIC_PNP_DEVICE              0x00000800
#define FILE_CHARACTERISTIC_TS_DEVICE               0x00001000
#define FILE_CHARACTERISTIC_WEBDAV_DEVICE           0x00002000
#define FILE_CHARACTERISTIC_CSV                     0x00010000
#define FILE_DEVICE_ALLOW_APPCONTAINER_TRAVERSAL    0x00020000
#define FILE_PORTABLE_DEVICE                        0x00040000

// Define the create disposition values (pIrp->Tail.Overlay.CurrentStackLocation.Parameters.Create.Options >> 24)
#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005

// create/open option flags
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
#define FILE_OPEN_REMOTE_INSTANCE               0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

#define FILE_OPEN_REQUIRING_OPLOCK              0x00010000
#define FILE_DISALLOW_EXCLUSIVE                 0x00020000
#define FILE_SESSION_AWARE                      0x00040000

#define FILE_RESERVE_OPFILTER                   0x00100000
#define FILE_OPEN_REPARSE_POINT                 0x00200000
#define FILE_OPEN_NO_RECALL                     0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000

//NTSTATUS
//XxxDispatchRead(
//				IN PDEVICE_OBJECT  DeviceObject,
//				IN PIRP  Irp
//				);

// INCOMPLETE!! DEVICE_TYPE
#define FILE_DEVICE_CD_ROM              0x00000002 // SataCdRomDriverObject
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003 // OdfxDriverObject
#define FILE_DEVICE_CONTROLLER          0x00000004 // SataCdRomDispatchIo
#define FILE_DEVICE_HDD	                0x00000007 // SataDiskDriverObject
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008 // nomnil FatwDriverObject FatxDriverObject RawxDriverObject HfspDriverObject
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014 // connectx 'smb' device
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_MASS_STORAGE        0x0000002d // MassIoDriverObject
#define FILE_DEVICE_MASS1				0x0000003a // MassIoDriverObject
#define FILE_DEVICE_MASS2				0x0000003e // MassIoDriverObject
#define FILE_DEVICE_SFCX				0x0000003c // SfcxDriverObject
#define FILE_DEVICE_STFS_FILE_SYSTEM	0x0000003d // StfsCreateDevice
#define FILE_DEVICE_SVOD_FILE_SYSTEM	0x00000040 // SvodCreateDevice
#define FILE_DEVICE_SFCX_MU				0x00000041 // SfcxMuDriverObject
#define FILE_DEVICE_PIAF_DEVICE			0x00000042 // PiafCreateDevice
#define FILE_DEVICE_OMNI_DEIVCE			0x00000043 // NomnilDriverEntry - wireless n
#define FILE_DEVICE_MASS3				0x00000044 // MassIoDriverObject
#define FILE_DEVICE_MASS4				0x00000045 // MassIoDriverObject
#define FILE_DEVICE_PIAF_FILE_SYSTEM	0x00000046 // PiafCreatePartition
#define FILE_DEVICE_DEV_AUTH			0x00000047 // DevAuthIoDriverObject
#define FILE_DEVICE_MMC_SYS				0x00000048 // MmcxInitializeDeviceExtension
#define FILE_DEVICE_MMC_MU				0x00000049 // MmcxMuMountStorage

#define CTL_CODE( DeviceType, Function, Method, Access ) (((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
#define CTL_CODE_DEVTYPE(Code)	((Code>>16)&0xFFFF)		// 0xFFFF0000
#define CTL_CODE_FUNCTION(Code)	((Code>>2)&0xFFF)		// 0x00003FFC
#define CTL_CODE_ACCESS(Code)	((Code>>14)&0x3)		// 0x0000C000 - buffered = 0, in direct = 1, out direct = 2, neither = 3
#define CTL_CODE_METHOD(Code)	(Code&0x3)				// 0x00000003 - any = 0, read = 1, write = 2

#define SCSI_CMD_TEST_UNIT_READY				0x00
#define SCSI_CMD_REQUEST_SENSE					0x03
#define SCSI_CMD_FORMAT_UNIT					0x04
#define SCSI_CMD_FORMAT_INQUIRY					0x12
#define SCSI_CMD_START_STOP_UNIT				0x1B
#define SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL	0x1E
#define SCSI_CMD_READ_FORMAT_CAPACITIES			0x23
#define SCSI_CMD_READ_CAPACITY					0x25
#define SCSI_CMD_READ_10						0x28
#define SCSI_CMD_WRITE_10						0x2A
#define SCSI_CMD_SEEK_10						0x2B
#define SCSI_CMD_WRITE_AND_VERIFY_10			0x2E
#define SCSI_CMD_VERIFY_10						0x2F
#define SCSI_CMD_SYNCHRONIZE_CACHE				0x35
#define SCSI_CMD_WRITE_BUFFER					0x3B
#define SCSI_CMD_READ_BUFFER					0x3C
#define SCSI_CMD_READ_TOC_PMA_ATIP				0x43
#define SCSI_CMD_GET_CONFIGURATION				0x46
#define SCSI_CMD_GET_EVENT_STATUS_NOTIFICATION	0x4A
#define SCSI_CMD_READ_DISC_INFORMATION			0x51
#define SCSI_CMD_READ_TRACK_INFORMATION			0x52
#define SCSI_CMD_RESERVE_TRACK					0x53
#define SCSI_CMD_SEND_OPC_INFORMATION			0x54
#define SCSI_CMD_MODE_SELECT_10					0x55
#define SCSI_CMD_REPAIR_TRACK					0x58
#define SCSI_CMD_MODE_SENSE_10					0x5A
#define SCSI_CMD_CLOSE_TRACK_SESSION			0x5B
#define SCSI_CMD_READ_BUFFER_CAPACITY			0x5C
#define SCSI_CMD_SEND_CUE_SHEET					0x5D
#define SCSI_CMD_REPORT_LUNS					0xA0
#define SCSI_CMD_BLANK							0xA1
#define SCSI_CMD_SECURITY_PROTOCOL_IN			0xA2
#define SCSI_CMD_SEND_KEY						0xA3
#define SCSI_CMD_REPORT_KEY						0xA4
#define SCSI_CMD_LOAD_UNLOAD_MEDIUM				0xA6
#define SCSI_CMD_SET_READ_AHEAD					0xA7
#define SCSI_CMD_READ_12						0xA8
#define SCSI_CMD_WRITE_12						0xAA
#define SCSI_CMD_READ_MEDIA_SERIAL_NUMBER		0xAB
#define SCSI_CMD_GET_PERFORMANCE				0xAC
#define SCSI_CMD_READ_DISC_STRUCTURE			0xAD
#define SCSI_CMD_SECURITY_PROTOCOL_OUT			0xB5
#define SCSI_CMD_SET_STREAMING					0xB6
#define SCSI_CMD_READ_CD_MSF					0xB9
#define SCSI_CMD_SET_CD_SPEED					0xBB
#define SCSI_CMD_MECHANISM_STATUS				0xBD
#define SCSI_CMD_READ_CD 						0xBE
#define SCSI_CMD_SEND_DISC_STRUCTURE			0xBF

typedef VOID (NTAPI *PKNORMAL_ROUTINE)(
	IN		PVOID NormalContext OPTIONAL,
	IN		PVOID SystemArgument1 OPTIONAL,
	IN		PVOID SystemArgument2 OPTIONAL
	);

typedef VOID (NTAPI *PKRUNDOWN_ROUTINE)(
	IN		KAPC *Apc
	);

typedef VOID (NTAPI *PKKERNEL_ROUTINE)(
	IN		KAPC *Apc,
	IN OUT	PKNORMAL_ROUTINE *NormalRoutine OPTIONAL,
	IN OUT	PVOID *NormalContext OPTIONAL,
	IN OUT	PVOID *SystemArgument1 OPTIONAL,
	IN OUT	PVOID *SystemArgument2 OPTIONAL
	);

typedef struct _SCSI_PASS_THROUGH_DIRECT { 
	WORD Length; // 0x0 sz:0x2
	BYTE ScsiStatus; // 0x2 sz:0x1
	BYTE PathId; // 0x3 sz:0x1
	BYTE TargetId; // 0x4 sz:0x1
	BYTE Lun; // 0x5 sz:0x1
	BYTE CdbLength; // 0x6 sz:0x1
	BYTE DataIn; // 0x7 sz:0x1
	DWORD DataTransferLength; // 0x8 sz:0x4
	DWORD TimeOutValue; // 0xC sz:0x4
	void * DataBuffer; // 0x10 sz:0x4
	BYTE Cdb[0x10]; // 0x14 sz:0x10
} SCSI_PASS_THROUGH_DIRECT, *PSCSI_PASS_THROUGH_DIRECT; // size 36
C_ASSERT(sizeof(SCSI_PASS_THROUGH_DIRECT) == 0x24);

typedef enum {
	DriverQuiesceRundown = 0x0,
	DriverQuiesceStartup = 0x1,
	DriverShutdown = 0x2,
} KDRIVER_NOTIFICATION_TYPE;

// function location in array of u32's
typedef enum {
	DEVICEOB_Start = 0,
	DEVICEOB_Del,
	DEVICEOB_Dismount,
	DEVICEOB_FCreate,
	DEVICEOB_FClose,
	DEVICEOB_FRead,
	DEVICEOB_FWrite,
	DEVICEOB_FQuery,
	DEVICEOB_FSet,
	DEVICEOB_FFlush,
	DEVICEOB_FQueryVol,
	DEVICEOB_FDirCntrl,
	DEVICEOB_FDevCntrl,
	DEVICEOB_FCleanup,
} DEVICEOB_FUNS;

typedef struct _DVD_SPINDLE_SPEED_INFO { 
	DWORD CurrentSpeed; // 0x0 sz:0x4
	DWORD MaximumSpeed; // 0x4 sz:0x4
	DWORD FastestSpeed; // 0x8 sz:0x4
	DWORD DesiredSpeed; // 0xC sz:0x4
} DVD_SPINDLE_SPEED_INFO, *PDVD_SPINDLE_SPEED_INFO; // size 16
C_ASSERT(sizeof(DVD_SPINDLE_SPEED_INFO) == 0x10);

typedef struct _XGD2_GET_DRIVE_INFO { 
	DWORD HashTableIndexLBA; // 0x0 sz:0x4 from security sector
	BYTE BCADescriptor; // 0x4 sz:0x1
	BYTE CacheFlags; // 0x5 sz:0x1 based on disk type 0,1,2,3,4 - I've only seen 3 on game disks
	BYTE Reserved[0x2]; // 0x6 sz:0x2
	DWORD LastDiscAuthTime; // 0x8 sz:0x4 time in ticks it took to auth the disk
	DWORD Layer0Length; // 0xC sz:0x4 calculated from security sector, 0x1000 byte sector size
	DWORD Layer1Length; // 0x10 sz:0x4 calculated from security sector, 0x1000 byte sector size
	BYTE HashValueOfTable[0x14]; // 0x14 sz:0x14 from security sector
} XGD2_GET_DRIVE_INFO, *PXGD2_GET_DRIVE_INFO; // size 40
C_ASSERT(sizeof(XGD2_GET_DRIVE_INFO) == 0x28);

typedef struct _XGD2_GET_TEST_INFO { 
	DWORD HashTableIndexLBA; // 0x0 sz:0x4
	BYTE BCADescriptor; // 0x4 sz:0x1
	BYTE Reserved[0x3]; // 0x5 sz:0x3
	DWORD LastDiscAuthTime; // 0x8 sz:0x4
} XGD2_GET_TEST_INFO, *PXGD2_GET_TEST_INFO; // size 12
C_ASSERT(sizeof(XGD2_GET_TEST_INFO) == 0xC);

// this probably isn't right/complete... but it works when dealing with drivers
typedef struct _DISK_GEOMETRY {
	DWORD Sectors; // 0x0 sz:0x4
	DWORD BytesPerSector; // 0x4 sz:0x4
} DISK_GEOMETRY, *PDISK_GEOMETRY; // size 8
C_ASSERT(sizeof(DISK_GEOMETRY) == 0x8);
/* // from MSDN
typedef struct _DISK_GEOMETRY {
LARGE_INTEGER Cylinders;
MEDIA_TYPE    MediaType;
DWORD         TracksPerCylinder;
DWORD         SectorsPerTrack;
DWORD         BytesPerSector;
} DISK_GEOMETRY;
*/

typedef struct _DUMMY_MUTEX { // example default values given
	BYTE Type; // 1 EventSynchronizationObject
	BYTE SpinCount; // 0
	BYTE Size; // 4
	BYTE Inserted; // 0
	DWORD SignalState; // 0
	LIST_ENTRY WaitListHead;
	LONG LockCount; // 0xFFFFFFFF or -1
	LONG RecursionCount; // 0
	HANDLE OwningThread; // 0
} DUMMY_MUTEX, *PDUMMY_MUTEX;
C_ASSERT(sizeof(DUMMY_MUTEX) == 0x1C);

#pragma warning(disable: 4115)
typedef VOID (KDRIVER_NOTIFICATION_ROUTINE)(
	IN		struct _KDRIVER_NOTIFICATION_REGISTRATION* Dpc
	);
typedef KDRIVER_NOTIFICATION_ROUTINE *PKDRIVER_NOTIFICATION_ROUTINE;
#pragma warning(default: 4115)

typedef struct _KDRIVER_NOTIFICATION_REGISTRATION { 
	PKDRIVER_NOTIFICATION_ROUTINE NotificationRoutine; // 0x0 sz:0x4
	long Priority; // 0x4 sz:0x4
	LIST_ENTRY ListEntry; // 0x8 sz:0x8
} KDRIVER_NOTIFICATION_REGISTRATION, *PKDRIVER_NOTIFICATION_REGISTRATION; // size 16
C_ASSERT(sizeof(KDRIVER_NOTIFICATION_REGISTRATION) == 0x10);

typedef struct _KDEVICE_QUEUE_ENTRY { 
	LIST_ENTRY DeviceListEntry; // 0x0 sz:0x8
	DWORD SortKey; // 0x8 sz:0x4
	BYTE Inserted; // 0xC sz:0x1
} KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY; // size 16
C_ASSERT(sizeof(KDEVICE_QUEUE_ENTRY) == 0x10);

typedef struct _KDEVICE_QUEUE{
	short Type; // 0x0 sz:0x2
	BYTE Padding; // 0x2 sz:0x1
	BYTE Busy; // 0x3 sz:0x1
	DWORD Lock; // 0x4 sz:0x4
	LIST_ENTRY DeviceListHead; // 0x8 sz:0x8
} KDEVICE_QUEUE, *PKDEVICE_QUEUE; // 16
C_ASSERT(sizeof(KDEVICE_QUEUE) == 16);

typedef struct _OBJECT_SYMBOLIC_LINK { 
	void * LinkTargetObject; // 0x0 sz:0x4
	STRING LinkTarget; // 0x4 sz:0x8
} OBJECT_SYMBOLIC_LINK, *POBJECT_SYMBOLIC_LINK; // size 12
C_ASSERT(sizeof(OBJECT_SYMBOLIC_LINK) == 0xC);

// the major functions
typedef enum IO_STACK_LOCATION_MJ_FUNCTIONS { // just a quick way to enum CurrentStackLocation.MajorFunction
	IOS_MJ_CREATE = 0,
	IOS_MJ_CLOSE = 1,
	IOS_MJ_READ = 2,
	IOS_MJ_WRITE = 3,
	IOS_MJ_QUERYINFO = 4,
	IOS_MJ_SETINFO = 5,
	IOS_MJ_FLUSHBUF = 6,
	IOS_MJ_QUERYVOLINFO = 7,
	IOS_MJ_DIRECTORYCTRL = 8,
	IOS_MJ_DEVICECTRL = 9,
	IOS_MJ_CLEANUP = 10,
};

typedef void (*DRIVERVOID)(void* pDeviceObject, void* pIrp);
typedef NTSTATUS (*DRIVERLONG)(void* pDeviceObject, void* pIrp);

typedef struct _DRIVER_OBJECT_FUNCTIONS{
	DRIVERLONG DObCreate;
	DRIVERLONG DObClose;
	DRIVERLONG DObRead;
	DRIVERLONG DObWrite;
	DRIVERLONG DObQueryInfo;
	DRIVERLONG DObSetInfo;
	DRIVERLONG DObFlushBuffers;
	DRIVERLONG DObQueryVolumeInfo;
	DRIVERLONG DObDirectoryControl;
	DRIVERLONG DObDeviceControl;
	DRIVERLONG DObCleanup;
} DRIVER_OBJECT_FUNCTIONS, *PDRIVER_OBJECT_FUNCTIONS;

typedef struct _DRIVER_OBJECT{
	DRIVERVOID DriverStartIo; // function pointers
	DRIVERVOID DriverDeleteDevice;
	DRIVERLONG DriverDismountVolume;
	union{
		DRIVERLONG MajorFunction[11];
		DRIVER_OBJECT_FUNCTIONS dObFuns;
	};
} DRIVER_OBJECT, *PDRIVER_OBJECT; //56
C_ASSERT(sizeof(DRIVER_OBJECT) == 56);

typedef void* (*OBJALLOCATE)(DWORD, DWORD, DWORD);
typedef void (*OBJFREE)(PVOID arg1);
typedef void (*OBJCLOSE)(PVOID arg1);
typedef void (*OBJDELETE)(PVOID arg1);
typedef NTSTATUS (*OBJPARSE)(PVOID cObj, PVOID argR4, PVOID argR5, PVOID argR6, LARGE_INTEGER* argR7, PVOID argR8, PVOID argR9); // incomplete!!!

typedef struct _OBJECT_TYPE { 
	OBJALLOCATE AllocateProcedure; // 0x0 sz:0x4		PVOID __stdcall ExAllocatePoolTypeWithTag(DWORD NumberOfBytes, DWORD Tag, POOL_TYPE PoolType)
	OBJFREE FreeProcedure; // 0x4 sz:0x4				VOID __stdcall ExFreePool(PVOID arg1)
	OBJCLOSE CloseProcedure; // 0x8 sz:0x4				VOID __stdcall ExFreePool(VOID arg1)
	OBJDELETE DeleteProcedure; // 0xC sz:0x4			VOID __stdcall ExFreePool(VOID arg1)
	OBJPARSE ParseProcedure; // 0x10 sz:0x4
	void * DefaultObject; // 0x14 sz:0x4
	DWORD PoolTag; // 0x18 sz:0x4
} OBJECT_TYPE, *POBJECT_TYPE; // size 28
C_ASSERT(sizeof(OBJECT_TYPE) == 0x1C);

typedef struct _IO_COMPLETION_CONTEXT{
	void * Port;
	void * Key;
} IO_COMPLETION_CONTEXT, *PIO_COMPLETION_CONTEXT;
C_ASSERT(sizeof(IO_COMPLETION_CONTEXT) == 8);

typedef struct _DEVICE_OBJECT { 
	SHORT Type; // 0x0 sz:0x2
	WORD Size; // 0x2 sz:0x2
	long ReferenceCount; // 0x4 sz:0x4
	PDRIVER_OBJECT DriverObject; // 0x8 sz:0x4
	struct _DEVICE_OBJECT * MountedOrSelfDevice; // 0xC sz:0x4
	void * CurrentIrp; // PIRP * 0x10 sz:0x4
	DWORD Flags; // 0x14 sz:0x4
	void * DeviceExtension; // 0x18 sz:0x4
	BYTE DeviceType; // 0x1C sz:0x1
	BYTE StartIoFlags; // 0x1D sz:0x1
	char StackSize; // 0x1E sz:0x1
	BYTE DeletePending; // 0x1F sz:0x1
	DWORD SectorSize; // 0x20 sz:0x4
	DWORD AlignmentRequirement; // 0x24 sz:0x4
	KDEVICE_QUEUE DeviceQueue; // 0x28 sz:0x10
	KEVENT DeviceLock; // 0x38 sz:0x10
	DWORD StartIoCount; // 0x48 sz:0x4
	DWORD StartIoKey; // 0x4C sz:0x4
} DEVICE_OBJECT, *PDEVICE_OBJECT; // size 80
C_ASSERT(sizeof(DEVICE_OBJECT) == 0x50);

typedef enum DVD_STRUCTURE_FORMAT {
	DvdPhysicalDescriptor,
	DvdCopyrightDescriptor,
	DvdDiskKeyDescriptor,
	DvdBCADescriptor,
	DvdManufacturerDescriptor,
	DvdMaxDescriptor
} DVD_STRUCTURE_FORMAT, *PDVD_STRUCTURE_FORMAT;

typedef struct _DVD_DESCRIPTOR_HEADER {
	WORD Length;
	BYTE Reserved[2];
	BYTE Data[0];
} DVD_DESCRIPTOR_HEADER, *PDVD_DESCRIPTOR_HEADER;

// *********** PACKING STARTS HERE **************//
#pragma pack(push, 1)
// *********** PACKING STARTS HERE **************//

typedef struct _DVD_LAYER_DESCRIPTOR {
	BYTE  BookVersion : 4;
	BYTE  BookType : 4;
	BYTE  MinimumRate : 4;
	BYTE  DiskSize : 4;
	BYTE  LayerType : 4;
	BYTE  TrackPath : 1;
	BYTE  NumberOfLayers : 2;
	BYTE  Reserved1 : 1;
	BYTE  TrackDensity : 4;
	BYTE  LinearDensity : 4;
	DWORD  StartingDataSector;
	DWORD  EndDataSector;
	DWORD  EndLayerZeroSector;
	BYTE  Reserved5 : 7;
	BYTE  BCAFlag : 1;
	BYTE  Reserved6;
} DVD_LAYER_DESCRIPTOR, *PDVD_LAYER_DESCRIPTOR;

typedef struct DVD_READ_STRUCTURE {
	LARGE_INTEGER  BlockByteOffset;
	DVD_STRUCTURE_FORMAT  Format;
	DWORD  SessionId;
	BYTE  LayerNumber;
} DVD_READ_STRUCTURE, *PDVD_READ_STRUCTURE;

typedef struct _SHARE_ACCESS { 
	BYTE OpenCount; // 0x0 sz:0x1
	BYTE Readers; // 0x1 sz:0x1
	BYTE Writers; // 0x2 sz:0x1
	BYTE Deleters; // 0x3 sz:0x1
	BYTE SharedRead; // 0x4 sz:0x1
	BYTE SharedWrite; // 0x5 sz:0x1
	BYTE SharedDelete; // 0x6 sz:0x1
} SHARE_ACCESS, *PSHARE_ACCESS; // size 7
C_ASSERT(sizeof(SHARE_ACCESS) == 0x7);

typedef struct _ERWLOCK { // for ExAcquireReadWriteLockExclusive
	int LockCount; // 0x0 sz:0x4
	DWORD WritersWaitingCount; // 0x4 sz:0x4
	DWORD ReadersWaitingCount; // 0x8 sz:0x4
	DWORD ReadersEntryCount; // 0xC sz:0x4
	KEVENT WriterEvent; // 0x10 sz:0x10
	KSEMAPHORE ReaderSemaphore; // 0x20 sz:0x14
	DWORD SpinLock; // 0x34 sz:0x4
} ERWLOCK, *PERWLOCK; // size 56
C_ASSERT(sizeof(ERWLOCK) == 0x38);

typedef struct _FILE_OBJECT { 
	SHORT Type; // 0x0 sz:0x2
	BYTE Flags; // 0x2 sz:0x1
	BYTE Flags2; // 0x3 sz:0x1
	PDEVICE_OBJECT DeviceObject; // 0x4 sz:0x4
	void * FsContext; // 0x8 sz:0x4
	void * FsContext2; // 0xC sz:0x4
	long FinalStatus; // 0x10 sz:0x4
	LARGE_INTEGER CurrentByteOffset; // 0x14 sz:0x8
	struct _FILE_OBJECT * RelatedFileObject; // 0x1C sz:0x4
	PIO_COMPLETION_CONTEXT CompletionContext; // 0x20 sz:0x4
	long LockCount; // 0x24 sz:0x4
	KEVENT Lock; // 0x28 sz:0x10
	KEVENT Event; // 0x38 sz:0x10
	LIST_ENTRY ProcessListEntry; // 0x48 sz:0x8
	LIST_ENTRY FileSystemListEntry; // 0x50 sz:0x8
	BYTE IoPriority; // 0x58 sz:0x1
	BYTE PoolPadding[0xF]; // 0x59 sz:0xF
} FILE_OBJECT, *PFILE_OBJECT; // size 104
C_ASSERT(sizeof(FILE_OBJECT) == 0x68);

typedef struct _IO_STACK_LOCATION_CREATE { 
	DWORD DesiredAccess; // 0x0 sz:0x4
	DWORD Options; // 0x4 sz:0x4
	WORD FileAttributes; // 0x8 sz:0x2
	WORD ShareAccess; // 0xA sz:0x2
	STRING * RemainingName; // 0xC sz:0x4
} IO_STACK_LOCATION_CREATE, *PIO_STACK_LOCATION_CREATE; // size 16
C_ASSERT(sizeof(IO_STACK_LOCATION_CREATE) == 0x10);

typedef struct _IO_STACK_LOCATION_READ { 
	DWORD Length; // 0x0 sz:0x4
	union {
		DWORD BufferOffset; // 0x4 sz:0x4
		void * CacheBuffer; // 0x4 sz:0x4
	};
	LARGE_INTEGER ByteOffset; // 0x8 sz:0x8
} IO_STACK_LOCATION_READ, *PIO_STACK_LOCATION_READ; // size 16
C_ASSERT(sizeof(IO_STACK_LOCATION_READ) == 0x10);

typedef struct _IO_STACK_LOCATION_WRITE { 
	DWORD Length; // 0x0 sz:0x4
	union {
		DWORD BufferOffset; // 0x4 sz:0x4
		void * CacheBuffer; // 0x4 sz:0x4
	};
	LARGE_INTEGER ByteOffset; // 0x8 sz:0x8
} IO_STACK_LOCATION_WRITE, *PIO_STACK_LOCATION_WRITE; // size 16
C_ASSERT(sizeof(IO_STACK_LOCATION_WRITE) == 0x10);

typedef struct _IO_STACK_LOCATION_QUERYDIRECTORY { 
	DWORD Length; // 0x0 sz:0x4
	STRING * FileName; // 0x4 sz:0x4
} IO_STACK_LOCATION_QUERYDIRECTORY, *PIO_STACK_LOCATION_QUERYDIRECTORY; // size 8
C_ASSERT(sizeof(IO_STACK_LOCATION_QUERYDIRECTORY) == 0x8);

typedef struct _IO_STACK_LOCATION_QUERYFILE { 
	DWORD Length; // 0x0 sz:0x4
	FILE_INFORMATION_CLASS FileInformationClass; // 0x4 sz:0x4
} IO_STACK_LOCATION_QUERYFILE, *PIO_STACK_LOCATION_QUERYFILE; // size 8
C_ASSERT(sizeof(IO_STACK_LOCATION_QUERYFILE) == 0x8);

typedef struct _IO_STACK_LOCATION_SETFILE { 
	DWORD Length; // 0x0 sz:0x4
	FILE_INFORMATION_CLASS FileInformationClass; // 0x4 sz:0x4
	PFILE_OBJECT FileObject; // 0x8 sz:0x4
} IO_STACK_LOCATION_SETFILE, *PIO_STACK_LOCATION_SETFILE; // size 12
C_ASSERT(sizeof(IO_STACK_LOCATION_SETFILE) == 0xC);

typedef struct _IO_STACK_LOCATION_QUERYVOLUME { 
	DWORD Length; // 0x0 sz:0x4
	FSINFOCLASS FsInformationClass; // 0x4 sz:0x4
} IO_STACK_LOCATION_QUERYVOLUME, *PIO_STACK_LOCATION_QUERYVOLUME; // size 8
C_ASSERT(sizeof(IO_STACK_LOCATION_QUERYVOLUME) == 0x8);

typedef struct _IO_STACK_LOCATION_SETVOLUME { 
	DWORD Length; // 0x0 sz:0x4
	FSINFOCLASS FsInformationClass; // 0x4 sz:0x4
} IO_STACK_LOCATION_SETVOLUME, *PIO_STACK_LOCATION_SETVOLUME; // size 8
C_ASSERT(sizeof(IO_STACK_LOCATION_QUERYVOLUME) == 0x8);

typedef struct _IO_STACK_LOCATION_DEVICEIOCONTROL { 
	DWORD OutputBufferLength; // 0x0 sz:0x4
	void * InputBuffer; // 0x4 sz:0x4
	DWORD InputBufferLength; // 0x8 sz:0x4
	DWORD IoControlCode; // 0xC sz:0x4
} IO_STACK_LOCATION_DEVICEIOCONTROL, *PIO_STACK_LOCATION_DEVICEIOCONTROL; // size 16
C_ASSERT(sizeof(IO_STACK_LOCATION_DEVICEIOCONTROL) == 0x10);

typedef struct _IO_STACK_LOCATION_SECTORIO { 
	DWORD Length; // 0x0 sz:0x4
	BYTE * Buffer; // 0x4 sz:0x4
	DWORD SectorNumber; // 0x8 sz:0x4
	DWORD BufferOffset; // 0xC sz:0x4
} IO_STACK_LOCATION_SECTORIO, *PIO_STACK_LOCATION_SECTORIO; // size 16
C_ASSERT(sizeof(IO_STACK_LOCATION_SECTORIO) == 0x10);

typedef struct _IO_STACK_LOCATION_OTHERS { 
	void * Argument1; // 0x0 sz:0x4
	void * Argument2; // 0x4 sz:0x4
	void * Argument3; // 0x8 sz:0x4
	void * Argument4; // 0xC sz:0x4
} IO_STACK_LOCATION_OTHERS, *PIO_STACK_LOCATION_OTHERS; // size 16
C_ASSERT(sizeof(IO_STACK_LOCATION_OTHERS) == 0x10);

typedef union _UIO_STACK_LOCATION_PARMS { 
	IO_STACK_LOCATION_CREATE Create; // 0x0 sz:0x10
	IO_STACK_LOCATION_READ Read; // 0x0 sz:0x10
	IO_STACK_LOCATION_WRITE Write; // 0x0 sz:0x10
	IO_STACK_LOCATION_QUERYDIRECTORY QueryDirectory; // 0x0 sz:0x8
	IO_STACK_LOCATION_QUERYFILE QueryFile; // 0x0 sz:0x8
	IO_STACK_LOCATION_SETFILE SetFile; // 0x0 sz:0xC
	IO_STACK_LOCATION_QUERYVOLUME QueryVolume; // 0x0 sz:0x8
	IO_STACK_LOCATION_SETVOLUME SetVolume; // 0x0 sz:0x8
	IO_STACK_LOCATION_DEVICEIOCONTROL DeviceIoControl; // 0x0 sz:0x10
	IO_STACK_LOCATION_SECTORIO SectorIo; // 0x0 sz:0x10
	IO_STACK_LOCATION_OTHERS Others; // 0x0 sz:0x10
} UIO_STACK_LOCATION_PARMS, *PUIO_STACK_LOCATION_PARMS; // size 16
C_ASSERT(sizeof(UIO_STACK_LOCATION_PARMS) == 0x10);

typedef struct _IO_STACK_LOCATION { 
	BYTE MajorFunction; // 0x0 sz:0x1
	BYTE MinorFunction; // 0x1 sz:0x1
	BYTE Flags; // 0x2 sz:0x1
	BYTE Control; // 0x3 sz:0x1
	UIO_STACK_LOCATION_PARMS Parameters; // 0x4 sz:0x10
	PDEVICE_OBJECT DeviceObject; // 0x14 sz:0x4
	PFILE_OBJECT FileObject; // 0x18 sz:0x4
	void * CompletionRoutine; // 0x1C sz:0x4	function long(*)()
	void * Context; // 0x20 sz:0x4
} IO_STACK_LOCATION, *PIO_STACK_LOCATION; // size 36
C_ASSERT(sizeof(IO_STACK_LOCATION) == 0x24);

// *********** PACKING ENDS HERE **************//
#pragma pack(pop)
// *********** PACKING ENDS HERE **************//

typedef struct _IRP_ASYNC_PARAM { 
	void * UserApcRoutine; // 0x0 sz:0x4 function void(*)()
	void * UserApcContext; // 0x4 sz:0x4
} IRP_ASYNC_PARAM, *PIRP_ASYNC_PARAM; // size 8
C_ASSERT(sizeof(IRP_ASYNC_PARAM) == 0x8);

typedef union _UIRP_OVERLAY { 
	IRP_ASYNC_PARAM AsynchronousParameters; // 0x0 sz:0x8
	LARGE_INTEGER AllocationSize; // 0x0 sz:0x8
} UIRP_OVERLAY, *PUIRP_OVERLAY; // size 8
C_ASSERT(sizeof(UIRP_OVERLAY) == 0x8);

typedef struct _IRP_OVERLAY {
	union{
		KDEVICE_QUEUE_ENTRY DeviceQueueEntry; // 0x0 sz:0x10
		LIST_ENTRY DeviceListEntry; // 0x0 sz:0x8
		void * DriverContext[4]; // 0x0 sz:0x10
	};
	DWORD LockedBufferLength; // 0x10 sz:0x4
	PKTHREAD Thread; // 0x14 sz:0x4
	LIST_ENTRY ListEntry; // 0x18 sz:0x8
	union{
		PIO_STACK_LOCATION CurrentStackLocation; // 0x20 sz:0x4
		DWORD PacketType; // 0x20 sz:0x4
	};
	PFILE_OBJECT OriginalFileObject; // 0x24 sz:0x4
} IRP_OVERLAY, *PIRP_OVERLAY; // size 40
C_ASSERT(sizeof(IRP_OVERLAY) == 0x28);

typedef union _UIRP_TAIL { 
	IRP_OVERLAY Overlay; // 0x0 sz:0x28
	KAPC Apc; // 0x0 sz:0x28
	void * CompletionKey; // 0x0 sz:0x4
} UIRP_TAIL, *PUIRP_TAIL; // size 40
C_ASSERT(sizeof(UIRP_TAIL) == 0x28);

typedef struct _IRP { 
	SHORT Type; // 0x0 sz:0x2
	USHORT Size; // 0x2 sz:0x2
	DWORD Flags; // 0x4 sz:0x4
	LIST_ENTRY ThreadListEntry; // 0x8 sz:0x8
	IO_STATUS_BLOCK IoStatus; // 0x10 sz:0x8
	char StackCount; // 0x18 sz:0x1
	char CurrentLocation; // 0x19 sz:0x1
	BYTE PendingReturned; // 0x1A sz:0x1
	BYTE Cancel; // 0x1B sz:0x1
	void * UserBuffer; // 0x1C sz:0x4
	PIO_STATUS_BLOCK UserIosb; // 0x20 sz:0x4
	PKEVENT UserEvent; // 0x24 sz:0x4
	UIRP_OVERLAY Overlay; // 0x28 sz:0x8
	UIRP_TAIL Tail; // 0x30 sz:0x28
	void * CancelRoutine; // 0x58 sz:0x4  function void(*)()
} IRP, *PIRP; // size 96
C_ASSERT(sizeof(IRP) == 0x60);


// some structs relevant to PCI
typedef struct _PCI_CONF_HDR {
	SHORT DeviceID; // 0
	SHORT VendorID; // 2
	SHORT Status; // 4
	SHORT Command; // 6
	BYTE ClassBase; // 7
	BYTE ClassSub; // 8
	BYTE ClassIf; // 9
	// BYTE Class[3]; // 8 sz 0x3
	BYTE RevisionID; // 0xB
	BYTE BIST; // 0xC
	BYTE HType; // 0xD
	BYTE LatencyTmr; // 0xE
	BYTE CachelineSz; // 0xF
} PCI_CONF_HDR, *PPCI_CONF_HDR;
C_ASSERT(sizeof(PCI_CONF_HDR) == 0x10);

typedef struct _PCI_TYPE_0 {
	PCI_CONF_HDR conf; // 0 sz 0x10
	DWORD BAR[6]; // 0x10 sz 0x18
	DWORD CarbusCIS; // 0x28
	SHORT SubsysID; // 0x2C
	SHORT SubsysVID; // 0x2E
	DWORD ExROMBase; // 0x30
	BYTE Reserved[3]; // 0x34, 0x35, 0x36 sz 3
	BYTE capPtr; // 0x37
	DWORD Reserved2; // 0x38
	BYTE max_lat; // 0x3C
	BYTE min_gnt; // 0x3D
	BYTE int_pin; // 0x3E
	BYTE int_line; // 0x3F
} PCI_TYPE_0, *PPCI_TYPE_0;
C_ASSERT(sizeof(PCI_TYPE_0) == 0x40);

typedef struct _PCI_TYPE_1 {
	PCI_CONF_HDR conf; // 0 sz 0x10
	DWORD BAR[2]; // 0x10 sz 0x8
	BYTE secLatencyTmr; // 0x18
	BYTE subBusNum; // 0x19
	BYTE secBusNum; // 0x1a
	BYTE primBusNum; // 0x1b
	SHORT secStatus; // 0x1c
	BYTE ioLimit; // 0x1e
	BYTE ioBase; // 0x1f
	SHORT memLim; // 0x20
	SHORT memBase; // 0x22
	SHORT prefMemLim; // 0x24
	SHORT prefMemBase; // 0x26
	DWORD prefBaseUpper; // 0x28
	DWORD prefLimUpper; // 0x2C
	SHORT ioLimitUpper; // 0x30
	SHORT ioBaseUpper; // 0x32
	BYTE reserved[3]; // 0x34, 0x35, 0x36 sz 3
	BYTE capPtr; // 0x37
	DWORD ExROMBase; // 0x38
	SHORT bridgeCntrl; // 0x3C
	BYTE int_pin; // 0x3E
	BYTE int_line; // 0x3F
} PCI_TYPE_1, *PPCI_TYPE_1;
C_ASSERT(sizeof(PCI_TYPE_1) == 0x40);




#endif // __KEDRIVER_H
