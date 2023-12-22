#pragma once

#ifndef COREHOOKS_H
#define COREHOOKS_H
#include "stdafx.h"

VOID SetupNetDllHooks();
VOID RegisterHaloLogger(DWORD Address);
VOID SetupXUserReadStatsHook(DWORD Address);

#endif