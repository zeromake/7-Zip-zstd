// Common/CRC.cpp

#include "StdAfx.h"

#include "../../C/7zCrc.h"

static struct CCRCTableInit { CCRCTableInit() { CrcGenerateTable(); } } g_CRCTableInit;
#ifndef USE_DLL_EXPORT
void registerCCRCTableInit() { CrcGenerateTable(); }
#endif
