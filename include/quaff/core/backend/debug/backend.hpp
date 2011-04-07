/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_DEBUG_BACKEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_DEBUG_BACKEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/debug/backend.hpp
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace backend
{
  struct debug_
  {
    void terminate()  {}
    void start()      {}

    // How to run a network
    template<class Network> void accept( Network const& n )
    {
      boost::fusion::for_each(n.nodes(),runner(*this));
    }
    

    // How to run a process
    template<class Proc> void run(Proc const& p)
    {
      typename Proc::input_type   ins;
      typename Proc::output_type  outs;
      std::cout << "[ Running process " << Proc::pid_type::value << "]\n";
      p(ins,outs);
      std::cout << "[-------------------------------]\n";
    }
    
    // Some helpers
    struct runner
    {
      debug_& be;
      runner(debug_& b) :be(b) {}
      template<class P> void operator()(P& proc) const { be.run(proc); }
    };
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Generate a debug on the standard output
////////////////////////////////////////////////////////////////////////////////
template<class X> void debug(X const& xpr)
{
  quaff::semantic::convert<quaff::tag::process_network_>  converter;
  quaff::model::empty_environment                         env;
  quaff::backend::debug_ target;

  converter( xpr, env, target ).network().run(target);
}

#include <quaff/core/backend/debug/instructions/call.hpp>

#endif
