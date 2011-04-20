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
  template<class Pid,class In, class Out,class Context> struct runner
  {
    Pid const& pid; In& in; Out& out; Context& context;
    runner(Pid const& p,In& i, Out& o, Context& c)
          : pid(p), in(i), out(o), context(c) {}
    template<class Code> void operator()(Code const& op) const
    {
      op( pid, in, out, context );
    }
  };

  template<class Pid,class I,class O,class D> inline
  runner<Pid,I,O,D> run(Pid const& p , I& i, O& o, D& d)
  {
    runner<Pid,I,O,D> that(p,i,o,d);
    return that;
  }
} }

#endif
