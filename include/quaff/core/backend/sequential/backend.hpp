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
    sequential_() { start(); }

    void terminate()  { status_ = false; }
    void start()      { status_ = true; }

    bool status_;

    // How to run a network
    template<class Network> void accept( Network const& n )
    {
      boost::fusion::for_each(n.nodes(),runner(*this));
    }
    
    // How to run a process
    template<class Proc> void run(Proc const& p)
    {
      start();

      // Generate data
      typename Proc::input_type   ins;
      typename Proc::output_type  outs;
      
      do
      {
        p(ins,outs);
      }
      while( status_ );
    }
    
    // Some helpers
    struct runner
    {
      sequential_& be;
      runner(sequential_& b) : be(b) {}
      template<class P> void operator()(P& proc) const { be.run(proc); }
    };
  };
} }

namespace quaff
{
  typedef backend::sequential_ current_backend_type;

  extern current_backend_type current_backend;
}

#include <quaff/core/backend/sequential/instructions/call.hpp>

#endif
