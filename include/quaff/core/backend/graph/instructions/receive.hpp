/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_GRAPH_INSTRUCTIONS_RECEIVE_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_GRAPH_INSTRUCTIONS_RECEIVE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/graph/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/as_set.hpp>
#include <boost/fusion/include/for_each.hpp>

namespace quaff { namespace instruction
{
  template<class Pid, class Stream> struct display_pid
  {
    typedef void result_type;

    display_pid(Stream& os, Pid const& p) : ost(os), pid(p) {}
   
    template<class T> void operator()(T& t) const
    {
      os << "do" << T::begin << " -- di" ;
      os << pid;
      os << " [dir=forward arrowsize=3];\n\t";
    }

    Stream&     os;
    Pid const&  pid;
  };

  template<class Sources>
  struct receive<Sources,backend::graph_>
  {
    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const& p
                    , Input&
                    , Output& out
                    , Context& os
                    ) const
    {
      display_pid<Pid,Context>a(os, p);
      for_each(boost::fusion::as_set(Sources()), (a));
    }
  }; 
} }

#endif
