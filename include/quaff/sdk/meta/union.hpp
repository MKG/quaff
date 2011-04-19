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

#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>

////////////////////////////////////////////////////////////////////////////////
// Force build the union of two ExtendableSequence
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace meta
{
  template<class T1,class T2>
  struct  union_
        : boost::mpl::copy<T2, boost::mpl::back_inserter<T1> >
  {
  };
} }

#endif
