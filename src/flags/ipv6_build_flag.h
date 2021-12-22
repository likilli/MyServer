/*
 * ipv6_build_flag.h
 * Create on 2021-12-22
 * LiKai
 */


#pragma once


#include "build_flag.h"


#if defined(ENABLE_IPv6)
#define BUILDFLAG_INTERNAL_IPv6() (!false)
#else
#define BUILDFLAG_INTERNAL_IPv6() (false)
#endif