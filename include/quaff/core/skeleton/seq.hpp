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
#include <quaff/sdk/meta/action.hpp>
#include <boost/utility/enable_if.hpp>
#include <quaff/core/dsl/terminal.hpp>
#include <boost/proto/proto_typeof.hpp>
#include <quaff/sdk/meta/is_callable.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <string>


namespace quaff
{
  /////////////////////////////////////////////////////////////////////////////
  // Turn function pointer into seq skeleton usign action<>
  /////////////////////////////////////////////////////////////////////////////

  
  template<class Out, class In>
  dsl::skeleton_terminal< meta::named_action<Out, In> >
  seq( Out(*f)(In), const std::string func_name )
  {
    meta::action<Out(*)(In)> them = f;
    meta::named_action<Out, In> test = meta::named_action<Out, In>(them, func_name);
    dsl::skeleton_terminal< meta::named_action<Out, In> > that( test );
    return that;
  }
  
  
  

  /////////////////////////////////////////////////////////////////////////////
  // Macro for declaring global seq object
  /////////////////////////////////////////////////////////////////////////////
  #define QUAFF_TASK(Name,Function)             \
  BOOST_PROTO_AUTO(Name, quaff::seq(Function) ) \
  /**/
  #define SEQ(Function) \
  seq(Function, #Function) \
  /**/
}

#endif
