#include "stdafx.h"

BYTE* doReadFile(HANDLE fhand, PDWORD len)
{
	DWORD rlen;
	*len = 0;
	rlen = GetFileSize(fhand, NULL);
	if(rlen != 0)
	{
		BYTE* buf = (BYTE*)malloc(rlen+1);
		if(buf != NULL)
		{
			DWORD bRead;
			ZeroMemory(buf, rlen+1);
			if(ReadFile(fhand, buf, rlen, &bRead, NULL))
			{
				*len = bRead;
				CloseHandle(fhand);
				return buf;
			}
			else
				printf("ReadFile error! %d\n", GetLastError());
			free(buf);
		}
		else
			printf("error allocating buffer for file!\n");
	}
	else
		printf("file size is zero!\n");
	CloseHandle(fhand);
	return NULL;
}

BYTE* loadFileToBuf(char* fname, PDWORD len)
{
	if((fname != NULL)&&(len != NULL))
	{
		HANDLE fhand;
		fhand = CreateFileA(fname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(fhand != INVALID_HANDLE_VALUE)
		{
			return doReadFile(fhand, len);
		}
		else
			printf("error opening %s for read!\n", fname);
	}
	else
		printf("error, loadfile called with incorrect args!\n");
	return NULL;
}

BYTE* loadFileToBuf(WCHAR* fname, PDWORD len)
{
	if((fname != NULL)&&(len != NULL))
	{
		HANDLE fhand;
		fhand = CreateFileW(fname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(fhand != INVALID_HANDLE_VALUE)
		{
			return doReadFile(fhand, len);
		}
		else
			printf("error opening %S for read!\n", fname);
	}
	else
		printf("error, loadfile called with incorrect args!\n");
	return NULL;
}
