/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CONFIG__COMPILER__GCC_HPP__INCLUDED__
#define __QUAFF__CONFIG__COMPILER__GCC_HPP__INCLUDED__

// Has any compiler be detected ?
#if !defined(CONFIG_COMPILER_DETECTED)
// Check for GNU GCC
# if defined(__GNUC__)
#  define CONFIG_COMPILER_DETECTED
#  define CONFIG_COMPILER_GCC

#if defined(__SPU__)
#include <malloc_align.h>
#include <free_align.h>
#endif

namespace quaff
{
  // Return compilers version string
  static inline const char* compiler_string() { return "GNU C++ version " __VERSION__; }

  // Allocates an aligned slice of memory
#  if defined(CONFIG_PLATFORM_CYGWIN)
  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    ptr = static_cast<T*>(memalign(n*sizeof(T),16));
  }
#  elif defined( __MINGW32__ )
  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    ptr = static_cast<T*>(__mingw_aligned_malloc(n*sizeof(T),16));
  }
#  elif defined(CONFIG_PLATFORM_MACOS)
  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    ptr = new T[n];
  }
#  elif defined(__SPU__)
  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    ptr = (T*)(_malloc_align(n*sizeof(T),7));
  }
#  elif defined(__PPU__)
  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    ptr = (T*)(memalign(128,n*sizeof(type)));
  }
#  else
  template<class T> static inline void memory_alloc( T*& ptr, size_t n )
  {
    void* local;
    posix_memalign(&local, 16, n*sizeof(T));
    ptr = static_cast<T*>(local);
  }
#  endif

  // Releases an aligned slice of memory
#  if defined( __MINGW32__ )
  template<class T> static inline void memory_desalloc(T* ptr)
  {
    __mingw_aligned_free(ptr);
  }
#  elif defined(CONFIG_PLATFORM_MACOS)
  template<class T> static inline void memory_desalloc(T* ptr)
  {
    delete[] ptr;
  }
#  elif defined(__SPU__)
  template<class T> static inline void memory_desalloc(T* ptr)
  {
    _free_align(ptr);
  }
#  elif defined(__PPU__)
  template<class T> static inline void memory_desalloc(T* ptr)
  {
    free(ptr);
  }
#  else
  template<class T> static inline void memory_desalloc(T* ptr)
  {
    free(ptr);
  }
#  endif
}

# endif
#endif
#endif
