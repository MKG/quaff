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
#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/transform.hpp>
#include <quaff/core/models/process_network/accept.hpp>

namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  // a network is built from a:
  //  - a FusionRandomAccessSequence of process (usually a fusion::vector)
  //  - a MetaAssociativeSequence of input and output nodes (usually a mpl::set)
  //  - a list of Value Type used through the whole system
  //////////////////////////////////////////////////////////////////////////////
  template<class Nodes, class InputSet, class OutputSet, class DataTypes>
  struct network
  {
    typedef Nodes                             nodes_type;
    typedef InputSet                          input_set;
    typedef OutputSet                         output_set;
    typedef boost::fusion::vector1<DataTypes> data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build a network form its Nodes sequence
    ////////////////////////////////////////////////////////////////////////////
    network(nodes_type const& n) : nodes_(n) {}

    ////////////////////////////////////////////////////////////////////////////
    // Pass backend over processes
    ////////////////////////////////////////////////////////////////////////////
    template<class BackEnd,class Data>
    void accept(BackEnd const& b, Data& d) const
    {
      accept_<BackEnd,Data> acceptor(b,d);
      boost::fusion::for_each(nodes_,acceptor);
    }

    nodes_type nodes_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a network out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class DT, class P, class I,class O>
  network<P,I,O,DT> make_network( P const& n, I const&, O const& )
  {
    network<P,I,O,DT> that(n);
    return that;
  }
} }

#endif
