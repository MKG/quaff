/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CONFIG__COMPILER__VISUALC_HPP__INCLUDED__
#define __QUAFF__CONFIG__COMPILER__VISUALC_HPP__INCLUDED__

// Has any compiler be detected ?
#if !defined(CONFIG_COMPILER_DETECTED)
// Check for MSVC version
# if defined(_MSC_VER)
#  define CONFIG_COMPILER_DETECTED
#  define CONFIG_COMPILER_MSVC

// Uneeded warnings
#  pragma warning( disable : 4554 ) // precedence on & operator
#  pragma warning( disable : 4244 ) // converting types to double
#  pragma warning( disable : 4804 ) // unsafe use of >
#  pragma warning( disable : 4996 ) // unsafe iostream call
#  pragma warning( disable : 4710 ) // undefined preprocessor macro
#  pragma warning( disable : 4668 ) // undefined preprocessor macro (yeah twice wtf)
#  pragma warning( disable : 4820 ) // paddign warning in Winnt.h

// Needed undef to be able to use std::limits
#  undef min
#  undef max
#  include <math.h>

namespace quaff
{
  static inline const char* compiler_string()
  {
    static char version[33];
    sprintf(version,"Microsoft Visual C++ v%d.%d",_MSC_VER / 100,_MSC_VER % 100,33);
    return version;
  }

  template<class T> static inline
  void memory_alloc( T*& ptr, size_t n )
  {
    ptr = static_cast<T*>( _aligned_malloc(n*sizeof(T),16) );
  }

  template<class T> static inline
  void memory_desalloc(T* ptr) { _aligned_free(ptr); }
}

# endif
#endif
#endif
