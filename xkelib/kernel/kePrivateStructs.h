#ifndef __KEPRIVATESTRUCTS_H
#define __KEPRIVATESTRUCTS_H

/* **** FIXME ****
_OBJECT_HANDLE_TABLE
_KTHREAD
*/

/* HalReadArgonEeprom read on a falcon jtag at 14719
ArgonEepromErrorBitfield: ret 0x0 read 0x7	: 00 00 00 00 04 00 00
ArgonEepromV12P0		: ret 0x0 read 0x8	: BB 1B B1 13 00 4A 5D 01
ArgonEepromAll			: ret 0x0 read 0x10	: 0F 00 00 00 00 04 00 00 BB 1B B1 13 00 4A 5D 01 */
typedef enum {
	ArgonEepromErrorBitfield = 0x0, // buf size 0xC
	ArgonEepromV12P0 = 0x1, // buf size 8
	ArgonEepromAll = 0x2,
} ARGON_EEPROM_FIELD;

// for KeGetCurrentProcessType()
typedef enum  {
	PROC_IDLE = 0,
	PROC_USER = 1,
	PROC_SYSTEM = 2,
	PROC_DEBUG = 3,
} _KPROC_TYPE;

typedef enum {
	EventNotificationObject = 0x0,
	EventSynchronizationObject = 0x1,
	MutantObject = 0x2,
	ProcessObject = 0x3,
	QueueObject = 0x4,
	SemaphoreObject = 0x5,
	ThreadObject = 0x6,
	Spare1Object = 0x7, // ExAcquireReadWriteLockExclusive
	TimerNotificationObject = 0x8,
	TimerSynchronizationObject = 0x9,
	Spare2Object = 0xA,
	Spare3Object = 0xB,
	Spare4Object = 0xC,
	Spare5Object = 0xD,
	Spare6Object = 0xE,
	Spare7Object = 0xF,
	Spare8Object = 0x10,
	Spare9Object = 0x11,
	ApcObject = 0x12,
	DpcObject = 0x13,
	DeviceQueueObject = 0x14,
	EventPairObject = 0x15,
	InterruptObject = 0x16,
	ProfileObject = 0x17,
} KOBJECTS;

typedef enum {
	NotificationTimer = 0x0,
	SynchronizationTimer = 0x1,
} TIMER_TYPE;

typedef enum {
	Executive = 0x0,
	DelayExecution = 0x1,
	Suspended = 0x2,
	UserRequest = 0x3,
	WrQueue = 0x4,
	WrFsCacheIn = 0x5,
	WrFsCacheOut = 0x6,
	WrReadWriteLock = 0x7,
	WrCriticalSection = 0x8,
	MaximumWaitReason = 0x9,
} KWAIT_REASON;

typedef enum {
	KernelMode = 0x0,
	UserMode = 0x1,
	MaximumMode = 0x2,
} WAIT_MODE;

typedef WAIT_MODE		KPROCESSOR_MODE;

// for 32 bit version splitting/creating
#pragma pack(push, 1)
typedef union _XBOX32VER {
	struct {
	unsigned char Major : 4;
	unsigned char Minor : 4;
	unsigned short Build;
	unsigned char Qfe;
	};
	DWORD asULong;
} XBOX32VER, *PXBOX32VER;
#pragma pack(pop)

typedef ULONG_PTR KIPI_BROADCAST_WORKER (
	__in ULONG_PTR Argument
	);
typedef KIPI_BROADCAST_WORKER *PKIPI_BROADCAST_WORKER;

#pragma warning(disable: 4115)
typedef VOID (KDEFERRED_ROUTINE)(
	IN		struct _KDPC* Dpc,
	IN		PVOID DeferredContext OPTIONAL,
	IN		PVOID SystemArgument1 OPTIONAL,
	IN		PVOID SystemArgument2 OPTIONAL
	);
typedef KDEFERRED_ROUTINE *PKDEFERRED_ROUTINE;

typedef BOOLEAN (NTAPI KSERVICE_ROUTINE)(
	IN		struct _KINTERRUPT *Interrupt,
	IN		PVOID ServiceContext
	);
typedef KSERVICE_ROUTINE *PKSERVICE_ROUTINE;
#pragma warning(default: 4115)

