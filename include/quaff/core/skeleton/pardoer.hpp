/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_SKELETON_PARDOER_HPP_INCLUDED
#define QUAFF_CORE_SKELETON_PARDOER_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/skeleton/pardoer.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/meta/action.hpp>
#include <boost/utility/enable_if.hpp>
#include <quaff/core/dsl/terminal.hpp>
#include <boost/proto/proto_typeof.hpp>
#include <quaff/sdk/meta/is_callable.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <quaff/core/skeleton/seq.hpp>

namespace quaff
{
  /////////////////////////////////////////////////////////////////////////////
  // Turn pardo<N>(skeleton) into pardoer(N,skeleton)
  /////////////////////////////////////////////////////////////////////////////
  
  template<int N, class Skeleton> 
  typename boost::proto::result_of::make_expr< tag::pardoer_
                                              , boost::mpl::int_<N>
                                              , Skeleton const&
                                              >::type
  pardo(boost::mpl::int_<N>, Skeleton const& s)
  {
    return  boost::proto::
            make_expr<tag::pardoer_>( boost::mpl::int_<N>(), boost::cref(s));
  }
}

#endif
