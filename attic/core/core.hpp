/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__CORE_HPP__INCLUDED__
#define __QUAFF__CORE__CORE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/void.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/proto/proto.hpp>

namespace quaff
{
  namespace bm = boost::mpl;
  namespace bt = boost::tuples;
  namespace bp = boost::proto;
}

#include <quaff/core/marker/marker.hpp>
#include <quaff/core/runtime/runtime.hpp>
#include <quaff/core/types/types.hpp>
#include <quaff/core/language/language.hpp>

#endif


