#ifndef __KEXECRYPT_H
#define __KEXECRYPT_H

typedef enum _XE_RSA_KEY_TYPE { // for XeKeysVerifyRSASignature
	XE_PIRS_RSA_KEY = 0x0,
	XE_LIVEDRM_RSA_KEY = 0x1,
	XE_DEVICE_RSA_KEY = 0x2,
	XE_XSIGNER2_RSA_KEY = 0x3,
	XE_MAX_RSA_KEY = 0x4,
} XE_RSA_KEY_TYPE;

#define XECRYPT_DES_BLOCK_SIZE      (0x8)
#define XECRYPT_DES_KEY_SIZE        (0x8)
#define XECRYPT_DES3_KEY_SIZE       (0x18)
#define XECRYPT_AES_BLOCK_SIZE      (0x10)
#define XECRYPT_AES_KEY_SIZE        (0x10)
#define XECRYPT_SHA_DIGEST_SIZE     (0x14)
#define XECRYPT_MD5_DIGEST_SIZE     (0x10)
#define XECRYPT_PARVE_BLOCK_SIZE    (0x8)
#define XECRYPT_PARVE_KEY_SIZE      (0x8)
#define XECRYPT_PARVE_SBOX_SIZE     (0x100)
#define XECRYPT_PARVE_MAC_SIZE      (0x8)


/* ******************* console certificate stuff ******************* */
#pragma pack(push, 1)
typedef struct _XE_CONSOLE_ID {
	union{
		struct {
			BYTE refurbBits : 4;
			BYTE ManufactureMonth : 4;
			DWORD ManufactureYear : 4;
			DWORD MacIndex3 : 8;
			DWORD MacIndex4 : 8;
			DWORD MacIndex5 : 8;
			DWORD Crc : 4;
		} asBits;
		BYTE abData[5];
	};
} XE_CONSOLE_ID, *PXE_CONSOLE_ID; // size 5
C_ASSERT(sizeof(XE_CONSOLE_ID) == 0x5);
#pragma pack(pop)

typedef struct _CONSOLE_PUBLIC_KEY { 
	BYTE PublicExponent[0x4]; // 0x0 sz:0x4
	BYTE Modulus[0x80]; // 0x4 sz:0x80
} CONSOLE_PUBLIC_KEY, *PCONSOLE_PUBLIC_KEY; // size 132
C_ASSERT(sizeof(CONSOLE_PUBLIC_KEY) == 0x84);

typedef struct _XE_CONSOLE_CERTIFICATE { 
	WORD CertSize; // 0x0 sz:0x2
	XE_CONSOLE_ID ConsoleId; // 0x2 sz:0x5
	BYTE ConsolePartNumber[0xB]; // 0x7 sz:0xB
	BYTE Reserved[0x4]; // 0x12 sz:0x4
	WORD Privileges; // 0x16 sz:0x2
	DWORD ConsoleType; // 0x18 sz:0x4
	char ManufacturingDate[0x8]; // 0x1C sz:0x8
	CONSOLE_PUBLIC_KEY ConsolePublicKey; // 0x24 sz:0x84
	BYTE Signature[0x100]; // 0xA8 sz:0x100
} XE_CONSOLE_CERTIFICATE, *PXE_CONSOLE_CERTIFICATE; // size 424
C_ASSERT(sizeof(XE_CONSOLE_CERTIFICATE) == 0x1A8);

typedef struct _XE_CONSOLE_SIGNATURE { 
	XE_CONSOLE_CERTIFICATE Cert; // 0x0 sz:0x1A8
	BYTE Signature[0x80]; // 0x1A8 sz:0x80
} XE_CONSOLE_SIGNATURE, *PXE_CONSOLE_SIGNATURE; // size 552
C_ASSERT(sizeof(XE_CONSOLE_SIGNATURE) == 0x228);

/* ******************* DES stuff ******************* */
typedef struct _XECRYPT_DES_STATE { 
	DWORD keytab[0x10][0x2]; // 0x0 sz:0x80
} XECRYPT_DES_STATE, *PXECRYPT_DES_STATE; // size 128
C_ASSERT(sizeof(XECRYPT_DES_STATE) == 0x80);

/* ******************* DES3 stuff ******************* */
typedef struct _XECRYPT_DES3_STATE { 
	XECRYPT_DES_STATE aDesState[0x3]; // 0x0 sz:0x180
} XECRYPT_DES3_STATE, *PXECRYPT_DES3_STATE; // size 384
C_ASSERT(sizeof(XECRYPT_DES3_STATE) == 0x180);

/* ******************* AES stuff ******************* */
typedef struct _XECRYPT_AES_STATE { 
	BYTE keytabenc[0xB][0x4][0x4]; // 0x0 sz:0xB0
	BYTE keytabdec[0xB][0x4][0x4]; // 0xB0 sz:0xB0
} XECRYPT_AES_STATE, *PXECRYPT_AES_STATE; // size 352
C_ASSERT(sizeof(XECRYPT_AES_STATE) == 0x160);

/* ******************* RC4 stuff ******************* */
typedef struct _XECRYPT_RC4_STATE { 
	BYTE S[0x100]; // 0x0 sz:0x100
	BYTE i; // 0x100 sz:0x1
	BYTE j; // 0x101 sz:0x1
} XECRYPT_RC4_STATE, *PXECRYPT_RC4_STATE; // size 258
C_ASSERT(sizeof(XECRYPT_RC4_STATE) == 0x102);

