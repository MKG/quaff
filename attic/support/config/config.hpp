/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__CONFIG_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__CONFIG_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Configuration component
///
/// This file uses a large set of preprocessing tests to provides a platform,
/// compiler and architecture independant code for handling the basics of any
/// kind of library.
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <boost/cstdint.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @brief configuration functions and classes namespace
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  // BOOST cstdint injection
  //////////////////////////////////////////////////////////////////////////////
  using boost::int8_t;  using boost::uint8_t;
  using boost::int16_t; using boost::uint16_t;
  using boost::int32_t; using boost::uint32_t;
  using boost::int64_t; using boost::uint64_t;
}

#include <quaff/support/config/platform.hpp>
#include <quaff/support/config/compiler.hpp>
#include <quaff/support/config/arch.hpp>
#include <quaff/support/config/mpi.hpp>
#include <quaff/support/config/std.hpp>

#endif

////////////////////////////////////////////////////////////////////////////////
// End of config.hpp
////////////////////////////////////////////////////////////////////////////////
