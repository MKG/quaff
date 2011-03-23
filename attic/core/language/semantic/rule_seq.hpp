#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_SEQ_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_SEQ_HPP__INCLUDED__

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
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace quaff
{
  struct seq {};

  //////////////////////////////////////////////////////////////////////////////
  // composer structure meets the requirement of adaptator interface and
  // act as a single function object. F1 o F2 is defined as being the successive
  // call of F1 then F2 by sharing F1 output and F2 input memory space. In term
  // of meta-interface, (F1 o F2) inputs are inputs of F1, (F1 o F2) outputs are
  // F2 outputs. Remanent types of F1 and F2 are concatenated with the shared
  // memory block for F1/F2 data sharing.
  //////////////////////////////////////////////////////////////////////////////
  template<class T1,class T2> struct composer
  {
    typedef typename T1::input_types              input_types;
    typedef typename T2::input_types              tmp_vals;
    typedef typename T2::output_types             output_types;
    typedef bt::cons< typename T1::remanent_types
                    , bt::cons<typename T2::remanent_types
                              ,bt::cons<typename T1::output_types
                                       ,bt::null_type
                                       >
                              >
                    >                                   remanent_types;

    void operator()(input_types& i,output_types& o,remanent_types& m ) const
    {
      F1(i ,bt::get<2>(m), bt::get<0>(m));
      if(process_status()) F2(adapt<tmp_vals>(bt::get<2>(m)),o , bt::get<1>(m));
    }

    mutable T1 F1;
    mutable T2 F2;
  };

  //////////////////////////////////////////////////////////////////////////////
  // rule_seq structure
  //
  // Meta-fonction representing the (SEQ) semantic rule.
  // This rule create a new process network from a couple of process descriptor
  // and their unique numerical ID.
  //
  //////////////////////////////////////////////////////////////////////////////
  template<class ID, class T1, class T2> struct rule_seq
  {
    // Retrieves the list of function
    typedef typename list_of_function<T1>::type fns1;
    typedef typename list_of_function<T2>::type fns2;
    typedef typename bm::at_c<fns1,0>::type     fn1;
    typedef typename bm::at_c<fns2,0>::type     fn2;
    typedef user_function< composer<fn1,fn2> >  func;

    // Building the process descriptor
    typedef typename func::type                                 base;
    typedef bm::vector< MacroCall< base > >                     instr;
    typedef descriptor<bm::vector<>,bm::vector<>,instr,regular> desc;

    // Building the processus itself
    typedef typename base::input_types                  i_types;
    typedef typename base::output_types                 o_types;
    typedef typename base::remanent_types               r_types;
    typedef processus<ID,desc,i_types,o_types,r_types>  proc;

    // Building the asssociated process network
    typedef process_network< bm::vector<proc>,bm::vector<ID>,bm::vector<ID> > type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto transform that apply rule_seq to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<seq,Dummy> : bp::transform< apply_rule<seq,Dummy> >
                               , bp::callable
  {
    template<typename Expr, typename State, typename Data>
    struct impl : bp::transform_impl<Expr, State, Data>
    {
      // Retrieves the skeleton_expression from the expression node
      typedef typename bp::result_of::child_c<Expr, 0>::type  arg1;
      typedef typename bp::result_of::child_c<Expr, 1>::type  arg2;

      // Transform both children
      typedef typename transform_network<arg1,State>::type  env1;
      typedef typename transform_network<arg2,State>::type  env2;
      typedef typename env1::type                           pn1;
      typedef typename env2::type                           pn2;

      // Build the process_network
      typedef typename State::pid                           pid;
      typedef typename bm::next<pid>::type                  next_pid;
      typedef typename rule_seq<pid,pn1,pn2>::type          base;
      typedef environnement<base,next_pid>                  result_type;
    };
  };
}

#endif

