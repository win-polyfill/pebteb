/*
 * Copyright 2024 Yonggang Luo
 * SPDX-License-Identifier: MIT
 */

#include "test.h"
#include "win-polyfill-peb.h"

void check_peb_BitField()
{
  {
    PEB peb{};
    peb.ImageUsedLargePages = 1;
    check_uchar_mask(&peb, 0x03, 0x01);
  }
  {
    PEB peb{};
    peb.IsProtectedProcess = 1;
    check_uchar_mask(&peb, 0x03, 0x02);
  }
  {
    PEB peb{};
    peb.IsLegacyProcess = 1;
    check_uchar_mask(&peb, 0x03, 0x04);
  }
  {
    PEB peb{};
    peb.IsImageDynamicallyRelocated_6_3 = 1;
    check_uchar_mask(&peb, 0x03, 0x04);
  }
  {
    PEB peb{};
    peb.IsImageDynamicallyRelocated_6_0 = 1;
    check_uchar_mask(&peb, 0x03, 0x08);
  }
  {
    PEB peb{};
    peb.SkipPatchingUser32Forwarders_6_3 = 1;
    check_uchar_mask(&peb, 0x03, 0x08);
  }
  {
    PEB peb{};
    peb.SkipPatchingUser32Forwarders_6_0_SPx = 1;
    check_uchar_mask(&peb, 0x03, 0x10);
  }
  {
    PEB peb{};
    peb.IsPackagedProcess_6_3 = 1;
    check_uchar_mask(&peb, 0x03, 0x10);
  }
  {
    PEB peb{};
    peb.IsPackagedProcess_6_2 = 1;
    check_uchar_mask(&peb, 0x03, 0x20);
  }
  {
    PEB peb{};
    peb.IsAppContainer_6_3 = 1;
    check_uchar_mask(&peb, 0x03, 0x20);
  }
  {
    PEB peb{};
    peb.IsAppContainer_6_2 = 1;
    check_uchar_mask(&peb, 0x03, 0x40);
  }
  {
    PEB peb{};
    peb.IsProtectedProcessLight = 1;
    check_uchar_mask(&peb, 0x03, 0x40);
  }
  {
    PEB peb{};
    peb.IsLongPathAwareProcess = 1;
    check_uchar_mask(&peb, 0x03, 0x80);
  }
}

void test_PEB_LDR_DATA()
{
  check_offsetof(offsetof(PEB_LDR_DATA, Length), 0x00, 0x00);
  check_offsetof(offsetof(PEB_LDR_DATA, Initialized), 0x04, 0x04);
  check_offsetof(offsetof(PEB_LDR_DATA, SsHandle), 0x08, 0x08);
  check_offsetof(offsetof(PEB_LDR_DATA, InLoadOrderModuleList), 0x0C, 0x10);
  check_offsetof(offsetof(PEB_LDR_DATA, InMemoryOrderModuleList), 0x14, 0x20);
  check_offsetof(offsetof(PEB_LDR_DATA, InInitializationOrderModuleList), 0x1C, 0x30);
  check_offsetof(offsetof(PEB_LDR_DATA, EntryInProgress), 0x24, 0x40);
  check_offsetof(offsetof(PEB_LDR_DATA, ShutdownInProgress), 0x28, 0x48);
  check_offsetof(offsetof(PEB_LDR_DATA, ShutdownThreadId), 0x2C, 0x50);
  check_sizeof(sizeof(PEB_LDR_DATA), 0x30, 0x58, alignof(PEB_LDR_DATA));
}

