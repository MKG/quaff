/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_DSL_FROM_DOMAIN_HPP_INCLUDED
#define QUAFF_SDK_DSL_FROM_DOMAIN_HPP_INCLUDED

#include <boost/proto/proto.hpp>

////////////////////////////////////////////////////////////////////////////////
// from_domain is a function that wraps an expression from domain X in domain Y
////////////////////////////////////////////////////////////////////////////////
namespace quaff
{
  namespace tag { struct from_domain_ {}; }

  template<class Expression>
  typename  boost::proto::result_of::
            make_expr < tag::from_domain_
                      , typename boost::proto::uncvref<Expression>::type const&
                      >::type
  from_domain( Expression const& xpr )
  {
    return boost::proto::make_expr<tag::from_domain_>( boost::cref(xpr) );
  }
}

////////////////////////////////////////////////////////////////////////////////
// from_domain also exists as proto grammar to be used in other EDSL gammars
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace dsl
{
  template<class Expr>
  struct from_domain : boost::proto::unary_expr<tag::from_domain_,Expr> {};
} }

#endif
