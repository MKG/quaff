/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_SEQUENTIAL_INSTRUCTIONS_CALL_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_SEQUENTIAL_INSTRUCTIONS_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/debug/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/skeleton/source.hpp>
#include <quaff/sdk/type_id.hpp>
namespace quaff { namespace instruction
{
  //////////////////////////////////////////////////////////////////////////////
  // call a function within proper interface
  //////////////////////////////////////////////////////////////////////////////
  template<class Function>
  struct call<Function,backend::sequential_>
  {
    typedef typename Function::input_type   input_type;
    typedef typename Function::output_type  output_type;

    call(Function const& f) : function_(f) {}

    template<class Pid, class Context>
    void operator() ( Pid const&
                    , input_type& ins
                    , output_type& outs
                    , Context& context
                    ) const
    {
      if(boost::fusion::at_c<1>(context)[Pid::value]) outs = function_(ins);
    }

    Function  function_;
  };
} }

#endif
