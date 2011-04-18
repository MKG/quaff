/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_CONCAT_NETWORK_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_CONCAT_NETWORK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/concat_network.hpp
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
  // concat network structure
  // Static datatype representing the concatenation of two process networks.
  //////////////////////////////////////////////////////////////////////////////
  template<class Network1,class Network2>
  struct concat_network
  {
    ////////////////////////////////////////////////////////////////////////////
    // nodes, input and output set of a concatenation network is the 
    // concatenation view of the underlying sequence of both original networks
    ////////////////////////////////////////////////////////////////////////////
    typedef boost::fusion::joint_view< typename Network1::nodes_type
                                     , typename Network2::nodes_type
                                     >                    nodes_type;
                               
    typedef typename Network1::input_set  input_set;

    typedef typename Network2::output_set output_set;

    typedef typename boost::mpl::
            copy < typename  Network2::data_type
                 , boost::mpl::back_inserter<typename Network1::data_type>
                 >::type                    data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build a concat network from two other Networks
    ////////////////////////////////////////////////////////////////////////////
    concat_network ( Network1 const& n1, Network2 const& n2 )
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
  // Concat two networks 
  //////////////////////////////////////////////////////////////////////////////
  template<class LHS,class RHS> inline
  concat_network<LHS,RHS> concaten_network( LHS const& n1, RHS const& n2 )
  {
    concat_network<LHS,RHS> that(n1,n2);
    return that;
  }
} }

#endif
