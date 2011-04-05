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

    process(Descriptor const& d) : code_(d) {}

    void operator()(BackEnd& be) const { be.run_process(*this); }

    Descriptor const& code() const { return code_; }
        
    Descriptor  code_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a process out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class PID,class D,class BE>
  process<PID,D,BE> make_process( PID const&, D const& d, BE const& )
  {
    process<PID,D,BE> that(d);
    return that;
  }
} }

#endif
