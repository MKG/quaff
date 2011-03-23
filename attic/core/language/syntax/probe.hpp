#ifndef __QUAFF__CORE__LANGUAGE__SYNTAX__PROBE_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SYNTAX__PROBE_HPP__INCLUDED__

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
#include <string>

namespace quaff
{
  template<class Expr> static inline
  string_type probe( const skeleton_expression<Expr>& )
  {
    string_type str;
    typedef typename make_network<Expr>::type::type network;
    network::probe(str);
    return str;
  }
}

#endif

