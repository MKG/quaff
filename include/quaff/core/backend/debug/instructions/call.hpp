/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_DEBUG_INSTRUCTIONS_CALL_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_DEBUG_INSTRUCTIONS_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/debug/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>

namespace quaff { namespace instruction
{
  template<class Function>
  struct call<Function,backend::debug_>
  {
    typedef typename Function::input_type   input_type;
    typedef typename Function::output_type  output_type;

    call(Function const& f) : mFunction(f) {}

    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const&
                    , Input&
                    , Output&
                    , Context& os
                    ) const
    {
      os << "| CALL "
                << type_id<typename Output::type>()
                << "("
                << type_id<typename Input::type>()
                <<")"
                << "\n";
    }

    Function  mFunction;
  };
} }

#endif
