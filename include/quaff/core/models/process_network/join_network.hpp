/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_JOIN_NETWORK_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_JOIN_NETWORK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/join_network.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/joint_view.hpp>

namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  ///join network structure
  ///
  /// Static datatype representing the union of two process networks. 
  //////////////////////////////////////////////////////////////////////////////
  template<class Network1,class Network2>
  struct join_network
  {
    typedef typename boost::fusion::result_of::
                     joint_view< typename Network1::processes
                               , typename Network2::processes
                               >::type              processes;
                               
                               
    typedef typename boost::fusion::result_of::
                     joint_view< typename Network1::inputs
                               , typename Network2::inputs
                               >::type              inputs;
                               
                               
    typedef typename boost::fusion::result_of::
                     joint_view< typename Network1::outputs
                               , typename Network2::outputs
                               >::type              outputs;

    join_network(Network1 const& n1, Network2 const& n2) 
                  : nodes1(n1)
                  , nodes2(n2) 
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Run each process in a process network using for_each.
    ////////////////////////////////////////////////////////////////////////////
    void operator()() const
    {
      boost::fusion::for_each(boost::fusion::joint_view(nodes1, nodes2),runner());
    }

    struct runner
    {
      template<class P> void operator()(P& proc) const { proc(); }
    };

    Network1 nodes1;
    Network2 nodes2;
  };
} }

#endif
