/*
 * Copyright 2024 Yonggang Luo
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include "win-polyfill-arch.h"

#include <windef.h>

#define RTL_MAX_DRIVE_LETTERS 32
#define RTL_DRIVE_LETTER_VALID (USHORT)0x0001

#ifdef __cplusplus
extern "C" {
#endif

//
// These data structures and type definitions are needed for compilation and use
// of the internal Windows APIs defined in win-polyfill-teb.h and win-polyfill-peb.h
//

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;

typedef CONST char *PCSZ;

typedef struct _STRING
{
  USHORT Length;
  USHORT MaximumLength;
  PCHAR Buffer;
} STRING;
typedef STRING *PSTRING;

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;
typedef PSTRING PCANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef CONST STRING *PCOEM_STRING;

typedef struct _UNICODE_STRING
{
  USHORT Length;
  USHORT MaximumLength;
  PWSTR Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef LONG KPRIORITY;

typedef struct _CLIENT_ID
{
  HANDLE UniqueProcess;
  HANDLE UniqueThread;
} CLIENT_ID;

#ifdef __cplusplus
}
#endif
