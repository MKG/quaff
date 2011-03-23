/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CONFIG__PLATORM__MACOS_HPP__INCLUDED__
#define __QUAFF__CONFIG__PLATORM__MACOS_HPP__INCLUDED__

// If no platform has been detected already ...
#if !defined(CONFIG_PLATFORM_DETECTED)

// Check if current platform is a Mac OS flavor
# if defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#  define CONFIG_PLATFORM_DETECTED
#  define CONFIG_PLATFORM_MACOS

namespace quaff
{
  // Return the platform identification string
  static inline const char* platform_string() { return "Mac OS"; }
}

#  endif
# endif
#endif