//typedef struct _DISPLAY_INFO{
//	WORD timing1; // 0x0
//	WORD timing2; // 0x2
//	BYTE colorspace; // 0x4
//	BYTE colorformat; // 0x5
//	BYTE padb_1[2]; // 0x6 pad
//	DWORD pitch; // 0x8
//	DWORD format; // 0xC
//	DWORD offsetx; // 0x10
//	DWORD offsety; // 0x14
//	DWORD sw; // 0x18
//	DWORD sh; // 0x1c
//	DWORD dwUnk1;
//	BYTE baUnk1[12];
//	DWORD dwUnk2;
//	BYTE baUnk2[12];
//	WORD waUnk1[6]; // last two may be important
//	DWORD dwAsFloat; // is a float?
//	DWORD dwUnk3;
//	BYTE padb_2[2]; //pad
//	WORD wUnk1;	
//} DISPLAY_INFO, *PDISPLAY_INFO; // total size 0x58 bytes
//C_ASSERT(sizeof(DISPLAY_INFO) == 88);
typedef struct _D3DPRIVATE_RECT {
	LONG x1, y1;
	LONG x2, y2;
} D3DPRIVATE_RECT, *PD3DPRIVATE_RECT;

typedef struct _D3DFILTER_PARAMETERS {
	FLOAT Nyquist;
	FLOAT FlickerFilter;
	FLOAT Beta;
} D3DFILTER_PARAMETERS, *PD3DFILTER_PARAMETERS;

typedef struct _D3DPRIVATE_SCALER_PARAMETERS {
	D3DPRIVATE_RECT		 ScalerSourceRect;
	LONG				 ScaledOutputWidth;
	LONG				 ScaledOutputHeight;
	DWORD				 VirticalFilterType;
	D3DFILTER_PARAMETERS VerticalFilterParameters;
	DWORD				 HorizontalFilterType;
	D3DFILTER_PARAMETERS HorizontalFilterParameters;
} D3DPRIVATE_SCALER_PARAMETERS, *PD3DPRIVATE_SCALER_PARAMETERS;

typedef struct _DISPLAY_INFORMATION {
	WORD						 FrontBufferWidth; // 0 sz 2
	WORD						 FrontBufferHeight; // 0x2 sz 2
	BYTE						 FrontBufferColorFormat; // 0x4 sz 1
	BYTE						 FrontBufferPixelFormat; // 0x5 sz 1
	D3DPRIVATE_SCALER_PARAMETERS ScalerParameters;  // 0x sz 2
	WORD						 DisplayWindowOverscanLeft; // 0x sz 2
	WORD						 DisplayWindowOverscanTop; // 0x sz 2
	WORD						 DisplayWindowOverscanRight; // 0x sz 2
	WORD						 DisplayWindowOverscanBottom; // 0x sz 2
	WORD						 DisplayWidth; // 0x sz 2
	WORD						 DisplayHeight; // 0x sz 2
	FLOAT						 DisplayRefreshRate; // 0x sz 8
	DWORD						 DisplayInterlaced; // 0x sz 4
	BYTE						 DisplayColorFormat; // 0x sz 1
	WORD						 ActualDisplayWidth; // 0x sz 2
} DISPLAY_INFO, *PDISPLAY_INFO;
C_ASSERT(sizeof(DISPLAY_INFO) == 0x58);

// *********** PACKING STARTS HERE **************//
#pragma pack(push, 1)
// *********** PACKING STARTS HERE **************//

typedef enum XboxMemoryRegionFlags{ // for MmQueryAddressProtect
	NoAccess = 0x1,
	ReadOnly = 0x2,
	ReadWrite = 0x4,
	WriteCopy = 0x8,
	Execute = 0x10,
	ExecuteRead = 0x20,
	ExecuteReadWrite = 0x40,
	ExecuteWriteCopy = 0x80,
	Guard = 0x100,
	NoCache = 0x200,
	WriteCombine = 0x400,
	UserReadOnly = 0x1000,
	UserReadWrite = 0x2000
};

