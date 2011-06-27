/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_GRAPH_BACKEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_GRAPH_BACKEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/graph/backend.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/identity.hpp>
#include <quaff/sdk/meta/run.hpp>
namespace quaff { namespace backend
{
  struct graph_
  {
    void terminate() const {}
    void start()     const {}

    template<class T> inline void accept( T const& n ) const
    {

      boost::fusion::at_c<1>(n) << "graph running_process {\n\t"
                                << "dd" << "[shape=box label=\"Source\"];\n\t"
                                << "df" << "[shape=box label=\"Puit\"];\n\t";
      boost::fusion::at_c<0>(n).accept(*this,boost::fusion::at_c<1>(n));
      boost::fusion::at_c<1>(n) << " }\n";
    }

    template<class Process, class Data>
    void accept(Process const& p,Data& os) const
    {
      typename Process::pid_type                          pid;
      boost::mpl::identity<typename Process::input_type>  ins;
      boost::mpl::identity<typename Process::output_type> outs;
      
      boost::fusion::for_each( p.code(), meta::run (pid, ins, outs, os ) );
    }
  };
} }

#include <quaff/core/backend/graph/runtime.hpp>

#endif
