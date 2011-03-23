#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_LINK_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_LINK_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/rule_link.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

namespace quaff
{
  namespace bm = boost::mpl;

  struct link {};

  // ///////////////////////////////////////////////////////////////////////////
  // rule_link structure
  //
  // Meta-fonction representing the (LINK) semantic rule.
  // ///////////////////////////////////////////////////////////////////////////
  template<class P1, class P2>
  struct rule_link
  {
   // Get list of processus from P1 and P2
    typedef typename P1::process                                proc1;
    typedef typename P2::process                                proc2;

    // Get P1 & P2 pids
    typedef typename list_of_pid<P1>::type                      master_pid;
    typedef typename list_of_pid<P2>::type                      worker_pids;

    // Set all I/O pid
    typedef typename link_to_master<proc2,master_pid>::type            workers;

    // Merge the processus list
    typedef typename bm::copy<workers,bm::back_inserter<proc1> >::type process;

    // Evaluates the input/output list
    typedef typename P1::inputs  inputs;
    typedef typename P1::outputs outputs;

    // Meta-function result
    typedef process_network<process,inputs,outputs>             type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto transform that apply rule_pipe to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<link,Dummy> : bp::transform< apply_rule<link,Dummy> >
                                , bp::callable
  {
    template<typename Expr, typename State, typename Data>
    struct impl : bp::transform_impl<Expr, State, Data>
    {
      // Retrieves the skeleton_expression from the expression node
      typedef typename bp::result_of::child_c<Expr, 0>::type  arg1;
      typedef typename bp::result_of::child_c<Expr, 1>::type  arg2;

      // Transform the first and gets its PID
      typedef typename transform_network<arg1,State>::type  env1;
      typedef typename env1::type                           pn1;

      // Transform the second, passing the PID as state
      typedef typename transform_network<arg2,env1>::type env2;
      typedef typename env2::type                         pn2;
      typedef typename env2::pid                          next_pid;

      // Merge both in a new process_network
      typedef typename rule_link<pn1,pn2>::type           base;

      // Return new environnement
      typedef environnement<base,next_pid>                result_type;
    };
  };
}

#endif
