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
#include <quaff/sdk/type_id.hpp>
#include <quaff/sdk/meta/run.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace quaff { namespace backend
{
  struct graph_
  {
    graph_() {}

    void terminate() const {}
    void start()     const {}

    // How to run a network
    template<class T>
    void accept( T const& n ) const
    {
      boost::fusion::at_c<1>(n)<< "graph running_process {\n\t";
      boost::fusion::at_c<1>(n)<< "dd" << "[shape=box label=\"Source\"];\n\t";
      boost::fusion::at_c<1>(n)<< "df" <<  "[shape=box label=\"Puit\"];\n\t";
      
      boost::fusion::at_c<0>(n).accept(*this,boost::fusion::at_c<1>(n));

      boost::fusion::at_c<1>(n)<< " }\n";
    }

    // How to run a process
    template<class Process, class Data>
    void accept(Process const& p,Data& os) const
    {
      typedef typename Process::pid_type pid;
      boost::mpl::identity<typename Process::input_type>  ins;
      boost::mpl::identity<typename Process::output_type> outs;
      
      

      boost::fusion::
      for_each( p.code()
              , meta::run (pid(), ins, outs, os )
              
              );
     
    }
    
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Generate a debug on the standard output
////////////////////////////////////////////////////////////////////////////////
template<class X, class Stream> void graph(X const& xpr, Stream& os)
{
  quaff::semantic::convert<quaff::tag::process_network_>  converter;
  quaff::model::empty_environment                         env;
  quaff::backend::graph_ target;

  target.accept ( boost::fusion::vector_tie ( converter(xpr,env,target).network()
                                            , os
                                            )
                );
}

#include <quaff/core/backend/graph/instructions/call.hpp>
#include <quaff/core/backend/graph/instructions/send.hpp>
#include <quaff/core/backend/graph/instructions/receive.hpp>
#endif
