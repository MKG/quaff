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
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <quaff/core/models/process_network/accept.hpp>

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
    typedef boost::fusion::joint_view< typename Network1::nodes_type
                                     , typename Network2::nodes_type
                                     >                    nodes_type;
                               
    typedef boost::fusion::joint_view< typename Network1::input_set
                                     , typename Network2::input_set
                                     >                    input_set;

    typedef boost::fusion::joint_view< typename Network1::output_set
                                     , typename Network2::output_set
                                     >                    output_set;

    typedef typename boost::mpl::
            copy < typename  Network2::data_type
                 , boost::mpl::back_inserter<typename Network1::data_type>
                 >::type                    data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build a joint network from two other Networks
    ////////////////////////////////////////////////////////////////////////////
    joint_network ( Network1 const& n1, Network2 const& n2 )
                  : nodes1(n1), nodes2(n2) 
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Pass backend over processes
    ////////////////////////////////////////////////////////////////////////////
    template<class BackEnd,class Data>
    void accept(BackEnd const& b, Data& d) const
    {
      nodes1.accept(b,d);
      nodes2.accept(b,d);
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
