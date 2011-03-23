/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__STD_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__STD_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief STL support configuration file.
////////////////////////////////////////////////////////////////////////////////

#if defined(CONFIG_NO_LIBSTD)
# include <quaff/support/config/stdlib/string.hpp>
namespace quaff
{
  static inline const char* std_string() { return "not supported"; }
  typedef string string_type;
}
# else
# include <string>
namespace quaff
{
  static inline const char* std_string() { return "supported"; }
  typedef std::string string_type;
}
#endif

#endif



