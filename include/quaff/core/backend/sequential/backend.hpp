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
    sequential_() {}

    void terminate() const { status_ = false;  }
    void start()     const { status_ = true;   }

    mutable bool status_;

    // How to run a network
    template<class Network>
    void accept( Network const& n ) const
    {
      // Sequential process handles all data externally
      typedef typename Network::data_type data_type;
      data_type data;

      // Loop until something stops me
      do
      {
        n.accept(*this,data);
      } while( status_ );

    }
    
    // How to run a process
    template<class Process, class Data>
    void accept(Process const& p,Data& d) const
    {
      // Start the process again
      start();
      typedef typename Process::pid_type pid;
      boost::fusion::
      for_each( p.code()
              , run ( boost::fusion::at_c<0>(boost::fusion::at_c<pid::value>(d))
                    , boost::fusion::at_c<1>(boost::fusion::at_c<pid::value>(d))
                    , d
                    )
              );
    }
    
    // Some helpers
    template<class In, class Out,class Data> struct runner
    {
      In& in; Out& out; Data& data;
      runner(In& i, Out& o, Data& d) : in(i), out(o), data(d) {}
      template<class Code> void operator()(Code const& op) const
      {
        op( in,out, data );
      }
    };


    template<class I,class O,class D>
    runner<I,O,D> run(I& i, O& o, D& d) const
    {
      runner<I,O,D> that(i,o,d);
      return that;
    }

  };
} }

namespace quaff
{
  typedef backend::sequential_ current_backend_type;

  extern current_backend_type current_backend;
}

#include <quaff/core/backend/sequential/instructions/call.hpp>

#endif
