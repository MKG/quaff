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

    ////////////////////////////////////////////////////////////////////////////
    // Upgrade network by applyign a transform on its inputs
    ////////////////////////////////////////////////////////////////////////////

    template<class Transform, class Set>
    struct apply_if
    {
      template<class Sig> struct result;

      template<class This,class Element>
      struct result<This(Element const&)>
      {
        typedef typename boost::mpl::
                if_ < boost::mpl::has_key < Set
                                          , typename Element::pid_type
                                          >
                    , typename boost::result_of<Transform(Element)>::type
                    , Element
                    >::type type;
      };

      template<class Element> inline
      typename result<apply_if(Element const&)>::type
      operator()(Element const& e)
      {
        return eval(e,boost::mpl::has_key<Set,typename Element::pid_type>::value);
      }

      template<class Element> inline
      typename result<apply_if(Element const&)>::type
      eval(Element const& e, boost::mpl::false_ const &)
      {
        return e;
      }

      template<class Element> inline
      typename result<apply_if(Element const&)>::type
      eval(Element const& e, boost::mpl::true_ const &)
      {
        Transform callee;
        return callee(e);
      }
    };

    template<class Transform> inline
    network < typename  boost::fusion::result_of::
                        as_vector< typename  boost::fusion::result_of::
                                             transform< Nodes const
                                                      , apply_if< Transform
                                                                , input_set
                                                                >
                                                      >::type
                                 >::type
            , InputSet
            , OutputSet
            , DataTypes
            >
    update_inputs(Transform const& t)
    {
      apply_if<Transform, input_set> callee;

      network < typename  boost::fusion::result_of::
                          as_vector< typename  boost::fusion::result_of::
                                               transform< Nodes const
                                                        , apply_if< Transform
                                                                  , input_set
                                                                  >
                                                        >::type
                                   >::type
              , InputSet
              , OutputSet
              , DataTypes
              >
      that(boost::fusion::as_vector(boost::fusion::transform(nodes_,callee)));

      return that;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Upgrade network by applyign a transform on its outputs
    ////////////////////////////////////////////////////////////////////////////

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
