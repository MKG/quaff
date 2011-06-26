/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_SKELETON_SEQ_HPP_INCLUDED
#define QUAFF_CORE_SKELETON_SEQ_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/skeleton/seq.hpp
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <quaff/sdk/meta/action.hpp>
#include <quaff/sdk/meta/named_action.hpp>
#include <quaff/core/dsl/terminal.hpp>
#include <boost/proto/proto_typeof.hpp>

namespace quaff
{
  /////////////////////////////////////////////////////////////////////////////
  // Turn function pointer into seq skeleton usign action<>
  /////////////////////////////////////////////////////////////////////////////
  template<class Out, class In>
  dsl::skeleton_terminal< meta::action<Out(*)(In)> >
  seq( Out(*f)(In) )
  {
    meta::action<Out(*)(In)> them = f;
    dsl::skeleton_terminal< meta::action<Out(*)(In)> > that( them );
    return that;
  }
  
  template<class Out, class In>
  dsl::skeleton_terminal< meta::named_action<Out(*)(In)> >
  seq( Out(*f)(In), std::string const& name )
  {
    meta::named_action<Out(*)(In)> them(f, name);
    dsl::skeleton_terminal< meta::named_action<Out(*)(In)> > that( them );
    return that;
  }
  
  /////////////////////////////////////////////////////////////////////////////
  // Macro for declaring global seq object
  /////////////////////////////////////////////////////////////////////////////
  #define QUAFF_TASK(Name,Function)             \
  BOOST_PROTO_AUTO(Name, quaff::seq(Function) ) \
  /**/

  /////////////////////////////////////////////////////////////////////////////
  // Macro for declaring global seq object with a name
  /////////////////////////////////////////////////////////////////////////////
  #define QUAFF_NAMED_TASK(Name,Function)                                     \
  BOOST_PROTO_AUTO(Name, quaff::seq(Function,BOOST_PP_STRINGIZE(Function)) )  \
  /**/
}

#endif
