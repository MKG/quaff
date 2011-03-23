#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_PIPE_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_PIPE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/rule_seq.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

namespace quaff
{
  namespace bm = boost::mpl;

  struct pipe {};

  // ///////////////////////////////////////////////////////////////////////////
  // rule_pipe structure
  //
  // Meta-fonction representing the (PIPE) semantic rule.
  // This rule create a new process network from two
  // other process networks, linking via a pipeline.
  // ///////////////////////////////////////////////////////////////////////////
  template<class P1, class P2>
  struct rule_pipe
  {
    // Get list of processus from P1 and P2
    typedef typename P1::process  proc1;
    typedef typename P2::process  proc2;

    // Get list of input/output from P1 and P2
    typedef typename P1::inputs   i1;
    typedef typename P2::inputs   i2;
    typedef typename P1::outputs  o1;
    typedef typename P2::outputs  o2;

    // Add communication instructions into P1 and P2 instructions lists
    typedef typename bm::transform< proc1, apply_suffix<bm::_1,o1,i2> >::type np1;
    typedef typename bm::transform< proc2, apply_prefix<bm::_1,i2,o1> >::type np2;

    // Add new process graph into the new process network
    typedef typename bm::copy<np2, bm::back_inserter< np1 > >::type  process;

    typedef typename P1::inputs         inputs;
    typedef typename P2::outputs        outputs;

    typedef process_network<process,inputs,outputs> type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto transform that apply rule_pipe to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<pipe,Dummy> : bp::transform< apply_rule<pipe,Dummy> >
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
      typedef typename rule_pipe<pn1,pn2>::type base;

      // Return new environnement
      typedef environnement<base,next_pid> result_type;
    };
  };
}

#endif