typedef struct _MM_STATISTICS{
	DWORD Length;
	DWORD TotalPhysicalPages;
	DWORD KernelPages;
	DWORD TitleAvailablePages;
	DWORD TitleTotalVirtualMemoryBytes;
	DWORD TitleReservedVirtualMemoryBytes;
	DWORD TitlePhysicalPages;
	DWORD TitlePoolPages;
	DWORD TitleStackPages;
	DWORD TitleImagePages;
	DWORD TitleHeapPages;
	DWORD TitleVirtualPages;
	DWORD TitlePageTablePages;
	DWORD TitleCachePages;
	DWORD SystemAvailablePages;
	DWORD SystemTotalVirtualMemoryBytes;
	DWORD SystemReservedVirtualMemoryBytes;
	DWORD SystemPhysicalPages;
	DWORD SystemPoolPages;
	DWORD SystemStackPages;
	DWORD SystemImagePages;
	DWORD SystemHeapPages;
	DWORD SystemVirtualPages;
	DWORD SystemPageTablePages;
	DWORD SystemCachePages;
	DWORD HighestPhysicalPage;
} MM_STATISTICS, *PMMSTATISTICS; // 104
C_ASSERT(sizeof(MM_STATISTICS) == 104);

typedef struct _KINTERRUPT { 
	PKSERVICE_ROUTINE ServiceRoutine; // VOID(*)() 0x0 sz:0x4
	PVOID ServiceContext; // 0x4 sz:0x4
	DWORD SpinLock; // 0x8 sz:0x4
	DWORD ServiceCount; // 0xC sz:0x4
	BYTE BusIrql; // 0x10 sz:0x1
	BYTE Irql; // 0x11 sz:0x1
	BYTE Connected : 1; // 0x12 bfo:0x7
	BYTE Mode : 7; // 0x12 bfo:0x0
// 	BYTE ModeConnected;
	BYTE TargetNumber; // 0x13 sz:0x1
} KINTERRUPT, *PKINTERRUPT; // size 20
C_ASSERT(sizeof(KINTERRUPT) == 0x14);

typedef struct _KTRAP_FRAME { 
	STACK_FRAME_HEADER Header; // 0x0 sz:0x50
	QWORD Gpr0; // 0x50 sz:0x8
	QWORD Gpr1; // 0x58 sz:0x8
	QWORD Gpr2; // 0x60 sz:0x8
	QWORD Gpr3; // 0x68 sz:0x8
	QWORD Gpr4; // 0x70 sz:0x8
	QWORD Gpr5; // 0x78 sz:0x8
	QWORD Gpr6; // 0x80 sz:0x8
	QWORD Gpr7; // 0x88 sz:0x8
	QWORD Gpr8; // 0x90 sz:0x8
	QWORD Gpr9; // 0x98 sz:0x8
	QWORD Gpr10; // 0xA0 sz:0x8
	QWORD Gpr11; // 0xA8 sz:0x8
	QWORD Gpr12; // 0xB0 sz:0x8
	QWORD Gpr13; // 0xB8 sz:0x8
	QWORD Gpr14; // 0xC0 sz:0x8
	QWORD Gpr15; // 0xC8 sz:0x8
	QWORD Gpr16; // 0xD0 sz:0x8
	QWORD Gpr17; // 0xD8 sz:0x8
	QWORD Gpr18; // 0xE0 sz:0x8
	QWORD Gpr19; // 0xE8 sz:0x8
	QWORD Gpr20; // 0xF0 sz:0x8
	QWORD Gpr21; // 0xF8 sz:0x8
	QWORD Gpr22; // 0x100 sz:0x8
	QWORD Gpr23; // 0x108 sz:0x8
	QWORD Gpr24; // 0x110 sz:0x8
	QWORD Gpr25; // 0x118 sz:0x8
	QWORD Gpr26; // 0x120 sz:0x8
	QWORD Gpr27; // 0x128 sz:0x8
	QWORD Gpr28; // 0x130 sz:0x8
	QWORD Gpr29; // 0x138 sz:0x8
	QWORD Gpr30; // 0x140 sz:0x8
	QWORD Gpr31; // 0x148 sz:0x8
	union{
		struct{
			BYTE OldIrql;
			PKINTERRUPT InterruptObject;
			BYTE InterruptIrql;
		} asIrq;
		BYTE ExceptionRecord[0x50];
	} irqExc;
	QWORD Ctr; // 0x1A0 sz:0x8
	DWORD Lr; // 0x1A8 sz:0x4
	DWORD Iar; // 0x1AC sz:0x4
	DWORD Cr; // 0x1B0 sz:0x4
	DWORD Msr; // 0x1B4 sz:0x4
	DWORD Xer; // 0x1B8 sz:0x4
	DWORD UserModeControl; // 0x1BC sz:0x4
} KTRAP_FRAME, *PKTRAP_FRAME; // size 448
C_ASSERT(sizeof(KTRAP_FRAME) == 0x1C0);

