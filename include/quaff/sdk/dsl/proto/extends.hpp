/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_DSL_PROTO_EXTENDS_HPP
#define QUAFF_SDK_DSL_PROTO_EXTENDS_HPP

#include <quaff/sdk/preprocessor.hpp>

////////////////////////////////////////////////////////////////////////////////
// BOOST_PROTO_BASIC_EXTENDS working with template Domain
////////////////////////////////////////////////////////////////////////////////
#define BOOST_PROTO_BASIC_EXTENDS_TPL(Expr, Derived, Domain)                  \
BOOST_PROTO_BASIC_EXTENDS_( QUAFF_PP_STRIP(Expr)                              \
                          , QUAFF_PP_STRIP(Derived)                           \
                          , QUAFF_PP_STRIP(Domain)                            \
                          )                                                   \
typedef void                                            proto_is_aggregate_;  \
typedef typename QUAFF_PP_STRIP(Domain)::proto_generator  proto_generator;    \
/**/

#endif
