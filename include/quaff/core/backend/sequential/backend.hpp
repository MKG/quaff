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
#include <boost/array.hpp>
#include <quaff/sdk/meta/run.hpp>

namespace quaff { namespace backend
{
  struct sequential_
  {
    sequential_() {}

    ////////////////////////////////////////////////////////////////////////////
    // Execution controls and checks
    ////////////////////////////////////////////////////////////////////////////
    void terminate() const
    {
      if(next_ != last_ ) *next_++ = false;
    }

    ////////////////////////////////////////////////////////////////////////////
    // next_terminating tracks the process as they are terminated
    ////////////////////////////////////////////////////////////////////////////
    mutable bool       *next_ , *last_;

    ////////////////////////////////////////////////////////////////////////////
    // How to run a network
    ////////////////////////////////////////////////////////////////////////////
    template<class Network> void accept( Network const& n ) const
    {
      // How many process do we have ?
      static const std::size_t
      count = boost::mpl::size<typename Network::nodes_type>::value;

      // Sequential process handles all data externally
      // and use a boolean array to transfer state informations
      typedef
      boost::fusion::vector2< typename Network::data_type
                            , boost::array<bool,count>
                            > data_type;
      data_type data;

      // Initialize the state of processes
      boost::fusion::at_c<1>(data).fill(true);

      // Initialize the process termination counter
      next_ = &(boost::fusion::at_c<1>(data)[0]);
      last_ = &(boost::fusion::at_c<1>(data)[count-1]);

      // Loop until everybody stopped
      do { n.accept(*this,data); } while( next_ != last_ );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // How to run a process
    ////////////////////////////////////////////////////////////////////////////
    template<class Process, class Context>
    void accept(Process const& p,Context& d) const
    {
      typedef typename Process::pid_type pid;

      // Walk down the list of code fragment and run them using a proper context
      boost::fusion::
      for_each( p.code()
              , meta::
                run ( pid()
                    , boost::fusion::
                      at_c<2*pid::begin>(boost::fusion::at_c<0>(d))
                    , boost::fusion::
                      at_c<2*pid::begin+1>(boost::fusion::at_c<0>(d))
                    , d
                    )
              );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Specify sequential_ as the defualt backend and initializes its instance
////////////////////////////////////////////////////////////////////////////////
namespace quaff
{
  typedef backend::sequential_ current_backend_type;

  extern current_backend_type current_backend;
}

#include <quaff/core/backend/sequential/instructions/call.hpp>
#include <quaff/core/backend/sequential/instructions/send.hpp>
#include <quaff/core/backend/sequential/instructions/receive.hpp>

#endif
