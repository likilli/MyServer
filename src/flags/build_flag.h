/*
 * build_flag.h
 * Create on 2021-12-22
 * LiKai
 *
 * Learn from Google Chromium:
 * Source link: https://chromium.googlesource.com/chromium/src/build/+/refs/heads/main/buildflag.h
 */

#pragma once


#define BUILDFLAG_CAT_INDIRECT(a, b) a ## b
#define BUILDFLAG_CAT(a, b) BUILDFLAG_CAT_INDIRECT(a, b)

#define BUILDFLAG(flag) (BUILDFLAG_CAT(BUILDFLAG_INTERNAL_, flag)())