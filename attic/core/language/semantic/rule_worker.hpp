#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_WORKER_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_WORKER_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/rule_worker.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace quaff
{
  struct worker {};

  //////////////////////////////////////////////////////////////////////////////
  // rule_worker structure
  //
  // Meta-fonction representing the (WORK) semantic rule.
  // This rule create a new process network from an existing process network by
  // adding receive/send repetition to match the SCM worker construction.
  //////////////////////////////////////////////////////////////////////////////
  template<class ID, class MAP, class PN> struct rule_worker
  {
    // Extracts PN MacroCall
    typedef typename bm::at_c<typename PN::process,0>::type procs;
    typedef typename procs::descriptor::macro               macros;
    typedef typename bm::at_c<macros,0>::type               callee;

    // Computes repetition pattern
    static const long rem  = MAP::virtual_size % MAP::real_size;
    static const long iter = MAP::virtual_size / MAP::real_size
                           + (ID::value < rem ? 1 : 0);

    // Building the process descriptor
    typedef bm::vector< MacroRecv,callee,MacroSend>             repeat;
    typedef bm::vector< MacroRepeat<repeat,iter> >              instr;
    typedef descriptor<bm::vector<>,bm::vector<>,instr,regular> desc;

    // Building the processus itself
    typedef typename procs::input_types                 i_types;
    typedef typename procs::output_types                o_types;
    typedef typename procs::remanent_types              r_types;
    typedef processus<ID,desc,i_types,o_types,r_types>  proc;

    // Building the asssociated process network
    typedef process_network< bm::vector<proc>,bm::vector<ID>,bm::vector<ID> > type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto transform that apply rule_seq to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<worker,Dummy> : bp::transform< apply_rule<worker,Dummy> >
                                  , bp::callable
  {
    template<typename Expr, typename State, typename Data>
    struct impl : bp::transform_impl<Expr, State, Data>
    {
      // Retrieves the mapping information from the expression node
      typedef typename bp::result_of::child_c<Expr, 0>::type  arg1;
      typedef typename bp::result_of::child_c<arg1, 0>::type  worker_info;
      typedef typename worker_info::type                    val;

      typedef typename State::pid                           pid;

      // Retrieves the skeleton_expression from the expression node
      typedef typename bp::result_of::child_c<Expr, 1>::type  arg;

      // Build the skeleton
      typedef typename transform_network<arg,State>::type   env1;
      typedef typename env1::type                           pn1;

      // Build the process_network
      typedef typename bm::next<pid>::type            next_pid;
      typedef typename rule_worker<pid,val,pn1>::type base;
      typedef environnement<base,next_pid>            result_type;
    };
  };
}

#endif