void test_RTL_USER_PROCESS_PARAMETERS()
{
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, MaximumLength), 0x00, 0x00);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, Length), 0x04, 0x04);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, Flags), 0x08, 0x08);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, DebugFlags), 0x0C, 0x0C);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, ConsoleHandle), 0x10, 0x10);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, ConsoleFlags), 0x14, 0x18);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, StandardInput), 0x18, 0x20);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, StandardOutput), 0x1C, 0x28);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, StandardError), 0x20, 0x30);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CurrentDirectory), 0x24, 0x38);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, DllPath), 0x30, 0x50);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, ImagePathName), 0x38, 0x60);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CommandLine), 0x40, 0x70);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, Environment), 0x48, 0x80);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, StartingX), 0x4C, 0x88);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, StartingY), 0x50, 0x8C);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CountX), 0x54, 0x90);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CountY), 0x58, 0x94);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CountCharsX), 0x5C, 0x98);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CountCharsY), 0x60, 0x9C);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, FillAttribute), 0x64, 0xA0);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, WindowFlags), 0x68, 0xA4);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, ShowWindowFlags), 0x6C, 0xA8);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, WindowTitle), 0x70, 0xB0);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, DesktopInfo), 0x78, 0xC0);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, ShellInfo), 0x80, 0xD0);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, RuntimeData), 0x88, 0xE0);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, CurrentDirectores), 0x90, 0xF0);

  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, EnvironmentSize), 0x0290, 0x03F0);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, EnvironmentVersion), 0x0294, 0x03F8);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, PackageDependencyData), 0x0298, 0x0400);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, ProcessGroupId), 0x029C, 0x0408);
  check_offsetof(offsetof(RTL_USER_PROCESS_PARAMETERS, LoaderThreads), 0x02A0, 0x040C);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, RedirectionDllName), 0x02A4, 0x0410);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, HeapPartitionName), 0x02AC, 0x0420);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, DefaultThreadpoolCpuSetMasks), 0x02B4, 0x0430);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, DefaultThreadpoolCpuSetMaskCount),
    0x02B8,
    0x0438);
  check_offsetof(
    offsetof(RTL_USER_PROCESS_PARAMETERS, DefaultThreadpoolThreadMaximum),
    0x02BC,
    0x043C);
  check_sizeof(
    sizeof(RTL_USER_PROCESS_PARAMETERS),
    0x02C0,
    0x0440,
    alignof(RTL_USER_PROCESS_PARAMETERS));
}

void check_peb_CrossProcessFlags()
{
  {
    PEB peb{};
    peb.ProcessInJob = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000001);
  }
  {
    PEB peb{};
    peb.ProcessInitializing = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000002);
  }
  {
    PEB peb{};
    peb.ProcessUsingVEH = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000004);
  }
  {
    PEB peb{};
    peb.ProcessUsingVCH = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000008);
  }
  {
    PEB peb{};
    peb.ProcessUsingFTH = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000010);
  }
  {
    PEB peb{};
    peb.ProcessPreviouslyThrottled = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000020);
  }
  {
    PEB peb{};
    peb.ProcessCurrentlyThrottled = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000040);
  }
  {
    PEB peb{};
    peb.ProcessImagesHotPatched = 1;
    check_ulong_mask_both(&peb, 0x28, 0x50, 0x00000080);
  }
}

