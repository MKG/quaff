/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_DETAILS_PIPE_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_DETAILS_PIPE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/semantic/details/pipe
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/has_key.hpp>
#include <quaff/sdk/meta/push_back.hpp>
#include <quaff/sdk/meta/push_front.hpp>

////////////////////////////////////////////////////////////////////////////////
// Helper functor to build a pipe
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // is_inside checks for a PID existence into a PID set
  //////////////////////////////////////////////////////////////////////////////
  template<class Set>
  struct is_inside
  {
    template<class Process>
    struct  apply
          : boost::mpl::has_key<Set, typename Process::pid_type>
    {};
  };

  //////////////////////////////////////////////////////////////////////////////
  // add_send adds a send instructions to each process requiring it
  //////////////////////////////////////////////////////////////////////////////
  template<class Destinations,class Backend>
  struct add_send
  {
    template<class Sig> struct result;

    template<class This, class Process>
    struct  result<This(Process)>
          : result_of::push_back< Process
                                , instruction::send<Destinations,Backend>
                                >
    {};

    template<class Process>
    typename result<add_send(Process)>::type
    operator()(Process const& p) const
    {
      instruction::send<Destinations,Backend> sender;
      return meta::push_back(p,sender);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // add_recv adds a receive instructions to each process requiring it
  //////////////////////////////////////////////////////////////////////////////
  template<class Sources,class Backend>
  struct add_recv
  {
    template<class Sig> struct result;

    template<class This, class Process>
    struct  result<This(Process)>
          : result_of::push_front< Process
                                , instruction::receive<Sources,Backend>
                                >
    {};

    template<class Process>
    typename result<add_recv(Process)>::type
    operator()(Process const& p) const
    {
      instruction::receive<Sources,Backend> sender;
      return meta::push_front(p,sender);
    }
   };
} }

#endif
