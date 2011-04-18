/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_RUN_HPP_INCLUDED
#define QUAFF_SDK_META_RUN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/run.hpp
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace meta
{
  template<class In, class Out,class Data> struct runner
  {
    In& in; Out& out; Data& data;
    runner(In& i, Out& o, Data& d) : in(i), out(o), data(d) {}
    template<class Code> void operator()(Code const& op) const
    {
      op( in,out, data );
    }
  };

  template<class I,class O,class D> inline
  runner<I,O,D> run(I& i, O& o, D& d)
  {
    runner<I,O,D> that(i,o,d);
    return that;
  }
} }

#endif
