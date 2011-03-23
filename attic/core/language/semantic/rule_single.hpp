#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_SINGLE_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_SINGLE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/rule_single.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace quaff
{
  struct single {};

  //////////////////////////////////////////////////////////////////////////////
  // rule_single structure
  // Meta-function representing the (SINGL) semantic rule.
  // This rule create a new process network from a function descriptor
  // and its numerical ID.
  //////////////////////////////////////////////////////////////////////////////
  template<class ID, class FUNC> struct rule_single
  {
    // Building the process descriptor
    typedef bm::vector< MacroCall<FUNC> >                                 instr;
    typedef descriptor<bm::vector<>,bm::vector<>,instr,regular>            desc;

    // Building the processus itself
    typedef typename FUNC::input_types                              input_types;
    typedef typename FUNC::output_types                            output_types;
    typedef typename FUNC::remanent_types                        remanent_types;
    typedef processus<ID,desc,input_types,output_types,remanent_types>     proc;

    // Building the asssociated process network
    typedef process_network<bm::vector<proc>,bm::vector<ID>,bm::vector<ID> > type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto transform that apply rule_single to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<single,Dummy> : bp::transform< apply_rule<single,Dummy> >
                                  , bp::callable
  {
    template<typename Expr, typename State, typename Data>
    struct impl : bp::transform_impl<Expr, State, Data>
    {
      typedef typename Expr::type                   func;
      typedef typename State::pid                   pid;
      typedef typename bm::next<pid>::type          next_pid;
      typedef typename rule_single<pid,func>::type  base;
      typedef environnement<base,next_pid>          result_type;
    };
  };
}

#endif