void test_peb()
{
  printf("alignof(LARGE_INTEGER):0x%x\n", (int)alignof(LARGE_INTEGER));
  printf("alignof(PEB):0x%x\n", (int)alignof(PEB));
  printf("sizeof(PEB):0x%x\n", (int)sizeof(PEB));

  {
    PEB peb{};
    peb.InheritedAddressSpace = 1;
    check_uchar_mask(&peb, 0x00, 0x01);
  }
  check_offsetof(offsetof(PEB, InheritedAddressSpace), 0x00, 0x00);
  check_offsetof(offsetof(PEB, ReadImageFileExecOptions), 0x01, 0x01);
  check_offsetof(offsetof(PEB, BeingDebugged), 0x02, 0x02);
  check_offsetof(offsetof(PEB, SpareBool), 0x03, 0x03);
  check_offsetof(offsetof(PEB, BitField), 0x03, 0x03);
  check_peb_BitField();
#ifdef _WIN64
  check_offsetof(offsetof(PEB, Padding0), SIZE_MAX, 0x04);
#endif
  check_offsetof(offsetof(PEB, Mutant), 0x04, 0x08);
  check_offsetof(offsetof(PEB, ImageBaseAddress), 0x08, 0x10);
  test_PEB_LDR_DATA();
  check_offsetof(offsetof(PEB, Ldr), 0x0C, 0x18);
  test_RTL_USER_PROCESS_PARAMETERS();
  check_offsetof(offsetof(PEB, ProcessParameters), 0x10, 0x20);
  check_offsetof(offsetof(PEB, SubSystemData), 0x14, 0x28);
  check_offsetof(offsetof(PEB, ProcessHeap), 0x18, 0x30);

#ifndef _WIN64
  check_offsetof(offsetof(PEB, nt_3_10_p1.FastPebLock), 0x1C, SIZE_MAX);
#endif
  check_offsetof(offsetof(PEB, FastPebLock), 0x1C, 0x38);
#ifndef _WIN64
  check_offsetof(offsetof(PEB, FastPebLockRoutine), 0x20, SIZE_MAX);
  check_offsetof(offsetof(PEB, SparePtr1), 0x20, SIZE_MAX);
#endif
  check_offsetof(offsetof(PEB, AtlThunkSListPtr), 0x20, 0x40);
#ifndef _WIN64
  check_offsetof(offsetof(PEB, FastPebUnlockRoutine), 0x24, 0x48);
#endif
  check_offsetof(offsetof(PEB, SparePtr2), 0x24, 0x48);
  check_offsetof(offsetof(PEB, IFEOKey), 0x24, 0x48);

#ifndef _WIN64
  check_offsetof(offsetof(PEB, nt_3_10_p2.Unaccounted), 0x28, SIZE_MAX);
#endif
  check_offsetof(offsetof(PEB, EnvironmentUpdateCount), 0x28, 0x50);
  check_peb_CrossProcessFlags();
  check_offsetof(offsetof(PEB, CrossProcessFlags), 0x28, 0x50);
#ifdef _WIN64
  check_offsetof(offsetof(PEB, Padding1), SIZE_MAX, 0x54);
#endif

#ifndef _WIN64
  check_offsetof(offsetof(PEB, nt_3_50_p1.Unaccounted), 0x2c, SIZE_MAX);
#endif
  check_offsetof(offsetof(PEB, KernelCallbackTable), 0x2c, 0x58);
  check_offsetof(offsetof(PEB, UserSharedInfoPtr), 0x2c, 0x58);
#ifndef _WIN64
  check_offsetof(offsetof(PEB, EventLogSection), 0x30, SIZE_MAX);
#endif
  check_offsetof(offsetof(PEB, SystemReserved0), 0x30, 0x60);
#ifndef _WIN64
  check_offsetof(offsetof(PEB, EventLog), 0x34, SIZE_MAX);
  check_offsetof(offsetof(PEB, SystemReserved1), 0x34, SIZE_MAX);
  {
    PEB peb{};
    peb.ExecuteOptions = 0x3;
    check_ulong_mask_both(&peb, 0x34, 0x64, 0x00000003);
  }
#endif
  check_offsetof(offsetof(PEB, SpareUlong), 0x34, 0x64);
  check_offsetof(offsetof(PEB, AtlThunkSListPtr32), 0x34, 0x64);

  check_offsetof(offsetof(PEB, FreeList), 0x38, 0x68);
  check_offsetof(offsetof(PEB, SparePebPtr0), 0x38, 0x68);
  check_offsetof(offsetof(PEB, ApiSetMap), 0x38, 0x68);

  check_offsetof(offsetof(PEB, TlsExpansionCounter), 0x3C, 0x70);
#ifdef _WIN64
  check_offsetof(offsetof(PEB, Padding2), SIZE_MAX, 0x74);
#endif
  check_offsetof(offsetof(PEB, TlsBitmap), 0x40, 0x78);
  check_offsetof(offsetof(PEB, TlsBitmapBits), 0x44, 0x80);
  check_offsetof(offsetof(PEB, ReadOnlySharedMemoryBase), 0x4C, 0x88);
  check_offsetof(offsetof(PEB, ReadOnlySharedMemoryHeap), 0x50, 0x90);
  check_offsetof(offsetof(PEB, HotpatchInformation), 0x50, 0x90);
  check_offsetof(offsetof(PEB, SparePvoid0), 0x50, 0x90);
  check_offsetof(offsetof(PEB, SharedData), 0x50, 0x90);
  check_offsetof(offsetof(PEB, ReadOnlyStaticServerData), 0x54, 0x98);
  check_offsetof(offsetof(PEB, AnsiCodePageData), 0x58, 0xA0);
  check_offsetof(offsetof(PEB, OemCodePageData), 0x5C, 0xA8);
#ifndef _WIN64
  check_offsetof(offsetof(PEB, nt_3_10.UnicodeCaseTableData), 0x60, 0xB0);
  check_offsetof(offsetof(PEB, nt_3_10.CriticalSectionTimeout), 0x68, SIZE_MAX);
  // Check size for Windows NT 3.10 and 3.50
  check_sizeof(
    tail_offsetof(PEB, nt_3_10.CriticalSectionTimeout), 0x70, SIZE_MAX, alignof(PEB));
#endif

  // Appended for Windows NT 3.51
  check_offsetof(offsetof(PEB, UnicodeCaseTableData), 0x60, 0xB0);
  check_offsetof(offsetof(PEB, NumberOfProcessors), 0x64, 0xB8);
  check_offsetof(offsetof(PEB, NtGlobalFlag), 0x68, 0xBC);
  check_offsetof(offsetof(PEB, CriticalSectionTimeout), 0x70, 0xC0);
  check_offsetof(offsetof(PEB, HeapSegmentReserve), 0x78, 0xC8);
  check_offsetof(offsetof(PEB, HeapSegmentCommit), 0x7C, 0xD0);
  check_offsetof(offsetof(PEB, HeapDeCommitTotalFreeThreshold), 0x80, 0xD8);
  check_offsetof(offsetof(PEB, HeapDeCommitFreeBlockThreshold), 0x84, 0xE0);
  check_offsetof(offsetof(PEB, NumberOfHeaps), 0x88, 0xE8);
  check_offsetof(offsetof(PEB, MaximumNumberOfHeaps), 0x8C, 0xEC);
  check_offsetof(offsetof(PEB, ProcessHeaps), 0x90, 0xF0);
  // Check size for Windows NT 3.51
  check_sizeof(tail_offsetof(PEB, ProcessHeaps), 0x98, SIZE_MAX, alignof(PEB));

  // Appended for Windows NT 4.0
  check_offsetof(offsetof(PEB, GdiSharedHandleTable), 0x94, 0xF8);
  check_offsetof(offsetof(PEB, ProcessStarterHelper), 0x98, 0x0100);
  check_offsetof(offsetof(PEB, GdiDCAttributeList), 0x9C, 0x0108);
#ifdef _WIN64
  check_offsetof(offsetof(PEB, Padding3), SIZE_MAX, 0x010C);
#endif
#ifndef _WIN64
  check_offsetof(offsetof(PEB, nt_4_0_p1.LoaderLock), 0xA0, 0x0110);
#endif
  check_offsetof(offsetof(PEB, LoaderLock), 0xA0, 0x0110);
  check_offsetof(offsetof(PEB, OSMajorVersion), 0xA4, 0x0118);
  check_offsetof(offsetof(PEB, OSMinorVersion), 0xA8, 0x011C);
  check_offsetof(offsetof(PEB, OSBuildNumber), 0xAC, 0x0120);
  check_offsetof(offsetof(PEB, OSCSDVersion), 0xAE, 0x0122);
  check_offsetof(offsetof(PEB, OSPlatformId), 0xB0, 0x0124);
  check_offsetof(offsetof(PEB, ImageSubsystem), 0xB4, 0x0128);
  check_offsetof(offsetof(PEB, ImageSubsystemMajorVersion), 0xB8, 0x012C);
  check_offsetof(offsetof(PEB, ImageSubsystemMinorVersion), 0xBC, 0x0130);
#ifdef _WIN64
  check_offsetof(offsetof(PEB, Padding4), SIZE_MAX, 0x0134);
#endif
  check_offsetof(offsetof(PEB, ImageProcessAffinityMask), 0xC0, 0x0138);
  check_offsetof(offsetof(PEB, ActiveProcessAffinityMask), 0xC0, 0x0138);
  check_offsetof(offsetof(PEB, GdiHandleBuffer), 0xC4, 0x0140);
  // Check size for Windows NT 4.0
  check_sizeof(tail_offsetof(PEB, GdiHandleBuffer) + 4, 0x0150, SIZE_MAX, alignof(PEB));

  // Appended for Windows 2000
  check_offsetof(offsetof(PEB, PostProcessInitRoutine), 0x014C, 0x0230);
  check_offsetof(offsetof(PEB, TlsExpansionBitmap), 0x0150, 0x0238);
  check_offsetof(offsetof(PEB, TlsExpansionBitmapBits), 0x0154, 0x0240);
  check_offsetof(offsetof(PEB, SessionId), 0x01D4, 0x02C0);
#ifdef _WIN64
  check_offsetof(offsetof(PEB, Padding5), SIZE_MAX, 0x02C4);
#endif
#ifndef _WIN64
  check_offsetof(offsetof(PEB, nt_5_0.AppCompatInfo), 0x01D8, SIZE_MAX);
  check_offsetof(offsetof(PEB, nt_5_0.CSDVersion), 0x01DC, SIZE_MAX);
  // Check size for Windows NT 5.0
  check_sizeof(tail_offsetof(PEB, nt_5_0.CSDVersion) + 4, 0x01E8, SIZE_MAX, alignof(PEB));
#endif

  // Appended for Windows XP
  check_offsetof(offsetof(PEB, AppCompatFlags), 0x01D8, 0x02C8);
  check_offsetof(offsetof(PEB, AppCompatFlagsUser), 0x01E0, 0x02D0);
  check_offsetof(offsetof(PEB, pShimData), 0x01E8, 0x02D8);
  check_offsetof(offsetof(PEB, AppCompatInfo), 0x01EC, 0x02E0);
  check_offsetof(offsetof(PEB, CSDVersion), 0x01F0, 0x02E8);
  check_offsetof(offsetof(PEB, ActivationContextData), 0x01F8, 0x02F8);
  check_offsetof(offsetof(PEB, ProcessAssemblyStorageMap), 0x01FC, 0x0300);
  check_offsetof(offsetof(PEB, SystemDefaultActivationContextData), 0x0200, 0x0308);
  check_offsetof(offsetof(PEB, SystemAssemblyStorageMap), 0x0204, 0x0310);
  check_offsetof(offsetof(PEB, MinimumStackCommit), 0x0208, 0x0318);
#ifndef _WIN64
  // Note: Windows XP 32bit is 5.1 and Windows XP 64 bit is 5.2
  // Their kernel is different
  // Check size for Windows NT 5.1
  check_sizeof(
    tail_offsetof(PEB, MinimumStackCommit) + 4, 0x0210, SIZE_MAX, alignof(PEB));
#endif

  // Appended for Windows Server 2003
  check_offsetof(offsetof(PEB, FlsCallback), 0x020C, 0x0320);
  check_offsetof(offsetof(PEB, FlsListHead), 0x0210, 0x0328);
  check_offsetof(offsetof(PEB, FlsBitmap), 0x0218, 0x0338);
  check_offsetof(offsetof(PEB, FlsBitmapBits), 0x021C, 0x0340);
  check_offsetof(offsetof(PEB, FlsHighIndex), 0x022C, 0x0350);
  check_offsetof(offsetof(PEB, SparePointers), 0x020C, 0x0320);
  check_offsetof(offsetof(PEB, SpareUlongs), 0x021C, 0x0340);
  // Check size for Windows NT 5.2
  check_sizeof(tail_offsetof(PEB, FlsHighIndex), 0x0230, 0x0358, alignof(PEB));
  check_sizeof(tail_offsetof(PEB, SpareUlongs), 0x0230, 0x0358, alignof(PEB));

  // Appended for Windows Vista
  check_offsetof(offsetof(PEB, WerRegistrationData), 0x0230, 0x0358);
  check_offsetof(offsetof(PEB, WerShipAssertPtr), 0x0234, 0x0360);
  // Check size for Windows NT 6.0
  check_sizeof(tail_offsetof(PEB, WerShipAssertPtr), 0x0238, 0x0368, alignof(PEB));

  // Appended for Windows 7
  check_offsetof(offsetof(PEB, pContextData), 0x0238, 0x0368);
  check_offsetof(offsetof(PEB, pUnused), 0x0238, 0x0368);
  check_offsetof(offsetof(PEB, pImageHeaderHash), 0x023C, 0x0370);
  {
    PEB peb{};
    peb.HeapTracingEnabled = 1;
    check_ulong_mask_both(&peb, 0x0240, 0x0378, 0x00000001);
  }
  {
    PEB peb{};
    peb.CritSecTracingEnabled = 1;
    check_ulong_mask_both(&peb, 0x0240, 0x0378, 0x00000002);
  }
  {
    PEB peb{};
    peb.LibLoaderTracingEnabled = 1;
    check_ulong_mask_both(&peb, 0x0240, 0x0378, 0x00000004);
  }
  check_offsetof(offsetof(PEB, TracingFlags), 0x0240, 0x0378);
  // Check size for Windows NT 6.1
  check_sizeof(tail_offsetof(PEB, TracingFlags) + 4, 0x0248, 0x0380, alignof(PEB));

  // Appended for Windows 8
  check_offsetof(offsetof(PEB, CsrServerReadOnlySharedMemoryBase), 0x0248, 0x0380);
  // Check size for Windows NT 6.2
  check_sizeof(
    tail_offsetof(PEB, CsrServerReadOnlySharedMemoryBase), 0x0250, 0x0388, alignof(PEB));

  // Appended Later in Windows 10
  check_offsetof(offsetof(PEB, TppWorkerpListLock), 0x0250, 0x0388);
  check_offsetof(offsetof(PEB, TppWorkerpList), 0x0254, 0x0390);
  check_offsetof(offsetof(PEB, WaitOnAddressHashTable), 0x025C, 0x03A0);
  check_offsetof(offsetof(PEB, TelemetryCoverageHeader), 0x045C, 0x07A0);
  check_offsetof(offsetof(PEB, CloudFileFlags), 0x0460, 0x07A8);
  check_offsetof(offsetof(PEB, CloudFileDiagFlags), 0x0464, 0x07AC);
  check_offsetof(offsetof(PEB, PlaceholderCompatibiltyMode), 0x0468, 0x07B0);
  check_offsetof(offsetof(PEB, PlaceholderCompatibilityModeReserved), 0x0469, 0x07B1);
  check_offsetof(offsetof(PEB, LeapSecondData), 0x0470, 0x07B8);
  check_offsetof(offsetof(PEB, LeapSecondFlags), 0x0474, 0x07C0);
  {
    PEB peb{};
    peb.SixtySecondEnabled = 1;
    check_ulong_mask_both(&peb, 0x0474, 0x07C0, 0x00000001);
  }
  check_offsetof(offsetof(PEB, NtGlobalFlag2), 0x0478, 0x07C4);
  // Check size for Windows NT 10.0 22H2
  check_sizeof(tail_offsetof(PEB, NtGlobalFlag2), 0x0480, 0x07C8, alignof(PEB));

  check_offsetof(offsetof(PEB, ExtendedFeatureDisableMask), 0x0480, 0x07C8);

  check_sizeof(sizeof(PEB), 0x488, 0X7D0, alignof(PEB));
}
