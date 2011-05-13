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

namespace quaff { namespace model
{
  /////////////////////////////////////////////////////////////////////////////
  // Define a process inside a process network with :
  // - a static Pid range [begin PID, end PID[
  // - a process Code Fragment
  /////////////////////////////////////////////////////////////////////////////
  template< class PID
          , class Code
          , class InputType
          , class OutputType
          >
  struct process
  {
    typedef PID         pid_type;
    typedef Code        codelet_type;
    typedef InputType   input_type;
    typedef OutputType  output_type;
    
    
    process(pid_type const& pid, codelet_type const& codelet, int N) 
    : code_(codelet) {
     
       
    typedef typename extends<pid, N>::type& pid_type;
       //typedef typename extends(pid, N)::type pid_type;
      //typedef  typename nested pid_type;
    }

    template<class Backend,class Data>
    void accept(Backend const& b,Data const& d) const
    {
      b.accept(*this,d);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Access to the code fragments
    ////////////////////////////////////////////////////////////////////////////
    codelet_type const& code() const { return code_; }

    codelet_type  code_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a process out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class I, class O, class P,class C, int N>
  process<P,C,I,O> make_process( P const& p, C const& c, boost::mpl::int_<N> )
  {
    process<P,C,I,O> that(p, c,N );
    return that;
  }
} }

#endif
