/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__TYPES__TUPLE_HPP__INCLUDED__
#define __QUAFF__CORE__TYPES__TUPLE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/types/selection.hpp
////////////////////////////////////////////////////////////////////////////////

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/reverse_fold.hpp>

namespace quaff
{
  /*****************************************************************************
   * build a tuple from a MPL sequence
   ****************************************************************************/
  template<class T> struct make_tuple
  {
    typedef typename bm::reverse_fold<T
                                      ,bt::null_type
                                      ,bt::cons<bm::_2,bm::_1>
                                      >::type type;
  };

  template<class A,class B> static
  inline A& adapt( B& i ) { return (A&)(i); }

  template<class A,class B> static
  inline A& adapt( const B& i ) { return (A&)(i); }
}

#endif
