/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_SKELETON_SINK_HPP_INCLUDED
#define QUAFF_CORE_SKELETON_SINK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/skeleton/source.hpp
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <quaff/sdk/meta/sink.hpp>
#include <quaff/core/dsl/terminal.hpp>
#include <boost/proto/proto_typeof.hpp>

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn function pointer into seq skeleton usign action<>
  //////////////////////////////////////////////////////////////////////////////
  template<class InputType>
  dsl::skeleton_terminal< meta::sink<void(*)(InputType)> >
  sink( void(*f)(InputType) )
  {
    meta::sink<void(*)(InputType)> them = f;
    dsl::skeleton_terminal< meta::sink<void(*)(InputType)> > that( them );
    return that;
  }

  template<class InputType>
  dsl::skeleton_terminal< meta::named_sink<void(*)(InputType)> >
  sink( void(*f)(InputType),const std::string name )
  {
    meta::named_sink<void(*)(InputType)> them(f, name);
    dsl::skeleton_terminal< meta::named_sink<void(*)(InputType)> > that( them );
    return that;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Macro for declaring global sink object
/////////////////////////////////////////////////////////////////////////////
#define QUAFF_SINK(Name,Function)               \
BOOST_PROTO_AUTO(Name, quaff::sink(Function) )  \
/**/

/////////////////////////////////////////////////////////////////////////////
// Macro for declaring global sink object with a name
/////////////////////////////////////////////////////////////////////////////
#define QUAFF_NAMED_SINK(Name,Function)                                     \
BOOST_PROTO_AUTO(Name, quaff::sink(Function,BOOST_PP_STRINGIZE(Function)) ) \
/**/

#endif
