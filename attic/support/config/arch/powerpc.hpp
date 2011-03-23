/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__ARCH__POWERPC_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__ARCH__POWERPC_HPP__INCLUDED__

#if !defined(CONFIG_ARCH_DETECTED)
#if defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(_M_PPC) || defined(_ARCH_PPC)
#define CONFIG_ARCH_DETECTED
#define CONFIG_ARCH_POWERPC
#define CONFIG_SUPPORT_MPI

namespace quaff
{
  static inline const char* arch_string() { return "Power PC"; }
}
#endif
#endif
#endif

