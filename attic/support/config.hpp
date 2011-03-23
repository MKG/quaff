/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Configuration component main header
////////////////////////////////////////////////////////////////////////////////

#include <quaff/support/config/config.hpp>

////////////////////////////////////////////////////////////////////////////////
// Global configuration informations
////////////////////////////////////////////////////////////////////////////////
namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  /// @fn configuration
  /// @brief display global configuration informations
  //////////////////////////////////////////////////////////////////////////////
  static inline void configuration()
  {
    printf("//////////////////////////////////////////////////////////////\n");
    printf("// QUAFF v%s (%s)\n",           version_string(),release_string());
    printf("//////////////////////////////////////////////////////////////\n");
    printf("// Compiler         : %s\n",                    compiler_string());
    printf("// Platform         : %s\n",                    platform_string());
    printf("// Architecture     : %s\n",                        arch_string());
    printf("// MPI Version      : %s\n",                         mpi_string());
    printf("//////////////////////////////////////////////////////////////\n");
  }
}

#endif