/* ******************* SHA stuff ******************* */
typedef struct _XECRYPT_SHA_STATE { 
	DWORD count; // 0x0 sz:0x4
	DWORD state[0x5]; // 0x4 sz:0x14
	BYTE buffer[0x40]; // 0x18 sz:0x40
} XECRYPT_SHA_STATE, *PXECRYPT_SHA_STATE; // size 88
C_ASSERT(sizeof(XECRYPT_SHA_STATE) == 0x58);

/* ******************* HMACSHA stuff ******************* */
typedef struct _XECRYPT_HMACSHA_STATE { 
	XECRYPT_SHA_STATE ShaState[0x2]; // 0x0 sz:0xB0
} XECRYPT_HMACSHA_STATE, *PXECRYPT_HMACSHA_STATE; // size 176
C_ASSERT(sizeof(XECRYPT_HMACSHA_STATE) == 0xB0);

/* ******************* MD5 stuff ******************* */
typedef struct _XECRYPT_MD5_STATE { 
	DWORD count; // 0x0 sz:0x4
	DWORD buf[0x4]; // 0x4 sz:0x10
	BYTE in[0x40]; // 0x14 sz:0x40
} XECRYPT_MD5_STATE, *PXECRYPT_MD5_STATE; // size 84
C_ASSERT(sizeof(XECRYPT_MD5_STATE) == 0x54);

/* ******************* HMACMD5 stuff ******************* */
typedef struct _XECRYPT_HMACMD5_STATE { 
	XECRYPT_MD5_STATE Md5State[0x2]; // 0x0 sz:0xA8
} XECRYPT_HMACMD5_STATE, *PXECRYPT_HMACMD5_STATE; // size 168
C_ASSERT(sizeof(XECRYPT_HMACMD5_STATE) == 0xA8);

/* ******************* RSA stuff ******************* */
typedef struct _XECRYPT_RSA { 
	DWORD cqw; // 0x0 sz:0x4
	DWORD dwPubExp; // 0x4 sz:0x4
	QWORD qwReserved; // 0x8 sz:0x8
} XECRYPT_RSA, *PXECRYPT_RSA; // size 16
C_ASSERT(sizeof(XECRYPT_RSA) == 0x10);

typedef struct _XECRYPT_RSAPUB_1024 { 
	XECRYPT_RSA Rsa; // 0x0 sz:0x10
	QWORD aqwM[0x10]; // 0x10 sz:0x80
} XECRYPT_RSAPUB_1024, *PXECRYPT_RSAPUB_1024; // size 144
C_ASSERT(sizeof(XECRYPT_RSAPUB_1024) == 0x90);

typedef struct _XECRYPT_RSAPUB_1536 { 
	XECRYPT_RSA Rsa; // 0x0 sz:0x10
	QWORD aqwM[0x18]; // 0x10 sz:0xC0
} XECRYPT_RSAPUB_1536, *PXECRYPT_RSAPUB_1536; // size 208
C_ASSERT(sizeof(XECRYPT_RSAPUB_1536) == 0xD0);

typedef struct _XECRYPT_RSAPUB_2048 { 
	XECRYPT_RSA Rsa; // 0x0 sz:0x10
	QWORD aqwM[0x20]; // 0x10 sz:0x100
} XECRYPT_RSAPUB_2048, *PXECRYPT_RSAPUB_2048; // size 272
C_ASSERT(sizeof(XECRYPT_RSAPUB_2048) == 0x110);

typedef struct _XECRYPT_RSAPUB_4096 { 
	XECRYPT_RSA Rsa; // 0x0 sz:0x10
	QWORD aqwM[0x40]; // 0x10 sz:0x200
} XECRYPT_RSAPUB_4096, *PXECRYPT_RSAPUB_4096; // size 528
C_ASSERT(sizeof(XECRYPT_RSAPUB_4096) == 0x210);

typedef struct _XECRYPT_RSAPRV_1024 { 
	XECRYPT_RSAPUB_1024 RsaPub; // 0x0 sz:0x10
	QWORD aqwP[0x8]; // 0x90 sz:0x40
	QWORD aqwQ[0x8]; // 0xD0 sz:0x40
	QWORD aqwDP[0x8]; // 0x110 sz:0x40
	QWORD aqwDQ[0x8]; // 0x150 sz:0x40
	QWORD aqwCR[0x8]; // 0x190 sz:0x40
} XECRYPT_RSAPRV_1024, *PXECRYPT_RSAPRV_1024; // size 464
C_ASSERT(sizeof(XECRYPT_RSAPRV_1024) == 0x1D0);

typedef struct _XECRYPT_RSAPRV_1536 { 
	XECRYPT_RSAPUB_1536 RsaPub; // 0x0 sz:0x10
	QWORD aqwP[0xC]; // 0xD0 sz:0x60
	QWORD aqwQ[0xC]; // 0x130 sz:0x60
	QWORD aqwDP[0xC]; // 0x190 sz:0x60
	QWORD aqwDQ[0xC]; // 0x1F0 sz:0x60
	QWORD aqwCR[0xC]; // 0x250 sz:0x60
} XECRYPT_RSAPRV_1536, *PXECRYPT_RSAPRV_1536; // size 688
C_ASSERT(sizeof(XECRYPT_RSAPRV_1536) == 0x2B0);

