/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_DSL_TERMINAL_HPP_INCLUDED
#define QUAFF_CORE_DSL_TERMINAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/dsl/expression.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <quaff/core/dsl/expression.hpp>

namespace quaff { namespace dsl
{
  template<class Func, class Dummy = boost::proto::is_proto_expr>
  struct  skeleton_terminal
        : public skeletons<typename boost::proto::terminal<Func>::type >
  {
    ////////////////////////////////////////////////////////////////////////////
    // Internal typedefs
    ////////////////////////////////////////////////////////////////////////////
    typedef skeletons<typename boost::proto::terminal<Func>::type > parent;

    ////////////////////////////////////////////////////////////////////////////
    // Constructor & cie
    ////////////////////////////////////////////////////////////////////////////
    explicit skeleton_terminal(Func const &f)
    {
      boost::proto::value(*this) = f;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Functional interface (TODO)
    ////////////////////////////////////////////////////////////////////////////
  };
} }

#endif
