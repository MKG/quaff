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

#include <quaff/core/models/process_network/network.hpp>
#include <quaff/core/models/process_network/process.hpp>
#include <quaff/core/models/process_network/descriptor.hpp>
#include <quaff/core/models/process_network/semantic/environment.hpp>
#include <quaff/core/models/process_network/semantic/rule_seq.hpp>

namespace quaff { namespace model
{
  template<class BackEnd>
  struct  make_network
        : boost::proto::
          when< boost::proto::terminal<boost::proto::_>
              , environment < apply_rule<tag::seq_,BackEnd> ( boost::proto::_value
                                                            , pid_(boost::proto::_state)
                                                            )
                            , pid_(boost::proto::_state)
                            >(  apply_rule<tag::seq_,BackEnd> ( boost::proto::_value
                                                              , pid_(boost::proto::_state)
                                                              )
                             )
              >
  {};
} }

#endif
