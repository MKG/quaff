/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__MARKER__UPDATE_HPP__INCLUDED__
#define __QUAFF__CORE__MARKER__UPDATE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/marker/update.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  /*****************************************************************************
   * Update a data buffer by circulary permute its content
   ****************************************************************************/
  template<class T, long M>
  struct updater
  {
    void operator()( data<T,M>& d ) const { eval(d, bm::int_<M-1>() ); }

    template<int I>
    void eval( data<T,M>& d, bm::int_<I> const& ) const
    {
      d[-I] = d[-I+1];
      eval(d,bm::int_<I-1>());
    }

    void eval( data<T,M>& d, bm::int_<0> const& ) const { d[-1] = d[0]; }
  };

  template<class T> struct updater<T,1>
  {
    void operator()( data<T,1>& vals ) const {}
  };

  template<class T,long M> static inline void update( data<T,M>& values )
  {
    updater<T,M> callee;
    callee(values);
  }
}

#endif

