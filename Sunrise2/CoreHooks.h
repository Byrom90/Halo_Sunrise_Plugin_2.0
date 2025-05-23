#pragma once

#ifndef COREHOOKS_H
#define COREHOOKS_H
#include "stdafx.h"

VOID RegisterActiveServer(in_addr address, const char description[XTITLE_SERVER_MAX_SERVER_INFO_LEN]);
VOID RegisterActiveServerDomain(char* domain, const char description[XTITLE_SERVER_MAX_SERVER_INFO_LEN]);
VOID SetupNetDllHooks();
VOID RegisterHaloLogger(DWORD Address);
VOID SetupXUserReadStatsHook(DWORD Address);

#endif