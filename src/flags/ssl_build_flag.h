/*
 * ssl_build_flag.h
 * Create on 2021-12-22
 * LiKai
 */


#pragma once


#include "build_flag.h"

#if defined(ENABLE_SSL)
#define BUILDFLAG_INTERNAL_SSL() (!false)
#else
#define BUILDFLAG_INTERNAL_SSL() (false)
#endif