typedef struct _XECRYPT_RSAPRV_2048 { 
	XECRYPT_RSAPUB_2048 RsaPub; // 0x0 sz:0x10
	QWORD aqwP[0x10]; // 0x110 sz:0x80
	QWORD aqwQ[0x10]; // 0x190 sz:0x80
	QWORD aqwDP[0x10]; // 0x210 sz:0x80
	QWORD aqwDQ[0x10]; // 0x290 sz:0x80
	QWORD aqwCR[0x10]; // 0x310 sz:0x80
} XECRYPT_RSAPRV_2048, *PXECRYPT_RSAPRV_2048; // size 912
C_ASSERT(sizeof(XECRYPT_RSAPRV_2048) == 0x390);

typedef struct _XECRYPT_RSAPRV_4096 { 
	XECRYPT_RSAPUB_4096 RsaPub; // 0x0 sz:0x10
	QWORD aqwP[0x20]; // 0x210 sz:0x100
	QWORD aqwQ[0x20]; // 0x310 sz:0x100
	QWORD aqwDP[0x20]; // 0x410 sz:0x100
	QWORD aqwDQ[0x20]; // 0x510 sz:0x100
	QWORD aqwCR[0x20]; // 0x610 sz:0x100
} XECRYPT_RSAPRV_4096, *PXECRYPT_RSAPRV_4096; // size 1808
C_ASSERT(sizeof(XECRYPT_RSAPRV_4096) == 0x710);

/* ******************* SIG stuff ******************* */
typedef struct _XECRYPT_SIG { 
	QWORD aqwPad[0x1C]; // 0x0 sz:0xE0
	BYTE bOne; // 0xE0 sz:0x1
	BYTE abSalt[0xA]; // 0xE1 sz:0xA
	BYTE abHash[0x14]; // 0xEB sz:0x14
	BYTE bEnd; // 0xFF sz:0x1
} XECRYPT_SIG, *PXECRYPT_SIG; // size 256
C_ASSERT(sizeof(XECRYPT_SIG) == 0x100);

/* ******************* Diffie-Hellman stuff ******************* */
typedef struct _XECRYPT_DH { 
	DWORD cqw; // 0x0 sz:0x4
	DWORD dwReserved; // 0x4 sz:0x4
} XECRYPT_DH, *PXECRYPT_DH; // size 8
C_ASSERT(sizeof(XECRYPT_DH) == 0x8);

typedef struct _XECRYPT_DH_768 { 
	XECRYPT_DH Dh; // 0x0 sz:0x8
	QWORD aqwM[0xC]; // 0x8 sz:0x60
	QWORD aqwG[0xC]; // 0x68 sz:0x60
} XECRYPT_DH_768, *PXECRYPT_DH_768; // size 200
C_ASSERT(sizeof(XECRYPT_DH_768) == 0xC8);

typedef struct _XECRYPT_DH_1024 { 
	XECRYPT_DH Dh; // 0x0 sz:0x8
	QWORD aqwM[0x10]; // 0x8 sz:0x80
	QWORD aqwB[0x10]; // 0x88 sz:0x80
} XECRYPT_DH_1024, *PXECRYPT_DH_1024; // size 264
C_ASSERT(sizeof(XECRYPT_DH_1024) == 0x108);

/* ******************* eliptic curve stuff ******************* */
typedef struct _XECRYPT_ECPUB { 
	DWORD cqw; // 0x0 sz:0x4
	BYTE cbitR; // 0x4 sz:0x1
	BYTE cbitS; // 0x5 sz:0x1
	BYTE cbitA; // 0x6 sz:0x1
	BYTE cbitN; // 0x7 sz:0x1
} XECRYPT_ECPUB, *PXECRYPT_ECPUB; // size 8
C_ASSERT(sizeof(XECRYPT_ECPUB) == 0x8);

typedef struct _XECRYPT_ECPUB_512 { 
	XECRYPT_ECPUB EcPub; // 0x0 sz:0x8
	QWORD aqwM[0x8]; // 0x8 sz:0x40
	QWORD aqwC[0x10]; // 0x48 sz:0x80
	QWORD aqwG[0x10]; // 0xC8 sz:0x80
	QWORD aqwGP[0x10]; // 0x148 sz:0x80
} XECRYPT_ECPUB_512, *PXECRYPT_ECPUB_512; // size 456
C_ASSERT(sizeof(XECRYPT_ECPUB_512) == 0x1C8);

/* ******************* CRL.bin ******************* */
typedef struct _CERTIFICATE_REVOCATION_DATA { 
	DWORD Size; // 0x0 sz:0x4
	DWORD Version; // 0x4 sz:0x4
	DWORD Count; // 0x8 sz:0x4
} CERTIFICATE_REVOCATION_DATA, *PCERTIFICATE_REVOCATION_DATA; // size 12
C_ASSERT(sizeof(CERTIFICATE_REVOCATION_DATA) == 0xC);

typedef struct _CERTIFICATE_REVOCATION_BOX_DATA { 
	LARGE_INTEGER DateStamp; // 0x0 sz:0x8
	BYTE Padding[0x7]; // 0x8 sz:0x7
	BYTE UpdateSequence; // 0xF sz:0x1
} CERTIFICATE_REVOCATION_BOX_DATA, *PCERTIFICATE_REVOCATION_BOX_DATA; // size 16
C_ASSERT(sizeof(CERTIFICATE_REVOCATION_BOX_DATA) == 0x10);

