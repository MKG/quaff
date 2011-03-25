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
#include <boost/utility/enable_if.hpp>
#include <quaff/core/dsl/terminal.hpp>
#include <boost/proto/proto_typeof.hpp>
#include <quaff/sdk/meta/is_callable.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>

namespace quaff
{
  template<class Function>
  typename boost::enable_if_c < meta::is_callable<Function>::value
                              , dsl::skeleton_terminal<Function>
                              >::type

  seq( Function const& f )
  {
    dsl::skeleton_terminal< Function > that( f );
    return that;
  }

  template<class Function>
  typename
  boost::enable_if_c< boost::is_function<Function>::value
                    , dsl::skeleton_terminal< boost::function<Function> >
                    >::type
  seq( Function* f )
  {
    boost::function<Function> them = f;
    dsl::skeleton_terminal< boost::function<Function> > that( them );
    return that;
  }

  /////////////////////////////////////////////////////////////////////////////
  // Macro for declaring global seq object
  /////////////////////////////////////////////////////////////////////////////
  #define QUAFF_TASK(Name,Function)             \
  BOOST_PROTO_AUTO(Name, quaff::seq(Function) ) \
  /**/
}

#endif