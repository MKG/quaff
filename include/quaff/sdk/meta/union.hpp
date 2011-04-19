/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_UNION_HPP_INCLUDED
#define QUAFF_SDK_META_UNION_HPP_INCLUDED

#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/as_set.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/joint_view.hpp>

////////////////////////////////////////////////////////////////////////////////
// Force build the union of two Sequence or two AssociativeSequence
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace result_of
{
  template<class S1,class S2>
  struct  concatenate
        : boost::fusion::result_of::
          as_vector< boost::fusion::joint_view<S1,S2> >
  {};

  template<class S1,class S2>
  struct  union_
        : boost::fusion::result_of::
          as_set< boost::fusion::joint_view<S1,S2> >
  {};
} }

namespace quaff { namespace meta
{
  template<class S1,class S2>
  typename result_of::concatenate<S1 const,S2 const>::type
  concatenate( S1 const& s1, S2 const& s2)
  {
    return boost::fusion::as_vector( boost::fusion::join(s1,s2) );
  }

  template<class S1,class S2>
  typename result_of::concatenate<S1 const,S2 const>::type
  union_( S1 const& s1, S2 const& s2)
  {
    return boost::fusion::as_set( boost::fusion::join(s1,s2) );
  }

} }

#endif
