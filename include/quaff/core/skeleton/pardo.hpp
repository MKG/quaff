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
#include <quaff/quaff.hpp>
#include <boost/proto/proto_typeof.hpp>

namespace quaff
{
  namespace details
  {
    template<std::size_t N, class Skeleton>
    struct pardoer
    {
      static Skeleton const& s_;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested, (boost::proto::deep_copy(s_ & pardoer<N-1,Skeleton>()(s_))) )
      typedef typename nested::type result_type;
  
      result_type operator()(Skeleton const& s) const
      {
        pardoer<N-1,Skeleton> callee;
        return boost::proto::deep_copy(s & callee(s));
      }
    };

    template<class Skeleton>
    struct pardoer<2,Skeleton>
    {
      static Skeleton const& s_;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL( nested, boost::proto::deep_copy(s_ & s_) )
      typedef typename nested::type result_type;

      result_type operator()(Skeleton const& s) const
      {
        return boost::proto::deep_copy(s & s);
      }
    };
  }

  template<std::size_t N, class Skeleton>
  typename details::pardoer<N,Skeleton>::result_type
  pardo( Skeleton const& s)
  {
    details::pardoer<N,Skeleton> callee;
    return callee(s);
  }
}

#endif
