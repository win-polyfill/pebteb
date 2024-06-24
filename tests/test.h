#pragma once
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "win-polyfill-winternl.h"

#define ALIGN_POT(x, pot_align) (((x) + (pot_align) - 1) & ~((pot_align) - 1))

#define tail_offsetof(s,m) (offsetof(s, m) + sizeof(s::m))

static void
check_offsetof(size_t offset, size_t expected_offset_x86, size_t expected_offset_x64)
{
#ifndef _WIN64
  if (expected_offset_x86 != SIZE_MAX)
    assert(offset == expected_offset_x86);
#else
  if (expected_offset_x64 != SIZE_MAX)
    assert(offset == expected_offset_x64);
#endif
}

static void
check_sizeof(size_t size, size_t expected_sizeof_x86, size_t expected_sizeof_x64, size_t alignment)
{
  size = ALIGN_POT(size, alignment);
#ifndef _WIN64
  if (expected_sizeof_x86 != SIZE_MAX)
    assert(size == expected_sizeof_x86);
#else
  if (expected_sizeof_x64 != SIZE_MAX)
    assert(size == expected_sizeof_x64);
#endif
}

static void check_uchar_mask(void *ptr, size_t uchar_offset, UCHAR mask)
{
  UCHAR b = ((UCHAR *)ptr)[uchar_offset];
  assert((b & mask) == mask);
}

static void check_ulong_mask(void *ptr, size_t ulong_offset, ULONG mask)
{
  ULONG b = *(ULONG *)((UCHAR *)ptr + ulong_offset);
  assert((b & mask) == mask);
}

static void check_ulong_mask_both(
  void *ptr,
  size_t ulong_offset_x86,
  size_t ulong_offset_x64,
  ULONG mask)
{
#ifndef _WIN64
  if (ulong_offset_x86 != SIZE_MAX)
    check_ulong_mask(ptr, ulong_offset_x86, mask);
#else
  if (ulong_offset_x64 != SIZE_MAX)
    check_ulong_mask(ptr, ulong_offset_x64, mask);
#endif
}

void test_teb();
void test_peb();
