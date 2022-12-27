#ifndef __KENAND_H
#define __KENAND_H

typedef struct _BLDR_HEADER{
	WORD Magic;
	WORD Build;
	WORD Qfe;
	WORD Flags;
	DWORD Entry;
	DWORD Size;
} BLDR_HEADER, *PBLDR_HEADER;
C_ASSERT(sizeof(BLDR_HEADER) == 0x10);

typedef struct _BLDR_FLASH{ // magic 0xFF4f
	BLDR_HEADER blHeader; // 0
	char achCopyright[0x40]; // 0x10
	BYTE abReserved[0x10]; // 0x50	0x0 filled
	DWORD dwKeyVaultSize; // 0x60	size of the keyvault
	DWORD dwSysUpdateAddr; // 0x64	offset to first cf
	WORD wSysUpdateCount; // 0x68	number of patch slots
	WORD wKeyVaultVersion; // 0x6A	0x0712
	DWORD dwKeyVaultAddr; // 0x6C	offset of the keyvault from 0
	DWORD dwPatchSlotSize; // 0x70	if == 0 then = 0x10000, patch slot size 
	DWORD dwSmcConfigAddr; // 0x74	0x0
	DWORD dwSmcBootSize; // 0x78	size of smc.bin
	DWORD dwSmcBootAddr; // 0x7C	offset of smc.bin from 0
} BLDR_FLASH, *PBLDR_FLASH;
C_ASSERT(sizeof(BLDR_FLASH) == 0x80);

#endif // __KENAND_H
