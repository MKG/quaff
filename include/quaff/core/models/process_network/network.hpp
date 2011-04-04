/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_NETWORK_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_NETWORK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/network.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/vector.hpp>
#include <boost/mpl/set.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/at.hpp>

namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  ///network structure
  ///
  /// Static datatype representing a process network. In this representation,
  /// a process network is defined by a triplet <P,I,O>:
  /// - Process     : a list of processus
  /// - InputNodes  : a list of input nodes
  /// - OutputNodes : a list of outputs node
  //////////////////////////////////////////////////////////////////////////////
  template<class Processes,class InputNodes,class OutputNodes>
  struct network
  {
    typedef Processes   processes;
    typedef InputNodes  inputs;
    typedef OutputNodes outputs;

    network(Processes const& n) : nodes(n) {}

    ////////////////////////////////////////////////////////////////////////////
    // Run each process in a process network using for_each.
    ////////////////////////////////////////////////////////////////////////////
    void operator()() const
    {
      boost::fusion::for_each(nodes,runner());
    }

    struct runner
    {
      template<class P> void operator()(P& proc) const { proc(); }
    };

    Processes nodes;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a network out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class P, class I,class O>
  network<P,I,O> make_network( P const& n, I const&, O const& )
  {
    network<P,I,O> that(n);
    return that;
  }
  
  //////////////////////////////////////////////////////////////////////////////
  /// empty process network - to be used in process network transform
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct network<boost::fusion::vector<>, boost::mpl::set<>, boost::mpl::set<> >
  {
    typedef boost::fusion::vector<> processes;
    typedef boost::mpl::set<>       inputs;
    typedef boost::mpl::set<>       outputs;
  };
  
  typedef network< boost::fusion::vector<>
                 , boost::mpl::set<>
                 , boost::mpl::set<>
                 >                                  empty_network;
} }

#endif
