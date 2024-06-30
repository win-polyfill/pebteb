﻿/*
 * Copyright 2024 Yonggang Luo
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include "win-polyfill-winternl.h"

#ifdef __cplusplus
extern "C" {
#endif

//0x4 bytes (sizeof)
enum _LDR_DDAG_STATE
{
  LdrModulesMerged = -5,
  LdrModulesInitError = -4,
  LdrModulesSnapError = -3,
  LdrModulesUnloaded = -2,
  LdrModulesUnloading = -1,
  LdrModulesPlaceHolder = 0,
  LdrModulesMapping = 1,
  LdrModulesMapped = 2,
  LdrModulesWaitingForDependencies = 3,
  LdrModulesSnapping = 4,
  LdrModulesSnapped = 5,
  LdrModulesCondensed = 6,
  LdrModulesReadyToInit = 7,
  LdrModulesInitializing = 8,
  LdrModulesReadyToRun = 9
};

//0x4 bytes (sizeof)
enum _LDR_DLL_LOAD_REASON
{
  LoadReasonStaticDependency = 0,
  LoadReasonStaticForwarderDependency = 1,
  LoadReasonDynamicForwarderDependency = 2,
  LoadReasonDelayloadDependency = 3,
  LoadReasonDynamicLoad = 4,
  LoadReasonAsImageLoad = 5,
  LoadReasonAsDataLoad = 6,
  LoadReasonUnknown = -1
};

//0x4 bytes (sizeof)
enum _LDR_HOT_PATCH_STATE
{
  LdrHotPatchBaseImage = 0,
  LdrHotPatchNotApplied = 1,
  LdrHotPatchAppliedReverse = 2,
  LdrHotPatchAppliedForward = 3,
  LdrHotPatchFailedToPatch = 4,
  LdrHotPatchStateMax = 5
};

struct _LDRP_CSLIST
{
  struct _SINGLE_LIST_ENTRY *Tail; //0x0
};

struct _LDR_DDAG_NODE
{
  struct _LIST_ENTRY Modules;                     //0x0
  struct _LDR_SERVICE_TAG_RECORD *ServiceTagList; //0x10
  ULONG LoadCount;                                //0x18
  ULONG LoadWhileUnloadingCount;                  //0x1c
  ULONG LowestLink;                               //0x20
  struct _LDRP_CSLIST Dependencies;               //0x28
  struct _LDRP_CSLIST IncomingDependencies;       //0x30
  enum _LDR_DDAG_STATE State;                     //0x38
  struct _SINGLE_LIST_ENTRY CondenseLink;         //0x40
  ULONG PreorderNumber;                           //0x48
};

//0x18 bytes (sizeof)
struct _RTL_BALANCED_NODE
{
  union
  {
    // 0x00 0x00
    struct _RTL_BALANCED_NODE *Children[2];
    struct
    {
      // 0x00 0x00
      struct _RTL_BALANCED_NODE *Left;
      // 0x04 0x08
      struct _RTL_BALANCED_NODE *Right;
    };
  };
  // 0x08 0x10
  union
  {
    struct
    {
      UCHAR Red : 1;
      UCHAR Balance : 2;
    };
    ULONGLONG ParentValue;
  };
};

typedef struct _LDR_DATA_TABLE_ENTRY
{
  // 0x00 0x00 (3.10 and higher)
  LIST_ENTRY InLoadOrderLinks;
  // 0x08 0x10 (3.10 and higher)
  LIST_ENTRY InMemoryOrderLinks;
  // 0x10 0x20 (3.10 and higher)
  union
  {
    // 0x10 0x20 (3.10 and higher)
    LIST_ENTRY InInitializationOrderLinks;
    // 0x10 0x20 (6.2 and higher)
    LIST_ENTRY InProgressLinks;
  };
  VOID *DllBase;                      //0x30
  VOID *EntryPoint;                   //0x38
  ULONG SizeOfImage;                  //0x40
  struct _UNICODE_STRING FullDllName; //0x48
  struct _UNICODE_STRING BaseDllName; //0x58
  union
  {
    UCHAR FlagGroup[4]; //0x68
    ULONG Flags;        //0x68
    struct
    {
      ULONG PackagedBinary : 1;          //0x68
      ULONG MarkedForRemoval : 1;        //0x68
      ULONG ImageDll : 1;                //0x68
      ULONG LoadNotificationsSent : 1;   //0x68
      ULONG TelemetryEntryProcessed : 1; //0x68
      ULONG ProcessStaticImport : 1;     //0x68
      ULONG InLegacyLists : 1;           //0x68
      ULONG InIndexes : 1;               //0x68
      ULONG ShimDll : 1;                 //0x68
      ULONG InExceptionTable : 1;        //0x68
      ULONG ReservedFlags1 : 2;          //0x68
      ULONG LoadInProgress : 1;          //0x68
      ULONG LoadConfigProcessed : 1;     //0x68
      ULONG EntryProcessed : 1;          //0x68
      ULONG ProtectDelayLoad : 1;        //0x68
      ULONG ReservedFlags3 : 2;          //0x68
      ULONG DontCallForThreads : 1;      //0x68
      ULONG ProcessAttachCalled : 1;     //0x68
      ULONG ProcessAttachFailed : 1;     //0x68
      ULONG CorDeferredValidate : 1;     //0x68
      ULONG CorImage : 1;                //0x68
      ULONG DontRelocate : 1;            //0x68
      ULONG CorILOnly : 1;               //0x68
      ULONG ChpeImage : 1;               //0x68
      ULONG ChpeEmulatorImage : 1;       //0x68
      ULONG ReservedFlags5 : 1;          //0x68
      ULONG Redirected : 1;              //0x68
      ULONG ReservedFlags6 : 2;          //0x68
      ULONG CompatDatabaseProcessed : 1; //0x68
    };
  };
  USHORT ObsoleteLoadCount;                                //0x6c
  USHORT TlsIndex;                                         //0x6e
  LIST_ENTRY HashLinks;                                    //0x70
  ULONG TimeDateStamp;                                     //0x80
  struct _ACTIVATION_CONTEXT *EntryPointActivationContext; //0x88
  VOID *Lock;                                              //0x90
  struct _LDR_DDAG_NODE *DdagNode;                         //0x98
  LIST_ENTRY NodeModuleLink;                               //0xa0
  struct _LDRP_LOAD_CONTEXT *LoadContext;                  //0xb0
  VOID *ParentDllBase;                                     //0xb8
  VOID *SwitchBackContext;                                 //0xc0
  struct _RTL_BALANCED_NODE BaseAddressIndexNode;          //0xc8
  struct _RTL_BALANCED_NODE MappingInfoIndexNode;          //0xe0
  ULONGLONG OriginalBase;                                  //0xf8
  union _LARGE_INTEGER LoadTime;                           //0x100
  ULONG BaseNameHashValue;                                 //0x108
  enum _LDR_DLL_LOAD_REASON LoadReason;                    //0x10c
  ULONG ImplicitPathOptions;                               //0x110
  ULONG ReferenceCount;                                    //0x114
  ULONG DependentLoadFlags;                                //0x118
  UCHAR SigningLevel;                                      //0x11c
  ULONG CheckSum;                                          //0x120
  VOID *ActivePatchImageBase;                              //0x128
  enum _LDR_HOT_PATCH_STATE HotPatchState;                 //0x130
} LDR_DATA_TABLE_ENTRY;

// ==PEB_LDR_DATA==
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/ntpsapi_x/peb_ldr_data.htm?tx=185
// The PEB_LDR_DATA structure is the defining record of which user-mode modules
// are loaded in a process. It is essentially the head of three double-linked
// lists of LDR_DATA_TABLE_ENTRY structures. Each structure represents one
// loaded module. Each list links through the structures in a different order.
//
//
// Access
//
// Each process has the one PEB_LDR_DATA. Its address is kept in the Ldr member
// of the process’s PEB.
//
// In early versions, the PEB_LDR_DATA is in its own heap allocation that is
// obtained while NTDLL initialises the process. This is wasteful since the
// process will only ever have the one PEB_LDR_DATA. In version 5.2 and higher,
// this one and only PEB_LDR_DATA is an internal variable in the NTDLL data. It
// can be handy, when debugging, to know that the name of this internal variable
// is PebLdr.
//
//
// Documentation Status
//
// In an ideal world, the PEB_LDR_DATA might be opaque outside NTDLL. But
// various high-level modules supplied with Windows over the years have used at
// least one member of the PEB_LDR_DATA, which eventually had to be disclosed.
//
// A new header, named WINTERNL.H, for previously internal APIs was added to the
// Software Development Kit (SDK) apparently in 2002, and remains to this day.
// Anyone competent who was looking at the time, e.g., because they were paid to
// as work for a Technical Committee that was to enforce the settlement that
// compelled the disclosure, might have pointed out the PEB_LDR_DATA as a
// candidate. Somehow, though, it got missed. Make no mistake that I mean here
// that the Technical Committee can only have been incompetent and gullible, or
// have been too tired to avoid the appearance, and that by extension this
// appiles also to the government and court. There is a lesson here for future
// attempts at using anti-trust legislation against “big tech”.
//
// When WINTERNL.H eventually got round to the PEB_LDR_DATA, starting with the
// SDK for Windows 7, it presented only a modified PEB_LDR_DATA that has just
// the InMemoryOrderModuleList member, plus padding that gets this member to the
// same offset as in the true structure. Incomplete as this is, it’s out there
// now, and Microsoft seems unlikely to change the PEB_LDR_DATA in any way that
// moves this member.
//
//
// Layout
//
// Indeed, the PEB_LDR_DATA is surprisingly stable across Windows versions. No
// members have yet moved or even been redefined. The structure has grown only
// by extension. The following table shows the changing sizes:
//
// | Version                       | Size (x86) | Size (x64) |
// |-------------------------------|------------|------------|
// | 3.51 to 5.0                   | 0x24       |            |
// | 5.1 to early 6.0 (before SP1) | 0x28       | 0x48       |
// | late 6.0 to 2004              | 0x30       | 0x58       |
//
// These sizes, and the offsets, types and names in the tables that follow, are
// from public symbol files for the kernel starting with Windows 2000 SP3 and
// for NTDLL starting with Windows XP. Symbol files for earlier versions do not
// contain type information for the PEB_LDR_DATA, but something similar is
// available for a few earlier versions: type information in statically linked
// libraries GDISRVL.LIB for Windows NT 3.51 and SHELL32.LIB for Windows NT 4.0
// (both distributed with their respective editions of the Device Driver Kit);
// and the output of the KDEX2X86 debugger extension’s !strct command for the
// original Windows 2000. Inspection of binaries anyway confirms that all
// members that were in use for Windows 2000 SP3 were used the same way as far
// back as Windows NT 3.1.
//
//
// The Length and Initialized members are set to the size (in bytes) of the
// structure and to TRUE, respectively, when the structure is prepared. They are
// not known to change.
//
// No use is (yet) known of the SsHandle member in any version.
//
// Though EntryInProgress is retained in the symbol files, no use of it is
// known after version 6.1. In earlier versions, what it points to, when it
// points to anything, is a LDR_DATA_TABLE_ENTRY for a DLL whose imports are
// to be resolved. In version 5.1, imports became subject to activation
// contexts. The importing DLL may redirect its imports via a manifest. If a
// callback function for DLL manifest probing has been set by an earlier
// call to the undocumented NTDLL export LdrSetDllManifestProber, then
// EntryInProgress is set while the callback is made.
//
// Though ShutdownThreadId is shown above as a HANDLE, it is indeed a thread
// ID as suggested by its name. It is picked up from the UniqueThread member
// of the CLIENT_ID in the TEB of the thread that asks to terminate the
// process.
typedef struct _PEB_LDR_DATA
{
  // 0x00 0x00 all
  ULONG Length;

  // 0x04 0x04 all
  BOOLEAN Initialized;

  // 0x08 0x08 all
  PVOID SsHandle;

  // 0x0C 0x10 all
  LIST_ENTRY InLoadOrderModuleList;

  // 0x14 0x20 all
  LIST_ENTRY InMemoryOrderModuleList;

  // 0x1C 0x30 all
  LIST_ENTRY InInitializationOrderModuleList;

  // 0x24 0x40 5.1 and higher
  PVOID EntryInProgress;

  // 0x28 0x48 late 6.0 and higher
  BOOLEAN ShutdownInProgress;

  // 0x2C 0x50 late 6.0 and higher
  HANDLE ShutdownThreadId;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

// ==RTL_DRIVE_LETTER_CURDIR==
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/rtl_drive_letter_curdir.htm
// The RTL_DRIVE_LETTER_CURDIR structure (formally _RTL_DRIVE_LETTER_CURDIR) is
// a small structure that is presently thought to be defined in all Windows
// versions but not used in any.
//
// From the name, the intended purpose is for keeping a current directory for
// each drive (letter). This is consistent with the two known references to this
// structure in definitions of other structures.
//
// The better known, e.g., from public symbol files for the kernel, is that the
// RTL_USER_PROCESS_PARAMETERS has an RTL_DRIVE_LETTER_CURDIR array as a member
// named CurrentDirectores. Yes, this misspelling is Microsoft’s and there are
// 32 in the array, not 26. Nesting even one RTL_DRIVE_LETTER_CURDIR in the
// RTL_USER_PROCESS_PARAMETERS means that the former’s definition must be
// available for the latter’s—and the latter is in turn well known for being
// pointed to from the PEB. Public symbols for the kernel, starting with Windows
// 8, confirm that the RTL_DRIVE_LETTER_CURDIR is defined in a header named
// pebteb.h. But no code is (yet) known that uses this array—not in the kernel
// or NTDLL or even further afield, in any version.
//
// Much less well known is that a structure named RTL_PERTHREAD_CURDIR has a
// member named CurrentDirectories which is defined as pointing to an
// RTL_DRIVE_LETTER_CURDIR (or, surely, to an array of them). All known versions
// of 32-bit Windows have code that prepares an RTL_PERTHREAD_CURDIR but no code
// is yet known that initialises the CurrentDirectories pointer to anything but
// NULL. All known versions of Windows, both 32-bit and 64-bit, have code that
// will read an RTL_PERTHREAD_CURDIR (from the SubSystemTib pointer in the
// NT_TIB at the start of a TEB), but no code is yet known that reads the
// CurrentDirectories.
//
// Thus is the RTL_DRIVE_LETTER_CURDIR thought to be defined in all Windows
// versions but not used in any. That a structure is still defined without
// having ever been used is certainly not impossible, but the waste of it
// suggests that more research is required.
//
//
// Layout
//
// The RTL_DRIVE_LETTER_CURDIR is 0x10 and 0x18 bytes in 32-bit and 64-bit
// Windows, respectively, in all known versions. The structure’s name and the
// names and definitions of its members are known from public symbol files for
// the kernel, starting from Windows 2000 SP3. That the definitions apply also
// to earlier versions is a guess based on nothing more than the apparent
// reservation of the right amount of space in the RTL_USER_PROCESS_PARAMETERS
// all the way back to version 3.10.
typedef struct _RTL_DRIVE_LETTER_CURDIR
{
  WORD Flags;
  WORD Length;
  DWORD TimeStamp;
  STRING DosPath;
  // What any of these members mean—or were ever meant to mean—is not known, no
  // code having yet been found that accesses the structure whether in the
  // CurrentDirectores array or through the CurrentDirectories pointer.
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

// ==CURDIR==
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/curdir.htm?tx=179
// The CURDIR structure (formally _CURDIR) is a small structure that is known
// only within the RTL_USER_PROCESS_PARAMETERS. It there models its process’s
// notion of a current directory.
//
// The CURDIR is 0x0C and 0x18 bytes in 32-bit and 64-bit Windows, respectively.
//
// The Handle member records that Windows ordinarily keeps an open file handle
// to a process’s current directory. This is a useful optimisation for programs
// that are aware of having a current directory and may use relative pathnames
// when working with files. It can be problematic for programs that have no such
// awareness or do not provide easy means of changing the current directory. For
// instance, open a Command Prompt, create a directory, make it the current
// directory, run a simple program such as Notepad, change the Command Prompt to
// some other current directory and then try to remove the created directory:
//
// md path\test
// cd path\test
// notepad
// cd ..
// rd test
//
// You can expect to be told something like
// The process cannot access the file because it is being used by another process.
// In this case, Notepad has the created directory open as Notepad’s current directory. In real-world use of Windows it can be far from obvious what can be this “another process.”
typedef struct _CURDIR
{
  UNICODE_STRING DosPath;
  HANDLE Handle;
} CURDIR, *PCURDIR;

// ==RTL_USER_PROCESS_PARAMETERS==
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/rtl_user_process_parameters.htm?tx=179
// The RTL_USER_PROCESS_PARAMETERS structure (formally
// _RTL_USER_PROCESS_PARAMETERS) is the low-level packaging of the numerous
// arguments and parameters that can be specified to such Win32 API functions as
// CreateProcess.
//
// By the phrase “low-level packaging” I mean very deliberately that the
// structure is not specifically a packaging for the transition to and from
// kernel mode. Ask almost anyone in the last decade or more for a potted
// description of the RTL_USER_PROCESS_PARAMETERS, and you can expect to hear
// that these are parameters that are passed from user mode to kernel mode for
// handling the NtCreateUserProcess and ZwCreateUserProcess functions, and that
// the kernel creates a copy in the created process’s address space where it is
// then available in user mode through the created process’s PEB. This, however,
// is not the history. Even now, it is not the full story. The clue is in the
// name, specifically in the RTL prefix.
//
// For the first decade and more of Windows history, the
// RTL_USER_PROCESS_PARAMETERS structure does not cross between user and kernel
// modes as anything other than an uninterpreted blob that the creating process
// copies into the created process’s address space. The structure exists only as
// input to the RtlCreateUserProcess function. This Run Time Library (RTL)
// function is exported by name from NTDLL in all Windows versions, right from
// the beginning with version 3.10. It also exists in all versions of the
// kernel, but only as an internal routine which the kernel uses for starting
// the first user-mode process (and which is in a section that the kernel
// discards soon afterwards).
//
//
// Variability
//
// Presumably because of its role as input to an API function, albeit an
// undocumented one, the RTL_USER_PROCESS_PARAMETERS structure is strikingly
// stable. Indeed, while the RtlCreateUserProcess function was the only means of
// creating a user-mode process, its input structure did not change at all.
// Since then, the structure’s only variability is that new members are
// appended:
//
// | Version      | Size (x86) | Size (x64) |
// |--------------|------------|------------|
// | 3.10 to 5.2  | 0x0290     | 0x03F0     |
// | 6.0          | 0x0294     | 0x03F8     |
// | 6.1          | 0x0298     | 0x0400     |
// | 6.2 to 6.3   | 0x02A0     | 0x0410     |
// | 10.0 to 1803 | 0x02A4     | 0x0410     |
// | 1809         | 0x02AC     | 0x0420     |
// | 1903         | 0x02BC     | 0x0440     |
// | 2004         | 0x02C0     | 0x0440     |
//
//
// Layout
//
// These sizes, and the offsets, names and types of members in the table below,
// are from Microsoft’s public symbol files for the kernel starting with Windows
// 2000 SP3.
//
// For versions that predate the availability of type information in symbol
// files, continuity with the known definition for later versions is confirmed
// by inspection of the implementations and uses of RtlCreateUserProcess. For a
// handful of these early versions, the continuity can be established more
// readily. For instance, the import libraries GDISRVL.LIB and SHELL32.LIB that
// Microsoft supplied with the Device Driver Kit (DDK) for Windows NT 3.51 and
// 4.0, respectively, have an early form of type information, including for
// RTL_USER_PROCESS_PARAMETERS.
typedef struct _RTL_USER_PROCESS_PARAMETERS
{
  // 0x00 0x00 (all)
  ULONG MaximumLength;
  // 0x04 0x04 (all)
  ULONG Length;
  // 0x08 0x08 (all)
  ULONG Flags;
  // 0x0C 0x0C (all)
  ULONG DebugFlags;
  // 0x10 0x10 (all)
  HANDLE ConsoleHandle;
  // 0x14 0x18 (all)
  ULONG ConsoleFlags;
  // 0x18 0x20 (all)
  HANDLE StandardInput;
  // 0x1C 0x28 (all)
  HANDLE StandardOutput;
  // 0x20 0x30 (all)
  HANDLE StandardError;
  // 0x24 0x38 (all)
  CURDIR CurrentDirectory;
  // 0x30 0x50 (all)
  UNICODE_STRING DllPath;
  // 0x38 0x60 (all)
  UNICODE_STRING ImagePathName;
  // 0x40 0x70 (all)
  UNICODE_STRING CommandLine;
  // 0x48 0x80 (all)
  PVOID Environment;
  // 0x4C 0x88 (all)
  ULONG StartingX;
  // 0x50 0x8C (all)
  ULONG StartingY;
  // 0x54 0x90 (all)
  ULONG CountX;
  // 0x58 0x94 (all)
  ULONG CountY;
  // 0x5C 0x98 (all)
  ULONG CountCharsX;
  // 0x60 0x9C (all)
  ULONG CountCharsY;
  // 0x64 0xA0 (all)
  ULONG FillAttribute;
  // 0x68 0xA4 (all)
  ULONG WindowFlags;
  // 0x6C 0xA8 (all)
  ULONG ShowWindowFlags;
  // 0x70 0xB0 (all)
  UNICODE_STRING WindowTitle;
  // 0x78 0xC0 (all)
  UNICODE_STRING DesktopInfo;
  // 0x80 0xD0 (all)
  UNICODE_STRING ShellInfo;
  // 0x88 0xE0 (all)
  UNICODE_STRING RuntimeData;
  // 0x90 0xF0 (all)
  RTL_DRIVE_LETTER_CURDIR CurrentDirectores[RTL_MAX_DRIVE_LETTERS];

  // 0x0290 0x03F0 (6.0 and higher)
  ULONG_PTR EnvironmentSize;
  // 0x0294 0x03F8 (6.1 and higher)
  ULONG_PTR EnvironmentVersion;
  // 0x0298 0x0400 (6.2 and higher)
  PVOID PackageDependencyData;
  // 0x029C 0x0408 (6.2 and higher)
  ULONG ProcessGroupId;
  // 0x02A0 0x040C (10.0 and higher)
  ULONG LoaderThreads;
  // 0x02A4 0x0410 (1809 and higher)
  UNICODE_STRING RedirectionDllName;
  // 0x02AC 0x0420 (1903 and higher)
  UNICODE_STRING HeapPartitionName;
  // 0x02B4 0x0430 (1903 and higher)
  ULONGLONG *DefaultThreadpoolCpuSetMasks;
  // 0x02B8 0x0438 (1903 and higher)
  ULONG DefaultThreadpoolCpuSetMaskCount;
  // 0x02BC 0x043C (2004 and higher)
  ULONG DefaultThreadpoolThreadMaximum;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB_FREE_BLOCK
{
  struct _PEB_FREE_BLOCK *Next;
  ULONG Size;
} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

typedef struct _ACTIVATION_CONTEXT_DATA ACTIVATION_CONTEXT_DATA;
typedef struct _ASSEMBLY_STORAGE_MAP ASSEMBLY_STORAGE_MAP;
typedef struct _FLS_CALLBACK_INFO FLS_CALLBACK_INFO;
typedef struct _LEAP_SECOND_DATA LEAP_SECOND_DATA;

// ==PEB==
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/peb/index.htm
//
// The Process Environment Block (PEB) is a process’s user-mode representation.
// It has the highest-level knowledge of a process in kernel mode and the
// lowest-level in user mode. The PEB is created by the kernel but is mostly
// operated on from user mode. If a (system) process has no user-mode footprint,
// it has no PEB. If only in principle, if anything about a process is shared
// with kernel mode but can be properly managed in user mode without needing a
// transition to kernel mode, it goes in the PEB. If anything about a process
// might usefully be shared between user-mode modules, then it’s at least a
// candidate for going in the PEB for easy access. Very much more in principle
// than in practice, data may go into the PEB for sharing between processes more
// easily than by any formal inter-process communication.
//
//
// Access
//
// User-mode code can easily find its own process’s PEB, albeit only by using
// undocumented or semi-documented behaviour. While a thread executes in user
// mode, its fs or gs register, for 32-bit and 64-bit code respectively,
// addresses the thread’s TEB. That structure’s ProcessEnvironmentBlock member
// holds the address of the current process’s PEB. In NTDLL version 5.1 and
// higher, this simple work is available more neatly as an exported function,
// named RtlGetCurrentPeb, but it too is undocumented. Its implementation is
// something very like
//
// PEB *RtlGetCurrentPeb (VOID)
// {
//     return NtCurrentTeb () -> ProcessEnvironmentBlock;
// }
//
// For its own low-level user-mode programming, Microsoft has long had a macro
// or inlined routine, apparently named NtCurrentPeb, which reads directly from
// fs or gs, e.g.,
//
// PEB *NtCurrentPeb (VOID)
// {
//     return (PEB *) __readfsdword (FIELD_OFFSET (TEB, ProcessEnvironmentBlock));
// }
//
// The difference between an exported function (RtlGetCurrentPeb) and a macro or
// inlined routine (NtCurrentPeb) scarcely matters at run time but has forensic
// significance because use of the latter in a high-level module, e.g., for
// MSHTML.DLL from Internet Explorer 6, not only shows that Microsoft’s
// application programmers had undocumented knowledge of the PEB and TEB but
// also suggests they had access to otherwise private headers (if not to use
// them in their build, then at least to reproduce from them).
//
//
// Other Processes
//
// User-mode code can less easily access the PEB of any process for which it has
// a handle and sufficient access rights. The gatekeeper is the
// NtQueryInformationProcess function. This is exported by NTDLL in all known
// Windows versions. Its ProcessBasicInformation case fills a
// PROCESS_BASIC_INFORMATION structure whose member named PebBaseAddress is,
// unsurprisingly, the address of the queried process’s PEB. Of course, the
// address thus obtained is not directly usable. It is meaningful in the queried
// process’s address space. Even just to read that process’s PEB then requires
// such functions as ReadProcessMemory and the corresponding permission. To do
// much with what’s read may require synchronisation with or defence against
// changes being made by the queried process’s own threads—and writing to the
// queried process’s PEB certainly requires such synchronisation. In
// consequence, safe use of another process’s PEB is beyond many programers who
// attempt it, e.g., for malware and more notably for some of what gets foisted
// onto consumers as anti-malware or merely recommended to them as supposedly
// helpful system tools.
//
//
// Documentation Status
//
// In an ideal world, the PEB might be opaque outside the kernel and a few
// low-level user-mode modules such as NTDLL and KERNEL32. But, as noted in
// remarks above about forsensic signfiicance, various high-level modules
// supplied with Windows over the years have used a few members of the PEB, and
// this eventually had to be disclosed. A new header, named WINTERNL.H, for
// previously internal APIs was added to the Software Development Kit (SDK)
// apparently in 2002 as the main (if insubstantial) outcome of an anti-trust
// settlement, and remains to this day. It originally presented a modified PEB
// that has just the BeingDebugged and SessionId members, plus padding that gets
// these members to the same offsets as in the true structure. More members have
// been included in this modified PEB over the years: Ldr, ProcessParameters and
// PostProcessInitRoutine in the SDK for Windows 7; and AtlThunkSListPtr and
// AtlThunkSListPtr32 in the SDK for Windows 8. Notwithstanding the header’s
// warnings, it seems unlikely that Microsoft will change the PEB in any way
// that moves any of these members.
//
//
// Layout
//
// Indeed, the PEB is highly stable across Windows versions. When members fall
// out of use the space they occupied tends to be left in place, often to be
// reused eventually, but without shifting other members. Many members that are
// useful—to know about not just when debugging but also when studying
// malware—have kept their positions through all the known history. The PEB has
// grown mostly by adding new members at its end. The following sizes are known
// (with caveats that follow the table):
//
// | Version              | Size (x86) | Size (x64) | Comment                   |
// |----------------------|------------|------------|---------------------------|
// | 3.10                 | 0x70       |            |                           |
// | 3.50                 | 0x70       |            |                           |
// | 3.51                 | 0x98       |            |                           |
// | 4.0                  | 0x0150     |            |                           |
// | 5.0                  | 0x01E8     |            |                           |
// | 5.1 to 5.1 SP1       | 0x0210     |            | early 5.1 (before SP2)    |
// | 5.1 SP2 to 5.1 Final | 0x0210     |            | late 5.1 (SP2 and higher) |
// | 5.2                  | 0x0230     | 0x0358     | early 5.2 (before SP1)    |
// | 5.2 SP1 to 5.2 Final | 0x0230     | 0x0358     | late 5.2 (SP1 and higher) |
// | 6.0                  | 0x0238     | 0x0368     |                           |
// | 6.1                  | 0x0248     | 0x0380     |                           |
// | 6.2 to 10.0          | 0x0250     | 0x0388     |                           |
// | 10.0 1511 to 1703    | 0x0460     | 0x07A0     |                           |
// | 10.0 1709            | 0x0468     | 0x07B0     |                           |
// | 10.0 1803            | 0x0470     | 0x07B8     |                           |
// | 10.0 1809 to 2004    | 0x0480     | 0x07C8     |                           |
//
// These sizes, and the offsets, types and names in the tables that follow, are
// from Microsoft’s symbol files for the kernel starting with Windows 2000 SP3
// and for NTDLL starting with Windows XP, but are something of a guess for
// earlier versions since the symbol files for these do not contain type
// information for the PEB. What’s known of Microsoft’s names and types for
// earlier versions is instead inferred from what use NTOSKRNL and various
// low-level user-mode modules such as NTDLL are seen to make of the PEB.
// Exhaustively tracking down all such use would be difficult, if not
// impossible, even with source code.
typedef struct _PEB
{
  // Original (More or Less)
  //
  // The very first member is arguably too much overlooked, given that so many
  // programmers with backgrounds in Unix seem to think that assessment of Windows
  // as an operating system begins and ends with whether Windows truly can fork a
  // process. It is here thought to have been followed by unlabelled alignment
  // space until version 3.51 defined the next two booleans.

  // 0x00 0x00 (all)
  BOOLEAN InheritedAddressSpace;
  // 0x01 0x01 (3.51 and higher)
  BOOLEAN ReadImageFileExecOptions;
  // 0x02 0x02 (3.51 and higher)
  BOOLEAN BeingDebugged;
  union // https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/peb/bitfield.htm
  {
    // 0x03 0x03 (3.51 to early 5.2)
    BOOLEAN SpareBool;
    union
    {
      // 0x03 0x03 (late 5.2 and higher)
      UCHAR BitField;
      struct
      {
        // 0x01 (late 5.2 and higher)
        UCHAR ImageUsedLargePages : 1;
        UCHAR SpareBits_0x03_00 : 7;
      };
      struct
      {
        UCHAR SpareBits_0x03_01 : 1;
        // 0x02 (6.0 and higher)
        UCHAR IsProtectedProcess : 1;
        UCHAR SpareBits_0x03_02 : 6;
      };
      struct
      {
        UCHAR SpareBits_0x03_03 : 2;
        // 0x04 (6.0 to 6.2)
        UCHAR IsLegacyProcess : 1;
        UCHAR SpareBits_0x03_04 : 5;
      };
      struct
      {
        UCHAR SpareBits_0x03_05 : 2;
        // 0x04 (6.3 and higher)
        UCHAR IsImageDynamicallyRelocated_6_3 : 1;
        // 0x08 (6.0 to 6.2)
        UCHAR IsImageDynamicallyRelocated_6_0 : 1;
        UCHAR SpareBits_0x03_06 : 4;
      };
      struct
      {
        UCHAR SpareBits_0x03_07 : 3;
        // 0x08 (6.3 and higher)
        UCHAR SkipPatchingUser32Forwarders_6_3 : 1;
        // 0x10 (late 6.0 to 6.2);
        UCHAR SkipPatchingUser32Forwarders_6_0_SPx : 1;
        UCHAR SpareBits_0x03_08 : 3;
      };
      struct
      {
        UCHAR SpareBits_0x03_09 : 4;
        // 0x10 (6.3 and higher)
        UCHAR IsPackagedProcess_6_3 : 1;
        // 0x20 (6.2)
        UCHAR IsPackagedProcess_6_2 : 1;
        UCHAR SpareBits_0x03_10 : 2;
      };
      struct
      {
        UCHAR SpareBits_0x03_11 : 5;
        // 0x20 (6.3 and higher)
        UCHAR IsAppContainer_6_3 : 1;
        // 0x40 (6.2)
        UCHAR IsAppContainer_6_2 : 1;
        UCHAR SpareBits_0x03_12 : 1;
      };
      struct
      {
        UCHAR SpareBits_0x03_13 : 6;
        // 0x40 (6.3 and higher)
        UCHAR IsProtectedProcessLight : 1;
        // 0x80 (10.0 1607 and higher)
        UCHAR IsLongPathAwareProcess : 1;
      };
    };
  };
#ifdef _WIN64
  // none 0x04 (6.3 and higher)
  UCHAR Padding0[4];
#endif
  // 0x04 0x08 (all)
  HANDLE Mutant;
  // These first eight bytes of the PEB have a separate identity as an
  // INITIAL_PEB structure, apparently only for passing parameters to the
  // kernel’s internal routine that creates a PEB. No trace of this INITIAL_PEB
  // ever shows in public symbol files but it is known from the USERKDX debugger
  // extension that Microsoft supplied with the Device Driver Kit (DDK) for
  // Windows NT 4.0 and again for Windows 2000.
  //
  // The kernel sets BeingDebugged to indicate that the process has a debug
  // port. The (documented) KERNEL32 function IsDebuggerPresent does nothing
  // more than read BeingDebugged from the current PEB.

  // Whether the byte at offset 0x03 was labelled explicitly as a spare boolean
  // concurrently with definition of the two booleans at offsets 0x01 and 0x02
  // is not certain but is at least plausible. It anyway never was used as a
  // boolean but started getting used as bit fields in the build of version 5.2
  // that first put the CPU’s support for large pages to use as an efficiency
  // for executable images. The individual bits are presented separately,
  // description being complicated because Windows 8.1 deleted one of them
  // (IsLegacyProcess) and thus changed the masks for accessing the others.

  // 0x08 0x10 (all)
  PVOID ImageBaseAddress;
  // 0x0C 0x18 (all)
  PEB_LDR_DATA *Ldr;
  // 0x10 0x20 (all)
  RTL_USER_PROCESS_PARAMETERS *ProcessParameters;
  // 0x14 0x28 (all)
  PVOID SubSystemData;
  // 0x18 0x30 (all)
  PVOID ProcessHeap;
  // Of the original PEB members, Ldr and ProcessParameters are arguably the
  // most used by Microsoft’s higher-level modules and Microsoft eventually
  // included them in the reduced PEB that’s published in WINTERNL.H for all the
  // world to know about. In any world in which such publication had any
  // self-consistency, the ProcessHeap wouldn’t be far behind: the ancient
  // (documented) KERNEL32 function GetProcessHeap has always done nothing more
  // than read ProcessHeap from the current PEB, but very many Microsoft
  // programs and DLLs instead read ProcessHeap by themselves (as if
  // GetProcessHeap is inlined for their use).
  //
  // At the other extreme, the SubSystemData is about as obscure as anything
  // gets in Windows programming for ordinary purposes. As its name suggests, it
  // is intended for subsystems that don’t have enough of Microsoft’s attention
  // to justify defining their own members in the PEB itself. A subsystem, such
  // as supported by PSXDLL.DLL, can point SubSystemData at its own collection
  // of per-process data.

  union
  {
#ifndef _WIN64
    // 0x1C none (3.10 to 5.0)
    struct
    {
      PVOID FastPebLock;
    } nt_3_10_p1;
#endif
    // 0x1C 0x38 (5.1 and higher)
    PRTL_CRITICAL_SECTION FastPebLock;
  };
  union
  {
#ifndef _WIN64
    // 0x20 none (3.10 to 5.1)
    PVOID FastPebLockRoutine;
    // 0x20 none (early 5.2 only)
    PVOID SparePtr1;
#endif
    // 0x20 0x40 (late 5.2 and higher)
    PVOID AtlThunkSListPtr;
  };
  union
  {
#ifndef _WIN64
    // 0x24 0x48 (3.10 to 5.1)
    PVOID FastPebUnlockRoutine;
#endif
    // 0x24 0x48 (5.2 only)
    PVOID SparePtr2;
    // 0x24 0x48 (6.0 and higher)
    PVOID IFEOKey;
  };
  // In early versions, NTDLL supports its exported (undocumented)
  // RtlAcquirePebLock and RtlReleasePebLock functions by storing in the PEB the
  // addresses not just of a FastPebLock variable in the NTDLL data but of two
  // routines for acquiring and releasing whatever is this lock. Though it does
  // happen that the lock is a critical section and the routines are just the
  // expected RtlEnterCriticalSection and RtlLeaveCriticalSection, not until
  // version 5.1 is the lock’s nature formalised in the PEB and not until
  // version 5.2 does NTDLL stop saving the routines’ addresses in the PEB.
  //
  // You might wonder why they ever were saved in the PEB. After all, the
  // RtlAcquirePebLock and RtlReleasePebLock functions ought to suffice for
  // Microsoft’s user-mode code that’s outside NTDLL and wants to synchronise
  // its access to the PEB with access by other threads in the same process.
  // What fascinates me, and prompts this digression, is that the only use I
  // know of FastPebLock from outside NTDLL is in kernel mode. Moreover, it also
  // uses the long-gone FastPebLockRoutine and FastPebUnlockRoutine members. Go
  // back far enough and this is done by linking the exact same implementations
  // of the RtlAcquirePebLock and RtlReleasePebLock functions into both NTDLL
  // and the kernel—yes, with the kernel finding the PEB from the TEB, in turn
  // found from the fs register as described above. Version 5.1 re-implemented
  // so that the kernel instead progresses through structures that have no
  // user-mode susceptibility, thus from the fs register to the KPCR to the
  // KTHREAD to the EPROCESS for its pointer to the PEB. If this change was
  // motivated by thoughts of security, it was worse than pointless because the
  // kernel does not just follow the FastPebLockRoutine and FastPebUnlockRoutine
  // pointers in the PEB but calls through them to execute (what it hopes to be)
  // NTDLL code at its user-mode address. Do not miss that whatever is there
  // gets executed with ring 0 privilege.

  // This trick that is plainly too clever for anyone’s good was ended for
  // version 5.2 in 2003, which surely is everyone’s gain, yet it was retained
  // even for the long-lived last service pack of version 5.1 in 2008,
  // apparently without Microsoft ever warning anyone of it. In the very
  // earliest versions, it had extensive use. Among the reasons the kernel would
  // access the PEB in ways that needed synchronisation with access by other
  // threads (most likely in user mode) were such things as the kernel
  // allocating from and freeing to the process heap. Even as late as version
  // 5.1, this execution of user-mode code with kernel-mode prvilege was still
  // being done for the exported (and documented) function
  // RtlQueryRegistryValues to expand environment variables whose names are
  // found between percent signs in registry data that has the REG_EXPAND_SZ
  // type.

  // Can it really be that Microsoft was never called out for this
  // grotesqueness?

  //  0x28 0x50 (all)
  union
  {
#ifndef _WIN64
    // 0x28 none (3.10 only) unaccounted 0x10 bytes
    struct
    {
      BYTE Unaccounted[0x10];
    } nt_3_10_p2;
#endif
    // 0x28 0x50 (3.50 and higher)
    struct
    {
      // 0x28 0x50 (3.50 and higher)
      union
      {
        // 0x28 none (3.50 to 5.2)
        ULONG EnvironmentUpdateCount;
        // 0x28 0x50 (6.0 and higher)
        ULONG CrossProcessFlags;
        struct // https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/peb/crossprocessflags.htm
        {
          // 0x00000001 (6.0 and higher)
          ULONG ProcessInJob : 1;
          // 0x00000002 (6.0 and higher)
          ULONG ProcessInitializing : 1;
          // 0x00000004 (6.1 and higher)
          ULONG ProcessUsingVEH : 1;
          // 0x00000008 (6.1 and higher)
          ULONG ProcessUsingVCH : 1;
          // 0x00000010 (6.1 and higher)
          ULONG ProcessUsingFTH : 1;
          // 0x00000020 (1703 and higher)
          ULONG ProcessPreviouslyThrottled : 1;
          // 0x00000040 (1703 and higher)
          ULONG ProcessCurrentlyThrottled : 1;
          // 0x00000080 (1809 and higher)
          ULONG ProcessImagesHotPatched : 1;
          ULONG ReservedBits0 : 24;
        };
      };
#ifdef _WIN64
      // none 0x54 (6.3 and higher)
      UCHAR Padding1[4];
#endif
      // 0x2C 0x58 (3.50 and higher)
      union
      {
#ifndef _WIN64
        // 0x2C none (3.50 only) unaccounted four bytes
        struct
        {
          BYTE Unaccounted[4];
        } nt_3_50_p1;
#endif
        // 0x2C 0x58 (3.51 and higher)
        PVOID KernelCallbackTable;
        // 0x2C 0x58 (6.0 and higher)
        PVOID UserSharedInfoPtr;
      };
      // 0x30 0x60 (3.50 and higher)
      union
      {
#ifndef _WIN64
        // 0x30 none (3.50 to 4.0)
        HANDLE EventLogSection;
#endif
        // 0x30 0x60 (5.0 and higher)
        ULONG SystemReserved0;
      };
      // 0x34 0x64 (3.50 and higher)
      union
      {
#ifndef _WIN64
        // 0x34 none (3.50 to 4.0)
        PVOID EventLog;
        // 0x34 none (5.0 only)
        ULONG SystemReserved1;
        // 0x34 none (early 5.1; early 5.2)
        struct
        {
          // 0x00000003
          ULONG ExecuteOptions : 2;
          ULONG SpareBits_0x34 : 30;
        };
#endif
        // 0x34 0x64 (late 5.2 to 6.0)
        ULONG SpareUlong;
        // 0x34 0x64 (late 5.1; 6.1 and higher)
        ULONG AtlThunkSListPtr32;
      };
    };
  };

  // No use is known of the preceding 0x10 bytes in version 3.10. It seems
  // more than merely plausible that the explicit reservation of two dwords as
  // SystemReserved, as known from symbol files for late service packs of
  // Windows 2000, started as four.
  //
  // In those versions that have it, the EnvironmentUpdateCount is incremented
  // when an attempt to set the current directory gets as far as NTDLL’s
  // RtlSetCurrentDirectory_U function. What this has to do with any sort of
  // environment is not known. Windows Vista anyway replaced this counter with
  // a set of flags.
  //
  // What KernelCallbackTable points to is an array of function pointers to
  // support the exported (undocumented) KiUserCallbackDispatcher function.
  // This is one of the relatively few functions that NTDLL exports not to be
  // imported by other user-mode modules but to be found by the kernel. The
  // function is called by the kernel when a driver, typically WIN32K.SYS,
  // calls the kernel export KeUserModeCallback. Of course, the NTDLL function
  // is not actually called by the kernel. It instead becomes the target
  // address for the kernel’s exit from ring 0 to ring 3. Still,
  // KiUserCallbackDispatcher perceives that it has been called and that among
  // its arguments is an index into the KernelCallbackTable. This selects
  // where further to dispatch the execution deeper into user mode. Getting
  // back to kernel mode with the appearance of returning from a call to user
  // mode is important enough to have a dedicated interrupt number, 0x2B.
  //
  // The array of function pointers that is the KernelCallbackTable is set
  // into place by USER32.DLL during its initialisation, but not until after
  // USER32 connects to the CSRSS server. Starting with version 6.0, if the
  // process is a so-called protected process, the KernelCallbackTable pointer
  // is first put to double duty as the UserSharedInfoPtr. Just while
  // connecting, it becomes a side-channel for receiving a SHAREDINFO
  // structure directly from WIN32K.SYS.
  //
  // Windows XP and Windows Server 2003 got into some sort of tussle about
  // using the last of the previously reserved dwords. The ExecuteOptions
  // certainly are used in the early releases of both. These two bits do not,
  // however, have the same meaning as later flags for the Data Execution
  // Prevention (DEP) that came with the late builds of these versions. They
  // are concerned instead with checking for stack overflow.
  union
  {
    // 0x38 0x68 (3.10 to early 6.0)
    PEB_FREE_BLOCK *FreeList;
    // 0x38 0x68 (late 6.0 only)
    ULONG SparePebPtr0;
    // 0x38 0x68 (6.1 and higher)
    PVOID ApiSetMap;
  };
  // The PEB_FREE_BLOCK is simply a pointer to the Next of its type, presumably
  // to make a single-linked list, and a 32-bit unsigned Size. The suggestion is
  // of caching freed memory, but although FreeList is defined in symbol files,
  // no use is known of it in any version. The ApiSetMap that replaces it is the
  // process’s pointer to the kernel’s representation of the API Set Schema of
  // redirections that NTDLL is to apply when loading DLLs. What the kernel
  // points ApiSetMap to is a read-only mapping into the process’s address
  // space. Pointing ApiSetMap elsewhere would seem to be not just possible but
  // attractive, whether for mischief or for the supposedly well-intentioned
  // intrusiveness of security tools as an alternative to hooking API functions
  // by such techniques as patching code.

  // 0x3C 0x70 (all)
  ULONG TlsExpansionCounter;
#ifdef _WIN64
  // none 0x74 (6.3 and higher)
  UCHAR Padding2[4];
#endif
  // 0x40 0x78 (all)
  PVOID TlsBitmap;
  // 0x44 0x80 (all)
  ULONG TlsBitmapBits[2];
  // 0x4C 0x88 (all)
  PVOID ReadOnlySharedMemoryBase;
  union
  {
    // 0x50 0x90 (3.10 to 5.2)
    PVOID ReadOnlySharedMemoryHeap;
    // 0x50 0x90 (6.0 to 6.2)
    PVOID HotpatchInformation;
    // 0x50 0x90 (6.3 to 1607)
    PVOID SparePvoid0;
    // 0x50 0x90 (1703 and higher)
    PVOID SharedData;
  };
  // 0x54 0x98 (all)
  PVOID *ReadOnlyStaticServerData;
  // 0x58 0xA0 (all)
  PVOID AnsiCodePageData;
  // 0x5C 0xA8 (all)
  PVOID OemCodePageData;
  // 0x60 0xB0 (all)
  union
  {
#ifndef _WIN64
    // 0x60 none (3.10 to 3.50)
    struct
    {
      // 0x60 none (3.10 to 3.50)
      PVOID UnicodeCaseTableData;
      // 0x68 none (3.10 to 3.50);
      LARGE_INTEGER CriticalSectionTimeout;
    } nt_3_10;
#endif
    // 0x60 0xB0 (3.51 and higher)
    struct
    {
      // 0x60 0xB0 (all)
      PVOID UnicodeCaseTableData;
      // 0x64 0xB8 (3.51 and higher)
      ULONG NumberOfProcessors;
      // 0x68 0xBC (3.51 and higher)
      ULONG NtGlobalFlag;
      // 0x70 0xC0 (3.51 and higher)
      LARGE_INTEGER CriticalSectionTimeout;
    };
  };
  // The NtGlobalFlag member is intially the process’s copy of the kernel’s
  // (exported) NtGlobalFlag variable as it was when the kernel created the PEB.
  //
  // Before version 5.0, having an NtGlobalFlag in the PEB is nothing but a
  // convenience for NTDLL to initialise its own (internal) NtGlobalFlag
  // variable without having to call through NtQuerySystemInformation. It’s the
  // internal variable that gets per-processor adjustments, e.g., from the
  // GlobalFlag value in the Image File Execution Options or from applicable
  // fields in the Configuration Directory. It’s the internal variable that
  // matters. The NtGlobalFlag in the PEB can be just a stale record of what the
  // process started with.
  //
  // See that version 3.51 didn’t just append new members but instead inserted
  // two. One was in what looks to have been unused alignment space, but the
  // other turns CriticalSectionTimeout into the oldest known case of any PEB
  // member shifting between versions.

  //
  //
  // Appended for Windows NT 3.51
  //
  // 0x78 0xC8 (3.51 and higher)
  ULONG_PTR HeapSegmentReserve;
  ULONG_PTR HeapSegmentCommit;
  ULONG_PTR HeapDeCommitTotalFreeThreshold;
  ULONG_PTR HeapDeCommitFreeBlockThreshold;
  ULONG NumberOfHeaps;
  ULONG MaximumNumberOfHeaps;
  // 0x90 0xF0 (3.51 and higher)
  PVOID *ProcessHeaps;

  //
  //
  // Appended for Windows NT 4.0
  //
  // 0x94 0xF8 (4.0 and higher)
  PVOID GdiSharedHandleTable;
  // 0x98 0x0100 (4.0 and higher)
  PVOID ProcessStarterHelper;
  ULONG GdiDCAttributeList;
#ifdef _WIN64
  UCHAR Padding3[4];
#endif
  // 0xA0 0x0110 (4.0 and higher)
  union
  {
#ifndef _WIN64
    // 0xA0 0x0110 (4.0 to 5.1)
    struct
    {
      PVOID LoaderLock;
    } nt_4_0_p1;
#endif
    RTL_CRITICAL_SECTION *LoaderLock;
  };
  ULONG OSMajorVersion;
  ULONG OSMinorVersion;
  USHORT OSBuildNumber;
  USHORT OSCSDVersion;
  ULONG OSPlatformId;
  ULONG ImageSubsystem;
  ULONG ImageSubsystemMajorVersion;
  ULONG ImageSubsystemMinorVersion;
#ifdef _WIN64
  UCHAR Padding4[4];
#endif
  union
  {
    KAFFINITY ImageProcessAffinityMask;
    KAFFINITY ActiveProcessAffinityMask;
  };
#ifndef _WIN64
  // 0xC4 0x0140 (4.0 and higher)
  ULONG GdiHandleBuffer[0x22];
#else
  // 0xC4 0x0140 (all)
  ULONG GdiHandleBuffer[0x3C];
#endif
  // The point to the several members starting at OSMajorVersion is very much
  // that they need not be truly the operating system’s version numbers. They
  // can instead be whatever version numbers are meant to be perceived by
  // user-mode code in the process. Whether this happens depends on the
  // Win32VersionValue in the image header of the process’s executable. To this
  // day, 30th March 2019, Microsoft’s documentation would have it that “this
  // member is reserved and must be 0.” If, however, it is non-zero, as can have
  // been arranged using the linker’s undocumented /win32version switch, then
  // the kernel overrides the true Windows version numbers that would otherwise
  // be set into these PEB members:
  //
  // * OsMajorVersion from bits 0 to 7 of the Win32VersionValue;
  // * OSMinorVersion from bits 8 to 15;
  // * OSBuildNumber from bits 16 to 29;
  // * OSCSDVersion from the CSDVersion member of the
  //   IMAGE_LOAD_CONFIG_DIRECTORY, if non-zero, in version 5.0 and higher;
  // * OSPlatformId from bits 30 to 31 of the Win32VersionValue, with 0, 1, 2
  //   and 3 mapping respectively to 2 (VER_PLATFORM_WIN32_NT), 3, 0 and 1.

  //
  //
  // Appended for Windows 2000
  //
  // 0x014C 0x0230 (5.0 and higher)
  VOID (*PostProcessInitRoutine)(VOID);
  // 0x0150 0x0238 (5.0 and higher)
  PVOID TlsExpansionBitmap;
  ULONG TlsExpansionBitmapBits[0x20];
  // 0x01D4 0x02C0 (5.0 and higher)
  ULONG SessionId;
#ifdef _WIN64
  // none 0x02C4 (6.3 and higher)
  UCHAR Padding5[4];
#endif
  // The SessionId is one of the two PEB members that Microsoft documented when
  // required to disclose use of internal APIs by so-called middleware.
  //
  // Insertion of the next three members for Windows XP produces the last known
  // case of members whose offset varies between versions. Don’t miss the irony
  // that this was done in the name of application compatibility.
  union
  {
#ifndef _WIN64
    struct
    {
      // 0x01D8 none (5.0 only)
      PVOID AppCompatInfo;
      // 0x01DC none (5.0 only)
      UNICODE_STRING CSDVersion;
    } nt_5_0;
#endif
    struct
    {
      // 0x01D8 0x02C8 (5.1 and higher)
      ULARGE_INTEGER AppCompatFlags;
      // 0x01E0 0x02D0 (5.1 and higher)
      ULARGE_INTEGER AppCompatFlagsUser;
      // 0x01E8 0x02D8 (5.1 and higher)
      PVOID pShimData;
      // 0x01EC 0x02E0 (5.1 and higher)
      PVOID AppCompatInfo;
      // 0x01DC 0x02E8 (5.1 and higher)
      UNICODE_STRING CSDVersion;
    };
  };
  // The AppCompatFlags and AppCompatFlagsUser members are set by APPHELP.DLL
  // from TAG_FLAG_MASK_KERNEL (0x5005) and TAG_FLAG_MASK_USER (0x5008) tags for
  // the process’s description in an SDB file. In the XML that SDB files are
  // compiled from, the two are evaluated from the MASK attribute in a <FLAG>
  // tag whose TYPE attribute is KERNEL or USER, respectively.

  //
  //
  // Appended for Windows XP
  //
  // 0x01F8 0x02F8 (5.1 and higher)
  ACTIVATION_CONTEXT_DATA const *ActivationContextData;
  ASSEMBLY_STORAGE_MAP *ProcessAssemblyStorageMap;
  ACTIVATION_CONTEXT_DATA const *SystemDefaultActivationContextData;
  ASSEMBLY_STORAGE_MAP *SystemAssemblyStorageMap;
  // 0x0208 0x0318 (5.1 and higher)
  ULONG_PTR MinimumStackCommit;

  //
  //
  // Appended for Windows Server 2003
  //
  // 0x020C 0x0320 (5.2 and higher)
  union
  {
    struct
    {
      // 0x020C 0x0320 (5.2 to 1809)
      FLS_CALLBACK_INFO *FlsCallback;
      // 0x0210 0x0328 (5.2 to 1809)
      LIST_ENTRY FlsListHead;
      // 0x0218 0x0338 (5.2 to 1809)
      PVOID FlsBitmap;
      // 0x021C 0x0340 (5.2 to 1809)
      ULONG FlsBitmapBits[4];
      // 0x022C 0x0350 (5.2 to 1809)
      ULONG FlsHighIndex;
    };
    struct
    {
      // 0x020C 0x0320 (1903 and higher)
      PVOID SparePointers[4];
      // 0x021C 0x0340 (1903 and higher)
      ULONG SpareUlongs[5];
    };
  };

  //
  //
  // Appended for Windows Vista
  //
  // 0x0230 0x0358 (6.0 and higher)
  PVOID WerRegistrationData;
  // 0x0234 0x0360 (6.0 and higher)
  PVOID WerShipAssertPtr;

  //
  //
  // Appended for Windows 7
  //
  union
  {
    // 0x0238 0x0368 (6.1 only)
    PVOID pContextData;
    // 0x0238 0x0368 (6.2 and higher)
    PVOID pUnused;
  };
  // 0x023C 0x0370 (6.1 and higher)
  PVOID pImageHeaderHash;
  union
  {
    // 0x0240 0x0378 (6.1 and higher)
    ULONG TracingFlags;
    struct // https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/pebteb/peb/tracingflags.htm?tw=11px
    {
      // 0x00000001 (6.1 and higher)
      ULONG HeapTracingEnabled : 1;
      // 0x00000002 (6.1 and higher)
      ULONG CritSecTracingEnabled : 1;
      // 0x00000004 (6.2 and higher)
      ULONG LibLoaderTracingEnabled : 1;
      ULONG SpareTracingBits : 29;
    };
  };

  //
  //
  // Appended for Windows 8
  //
  // 0x0248 0x0380 (6.2 and higher)
  ULONGLONG CsrServerReadOnlySharedMemoryBase;

  //
  //
  // Appended Later in Windows 10
  //
  // 0x0250 0x0388 (1511 and higher)
  ULONG TppWorkerpListLock;
  // 0x0254 0x0390 (1511 and higher)
  LIST_ENTRY TppWorkerpList;
  // 0x025C 0x03A0 (1511 and higher)
  PVOID WaitOnAddressHashTable[0x80];
  // 0x045C 0x07A0 (1709 and higher)
  PVOID TelemetryCoverageHeader;
  // 0x0460 0x07A8 (1709 and higher)
  ULONG CloudFileFlags;
  // 0x0464 0x07AC (1803 and higher)
  ULONG CloudFileDiagFlags;
  // 0x0468 0x07B0 (1803 and higher)
  CHAR PlaceholderCompatibiltyMode;
  // 0x0469 0x07B1 (1803 and higher)
  CHAR PlaceholderCompatibilityModeReserved[7];
  // 0x0470 0x07B8 (1809 and higher)
  LEAP_SECOND_DATA *LeapSecondData;
  union
  {
    // 0x0474 0x07C0 (1809 and higher)
    ULONG LeapSecondFlags;
    struct
    {
      ULONG SixtySecondEnabled : 1;
      ULONG Reserved : 31;
    };
  };
  // 0x0478 0x07C4 (1809 and higher)
  ULONG NtGlobalFlag2;
  // The NtGlobalFlag2 member is indeed named for being in some sense an
  // extension of the much older NtGlobalFlag. Each corresponds to a registry
  // value that can be in either or both of two well-known keys. Each also is
  // the name of a variable in the kernel (one exported, the other only
  // internal), which the kernel initialises from the corresponding registry
  // value in the Session Manager key. This then provides the initial value for
  // the corresponding PEB member, which may then be re-initialised from the
  // same-named registry value in the program’s subkey of the Image File
  // Execution Options.
  //
  // Only one flag in the new set of them is yet known to be defined. A set
  // 0x00000001 bit in the data for the GlobalFlag2 registry value becomes a set
  // 0x00000001 bit in the NtGlobalFlag2 member. From there it may set the
  // SixtySecondEnabled bit in union with the LeapSecondFlags. The intended
  // effect is that the newly exported RtlpTimeFieldsToTime and
  // RtlpTimeToTimeFields functions become leap-second-aware: when
  // LeapSecondData is available, these functions accommodate 60 as the seconds
  // field in a time.
  //
  // This support for leap seconds was all new for the 1809 release and thus was
  // also still new, roughly, for the article Leap Seconds for the IT Pro: What
  // you need to knowExternal link at a Microsoft blog dated Feb 14 2019. Years
  // later, on 27th January 2023, this is still the only match that Google finds
  // when asked to search microsoft.com for pages that contain GlobalFlag2. This
  // is a good example of a trend in what passes as documentation. At various
  // levels of Windows administration and programming, it is often that
  // Microsoft’s only disclosure of some new feature, large or small, is a blog.
  // Administrators and programmers are inevitably grateful that Microsoft
  // employees take the time to blog. But let’s please not overlook that these
  // blogs are not documentation. The helpfulness of Microsoft’s employees in
  // explaining new features in fast-moving development, and the readiness of
  // occasionally desperate administrators and programmers to latch on to this
  // help, disguises that Microsoft is systematically skipping the work of
  // documenting these features.

  //
  //
  // Appended Later in Windows 11
  //
  // 0x0480 0x07C8 (NTDDI_WIN11_ZN and higher)
  ULONGLONG ExtendedFeatureDisableMask;
} PEB, PPEB;

#ifdef __cplusplus
}
#endif
