#include "stdafx.h"
#include "util.h"

#define MAX_LINE_SIZE 1024

typedef struct _ITEM_LIST{
	string name;
	DWORD ordinal;
	BOOL disable;
} ITEM_LIST, *PITEM_LIST;

vector<ITEM_LIST> g_items;
vector<string> g_txt;
DWORD deflen, listlen;
BYTE* deffile;
BYTE* listfile;
BOOL hasLibName = FALSE;
string libname;

void usage(void)
{
	printf("command line error, usage:\n");
	printf("deffix infile.def infile.txt outfile\n\n");
}

DWORD getLine(BYTE* data, char* line)
{
	DWORD cnt;
	for(cnt = 0; cnt < MAX_LINE_SIZE; cnt++)
	{
		if((data[cnt] != 0xd)&&(data[cnt] != 0xa)&&(data[cnt+1] != 0x0))
			line[cnt] = (char)data[cnt];
		else
		{
			line[cnt] = 0;
			if((data[cnt+1] == 0xd)||(data[cnt+1] == 0xa)||(data[cnt+1] == 0x0))
				return (cnt+2);
			else
				return cnt+1;
		}
	}
	return 0;
}

void parseDefLine(char* line, int len)
{
	int ps, ps2, curr = 0;
	ITEM_LIST itm;
	string name;
	string ord;
	itm.disable = FALSE;
	if((_strnicmp(line, "LIBRARY", strlen("LIBRARY")) == 0)||(strnicmp(line, "EXPORTS", strlen("EXPORTS")) == 0))
	{
		//printf("skipping LIBRARY/EXPORTS line\n");
		return;
	}
	// remove spaces, tabs and @
	if(line[curr] == ';')
	{
		itm.disable = TRUE;
		curr++;
	}
	if(line[curr] == '\t')
		curr++;
	name = &line[curr];
	ps = name.find_last_of('@',-1);
	ps2 = name.find_first_of('@', 0);
	ord = name.substr(ps+1);
	itm.ordinal = atoi(ord.c_str());
	itm.name = name.substr(0, ps-1);
	if(ps != ps2)
		itm.disable = TRUE;
	//printf("name: %s ordinal: %d disable: %d\n", itm.name.c_str(), itm.ordinal, itm.disable);
	g_items.push_back(itm);
}

void parseTxtLine(char* line, int len)
{
	if(strnicmp(line, "  Symbol name  : ", strlen("  Symbol name  : ")) == 0)
	{
		BOOL demangle = FALSE;
		int pos = strlen("  Symbol name  : ");
		if(line[pos] == '?')
		{
			pos++;
			demangle = TRUE;
		}
		string txt = &line[pos];
		if(demangle)
		{
			int ps = txt.find_first_of('@',0);
			if(ps != -1)
				txt.resize(ps);
		}
		//printf("txt: %s\n", txt.c_str());
		g_txt.push_back(txt);
	}
	else if(!hasLibName)
	{
		if(strnicmp(line, "  DLL name     : ", strlen("  DLL name     : ")) == 0)
			libname = &line[strlen("  DLL name     : ")];
	}
}

void parseDef(void)
{
	DWORD curr = 0, len;
	char line[MAX_LINE_SIZE];
	g_items.clear();
	while(curr < deflen)
	{
		len = getLine(&deffile[curr], line);
// 		printf("line (len %d): %s\n", len, line);
		parseDefLine(line, strlen(line));
		curr+=len;
	}
}

void parseTxt(void)
{
	DWORD curr = 0, len;
	char line[MAX_LINE_SIZE];
	g_txt.clear();
	while(curr < listlen)
	{
		len = getLine(&listfile[curr], line);
//		printf("line (len %d): %s\n", len, line);
		parseTxtLine(line, strlen(line));
		curr+=len;
	}
}

BOOL checkTxtItem(string targ)
{
	DWORD i;
	for(i = 0; i < g_txt.size(); i++)
	{
		if(g_txt.at(i).compare(targ) == 0)
			return TRUE;
	}
	return FALSE;
}

void checkTxt(void)
{
	DWORD i;
	for(i = 0; i < g_items.size(); i++)
	{
		if(checkTxtItem(g_items.at(i).name))
			g_items.at(i).disable = TRUE;
	}
}

int writeOutput(WCHAR* outname)
{
	int cnt = 0;
	HANDLE ofile;
	DeleteFileW(outname);
	ofile = CreateFileW(outname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(ofile != INVALID_HANDLE_VALUE)
	{
		char line[MAX_LINE_SIZE];
		DWORD i, bWrote;
		sprintf(line, "LIBRARY %s\n", libname.c_str());
		WriteFile(ofile, line, strlen(line), &bWrote, NULL);
		sprintf(line, "EXPORTS\n");
		WriteFile(ofile, line, strlen(line), &bWrote, NULL);
		for(i = 0; i < g_items.size(); i++)
		{
			if(g_items.at(i).disable)
			{
				sprintf(line, ";\t%s @%d\n", g_items.at(i).name.c_str(), g_items.at(i).ordinal);
				WriteFile(ofile, line, strlen(line), &bWrote, NULL);
				cnt++;
			}
			else
			{
				sprintf(line, "\t%s @%d\n", g_items.at(i).name.c_str(), g_items.at(i).ordinal);
				WriteFile(ofile, line, strlen(line), &bWrote, NULL);
			}
		}
		CloseHandle(ofile);
	}
	else
		printf("error opening %S for writing!\n", outname);
	return cnt;
}

void processFiles(WCHAR* outname)
{
	int tally;
	// parse def info into vector
	printf("parsing def...");
	parseDef();
	printf("done! %d items found.\nparsing txt...", g_items.size());
	parseTxt();
	printf("done! %d items found.\n", g_txt.size());
	// iterate vector to find and mark disabled instances in infile.txt
	printf("tidying things up...\n");
	checkTxt();
	printf("writing result to %S...", outname);
	tally = writeOutput(outname);
	printf("Done!\n%d of %d items were commented out\n", tally, g_items.size());
}

int _tmain(int argc, _TCHAR* argv[])
{
	//int i;
	//printf("argc: %d\n", argc);
	//for(i = 0; i < argc; i++)
	//	printf("arg %d: %S\n", i, argv[i]);
	if(argc != 4)
		usage();
	printf("reading %S to buffer...", argv[1]);
	deffile = loadFileToBuf(argv[1], &deflen);
	if((deffile != NULL)&&(deflen != 0))
	{
		printf("read 0x%x bytes OK\n", deflen);
		printf("reading %S to buffer...", argv[2]);
		listfile = loadFileToBuf(argv[2], &listlen);
		if((listfile != NULL)&&(listlen != 0))
		{
			printf("read 0x%x bytes OK\n", listlen);
			processFiles(argv[3]);
		}
	}
	if(deffile)
		free(deffile);
	if(listfile)
		free(listfile);
	printf("\n\n");
	return 0;
}
