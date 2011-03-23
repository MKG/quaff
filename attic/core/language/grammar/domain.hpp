#ifndef __QUAFF__CORE__LANGUAGE__GRAMMAR__DOMAIN_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__GRAMMAR__DOMAIN_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/grammar/definition.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/proto/context.hpp>
#include <boost/proto/transform.hpp>

namespace quaff
{
  namespace bp = boost::proto;

  struct skeleton_domain;

  template<typename Expr>
  struct skeleton_expression : bp::extends<Expr,skeleton_expression<Expr>,skeleton_domain>
  {
    typedef Expr expr_type;
    typedef bp::extends<Expr,skeleton_expression<Expr>,skeleton_domain> base_type;
    skeleton_expression() {}
    explicit skeleton_expression(Expr const &expr) : base_type(expr) {}
  };

  struct skeleton_domain : bp::domain<bp::generator<skeleton_expression>, skeleton > {};
}

#endif
