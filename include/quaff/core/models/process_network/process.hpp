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
  // - a process Code Fragment
  /////////////////////////////////////////////////////////////////////////////
  template< class PID
          , class CodeFragment
          >
  struct process
  {
    typedef PID           pid_type;
    typedef CodeFragment  codelet_type;

    process(codelet_type const& codelet) : codelet_(codelet) {}

    template<class Backend,class Data>
    void accept(Backend const& b,Data const& d) const
    {
      b.accept(*this,d);
    }

    codelet_type const& code() const { return codelet_; }
    codelet_type  codelet_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a process out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class P,class C>
  process<P,C> make_process( P const&, C const& c )
  {
    process<P,C> that(c);
    return that;
  }
} }

#endif