typedef struct _KAPC { 
	SHORT Type; // 0x0 sz:0x2
	BYTE ApcMode; // 0x2 sz:0x1
	BYTE Inserted; // 0x3 sz:0x1
	struct _KTHREAD * Thread; // 0x4 sz:0x4
	LIST_ENTRY ApcListEntry; // 0x8 sz:0x8
	void * KernelRoutine; // 0x10 sz:0x4  function void(*)()
	void * RundownRoutine; // 0x14 sz:0x4  function void(*)()
	void * NormalRoutine; // 0x18 sz:0x4  function void(*)()
	void * NormalContext; // 0x1C sz:0x4
	void * SystemArgument1; // 0x20 sz:0x4
	void * SystemArgument2; // 0x24 sz:0x4
} KAPC, *PKAPC; // size 40
C_ASSERT(sizeof(KAPC) == 0x28);

typedef struct _DISPATCHER_HEADER { 
	BYTE Type; // 0x0 sz:0x1
	BYTE Absolute; // 0x1 sz:0x1
	BYTE ProcessType; // 0x2 sz:0x1
	BYTE Inserted; // 0x3 sz:0x1
	LONG SignalState; // 0x4 sz:0x4
	LIST_ENTRY WaitListHead; // 0x8 sz:0x8
} DISPATCHER_HEADER, *PDISPATCHER_HEADER; // size 16
C_ASSERT(sizeof(DISPATCHER_HEADER) == 0x10);

typedef struct _KEVENT { 
	DISPATCHER_HEADER Header; // 0x0 sz:0x10
} KEVENT, *PKEVENT; // size 16
C_ASSERT(sizeof(KEVENT) == 0x10);

typedef struct _KDPC { 
	SHORT Type; // 0x0 sz:0x2
	BYTE InsertedNumber; // 0x2 sz:0x1
	BYTE TargetNumber; // 0x3 sz:0x1
	LIST_ENTRY DpcListEntry; // 0x4 sz:0x8
	PKDEFERRED_ROUTINE DeferredRoutine; // 0xC sz:0x4
	void * DeferredContext; // 0x10 sz:0x4
	void * SystemArgument1; // 0x14 sz:0x4
	void * SystemArgument2; // 0x18 sz:0x4
} KDPC, *PKDPC; // size 28
C_ASSERT(sizeof(KDPC) == 0x1C);

typedef struct _KWAIT_BLOCK {
	LIST_ENTRY WaitListEntry; // 0x0 sz:0x8
	struct _KTHREAD* Thread; // 0x8 sz:0x4
	void * Object; // 0xC sz:0x4
	struct _KWAIT_BLOCK * NextWaitBlock; // 0x10 sz:0x4
	WORD WaitKey; // 0x14 sz:0x2
	WORD WaitType; // 0x16 sz:0x2
} KWAIT_BLOCK, *PKWAIT_BLOCK; // size 24
C_ASSERT(sizeof(KWAIT_BLOCK) == 0x18);

typedef struct _KTIMER { 
	DISPATCHER_HEADER Header; // 0x0 sz:0x10
	ULARGE_INTEGER DueTime; // 0x10 sz:0x8
	LIST_ENTRY TimerListEntry; // 0x18 sz:0x8
	PKDPC Dpc; // 0x20 sz:0x4
	long Period; // 0x24 sz:0x4
} KTIMER, *PKTIMER; // size 40
C_ASSERT(sizeof(KTIMER) == 0x28);

