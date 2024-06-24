#include "test.h"
#include "win-polyfill-teb.h"

void test_teb()
{
  printf("alignof(TEB):0x%x\n", (int)alignof(TEB));
  printf("sizeof(TEB):0x%x\n", (int)sizeof(TEB));

  check_offsetof(offsetof(TEB, nt_3_10_p2.SystemReserved1), 0xCC, 0x0110);
  check_offsetof(offsetof(TEB, ReservedForDebuggerInstrumentation), 0xCC, 0x0110);
  check_offsetof(offsetof(TEB, SystemReserved1), 0x010C, 0x0190);
  check_offsetof(offsetof(TEB, PlaceholderCompatibilityMode), 0x0174, 0x0280);
  check_offsetof(offsetof(TEB, PlaceholderHydrationAlwaysExplicit), 0x0175, 0x0281);
  check_offsetof(offsetof(TEB, PlaceholderReserved), 0x0176, 0x0282);
  check_offsetof(offsetof(TEB, ProxiedProcessId), 0x0180, 0x028C);
  check_offsetof(offsetof(TEB, ActivationStack), 0x0184, 0x0290);
  check_offsetof(offsetof(TEB, WorkingOnBehalfOfTicket), 0x019C, 0x02B8);
  check_offsetof(tail_offsetof(TEB, WorkingOnBehalfOfTicket), 0x01A4, 0x02C0);
#ifndef _WIN64
  check_offsetof(offsetof(TEB, nt_3_10_p3.Spare1), 0x01A4, SIZE_MAX);
#endif
  check_offsetof(offsetof(TEB, ExceptionCode), 0x01A4, 0x02C0);
#ifdef _WIN64
  check_offsetof(offsetof(TEB, Padding0), SIZE_MAX, 0x02C4);
#endif
#ifndef _WIN64
  check_offsetof(offsetof(TEB, nt_3_10.Spare2), 0x01A8, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_10.Win32ThreadInfo), 0x01AC, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_10.GdiClientPID), 0x06F4, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_10.User32Reserved0), 0x0700, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_10.User32Reserved1), 0x0704, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_10.UserReserved), 0x0708, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_3_10.UserReserved), 0x0BF4, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_3_50_p2.Spare2), 0x01A8, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.CsrQlpcTeb), 0x01AC, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.Win32ClientInfo), 0x01C0, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.SystemReserved2), 0x01D4, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.gdiRgn), 0x06DC, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.User32Reserved0), 0x0700, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.User32Reserved1), 0x0704, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.UserReserved), 0x0708, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50_p2.glDispatchTable), 0x0714, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_3_50_p2.glDispatchTable), 0x0BE0, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_4_0_p2.ExceptionCode), 0x01A8, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_4_0_p2.SpareBytes1), 0x01AC, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_4_0_p2.glReserved2), 0x0BDC, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_4_0_p2.GdiTebBatch), 0x06DC, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_4_0_p2.glReserved2), 0x0BE0, SIZE_MAX);
