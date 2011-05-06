/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_DSL_EXPRESSION_HPP_INCLUDED
#define QUAFF_CORE_DSL_EXPRESSION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/dsl/expression.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <quaff/core/dsl/domain.hpp>

namespace quaff { namespace dsl
{
  template<class Expr>
  struct  skeleton_expression
        : boost::proto::extends<Expr,skeleton_expression<Expr>,skeleton_domain>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Internal typedefs
    ////////////////////////////////////////////////////////////////////////////
    typedef boost::proto
            ::extends<Expr,skeleton_expression<Expr>,skeleton_domain> parent;

    ////////////////////////////////////////////////////////////////////////////
    // Constructor & cie
    ////////////////////////////////////////////////////////////////////////////
    explicit skeleton_expression(Expr const &expr = Expr()) : parent(expr) {}

    ////////////////////////////////////////////////////////////////////////////
    // Functional interface (TODO)
    ////////////////////////////////////////////////////////////////////////////
  };

} }

#endif