typedef struct _KPROCESS { 
	DWORD ThreadListLock; // 0x0 sz:0x4
	LIST_ENTRY ThreadListHead; // 0x4 sz:0x8
	LONG ThreadQuantum; // 0xC sz:0x4
	DWORD DirectoryTableBase; // 0x10 sz:0x4
	DWORD ThreadCount; // 0x14 sz:0x4
	BYTE IdlePriorityClass; // 0x18 sz:0x1
	BYTE NormalPriorityClass; // 0x19 sz:0x1
	BYTE TimeCriticalPriorityClass; // 0x1A sz:0x1
	BYTE DisableQuantum; // 0x1B sz:0x1
	DWORD DefaultKernelStackSize; // 0x1C sz:0x4
	void * TlsStaticDataImage; // 0x20 sz:0x4
	DWORD SizeOfTlsStaticData; // 0x24 sz:0x4
	DWORD SizeOfTlsStaticDataImage; // 0x28 sz:0x4
	WORD SizeOfTlsSlots; // 0x2C sz:0x2
	BYTE Terminating; // 0x2E sz:0x1
	BYTE ProcessType; // 0x2F sz:0x1
	DWORD TlsSlotBitmap[0x8]; // 0x30 sz:0x20
	DWORD FileObjectListLock; // 0x50 sz:0x4
	LIST_ENTRY FileObjectListHead; // 0x54 sz:0x8
	void * Win32DefaultHeapHandle; // 0x5C sz:0x4
} KPROCESS, *PKPROCESS; // size 96
C_ASSERT(sizeof(KPROCESS) == 0x60);

typedef struct _KSEMAPHORE { 
	DISPATCHER_HEADER Header; // 0x0 sz:0x10
	LONG Limit; // 0x10 sz:0x4
} KSEMAPHORE, *PKSEMAPHORE; // size 20
C_ASSERT(sizeof(KSEMAPHORE) == 0x14);

typedef struct _KQUEUE { 
	DISPATCHER_HEADER Header; // 0x0 sz:0x10
	LIST_ENTRY EntryListHead; // 0x10 sz:0x8
	DWORD CurrentCount; // 0x18 sz:0x4
	DWORD MaximumCount; // 0x1C sz:0x4
	LIST_ENTRY ThreadListHead; // 0x20 sz:0x8
} KQUEUE, *PKQUEUE; // size 40
C_ASSERT(sizeof(KQUEUE) == 0x28);

// *********** PACKING ENDS HERE **************//
#pragma pack(pop)
// *********** PACKING ENDS HERE **************//

typedef struct _KPRCB { 
	struct _KTHREAD* CurrentThread; // 0x0 sz:0x4
	struct _KTHREAD* NextThread; // 0x4 sz:0x4
	struct _KTHREAD* IdleThread; // 0x8 sz:0x4
	BYTE Number; // 0xC sz:0x1
	DWORD SetMember; // 0x10 sz:0x4
	DWORD DpcTime; // 0x14 sz:0x4
	DWORD InterruptTime; // 0x18 sz:0x4
	DWORD InterruptCount; // 0x1C sz:0x4
	volatile DWORD IpiFrozen; // 0x20 sz:0x4
	volatile DWORD CurrentPacket[3]; // 0x24 sz:0xC
	DWORD TargetSet; // 0x30 sz:0x4
	PVOID WorkerRoutine; // 0x34 sz:0x4 Function Pointer
	struct _KPRCB* SignalDone; // 0x38 sz:0x4
	DWORD RequestSummary; // 0x3C sz:0x4
	DWORD DpcInterruptRequested; // 0x40 sz:0x4
	DWORD DpcLock; // 0x44 sz:0x4
	LIST_ENTRY DpcListHead; // 0x48 sz:0x8
	DWORD DpcRoutineActive; // 0x50 sz:0x4
	DWORD ReadyListLock; // 0x54 sz:0x4
	DWORD IdleThreadActive; // 0x58 sz:0x4
	SINGLE_LIST_ENTRY DeferredReadyListHead; // 0x5C sz:0x4
	DWORD ReadySummary; // 0x60 sz:0x4
	DWORD ReadySummaryMask; // 0x64 sz:0x4
	LIST_ENTRY DispatcherReadyListHead[32]; // 0x68 sz:0x100
	KDPC ThreadReaperDpc; // 0x168 sz:0x1C
	LIST_ENTRY ThreadReaperListHead; // 0x184 sz:0x8
	KDPC SwitchProcessorThreadDpc; // 0x18C sz:0x1C
} KPRCB, *PKPRCB; // size 424
C_ASSERT(sizeof(KPRCB) == 0x1A8);

