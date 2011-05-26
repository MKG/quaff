/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_PRINT_INSTRUCTIONS_RECEIVE_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_PRINT_INSTRUCTIONS_RECEIVE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/print/instructions/receive.hpp
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
 template<class Pid>
  struct aff_code
  {
   std::ostringstream& ost;
   Pid const& pid;
   typedef void result_type;
   aff_code(std::ostringstream& os, Pid const& p) : ost(os), pid(p) {}
   
      template<class T>
      void operator()(T& t) const
      {
          std::ofstream gen("gen.txt", std::ios::out | std::ios::app);
          gen << "\tmemcpy(";
          gen << "di" << pid;
          gen << " <- " << "do" << T::begin;
          gen << ");\n";
          gen.close();
      }
  };


  template<class Sources>
  struct receive<Sources,backend::print_>
  {
    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const& p
                    , Input&
                    , Output& out
                    , Context& os
                    ) const
    {
      std::ostringstream ost;
      aff_code <Pid>a(ost, p);
      for_each(boost::fusion::as_set(Sources()), (a));
      os << ost.str(); 
    }
  }; 
} }

#endif
