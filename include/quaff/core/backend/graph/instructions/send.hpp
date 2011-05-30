/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_GRAPH_INSTRUCTIONS_SEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_GRAPH_INSTRUCTIONS_SEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/graph/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/as_set.hpp>

namespace quaff { namespace instruction
{
  template<class Destinations>
  struct send<Destinations,backend::graph_>
  {
    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const& , Input&, Output&, Context& ) const {}
  };
} }

#endif