typedef struct _KTHREAD { 
	DISPATCHER_HEADER Header; // 0x0 sz:0x10
	LIST_ENTRY MutantListHead; // 0x10 sz:0x8
	KTIMER Timer; // 0x18 sz:0x28
	KWAIT_BLOCK TimerWaitBlock; // 0x40 sz:0x18
	DWORD KernelTime; // 0x58 sz:0x4
	PVOID StackBase; // 0x5C sz:0x4
	PVOID StackLimit; // 0x60 sz:0x4
	PVOID KernelStack; // 0x64 sz:0x4
	PVOID TlsData; // 0x68 sz:0x4
	BYTE State; // 0x6C sz:0x1
	BYTE Alerted[2]; // 0x6D sz:0x2
	BYTE Alertable; // 0x6F sz:0x1
	BYTE Priority; // 0x70 sz:0x1
	BYTE FpuExceptionEnable; // 0x71 sz:0x1
	BYTE CreateProcessType; // 0x72 sz:0x1
	BYTE CurrentProcessType; // 0x73 sz:0x1
	LIST_ENTRY ApcListHead[2]; // 0x74 sz:0x10
	PKPROCESS Process; // 0x84 sz:0x4
	BYTE KernelApcInProgress; // 0x88 sz:0x1
	BYTE KernelApcPending; // 0x89 sz:0x1
	BYTE UserApcPending; // 0x8A sz:0x1
	BYTE ApcQueueable; // 0x8B sz:0x1
	DWORD ApcQueueLock; // 0x8C sz:0x4
	DWORD ContextSwitches; // 0x90 sz:0x4
	LIST_ENTRY ReadyListEntry; // 0x94 sz:0x8
	union {
		struct {
			WORD MsrEnableMaskHigh; // 0x9C sz:0x2
			WORD MsrEnableMaskLow; // 0x9E sz:0x2
		} hilo;
		DWORD MsrEnableMask; // 0x9C sz:0x4
	} Msr;
	LONG WaitStatus; // 0xA0 sz:0x4
	BYTE WaitIrql; // 0xA4 sz:0x1
	BYTE WaitMode; // 0xA5 sz:0x1
	BYTE WaitNext; // 0xA6 sz:0x1
	BYTE WaitReason; // 0xA7 sz:0x1
	PKWAIT_BLOCK WaitBlockList; // 0xA8 sz:0x4
	DWORD Padding1; // 0xAC sz:0x4
	DWORD KernelApcDisable; // 0xB0 sz:0x4
	LONG Quantum; // 0xB4 sz:0x4
	char Saturation; // 0xB8 sz:0x1
	BYTE BasePriority; // 0xB9 sz:0x1
	BYTE PriorityDecrement; // 0xBA sz:0x1
	BYTE DisableBoost; // 0xBB sz:0x1
	char SuspendCount; // 0xBC sz:0x1
	BYTE Preempted; // 0xBD sz:0x1
	BYTE HasTerminated; // 0xBE sz:0x1
	BYTE CurrentProcessor; // 0xBF sz:0x1
	PKPRCB CurrentPrcb; // 0xC0 sz:0x4
	PKPRCB AffinityPrcb; // 0xC4 sz:0x4
	BYTE IdlePriorityClass; // 0xC8 sz:0x1
	BYTE NormalPriorityClass; // 0xC9 sz:0x1
	BYTE TimeCriticalPriorityClass; // 0xCA sz:0x1
	BYTE HasAsyncTerminated; // 0xCB sz:0x1
	DWORD ActiveTimerListLock; // 0xCC sz:0x4
	PVOID StackAllocatedBase; // 0xD0 sz:0x4
	KAPC SuspendApc; // 0xD4 sz:0x28
	KSEMAPHORE SuspendSemaphore; // 0xFC sz:0x14
	LIST_ENTRY ThreadListEntry; // 0x110 sz:0x8
	PKQUEUE Queue; // 0x118 sz:0x4
	LIST_ENTRY QueueListEntry; // 0x11C sz:0x8
	PVOID UserModeDispatcher; // 0x124 sz:0x4  Function Pointer
	PKTRAP_FRAME UserModeTrapFrame; // 0x128 sz:0x4
	LARGE_INTEGER CreateTime; // 0x130 sz:0x8
	LARGE_INTEGER ExitTime; // 0x138 sz:0x8
	LONG ExitStatus; // 0x140 sz:0x4
	LIST_ENTRY ActiveTimerListHead; // 0x144 sz:0x8
	PVOID ThreadId; // 0x14C sz:0x4
	PVOID StartAddress; // 0x150 sz:0x4 Function Pointer
	struct _LIST_ENTRY IrpList; // 0x154 sz:0x8
	PVOID DebugMonitorData; // 0x15C sz:0x4
	DWORD LastWin32ErrorCode; // 0x160 sz:0x4
	PVOID Win32CurrentFiber; // 0x164 sz:0x4
	DWORD Padding2; // 0x168 sz:0x4
	DWORD CreateOptions; // 0x16C sz:0x4
	float Vscr[4]; // 0x170 sz:0x10
	float Vr[4][128]; // 0x180 sz:0x800
	double Fpscr; // 0x980 sz:0x8
	double Fpr[32]; // 0x988 sz:0x100
	KAPC TerminateApc; // 0xA88 sz:0x28
} KTHREAD, *PKTHREAD; // size 2736
//C_ASSERT(sizeof(KTHREAD) == 0xAB0);

