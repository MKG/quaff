#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_PAR_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_PAR_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/rule_par.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/back_inserter.hpp>

namespace quaff
{
  namespace bm = boost::mpl;

  struct par {};

  //////////////////////////////////////////////////////////////////////////////
  // rule_par structure
  //
  // Meta-fonction representing the (PAR) semantic rule.
  // This rule create a new process network from two process networks
  // so they can run in parallel without communications.
  //
  //////////////////////////////////////////////////////////////////////////////
  template<class P1, class P2>
  struct rule_par
  {
    // Get list of processus from P1 and P2
    typedef typename P1::process                                proc1;
    typedef typename P2::process                                proc2;

    // Get list of inputs/outputs from P1 and P2
    typedef typename P1::inputs                                 inputs1;
    typedef typename P2::inputs                                 inputs2;
    typedef typename P1::outputs                                outputs1;
    typedef typename P2::outputs                                outputs2;

    // Merge the processus list
    typedef typename bm::copy<proc2,bm::back_inserter<proc1> >::type    process;

    // Merge the input/output list
    typedef typename bm::copy<inputs2,bm::back_inserter<inputs1> >::type  inputs;
    typedef typename bm::copy<outputs2,bm::back_inserter<outputs1> >::type outputs;

    // Meta-function result
    typedef process_network<process,inputs,outputs>             type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto tansform that apply rule_single to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<par,Dummy> : bp::transform< apply_rule<par,Dummy> >
                               , bp::callable
  {
    template<typename Expr, typename State, typename Data>
    struct impl : bp::transform_impl<Expr, State, Data>
    {
      // Retrieves the skeleton_expression from the expression node
      typedef typename bp::result_of::child_c<Expr, 0>::type arg1;
      typedef typename bp::result_of::child_c<Expr, 1>::type arg2;

      // Transform the first and gets its PID
      typedef typename transform_network<arg1,State>::type env1;
      typedef typename env1::type pn1;

      // Transform the second, passing the PID as state
      typedef typename transform_network<arg2,env1>::type env2;
      typedef typename env2::type pn2;
      typedef typename env2::pid  next_pid;

      // Merge both in a new process_network
      typedef typename rule_par<pn1,pn2>::type base;

      // Return new environnement
      typedef environnement<base,next_pid> result_type;
    };
  };
}

#endif
