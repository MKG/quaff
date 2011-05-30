/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_GRAPH_RUNTIME_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_GRAPH_RUNTIME_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/graph/backend.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/include/vector_tie.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generate a debug on the standard output
////////////////////////////////////////////////////////////////////////////////
template<class X, class Stream> void graph(X const& xpr, Stream& os)
{
  quaff::semantic::convert<quaff::tag::process_network_>  converter;
  quaff::model::empty_environment                         env;
  quaff::backend::graph_ target;

  target.accept ( boost::fusion::vector_tie ( converter(xpr,env,target).network()
                                            , os
                                            )
                );
}

#include <quaff/core/backend/graph/instructions/call.hpp>
#include <quaff/core/backend/graph/instructions/send.hpp>
#include <quaff/core/backend/graph/instructions/receive.hpp>

#endif