// *********** PACKING STARTS HERE **************//
#pragma pack(push, 1)
// *********** PACKING STARTS HERE **************//

//KPCR is %r13 (pointer)
//PKPCR __declspec(naked) GetThread_KPCR(VOID)
//{
//	asm{
//		mr		r3, r13
//		blr
//	}
//}

typedef struct _KPCR { 
	PVOID TlsData; // 0x0 sz:0x4
	union {
		struct {
			WORD MsrEnableMaskHigh; // 0x4 sz:0x2
			WORD MsrEnableMaskLow; // 0x6 sz:0x2
		} hilo;
		DWORD MsrEnableMask; // 0x4 sz:0x4
	} Msr;
	union {
		struct {
			BYTE DispatchInterrupt; // 0x8 sz:0x1
			BYTE ApcInterrupt; // 0x9 sz:0x1
		} hard;
		WORD SoftwareInterrupt; // 0x8 sz:0x2
	} Int;
	union {
		struct {
			BYTE DpcFpuStateSaved; // 0xA sz:0x1
			BYTE DpcVpuStateSaved; // 0xB sz:0x1
		} sep;
		WORD DpcFpuVpuStateSaved; // 0xA sz:0x2
	} Dpc;
	BYTE DpcCurrentProcessType; // 0xC sz:0x1
	BYTE QuantumEnd; // 0xD sz:0x1
	BYTE TimerRequest; // 0xE sz:0x1
	BYTE HvCr0Save; // 0xF sz:0x1
	PKTHREAD FpuOwnerThread; // 0x10 sz:0x4
	PKTHREAD VpuOwnerThread; // 0x14 sz:0x4
	BYTE CurrentIrql; // 0x18 sz:0x1
	BYTE BackgroundSchedulingActive; // 0x19 sz:0x1
	union {
		struct {
			BYTE StartBackgroundScheduling; // 0x1A sz:0x1
			BYTE StopBackgroundScheduling; // 0x1B sz:0x1
		} sep;
		WORD StartStopBackgroundScheduling; // 0x1A sz:0x2
	} Sched;
	DWORD TimerHand; // 0x1C sz:0x4
	union{
		struct{
			QWORD LrIarSave; // 0x20 sz:0x8
			QWORD CrMsrSave; // 0x28 sz:0x8
			QWORD Gpr13Save; // 0x30 sz:0x8
		} gpSave;
		struct{
			DWORD Gpr1Restore; // 0x20 sz:0x4
			DWORD IarRestore; // 0x24 sz:0x4
			DWORD CrRestore; // 0x28 sz:0x4
			DWORD MsrRestore; // 0x2C sz:0x4
		} gpRest;
	};
	QWORD HvGpr1Save; // 0x38 sz:0x8
	QWORD HvGpr3Save; // 0x40 sz:0x8
	QWORD HvGpr4Save; // 0x48 sz:0x8
	QWORD HvGpr5Save; // 0x50 sz:0x8
	DWORD UserModeControl; // 0x58 sz:0x4
	PVOID PanicStack; // 0x5C sz:0x4
	DWORD DarSave; // 0x60 sz:0x4
	DWORD DsisrSave; // 0x64 sz:0x4
	PVOID DbgLastDpcRoutine; // 0x68 sz:0x4
	DWORD OnInterruptStack; // 0x6C sz:0x4
	PVOID StackBase; // 0x70 sz:0x4
	PVOID StackLimit; // 0x74 sz:0x4
	PVOID InterruptStackBase; // 0x78 sz:0x4
	PVOID InterruptStackLimit; // 0x7C sz:0x4
	PVOID InterruptRoutine[0x20]; // 0x80 sz:0x80
	KPRCB PrcbData; // 0x100 sz:0x1A8
	PKPRCB Prcb; // 0x2A8 sz:0x4
	DWORD Unused; // 0x2AC sz:0x4
	PDWORD PixCurrent; // 0x2B0 sz:0x4
	PDWORD PixLimit; // 0x2B4 sz:0x4
	PDWORD ProfilerCurrent; // 0x2B8 sz:0x4
	PDWORD ProfilerLimit; // 0x2BC sz:0x4
	DWORD ProfilerFlags; // 0x2C0 sz:0x4
	QWORD Contention; // 0x2C8 sz:0x8 -> XProfilerContentionFlag 0x1
	PDWORD MonitorProfileData; // 0x2D0 sz:0x4
	// PcIdleThreadData 0x300
} KPCR, *PKPCR; // size 728
//C_ASSERT(sizeof(KPCR) == 0x2D8);