typedef struct _CERTIFICATE_REVOCATION_LIST_HEADER { // typically header is immediately followed by the data, starting with CERTIFICATE_REVOCATION_DATA
	DWORD Signer; // 0x0 sz:0x4
	BYTE ConsoleID[0x5]; // 0x4 sz:0x5
	BYTE Padding[0x3]; // 0x9 sz:0x3
	BYTE Digest[0x14]; // 0xC sz:0x14
	XECRYPT_SIG Signature; // 0x20 sz:0x100
	BYTE Nonce[0x10]; // 0x120 sz:0x10
	BYTE Key[0x10]; // 0x130 sz:0x10
	union {
		CERTIFICATE_REVOCATION_BOX_DATA BoxData; // 0x140 sz:0x10
		BYTE BoxDataAsBYTE[0x10]; // 0x140 sz:0x10
	};
} CERTIFICATE_REVOCATION_LIST_HEADER, *PCERTIFICATE_REVOCATION_LIST_HEADER; // size 336
C_ASSERT(sizeof(CERTIFICATE_REVOCATION_LIST_HEADER) == 0x150);

typedef union _DYNAMIC_REVOCATION_LIST { 
	CERTIFICATE_REVOCATION_LIST_HEADER RevocationList; // 0x0 sz:0x150
	BYTE Reserved[0x8000]; // 0x0 sz:0x8000
} DYNAMIC_REVOCATION_LIST, *PDYNAMIC_REVOCATION_LIST; // size 32768
C_ASSERT(sizeof(DYNAMIC_REVOCATION_LIST) == 0x8000);


/* ******************* HDD security sector ******************* */
// stored at sector 2?
typedef struct _HDD_SECURITY_BLOB { 
	BYTE SerialNumber[0x14]; // 0x0 sz:0x14
	BYTE FirmwareRevision[0x8]; // 0x14 sz:0x8
	BYTE ModelNumber[0x28]; // 0x1C sz:0x28
	BYTE LogoBitmapDigest[0x14]; // 0x44 sz:0x14
	DWORD UserAddressableSectors; // 0x58 sz:0x4
	BYTE Signature[0x100]; // 0x5C sz:0x100
} HDD_SECURITY_BLOB, *PHDD_SECURITY_BLOB; // size 348
C_ASSERT(sizeof(HDD_SECURITY_BLOB) == 0x15C);

/* ******************* DAE.BIN decrypted ******************* */
typedef struct _DVD_AUTH_EX_DATA_D { 
	WORD Flags; // 0x0 sz:0x2
	WORD Reserved02; // 0x2 sz:0x2
	WORD Reserved04; // 0x4 sz:0x2
	WORD Reserved06; // 0x6 sz:0x2
	WORD Reserved08; // 0x8 sz:0x2
	WORD Reserved0A; // 0xA sz:0x2
	WORD Reserved0C; // 0xC sz:0x2
	WORD Reserved0E; // 0xE sz:0x2
} DVD_AUTH_EX_DATA_D, *PDVD_AUTH_EX_DATA_D; // size 16
C_ASSERT(sizeof(DVD_AUTH_EX_DATA_D) == 0x10);

typedef struct _DVD_AUTH_EX_DATA_E { 
	LARGE_INTEGER DateStamp; // 0x0 sz:0x8
	WORD Reserved08; // 0x8 sz:0x2
	WORD Reserved0A; // 0xA sz:0x2
	WORD Reserved0C; // 0xC sz:0x2
	BYTE Reserved0E; // 0xE sz:0x1
	BYTE UpdateSequence; // 0xF sz:0x1
} DVD_AUTH_EX_DATA_E, *PDVD_AUTH_EX_DATA_E; // size 16
C_ASSERT(sizeof(DVD_AUTH_EX_DATA_E) == 0x10);

typedef struct _DVD_AUTH_EX_HEADER { 
	DWORD Signer; // 0x0 sz:0x4
	WORD Size; // 0x4 sz:0x2
	WORD Flags; // 0x6 sz:0x2
	WORD Version; // 0x8 sz:0x2
	WORD Reserved0A; // 0xA sz:0x2
	BYTE DigestTable[0x14]; // 0xC sz:0x14
	BYTE Signature[0x100]; // 0x20 sz:0x100
	DVD_AUTH_EX_DATA_D DataD; // 0x120 sz:0x10
	DVD_AUTH_EX_DATA_E DataE; // 0x130 sz:0x10
	BYTE DigestUnique[0x10]; // 0x140 sz:0x10
} DVD_AUTH_EX_HEADER, *PDVD_AUTH_EX_HEADER; // size 336
C_ASSERT(sizeof(DVD_AUTH_EX_HEADER) == 0x150);

/* ******************* SECDATA.BIN decrypted ******************* */
typedef enum _SOFTWARE_SECURITY_STAT_INDEX {
	SOFTWARE_SECURITY_STAT_RESERVED_FOR_COMPATIBILITY = 0x0, // 0x38 in secdata.bin, all DWORD
	SOFTWARE_SECURITY_STAT_DVD_BOOT_FAILURES = 0x1,
	SOFTWARE_SECURITY_STAT_FUSE_BLOW_FAILURES = 0x2,
	SOFTWARE_SECURITY_STAT_DVD_AUTH_EX_FAILURES = 0x3,
	SOFTWARE_SECURITY_STAT_DVD_AUTH_EX_TIMEOUTS = 0x4,
	SOFTWARE_SECURITY_STAT_MAXIMUM = 0x5,
};

