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

namespace quaff { namespace instruction
{
  template<class Function>
  struct call<Function,backend::debug_>
  {
    call(Function const& f) : mFunction(f) {}

    void operator()() const
    {
      std::cout << "CALL " << (void*)(&mFunction) << "\n";
    }

    Function  mFunction;
  };
} }

#endif
