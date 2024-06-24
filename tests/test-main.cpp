#include <sdkddkver.h>

#include "test.h"
#include "win-polyfill-peb.h"
#include "win-polyfill-teb.h"
#include <windows.h>

void get_windows_version(TEB *teb)
{
  unsigned dwMajorVersion = teb->ProcessEnvironmentBlock->OSMajorVersion;
  unsigned dwMinorVersion = teb->ProcessEnvironmentBlock->OSMinorVersion;
  unsigned dwBuild = teb->ProcessEnvironmentBlock->OSBuildNumber;
  unsigned OSCSDVersion = teb->ProcessEnvironmentBlock->OSCSDVersion;
  unsigned OSPlatformId = teb->ProcessEnvironmentBlock->OSPlatformId;

  printf(
    "Version is %d.%d (%d) OSCSD(0x%04X) OSPlatformId(%d) NTDDI_WIN2K:0x%08X NTDDI_WIN10_TH2:0x%08X 0x%p PlaceholderReserved:0x%p crt:0x%p\n",
    dwMajorVersion,
    dwMinorVersion,
    dwBuild,
    OSCSDVersion,
    OSPlatformId,
    NTDDI_WIN2K,
    NTDDI_WIN10_TH2,
    teb->PaddingVista, /* For below Win10 */
    (void*)(*(uintptr_t *)(teb->PlaceholderReserved + 2)), /* For Win10 */
    (void*)(uintptr_t)teb->ReservedForCrt);
}

int main()
{
  auto teb = NtCurrentTeb();
  get_windows_version(teb);
  test_teb();
  test_peb();
  return 0;
}
