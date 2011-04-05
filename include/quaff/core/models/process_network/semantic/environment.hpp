/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_ENVIRONMENT_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_ENVIRONMENT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/semantic/environment.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/next_prior.hpp>
#include <quaff/core/models/process_network/network.hpp>

namespace quaff { namespace model
{
  /*****************************************************************************
   * environment gathers network and current PID value inside proto transforms
   ****************************************************************************/
  template<class Network, class PID>
  struct environment
  {
    typedef Network network_type;
    typedef PID     pid_type;

    environment(Network const& n) : network_(n) {}

    template<class BackEnd> void operator()(BackEnd& be) const
    {
      network_(be);
    }

    Network const&  network() const { return network_; }
    pid_type        pid()     const { return pid_type(); }
    
    Network network_;
  };
  
  /*****************************************************************************
   * Build an environnement out of its component
   ****************************************************************************/
  template<class PID,class Network>
  environment<Network,PID> make_environment(Network const& n, PID const&)
  {
    environment<Network,PID> that(n);
    return that;
  }
  
  /*****************************************************************************
   * specialisation for empty environment
   ****************************************************************************/
  template<> struct environment<empty_network, boost::mpl::int_<0> >
  {
    typedef empty_network network_type;
    typedef boost::mpl::int_<0>     pid_type;
    
    network_type network()  const { return network_type(); }
    pid_type     pid()      const { return pid_type(); }
    
  };

  /*****************************************************************************
   * proto transforms retrieving the current pid of an environment
   ****************************************************************************/
   struct pid_ : boost::proto::callable
   {
     template<class Sig> struct result;

     template<class This, class Env>
     struct result<This(Env)>
     {
       typedef typename boost::proto::detail::uncvref<Env>::type  base;
       typedef typename base::pid_type                            type;
     };

     template<class Env> inline
     typename result<pid_(Env const&)>::type
     operator()(Env const& ) const
     {
       typename result<pid_(Env const&)>::type that;
       return that;
     }
   };

  typedef environment<empty_network, boost::mpl::int_<0> > empty_environment;
} }

#endif