typedef union _KPCR_PAGE {
	struct{
		KPCR Pcr; // 0x0 sz:0x2D8
		QWORD IdleThreadData[ANYSIZE_ARRAY]; // 0x300 sz:0x0
	} AsSeparate;
	BYTE PcrAsUCHARs[4096]; // 0x0 sz:0x1000
} KPCR_PAGE, *PKPCR_PAGE; // size 4096
C_ASSERT(sizeof(KPCR_PAGE) == 0x1000);
// *********** PACKING ENDS HERE **************//
#pragma pack(pop)
// *********** PACKING ENDS HERE **************//

typedef struct _KSPECIAL_REGISTERS { 
	DWORD KernelDr0; // 0x0 sz:0x4
	DWORD KernelDr1; // 0x4 sz:0x4
	DWORD KernelDr2; // 0x8 sz:0x4
	DWORD KernelDr3; // 0xC sz:0x4
	DWORD KernelDr4; // 0x10 sz:0x4
	DWORD KernelDr5; // 0x14 sz:0x4
	DWORD KernelDr6; // 0x18 sz:0x4
	DWORD KernelDr7; // 0x1C sz:0x4
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS; // size 32
C_ASSERT(sizeof(KSPECIAL_REGISTERS) == 0x20);

typedef struct _KPROCESSOR_STATE { 
	CONTEXT ContextFrame; // 0x0 sz:0xA40
	KSPECIAL_REGISTERS SpecialRegisters; // 0xA40 sz:0x20
} KPROCESSOR_STATE, *PKPROCESSOR_STATE; // size 2656
C_ASSERT(sizeof(KPROCESSOR_STATE) == 0xA60);


typedef struct _OBJECT_HANDLE_TABLE { 
	LONG HandleCount; // 0x0 sz:0x4
	DWORD FirstFreeTableOffset; // 0x4 sz:0x4
	DWORD TableAllocation; // 0x8 sz:0x4
	PVOID** RootTable; // 0xC sz:0x4
	PVOID* BuiltinRootTable[8]; // 0x10 sz:0x20
	DWORD SpinLock; // 0x30 sz:0x4
	BYTE PoolType; // 0x34 sz:0x1
	BYTE Discriminant; // 0x35 sz:0x1
	BYTE Terminating; // 0x36 sz:0x1
} OBJECT_HANDLE_TABLE, *POBJECT_HANDLE_TABLE; // size 56
C_ASSERT(sizeof(OBJECT_HANDLE_TABLE) == 0x38);



#endif // __KEPRIVATESTRUCTS_H
