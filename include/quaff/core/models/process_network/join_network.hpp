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
  ///joint network structure
  /// Static datatype representing the union of two process networks. 
  //////////////////////////////////////////////////////////////////////////////
  template<class Network1,class Network2>
  struct joint_network
  {
    typedef boost::fusion::joint_view< typename Network1::processes
                                     , typename Network2::processes
                                     >                    processes;
                               
                               
    typedef boost::fusion::joint_view< typename Network1::inputs
                                     , typename Network2::inputs
                                     >                    inputs;
                               
                               
    typedef boost::fusion::joint_view< typename Network1::outputs
                                     , typename Network2::outputs
                                     >                    outputs;

    joint_network ( Network1 const& n1, Network2 const& n2 ) 
                  : nodes1(n1), nodes2(n2) 
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Run each process in a process network using for_each.
    ////////////////////////////////////////////////////////////////////////////
    template<class BackEnd> void operator()(BackEnd& be) const 
    { 
      nodes1(be);
      nodes2(be);
    }
    
    Network1 nodes1;
    Network2 nodes2;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Join two networks 
  //////////////////////////////////////////////////////////////////////////////
  template<class LHS,class RHS> inline
  joint_network<LHS,RHS> join_network( LHS const& n1, RHS const& n2 )
  {
    joint_network<LHS,RHS> that(n1,n2);
    return that;
  }
} }

#endif
