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
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <iostream>
#include <sstream>


namespace quaff { namespace instruction
{
 
  struct aff
  {
   std::ostringstream& ost;
   typedef void result_type;
   aff(std::ostringstream& os) : ost(os) {}
   
      template<class T>
      void operator()(T& t) const
      {
          ost << "do" << T::value << " -- di" ;
          
      }
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
      std::ostringstream ost;
      aff a(ost);
      for_each(boost::fusion::as_set(Sources()), (a));
      os << ost.str();
      os << p;
      os << " [dir=forward arrowsize=3];\n\t";
    }
  }; 
} }

#endif
