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
  // a network is built from a:
  //  - a FusionRandomAccessSequence of process (usually a fusion::vector)
  //  - a MetaAssociativeSequence of input and output nodes (usually a mpl::set)
  //  - an input Type
  //  - an output Type
  //////////////////////////////////////////////////////////////////////////////
  template< class Nodes
          , class InputSet  , class OutputSet
          , class InputTypes, class OutputTypes
          >
  struct network
  {
    typedef Nodes       nodes_type;
    typedef InputSet    input_set;
    typedef OutputSet   output_set;
    typedef InputTypes  input_type;
    typedef OutputTypes output_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build a network form its Nodes sequence
    ////////////////////////////////////////////////////////////////////////////
    network(nodes_type const& n) : nodes_(n) {}

    ////////////////////////////////////////////////////////////////////////////
    // Pass current network to a Back-End
    ////////////////////////////////////////////////////////////////////////////
    template<class BackEnd> void run(BackEnd& be) const
    { 
      // The BackEnd acts like a Visitor over the network
      be.accept(*this);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Acces to the network Nodes sequence
    ////////////////////////////////////////////////////////////////////////////
    nodes_type const& nodes() const { return nodes_; }

    nodes_type nodes_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a network out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class IT, class OT, class P, class I,class O>
  network<P,I,O,IT,OT> make_network( P const& n, I const&, O const& )
  {
    network<P,I,O,IT,OT> that(n);
    return that;
  }
} }

#endif
