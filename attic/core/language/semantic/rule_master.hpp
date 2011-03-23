#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_MASTER_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__RULE_MASTER_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/rule_master.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>

namespace quaff
{
  struct master {};

  //////////////////////////////////////////////////////////////////////////////
  // scm_builder structure meets the requirement of adaptator interface and
  // act as the SCM master function.
  //////////////////////////////////////////////////////////////////////////////
  template<class T1,class T2,class T3,class ID,class MAP> struct scm_builder
  {
    typedef typename bm::at_c<T1,0>::type  adaptee1;
    typedef typename bm::at_c<T2,0>::type  adaptee2;
    typedef typename bm::at_c<T3,0>::type  adaptee3;

    typedef typename adaptee1::input_types            input_types;
    typedef typename adaptee3::output_types           output_types;

    typedef bt::cons< typename adaptee1::remanent_types,
            bt::cons< typename adaptee2::remanent_types,
            bt::cons< typename adaptee3::remanent_types,
            bt::cons< typename adaptee1::output_types,
            bt::cons< typename adaptee3::input_types,
            bt::null_type> > > > >                    remanent_types;


    typedef typename adaptee3::input_types  in_bits;
    typedef typename adaptee2::input_types  in_args;
    typedef typename adaptee2::output_types out_args;

    void operator()(input_types& i,output_types& o,remanent_types& m ) const
    {
      static const long worker = MAP::real_size;
      static const long iter   = MAP::virtual_size/MAP::real_size;
      static const long remain = MAP::virtual_size%MAP::real_size;

      // Remanent data contains the SCM size
      bt::get<0>(bt::get<0>(m)) = MAP::virtual_size;
      bt::get<0>(bt::get<2>(m)) = MAP::virtual_size;

      // Setup the vector of split data
      bt::get<0>(bt::get<3>(m)).resize(MAP::virtual_size);
      bt::get<0>(bt::get<4>(m)).resize(MAP::virtual_size);

      if(process_status())
      {
        //puts("prescatter");
      // Build list of sub-values
      Scatter( i ,bt::get<3>(m), bt::get<0>(m) );
      //puts("post-scatter");

        // Iterate over datas and dispatch as needed
        for(int i=0;i<iter;++i)
        {
          for(int w=1;w<worker;++w) send(w+ID::value,bt::get<0>(bt::get<3>(m))[i+w*iter],comm::Data);
          Compute( adapt<in_args>(bt::get<0>(bt::get<3>(m))[i])
                 , adapt<out_args>(bt::get<0>(bt::get<4>(m))[i])
                 , bt::get<1>(m)
                 );
          for(int w=1;w<worker;++w) receive(w+ID::value, bt::get<0>(bt::get<4>(m))[i+w*iter], comm::any_tag, status);
        }

        for(int w=1;w<worker;++w)
        {
          if(w<remain)
          {
            send(w+ID::value,bt::get<0>(bt::get<3>(m))[w+worker*iter],comm::Data);
          }
        }

        // Complete iterations with remaining loops over master
        if(remain)
        {
          Compute( adapt<in_args>(bt::get<0>(bt::get<3>(m))[iter*worker])
                 , adapt<out_args>(bt::get<0>(bt::get<4>(m))[iter*worker])
                 , bt::get<1>(m)
                 );
        }

        for(int w=1;w<worker;++w)
        {
          if(w<remain)
          {
            receive(w+ID::value, bt::get<0>(bt::get<4>(m))[w+worker*iter], comm::any_tag, status);
          }
        }

        // Merge the sub-results
        //puts("pre_merge");
        Merge( adapt<in_bits>(bt::get<4>(m)), o , bt::get<2>(m) );
        //puts("post-merge");
      }
      else
      {
        // Terminate all workers by sending Stop signals
        for(int w=1;w<worker;++w)
        {
          send(w+ID::value,bt::get<0>(bt::get<3>(m))[0],comm::Stop);
          if(w<remain) send(w+ID::value,bt::get<0>(bt::get<3>(m))[0],comm::Stop);
        }
      }
    }

    mutable adaptee1 Scatter;
    mutable adaptee2 Compute;
    mutable adaptee3 Merge;
    mutable status_t status;
  };

  //////////////////////////////////////////////////////////////////////////////
  // rule_worker structure
  //
  // Meta-fonction representing the (MASTER) semantic rule.
  // This rule create a new process network by building a SCM master process.
  //////////////////////////////////////////////////////////////////////////////
  template<class ID, class MAP, class S,class C, class M> struct rule_master
  {
    // Extracts SCM elements function
    typedef typename list_of_function<S>::type scatter;
    typedef typename list_of_function<C>::type compute;
    typedef typename list_of_function<M>::type merge;

    // Builds the SCm master process network
    typedef scm_builder<scatter,compute,merge,ID,MAP> scm_proc;

    // Building the process descriptor
    typedef bm::vector< MacroCall<scm_proc> >                   instr;
    typedef descriptor<bm::vector<>,bm::vector<>,instr,regular> desc;

    // Building the processus itself
    typedef typename scm_proc::input_types              i_types;
    typedef typename scm_proc::output_types             o_types;
    typedef typename scm_proc::remanent_types           r_types;
    typedef processus<ID,desc,i_types,o_types,r_types>  proc;

    // Building the asssociated process network
    typedef process_network< bm::vector<proc>,bm::vector<ID>,bm::vector<ID> > type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// proto transform that apply rule_master to a given node of the AST
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct apply_rule<master,Dummy> : bp::transform< apply_rule<master,Dummy> >
                                  , bp::callable
  {
    template<typename Expr, typename State, typename Data>
    struct impl : bp::transform_impl<Expr, State, Data>
    {
      // Retrieves the mapping information from the expression node
      typedef typename bp::result_of::child_c<Expr, 0>::type  arg0;
      typedef typename bp::result_of::child_c<arg0, 0>::type  worker_info;
      typedef typename worker_info::type                      val;

      // Retrieves the S,C,M skeelton from the expression nodes
      typedef typename bp::result_of::child_c<Expr, 1>::type  arg1;
      typedef typename transform_network<arg1,State>::type    env1;
      typedef typename env1::type                             pn1;
      typedef typename bp::result_of::child_c<Expr, 2>::type  arg2;
      typedef typename transform_network<arg2,State>::type    env2;
      typedef typename env2::type                             pn2;
      typedef typename bp::result_of::child_c<Expr, 3>::type  arg3;
      typedef typename transform_network<arg3,State>::type    env3;
      typedef typename env3::type                             pn3;

      // Build the process_network
      typedef typename State::pid                             pid;
      typedef typename bm::next<pid>::type                    next_pid;
      typedef typename rule_master<pid,val,pn1,pn2,pn3>::type base;
      typedef environnement<base,next_pid>                    result_type;
    };
  };
}

#endif
