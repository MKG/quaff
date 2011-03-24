/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_IS_INPUT_HPP_INCLUDED
#define QUAFF_SDK_META_IS_INPUT_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/is_input.hpp
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace meta
{
  /*****************************************************************************
   * Evaluates as mpl::true_ if T is an input type.
   ****************************************************************************/
  template<class T> struct is_input           : boost::mpl::true_   {};
  template<class T> struct is_input<T&>       : boost::mpl::false_  {};
  template<class T> struct is_input<T const&> : boost::mpl::true_   {};
} }

#endif