typedef struct _SECDATA_BLOB{
	BYTE abHash[0x10]; // 0 sz 0x10
	BYTE abConfounder[0x8];// 0x10
	BYTE SecurityActivated; // 0x18
	BYTE SecurityLockDownValue; // 0x19
	BYTE pad1[2]; // 0x1A sz 0x2
	WORD wUnkn1; // 0x1C
	WORD wUnkn2; // 0x1E
	FILETIME ftTime; // 0x20
	QWORD cSecurityDetectedError; // 0x28
	QWORD cSecurityActivatedError; // 0x30
	DWORD dwCompatReserved; // 0x38
	DWORD dwDvdBootFailures; // 0x3C
	DWORD dwFuseBlowFailures; // 0x40
	DWORD dwDvdAuthExFailures; // 0x44
	DWORD dwDvdAuthExTimeouts; // 0x48
	BYTE pad2[0x3B4]; // 0x5c

	//QWORD cDvdDetectionError; // 0x38 << old defines
	//QWORD cLockSystemUpdate; // 0x40
	//BYTE pad2[0x3B8]; // 0x48
} SECDATA_BLOB, *PSECDATA_BLOB;
C_ASSERT(sizeof(SECDATA_BLOB) == 0x400);

/* ******************* FCRT.BIN decrypted ******************* */
typedef struct _FCRT_HEADER{
	BYTE abSignature[0x100]; // 0 signature is calculcated with a has of header from abAesFeed to end of abPayloadHash, after abPayloadHash is calculated
	BYTE abAesFeed[0x10]; // 0x100 random value, with first byte being |0x1
	DWORD dwFlags; // 0x110
	DWORD dwVersion; // 0x114
	DWORD dwDataSize; // 0x118
	DWORD dwHeaderSize; // 0x11C
	BYTE abPad[0xC]; // 0x120
	BYTE abPayloadHash[0x14]; // 0x12C sha1 of data following this for dwDataSize
} FCRT_HEADER, *PFCRT_HEADER;
 C_ASSERT(sizeof(FCRT_HEADER) == 0x140);

 /* ******************* EXTENDED.BIN decrypted ******************* */
 typedef struct _EXTENDED_BIN_DATA{
	 BYTE abNonce[0x10]; 				// 0
	 BYTE abConfounder[0x8]; 			// 0x0010
	 BYTE abVidDevPubKey[0x28]; 			// 0x0018 XEKEYEX_VIDEO_DEVICE_PUBLIC_KEY: .set 0x100
	 BYTE abVidDevPrvKey[0x14]; 			// 0x0040 XEKEYEX_VIDEO_DEVICE_PRIVATE_KEY: .set 0x101
	 BYTE abVidDevCert[0x9C4]; 			// 0x0054 XEKEYEX_VIDEO_DEVICE_CERTIFICATE: .set 0x102
	 BYTE abIptvAvPrvKey[0x390]; 		// 0x0A18 XEKEYEX_IPTV_AV_PRIVATE_KEY: .set 0x103
	 BYTE abIptvAuthPrvKey[0x390]; 		// 0x0DA8 XEKEYEX_IPTV_AUTH_PRIVATE_KEY: .set 0x104
	 BYTE abIptvAvCert[0x5DC]; 			// 0x1138 XEKEYEX_IPTV_AV_CERTIFICATE: .set 0x105
	 BYTE abIptvAuthCert[0x5DC]; 		// 0x1714 XEKEYEX_IPTV_AUTH_CERTIFICATE: .set 0x106
	 BYTE abIptvAvSerializedCert[0x5DC]; // 0x1CF0 XEKEYEX_IPTV_AV_SERIALIZED_CERTIFICATE: .set 0x107
	 BYTE abIptvAuthSerializedCert[0x5DC];// 0x22CC XEKEYEX_IPTV_AUTH_SERIALIZED_CERTIFICATE: .set 0x108
	 BYTE abVidDevPrPubKeySign[0x40]; 	// 0x28A8 XEKEYEX_VIDEO_DEVICE_PR_PUBLIC_KEY_SIGN: .set 0x109
	 BYTE abVidDevPrPrvKeySign[0x20]; 	// 0x28C8 XEKEYEX_VIDEO_DEVICE_PR_PRIVATE_KEY_SIGN: .set 0x10A
	 BYTE abVidDevPrPubKeyEnc[0x40]; 	// 0x2908 XEKEYEX_VIDEO_DEVICE_PR_PUBLIC_KEY_ENCRYPT: .set 0x10B
	 BYTE abVidDevPrPrvKeyEnc[0x20]; 	// 0x2948 XEKEYEX_VIDEO_DEVICE_PR_PRIVATE_KEY_ENCRYPT: .set 0x10C
	 BYTE abVidDevPrCert[0x1388];		// 0x2968 XEKEYEX_VIDEO_DEVICE_PR_CERTIFICATE: .set 0x10D
	 BYTE pad[0x310];					// 0x3CF0
 }EXTENDED_BIN_DATA, *PEXTENDED_BIN_DATA;
 C_ASSERT(sizeof(EXTENDED_BIN_DATA) == 0x4000);

/* ******************* Functions ******************* */

