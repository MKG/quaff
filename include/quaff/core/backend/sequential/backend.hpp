/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_SEQUENTIAL_BACKEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_SEQUENTIAL_BACKEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/sequential/backend.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace backend
{
  struct sequential_
  {
    // How to run a network
    template<class N> void run_network( N const& n )
    {
      boost::fusion::for_each(n.nodes(),runner(*this));
    }
    
    // How to run a process
    template<class Proc> void run_process(Proc const& p)
    {
      // Geenerate data
      //do
      {
        // Run code till their are invalid
        p.code()(); //(args,back_end);
      } //while( is_running() );
    }
    
    // Some helpers
    struct runner
    {
      sequential_& be;
      runner(sequential_& b) :be(b) {}
      template<class P> void operator()(P& proc) const { proc(be); }
    };
  };
} }

#include <quaff/core/backend/sequential/instructions/call.hpp>

#endif
