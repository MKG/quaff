/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_JOINT_NETWORK_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_JOINT_NETWORK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/join_network.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/joint_view.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  // joint network structure
  // Static datatype representing the union of two process networks.
  //////////////////////////////////////////////////////////////////////////////
  template<class Network1,class Network2>
  struct joint_network
  {
    ////////////////////////////////////////////////////////////////////////////
    // nodes, input and output set of a joint network is the joint view
    // of the underlying sequence of both original networks
    ////////////////////////////////////////////////////////////////////////////
    typedef boost::fusion::joint_view< typename Network1::nodes_type const
                                     , typename Network2::nodes_type const
                                     >                    nodes_type;
                               
    typedef boost::fusion::joint_view< typename Network1::input_set
                                     , typename Network2::input_set
                                     >                    input_set;
                               
    typedef boost::fusion::joint_view< typename Network1::output_set
                                     , typename Network2::output_set
                                     >                    output_set;

    typedef boost::fusion::vector < typename Network1::input_type
                                  , typename Network2::input_type
                                  >                       input_type;

    typedef boost::fusion::vector < typename Network1::output_type
                                  , typename Network2::output_type
                                  >                       output_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build a joint network from two other Networks
    ////////////////////////////////////////////////////////////////////////////
    joint_network ( Network1 const& n1, Network2 const& n2 ) 
                  : nodes1(n1), nodes2(n2) 
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Pass current network to a Back-End
    ////////////////////////////////////////////////////////////////////////////
    template<class BackEnd> void run(BackEnd& be) const
    {
      // The BackEnd acts like a Visitor over the network
      be.accept(nodes1);
      be.accept(nodes2);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Acces to the network Nodes sequence
    ////////////////////////////////////////////////////////////////////////////
    boost::fusion::
    joint_view< typename Network1::nodes_type const
              , typename Network2::nodes_type const
              > const
    nodes() const
    {
      boost::fusion::
      joint_view< typename Network1::nodes_type const
                , typename Network2::nodes_type const
                > const
      that(nodes1.nodes(),nodes2.nodes()) ;

      return that;
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