#ifdef __cplusplus
extern "C" {
#endif
	NTSYSAPI
	EXPORTNUM(345)
	VOID
	NTAPI
	XeCryptAesKey(
		IN OUT	PXECRYPT_AES_STATE pAesState,
		IN		const PBYTE pbKey
	);

	NTSYSAPI
	EXPORTNUM(346)
	VOID
	NTAPI
	XeCryptAesEcb(
		IN		const PXECRYPT_AES_STATE pAesState,
		IN		const PBYTE pbInp,
		OUT		PBYTE pbOut,
		IN		BOOL fEncrypt
	);

	NTSYSAPI
	EXPORTNUM(347)
	VOID
	NTAPI
	XeCryptAesCbc(
		IN		const PXECRYPT_AES_STATE pAesState,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp,
		OUT		PBYTE pbOut,
		IN		PBYTE pbFeed,
		IN		BOOL fEncrypt
	);

	NTSYSAPI
	EXPORTNUM(348)
	BOOL
	NTAPI
	XeCryptBnDwLeDhEqualBase(
		IN		const PDWORD pdwA,
		IN		const PXECRYPT_DH pDh
	);

	NTSYSAPI
	EXPORTNUM(349)
	BOOL
	NTAPI
	XeCryptBnDwLeDhInvalBase(
		IN		const PDWORD pdwA,
		IN		const PXECRYPT_DH pDh
	);

	NTSYSAPI
	EXPORTNUM(350)
	BOOL
	NTAPI
	XeCryptBnDwLeDhModExp(
		IN		const PDWORD pdwA,
		IN		const PDWORD pdwB,
		IN OUT	PDWORD pdwC,
		IN		const PXECRYPT_DH pDh
	);

	NTSYSAPI
	EXPORTNUM(351)
	VOID
	NTAPI
	XeCryptBnDw_Copy(
		IN		const PDWORD pdwInp,
		OUT		PDWORD pdwOut,
		IN		DWORD cdw
	);

	NTSYSAPI
	EXPORTNUM(352)
	VOID
	NTAPI
	XeCryptBnDw_SwapLeBe(
		IN		const PDWORD pdwInp,
		OUT		PDWORD pdwOut,
		IN		DWORD cdw
	);

	NTSYSAPI
	EXPORTNUM(353)
	VOID
	NTAPI
	XeCryptBnDw_Zero(
		IN OUT	PDWORD pdw,
		IN		DWORD cdw
	);

	NTSYSAPI
	EXPORTNUM(354)
	VOID
	NTAPI
	XeCryptBnDwLePkcs1Format(
		IN		const PBYTE pbHash,
		IN		DWORD dwType,
		IN OUT	PBYTE pbSig,
		IN		DWORD cbSig
	);

	NTSYSAPI
	EXPORTNUM(355)
	BOOL
	NTAPI
	XeCryptBnDwLePkcs1Verify(
		IN		const PBYTE pbHash,
		IN		const PBYTE pbSig,
		IN		DWORD cbSig
	);

	NTSYSAPI
	EXPORTNUM(356)
	BOOL
	NTAPI
	XeCryptBnQwBeSigCreate(
		IN OUT	PXECRYPT_SIG pSig,
		IN		const PBYTE pbHash,
		IN		const PBYTE pbSalt,
		IN		const PXECRYPT_RSA pRsa
	);

	NTSYSAPI
	EXPORTNUM(357)
	VOID
	NTAPI
	XeCryptBnQwBeSigFormat(
		IN OUT	PXECRYPT_SIG pSig,
		IN		const PBYTE pbHash,
		IN		const PBYTE pbSalt
	);

	NTSYSAPI
	EXPORTNUM(358)
	BOOL
	NTAPI
	XeCryptBnQwBeSigVerify(
		IN		PXECRYPT_SIG pSig,
		IN		const PBYTE pbHash,
		IN		const PBYTE pbSalt,
		IN		const PXECRYPT_RSA pRsa
	);
	
	NTSYSAPI
	EXPORTNUM(359)
	BOOL
	NTAPI
	XeCryptBnQwNeModExp(
		IN OUT	PQWORD pqwOut,
		IN		const PQWORD pqwIn,
		IN		const PQWORD pqwInExp,
		IN		const PQWORD pqwInMod,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(360)
	BOOL
	NTAPI
	XeCryptBnQwNeModExpRoot(
		IN OUT	PQWORD pqwOut,
		IN		const PQWORD pqwIn,
		IN		const PQWORD pqwPP,
		IN		const PQWORD pqwQQ,
		IN		const PQWORD pqwDP,
		IN		const PQWORD pqwDQ,
		IN		const PQWORD pqwCR,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(361)
	QWORD
	NTAPI
	XeCryptBnQwNeModInv(
		IN		QWORD qw
	);

	NTSYSAPI
	EXPORTNUM(362)
	VOID
	NTAPI
	XeCryptBnQwNeModMul(
		IN		const PQWORD pqwA,
		IN		const PQWORD pqwB,
		IN OUT	PQWORD pqwOut,
		IN		QWORD qwMI,
		IN		const PQWORD pqwM,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(363)
	BOOL
	NTAPI
	XeCryptBnQwNeRsaKeyGen(
		IN		DWORD cbits,
		IN		DWORD dwPubExp,
		OUT		PXECRYPT_RSA pRsaPub,
		OUT		PXECRYPT_RSA pRsaPrv
	);

	NTSYSAPI
	EXPORTNUM(364)
	BOOL
	NTAPI
	XeCryptBnQwNeRsaPrvCrypt(
		IN		const PQWORD pqwIn,
		IN OUT	PQWORD pqwOut,
		IN		const PXECRYPT_RSA pRsa
	);

	NTSYSAPI
	EXPORTNUM(365)
	BOOL
	NTAPI
	XeCryptBnQwNeRsaPubCrypt(
		IN 		const PQWORD pqwIn,
		IN OUT	PQWORD pqwOut,
		IN		const PXECRYPT_RSA pRsa
	);

	NTSYSAPI
	EXPORTNUM(366)
	VOID
	NTAPI
	XeCryptBnQw_Copy(
		IN		const PQWORD pqwInp,
		OUT		PQWORD pqwOut,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(367)
	VOID
	NTAPI
	XeCryptBnQw_SwapDwQw(
		IN		const PQWORD pqwInp,
		OUT		PQWORD pqwOut,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(368)
	VOID
	NTAPI
	XeCryptBnQw_SwapDwQwLeBe(
		IN		const PQWORD pqwInp,
		OUT		PQWORD pqwOut,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(369)
	VOID
	NTAPI
	XeCryptBnQw_SwapLeBe(
		IN		const PQWORD pqwInp,
		OUT		PQWORD pqwOut,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(370)
	VOID
	NTAPI
	XeCryptBnQw_Zero(
		IN OUT	PQWORD pqw,
		IN		DWORD cqw
	);

	NTSYSAPI
	EXPORTNUM(371)
	VOID
	NTAPI
	XeCryptChainAndSumMac(
		IN		const PDWORD pdwCD,
		IN		const PDWORD pdwAB,
		IN		const PDWORD pdwInp,
		IN		DWORD cdwInp,
		IN OUT	PDWORD pdwOut
	);

	NTSYSAPI
	EXPORTNUM(372)
	VOID
	NTAPI
	XeCryptDesParity(
		IN		const PBYTE pbInp,
		IN		DWORD cbInp,
		OUT		PBYTE pbOut
	);

	NTSYSAPI
	EXPORTNUM(373)
	VOID
	NTAPI
	XeCryptDesKey(
		IN OUT	PXECRYPT_DES_STATE pDesState,
		IN		const PBYTE pbKey
	);

	NTSYSAPI
	EXPORTNUM(374)
	VOID
	NTAPI
	XeCryptDesEcb(
		IN		const PXECRYPT_DES_STATE pDesState,
		IN		const PBYTE pbInp,
		OUT		PBYTE pbOut,
		IN		BOOL fEncrypt
	);

	NTSYSAPI
	EXPORTNUM(375)
	VOID
	NTAPI
	XeCryptDesCbc(
		IN		const PXECRYPT_DES_STATE pDesState,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp,
		OUT		PBYTE pbOut,
		IN		PBYTE pbFeed,
		IN		BOOL fEncrypt
	);

	NTSYSAPI
	EXPORTNUM(376)
	VOID
	NTAPI
	XeCryptDes3Key(
		IN OUT	PXECRYPT_DES3_STATE pDes3State,
		IN		const PBYTE pbKey
	);

	NTSYSAPI
	EXPORTNUM(377)
	VOID
	NTAPI
	XeCryptDes3Ecb(
		IN		const PXECRYPT_DES3_STATE pDes3State,
		IN		const PBYTE pbInp,
		OUT		PBYTE pbOut,
		IN		BOOL fEncrypt
	);

	NTSYSAPI
	EXPORTNUM(378)
	VOID
	NTAPI
	XeCryptDes3Cbc(
		IN		const PXECRYPT_DES3_STATE pDes3State,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp,
		OUT		PBYTE pbOut,
		IN		PBYTE pbFeed,
		IN		BOOL fEncrypt
	);

	NTSYSAPI
	EXPORTNUM(379)
	VOID
	NTAPI
	XeCryptHmacMd5Init(
		IN OUT	PXECRYPT_HMACMD5_STATE pHmacMd5State,
		IN		const PBYTE pbKey,
		IN		DWORD cbKey
	);

	NTSYSAPI
	EXPORTNUM(380)
	VOID
	NTAPI
	XeCryptHmacMd5Update(
		IN OUT	PXECRYPT_HMACMD5_STATE pHmacMd5State,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp
	);

	NTSYSAPI
	EXPORTNUM(381)
	VOID
	NTAPI
	XeCryptHmacMd5Final(
		IN		PXECRYPT_HMACMD5_STATE pHmacMd5State,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(382)
	VOID
	NTAPI
	XeCryptHmacMd5(
		IN		const PBYTE pbKey,
		IN		DWORD cbKey,
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		IN		const PBYTE pbInp3,
		IN		DWORD cbInp3,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);
	
	NTSYSAPI
	EXPORTNUM(383)
	VOID
	NTAPI
	XeCryptHmacShaInit(
		IN OUT	PXECRYPT_HMACSHA_STATE pHmacShaState,
		IN		const PBYTE pbKey,
		IN		DWORD cbKey
	);

	NTSYSAPI
	EXPORTNUM(384)
	VOID
	NTAPI
	XeCryptHmacShaUpdate(
		IN OUT	PXECRYPT_HMACSHA_STATE pHmacShaState,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp
	);

	NTSYSAPI
	EXPORTNUM(385)
	VOID
	NTAPI
	XeCryptHmacShaFinal(
		IN		PXECRYPT_HMACSHA_STATE pHmacShaState,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(386)
	VOID
	NTAPI
	XeCryptHmacSha(
		IN		const PBYTE pbKey,
		IN		DWORD cbKey,
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		IN		const PBYTE pbInp3,
		IN		DWORD cbInp3,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(387)
	BOOL
	NTAPI
	XeCryptHmacShaVerify(
		IN		const PBYTE pbKey,
		IN		DWORD cbKey,
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		IN		const PBYTE pbInp3,
		IN		DWORD cbInp3,
		IN		const PBYTE pbVer,
		IN		DWORD cbVer
	);

	NTSYSAPI
	EXPORTNUM(388)
	VOID
	NTAPI
	XeCryptMd5Init(
		IN OUT	PXECRYPT_MD5_STATE pMd5State
	);

	NTSYSAPI
	EXPORTNUM(389)
	VOID
	NTAPI
	XeCryptMd5Update(
		IN OUT	PXECRYPT_MD5_STATE pMd5State,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp
	);

	NTSYSAPI
	EXPORTNUM(390)
	VOID
	NTAPI
	XeCryptMd5Final(
		IN		PXECRYPT_MD5_STATE pMd5State,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(391)
	VOID
	NTAPI
	XeCryptMd5(
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		IN		const PBYTE pbInp3,
		IN		DWORD cbInp3,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(392)
	VOID
	NTAPI
	XeCryptParveEcb(
		IN		const PBYTE pbKey,
		IN		const PBYTE pbSbox,
		IN		const PBYTE pbInp,
		IN OUT	PBYTE pbOut
	);

	NTSYSAPI
	EXPORTNUM(393)
	VOID
	NTAPI
	XeCryptParveCbcMac(
		IN		const PBYTE pbKey,
		IN		const PBYTE pbSbox,
		IN		const PBYTE pbIv,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp,
		IN OUT	PBYTE pbOut
	);

	NTSYSAPI
	EXPORTNUM(394)
	VOID
	NTAPI
	XeCryptRandom(
		OUT		BYTE * pb,
		IN		DWORD cb
	);

	NTSYSAPI
	EXPORTNUM(395)
	VOID
	NTAPI
	XeCryptRc4Key(
		IN OUT	PXECRYPT_RC4_STATE pRc4State,
		IN		const PBYTE pbKey,
		IN		DWORD cbKey
	);

	NTSYSAPI
	EXPORTNUM(396)
	VOID
	NTAPI
	XeCryptRc4Ecb(
		IN		PXECRYPT_RC4_STATE pRc4State,
		IN OUT	PBYTE pbInpOut,
		IN		DWORD cbInpOut
	);
	
	NTSYSAPI
	EXPORTNUM(397)
	VOID
	NTAPI
	XeCryptRc4(
		IN		const PBYTE pbKey,
		IN		DWORD cbKey,
		IN OUT	PBYTE pbInpOut,
		IN		DWORD cbInpOut
	);

	NTSYSAPI
	EXPORTNUM(398)
	VOID
	NTAPI
	XeCryptRotSumSha(
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(399)
	VOID
	NTAPI
	XeCryptShaInit(
		IN OUT	PXECRYPT_SHA_STATE pShaState
	);

	NTSYSAPI
	EXPORTNUM(400)
	VOID
	NTAPI
	XeCryptShaUpdate(
		IN OUT	PXECRYPT_SHA_STATE pShaState,
		IN		const PBYTE pbInp,
		IN		DWORD cbInp
	);

	NTSYSAPI
	EXPORTNUM(401)
	VOID
	NTAPI
	XeCryptShaFinal(
		IN		PXECRYPT_SHA_STATE pShaState,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(402)
	VOID
	NTAPI
	XeCryptSha(
		IN		const PBYTE pbInp1,
		IN		DWORD cbInp1,
		IN		const PBYTE pbInp2,
		IN		DWORD cbInp2,
		IN		const PBYTE pbInp3,
		IN		DWORD cbInp3,
		OUT		PBYTE pbOut,
		IN		DWORD cbOut
	);

	NTSYSAPI
	EXPORTNUM(600)
	BOOL
	NTAPI
	XeKeysVerifyRSASignature(
		IN		XE_RSA_KEY_TYPE key,
		IN		const BYTE *pbHash,
		IN		const BYTE *pbSig,
		IN		const BYTE *pubKey
	);

	NTSYSAPI
	EXPORTNUM(806)
	int
	NTAPI
	XeCryptBnQwNeCompare(
		IN		const PQWORD pqwA,
		IN		const PQWORD pqwB,
		IN		DWORD cqw
	);
	/* ** not included
	XeCryptSha256Init @784
	XeCryptSha256Update @785
	XeCryptSha256Final @786
	XeCryptSha256 @787
	XeCryptSha384Init @788
	XeCryptSha384Update @789
	XeCryptSha384Final @792
	XeCryptSha384 @798
	XeCryptSha512Init @799
	XeCryptSha512Update @803
	XeCryptSha512Final @804
	XeCryptSha512 @805
	XeCryptAesCtr @863
	XeCryptAesCbcMac @864
	XeCryptAesDmMac @865
	** */

#ifdef __cplusplus
}
#endif


#endif // __KEXECRYPT_H
