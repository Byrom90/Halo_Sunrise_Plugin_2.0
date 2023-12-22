#pragma once

#ifndef COREHOOKS_H
#define COREHOOKS_H
#include "stdafx.h"

VOID RegisterActiveServer(in_addr address, WORD port, const char description[XTITLE_SERVER_MAX_SERVER_INFO_LEN]);
VOID SetupNetDllHooks();
VOID RegisterHaloLogger(DWORD Address);
VOID SetupXUserReadStatsHook(DWORD Address);

#endif