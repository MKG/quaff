#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__LIST_OF_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__LIST_OF_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/tools/list_of.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  namespace bm = boost::mpl;

  //////////////////////////////////////////////////////////////////////////////
  // list_of_function builds the list of user function of a process network
  //////////////////////////////////////////////////////////////////////////////
  template<class Network> struct list_of_function
  {
    template<class Macro, class List = bm::vector<> >
    struct function_of
    {
      typedef List type;
    };

    template<class Function, class List>
    struct function_of< MacroCall<Function>, List >
    {
      typedef typename bm::push_back<List,Function>::type  type;
    };

    template<class Process, class List>
    struct process_function
    {
      typedef typename Process::descriptor::macro instrs;
      typedef typename bm::fold< instrs
                               , List
                               , function_of<bm::_2,bm::_1>
                               >::type type;
    };

    typedef typename Network::process processus;
    typedef typename bm::fold< processus
                             , bm::vector<>
                             , process_function<bm::_2,bm::_1>
                             >::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // list_of_pid builds the list of process PID of a process network
  //////////////////////////////////////////////////////////////////////////////
  template<class Network> struct list_of_pid
  {
    template<class Process, class List>
    struct process_id
    {
      typedef typename Process::pid                   pid;
      typedef typename bm::push_back<List,pid>::type  type;
    };

    typedef typename Network::process processus;
    typedef typename bm::fold< processus
                             , bm::vector<>
                             , process_id<bm::_2,bm::_1>
                             >::type type;
  };
}

#endif

