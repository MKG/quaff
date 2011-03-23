/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CONFIG__COMPILER__GCC_XML_HPP__INCLUDED__
#define __QUAFF__CONFIG__COMPILER__GCC_XML_HPP__INCLUDED__

// Has any compiler be detected ?
#if !defined(CONFIG_COMPILER_DETECTED)
// Check for XML GCC
# if defined(__GCCXML__)
#  define CONFIG_COMPILER_DETECTED
#  define CONFIG_COMPILER_GCC_XML

// compiler specific include
#  include <malloc.h>
namespace quaff
{
  static inline const char* compiler_string() { return "GCC-XML C++ version " __GCCXML__; }

  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    ptr = static_cast<T*>(posix_memalign(&ptr, 16, n*sizeof(T));
  }

  template<class T> static inline void memory_desalloc(T* ptr)
  {
    free(ptr);
  }
}
#endif
#endif
#endif
