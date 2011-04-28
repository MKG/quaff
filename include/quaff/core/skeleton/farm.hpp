/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_SKELETON_FARM_HPP_INCLUDED
#define QUAFF_CORE_SKELETON_FARM_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/skeleton/farm.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/meta/action.hpp>
//#include <quaff/sdk/meta/farm.hpp>
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
  // Turn function pointer into seq skeleton usign action<>
  /////////////////////////////////////////////////////////////////////////////
  
  template<int N, class Skeleton> 
  typename boost::proto::result_of::make_expr< tag::farm_
                                              , boost::mpl::int_<N>
                                              , Skeleton const&
                                              >::type
  farm(Skeleton const& s)
  {
    return boost::proto::make_expr<tag::farm_>( boost::mpl::int_<N>(), boost::cref(s));
  }
    
  /*
  template<class N> struct farm_
  {
    //BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,(dsl::skeleton::type & farm_<N-1>(dsl::skeleton::type)))
    //typedef typename nested::type type;
    typedef dsl::skeleton_terminal type;

    static inline
    typename type operator()(type  s ) const
    {
      return ( seq(s) & farm_<N-1>(s));
    }
  };

  template<class N> struct farm_<1>
  {
    typedef dsl::skeleton type;
    static inline 
    typename type operator()(type s) const
     { return seq(s); }
  };

  template<class N> static inline
  typename farm_<N>::type farm(N n, dsl::skeleton  s)
  {
    return farm_<N>(s);
  }*/
  

  /////////////////////////////////////////////////////////////////////////////
  // Macro for declaring global seq object
  /////////////////////////////////////////////////////////////////////////////
  #define QUAFF_TASK(Name,Function)             \
  BOOST_PROTO_AUTO(Name, quaff::seq(Function) ) \
  /**/
}

#endif
