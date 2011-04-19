/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_PUSH_BACK_HPP_INCLUDED
#define QUAFF_SDK_META_PUSH_BACK_HPP_INCLUDED

#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/as_vector.hpp>

////////////////////////////////////////////////////////////////////////////////
// Add a code fragment to a process type.
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace result_of
{
  template<class Process, class Instr>
  struct push_back;

  template<class P, class C, class I, class O, class Instr>
  struct push_back< model::process<P,C,I,O>, Instr >
  {
    typedef model::process< P
                          , typename  boost::fusion::result_of::
                                      as_vector < typename
                                                  boost::fusion::result_of::
                                                  push_front<C const,Instr>::type
                                                >::type
                          , I
                          , O
                          > type;
  };
} }

namespace quaff { namespace meta
{
  ////////////////////////////////////////////////////////////////////////////
   // Upgrade current process by adding a new instruction to its code list
   ////////////////////////////////////////////////////////////////////////////
   template<class P, class C, class I, class O, class Instr> inline
   typename result_of::push_back< model::process<P,C,I,O>, Instr>::type
   push_front(model::process<P,C,I,O> const& p, Instr const& x)
   {
     typename result_of::push_back< model::process<P,C,I,O>, Instr>::type
     that(boost::fusion::as_vector(boost::fusion::push_front(p.code(),x)));

     return that;
   }
} }

#endif
