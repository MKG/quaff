/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_CHAIN_NETWORK_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_CHAIN_NETWORK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/join_network.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/meta/union.hpp>

namespace quaff { namespace result_of
{
  template<class N1,class N2>
  struct chain_network
  {
    typedef model::network
            < typename result_of::concatenate < typename N1::nodes_type
                                              , typename N2::nodes_type
                                              >::type
            , typename N1::input_set
            , typename N2::output_set
            , typename result_of::concatenate < typename N1::data_type
                                              , typename N2::data_type
                                              >::type
            > type;
  };
} }

namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  // join two networks structure by taking union of network components
  //////////////////////////////////////////////////////////////////////////////
  template<class N1,class N2> inline
  typename result_of::chain_network<N1,N2>::type
  chain_network( N1 const& n1, N2 const& n2 )
  {
    typename result_of::chain_network<N1,N2>::type
    that( meta::concatenate(n1.nodes(),n2.nodes()) );
    return that;
  }
} }

#endif
