#ifndef __QUAFF__CORE__LANGUAGE__SYNTAX__RUN_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SYNTAX__RUN_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/syntax/syntax.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  template<class Expr> static inline
  void run( const skeleton_expression<Expr>& )
  {
    typedef typename make_network<Expr>::type::type network;
    network::run();
  }
}

#endif

