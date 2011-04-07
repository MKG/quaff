/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_TRANSFORM_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_TRANSFORM_HPP_INCLUDED

#include <quaff/core/dsl/semantic.hpp>

namespace quaff { namespace semantic
{
  //////////////////////////////////////////////////////////////////////////////
  // Switch table for the proto transform turnign a skeleton AST into a process
  // network. This allow for external extension of skeleton set
  //////////////////////////////////////////////////////////////////////////////
  struct process_network_cases
  {
    template<typename Tag>
    struct  case_ : boost::proto::not_< boost::proto::_ >
    {};
  };

  //////////////////////////////////////////////////////////////////////////////
  // Generate a process network based IR
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct  convert< quaff::tag::process_network_ >
        : boost::proto::switch_<process_network_cases>
  {};
} }

namespace boost { namespace proto
{
  //////////////////////////////////////////////////////////////////////////////
  // convert is a callable transform
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct  is_callable < quaff::semantic::
                        convert<quaff::tag::process_network_>
                      >
        : boost::mpl::true_  {};
} }

#endif