#endif

  {
#ifndef _WIN64
    check_offsetof(offsetof(TEB, SpareBytes1), 0x01A8, SIZE_MAX);
#endif
    check_offsetof(offsetof(TEB, ActivationContextStackPointer), 0x01A8, 0x02C8);
    check_offsetof(offsetof(TEB, InstrumentationCallbackSp), 0x01AC, 0x02D0);
    check_offsetof(offsetof(TEB, InstrumentationCallbackPreviousPc), 0x01B0, 0x02D8);
    check_offsetof(offsetof(TEB, TxFsContext), 0x01D0, 0x02E8);
    check_offsetof(offsetof(TEB, InstrumentationCallbackDisabled), 0x01B8, 0x02EC);
#ifdef _WIN64
    check_offsetof(offsetof(TEB, UnalignedLoadStoreExceptions), SIZE_MAX, 0x02ED);
    check_offsetof(offsetof(TEB, Padding1), SIZE_MAX, 0x02EE);
#else
    check_offsetof(offsetof(TEB, SpareBytes), 0x01B9, SIZE_MAX);
#endif
  }

  check_offsetof(offsetof(TEB, ReservedForNtRpc), 0x0F1C, 0x1698);
  // (last member in 3.10)
  check_offsetof(tail_offsetof(TEB, ReservedForNtRpc), 0x0F20, SIZE_MAX);

  check_offsetof(offsetof(TEB, GdiTebBatch), 0x01D4, 0x02F0);
  check_offsetof(offsetof(TEB, RealClientId), 0x06B4, 0x07D8);
  check_offsetof(offsetof(TEB, GdiCachedProcessHandle), 0x06BC, 0x07E8);
  check_offsetof(offsetof(TEB, GdiClientPID), 0x06C0, 0x07F0);
  check_offsetof(offsetof(TEB, GdiClientTID), 0x06C4, 0x07F4);
  check_offsetof(offsetof(TEB, GdiThreadLocalInfo), 0x06C8, 0x07F8);
  check_offsetof(offsetof(TEB, Win32ClientInfo), 0x06CC, 0x0800);
  check_offsetof(offsetof(TEB, glDispatchTable), 0x07C4, 0x09F0);
  check_offsetof(offsetof(TEB, glReserved1), 0x0B68, 0x1138);
  check_offsetof(offsetof(TEB, glReserved2), 0x0BDC, 0x1220);
  check_offsetof(tail_offsetof(TEB, glReserved2), 0x0BE0, 0x1228);
  check_offsetof(offsetof(TEB, glSectionInfo), 0x0BE0, 0x1228);
  check_offsetof(offsetof(TEB, glSection), 0x0BE4, 0x1230);
  check_offsetof(offsetof(TEB, glTable), 0x0BE8, 0x1238);
  check_offsetof(offsetof(TEB, glCurrentRC), 0x0BEC, 0x1240);
  check_offsetof(offsetof(TEB, glContext), 0x0BF0, 0x1248);
  check_offsetof(tail_offsetof(TEB, glContext), 0x0BF4, 0x1250);
  check_offsetof(offsetof(TEB, LastStatusValue), 0x0BF4, 0x1250);
#ifdef _WIN64
  check_offsetof(offsetof(TEB, Padding2), SIZE_MAX, 0x1254);
#endif
  check_offsetof(offsetof(TEB, StaticUnicodeString), 0x0BF8, 0x1258);

  check_offsetof(offsetof(TEB, WaitingOnLoaderLock), 0x0F84, 0x1760);

  check_offsetof(offsetof(TEB, TlsExpansionSlots), 0x0F94, 0x1780);
  check_offsetof(offsetof(TEB, FlsData), 0x0FB4, 0x17C8);
#ifndef _WIN64
  check_offsetof(offsetof(TEB, nt_5_1_sp2.SafeThunkCall), 0x0FB4, SIZE_MAX);
#endif
  check_offsetof(offsetof(TEB, nt_5_2_sp1_p2.SafeThunkCall), 0x0FB8, 0x17D0);

  check_offsetof(offsetof(TEB, PreferredLanguages), 0x0FB8, 0x17D0);
  check_offsetof(offsetof(TEB, UserPrefLanguages), 0x0FBC, 0x17D8);
  check_offsetof(offsetof(TEB, LockCount), 0x0FD8, 0x1808);

  check_offsetof(offsetof(TEB, ProcessRundown), 0x0FDC, 0x180C);
  check_offsetof(offsetof(TEB, SpareUlong0), 0x0FDC, 0x180C);
  check_offsetof(offsetof(TEB, WowTebOffset), 0x0FDC, 0x180C);
  check_offsetof(offsetof(TEB, LastSwitchTime), 0x0FE0, 0x1810);
  check_offsetof(offsetof(TEB, TotalSwitchOutTime), 0x0FE8, 0x1818);
  check_offsetof(offsetof(TEB, WaitReasonBitMap), 0x0FF0, 0x1820);
  check_offsetof(tail_offsetof(TEB, WaitReasonBitMap), 0x0FF8, 0x1828);
  check_offsetof(offsetof(TEB, PaddingVista), 0x0FF8, 0x1828);
  check_offsetof(tail_offsetof(TEB, PaddingVista), 0x0FFC, 0x1830);

  check_offsetof(offsetof(TEB, ResourceRetValue), 0x0FE0, 0x1810);
  check_offsetof(offsetof(TEB, ReservedForCrt), 0x0FE8, 0x1820);
  check_offsetof(tail_offsetof(TEB, EffectiveContainerId), 0x1000, 0x1838);
  check_offsetof(offsetof(TEB, LastSleepCounter), 0x1000, 0x1838);

  check_sizeof(sizeof(TEB), 0x1038, 0x1878, alignof(TEB));

  // Used for Windows Vista and lower
  check_offsetof(offsetof(TEB, PaddingVista), 0x0FF8, 0x1828);
  check_offsetof(offsetof(TEB, ReservedForCrt), 0x0FE8, 0x1820);
}
