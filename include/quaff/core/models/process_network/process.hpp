/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_PROCESS_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_PROCESS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/apply.hpp>
#include <boost/typeof/typeof.hpp>

namespace quaff { namespace model
{
  /////////////////////////////////////////////////////////////////////////////
  // Define a process inside a process network with :
  // - a static Pid value
  // - a process code Descriptor
  // - an execution BackEnd
  /////////////////////////////////////////////////////////////////////////////
  template<class Pid,class Descriptor,class BackEnd> struct process
  {
    typedef Pid         pid_type;
    typedef Descriptor  descriptor_type;

    process() {}
    process(Descriptor const& d) : code(d) {}

    Descriptor&       descriptor()       { return code; }
    Descriptor const& descriptor() const { return code; }

    void operator()() const
    {
      // If our dynamic PID is correct
      //if( back_end.accept(pid::value) )
      {
        // Build local process variable tuples

        //do
        {
          // Run code till their are invalid
          code(); //(args,back_end);
        } //while( back_end.is_running() );
      }
    }

    Descriptor  code;
  };
} }

#endif
