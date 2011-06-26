/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_DEBUG_RUNTIME_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_DEBUG_RUNTIME_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/debug/runtime.hpp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Generate a debug on the standard output
////////////////////////////////////////////////////////////////////////////////
namespace quaff
{
  template<class X, class Stream> void debug(X const& xpr, Stream& os)
  {
    quaff::semantic::convert<quaff::tag::process_network_>  converter;
    quaff::model::empty_environment                         env;
    quaff::backend::debug_ target;

    target.accept ( boost::fusion::
                    vector_tie ( converter(xpr,env,target).network(), os )
                  );
  }
}

#include <quaff/core/backend/debug/instructions/call.hpp>
#include <quaff/core/backend/debug/instructions/send.hpp>
#include <quaff/core/backend/debug/instructions/receive.hpp>

#endif
