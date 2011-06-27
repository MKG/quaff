/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_SKELETON_SOURCE_HPP_INCLUDED
#define QUAFF_CORE_SKELETON_SOURCE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/skeleton/source.hpp
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <quaff/core/dsl/terminal.hpp>
#include <boost/proto/proto_typeof.hpp>
#include <quaff/sdk/meta/named_source.hpp>

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn function pointer into seq skeleton usign action<>
  //////////////////////////////////////////////////////////////////////////////
  template<class ReturnType>
  dsl::skeleton_terminal< meta::source<ReturnType(*)()> >
  source( ReturnType(*f)() )
  {
    meta::source<ReturnType(*)()> them = f;
    dsl::skeleton_terminal< meta::source<ReturnType(*)()> > that( them );
    return that;
  }

  template<class ReturnType>
  dsl::skeleton_terminal< meta::named_source<ReturnType(*)()> >
  source( ReturnType(*f)(), const std::string& name )
  {
    meta::named_source<ReturnType(*)()> them(f, name);
    dsl::skeleton_terminal< meta::named_source<ReturnType(*)()> > that( them );
    return that;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Macro for declaring global sink object
/////////////////////////////////////////////////////////////////////////////
#define QUAFF_SOURCE(Name,Function)               \
BOOST_PROTO_AUTO(Name, quaff::source(Function) )  \
/**/

/////////////////////////////////////////////////////////////////////////////
// Macro for declaring global sink object with a name
/////////////////////////////////////////////////////////////////////////////
#define QUAFF_NAMED_SOURCE(Name,Function)                                     \
BOOST_PROTO_AUTO(Name, quaff::source(Function,BOOST_PP_STRINGIZE(Function)) ) \
/**/

#endif
