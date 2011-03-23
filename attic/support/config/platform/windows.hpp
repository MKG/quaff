/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__PLATORM__WINDOWS_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__PLATORM__WINDOWS_HPP__INCLUDED__

// If no platform has been detected already ...
#if !defined(CONFIG_PLATFORM_DETECTED)

// Check if current platform is any Microsoft Windows flavor
# if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define CONFIG_PLATFORM_DETECTED
#  define CONFIG_PLATFORM_WINDOWS

// Remove superfluous includes and linking steps
#  define VC_EXTRALEAN
#  define WIN32_LEAN_AND_MEAN

// Include base header for considered platform
#  include <windows.h>
#  include <malloc.h>

namespace quaff
{
  // (u)int64_t is undefined by default under windows
  typedef unsigned long long uint64_t;
  typedef signed long long   int64_t;

  // Return the platform identification string
  static inline const char* platform_string() { return "Microsoft Windows"; }
}

#  endif
# endif
#endif
