#include "test.h"
#include "win-polyfill-teb.h"

void test_teb()
{
  printf("alignof(TEB):0x%x\n", (int)alignof(TEB));
  printf("sizeof(TEB):0x%x\n", (int)sizeof(TEB));

#ifndef _WIN64
  check_offsetof(offsetof(TEB, nt_3_1.Spare1), 0x01A4, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_50.Spare1), 0x01A4, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_4_0.Spare1), 0x01A4, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_3_1.Spare2), 0x01A8, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_1.Win32ThreadInfo), 0x01AC, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_1.GdiClientPID), 0x06F4, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_3_1.UserReserved), 0x0708, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_3_1.UserReserved), 0x0BF4, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_3_50.Spare2), 0x01A8, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_4_0.ExceptionCode), 0x01A8, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_3_50.CsrQlpcTeb), 0x01AC, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_3_50.gdiRgn), 0x06DC, SIZE_MAX);

  check_offsetof(offsetof(TEB, nt_3_50.glDispatchTable), 0x0714, SIZE_MAX);
  check_offsetof(offsetof(TEB, nt_4_0.glReserved2), 0x0BDC, SIZE_MAX);

  check_offsetof(tail_offsetof(TEB, nt_3_50.SystemReserved2), 0x06DC, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_4_0.GdiTebBatch), 0x06DC, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_3_50.glDispatchTable), 0x0BE0, SIZE_MAX);
  check_offsetof(tail_offsetof(TEB, nt_4_0.glReserved2), 0x0BE0, SIZE_MAX);
#endif

  {
    check_offsetof(offsetof(TEB, ExceptionCode), 0x01A4, 0x02C0);
#ifdef _WIN64
    check_offsetof(offsetof(TEB, Padding0), SIZE_MAX, 0x02C4);
#endif
    check_offsetof(offsetof(TEB, ExceptionCode), 0x01A4, 0x02C0);
#ifndef _WIN64
    check_offsetof(offsetof(TEB, ActivationContextStack), 0x01A8, SIZE_MAX);
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
  check_offsetof(offsetof(TEB, Tail_3_10), 0x0F20, SIZE_MAX);

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
  check_offsetof(offsetof(TEB, nt_5_2_sp1.SafeThunkCall), 0x0FB8, 0x17D0);

  check_offsetof(offsetof(TEB, PreferredLanguages), 0x0FB8, 0x17D0);
  check_offsetof(offsetof(TEB, UserPrefLanguages), 0x0FBC, 0x17D8);
  check_offsetof(offsetof(TEB, LockCount), 0x0FD8, 0x1808);
  check_offsetof(offsetof(TEB, LastSleepCounter), 0x1000, 0x1838);
  check_sizeof(sizeof(TEB), 0x1038, 0x1878);
}
