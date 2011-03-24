/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_DETAILS_IGNORE_UNUSED_HPP_INCLUDED
#define QUAFF_SDK_DETAILS_IGNORE_UNUSED_HPP_INCLUDED

namespace quaff { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // In some SFINAE enabled code, some functions parameters may be declared
  // but not used in a given implementation. Calling this function on such
  // parameters prevent compilers to generate spurious warnings.
  //////////////////////////////////////////////////////////////////////////////
  template<class T> void ignore_unused( T const& )  {}
} }

#endif
