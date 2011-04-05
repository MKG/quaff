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
#include <quaff/core/models/process_network/semantic/apply_rule.hpp>
#include <quaff/core/models/process_network/semantic/rule_seq.hpp>
#include <quaff/core/models/process_network/semantic/rule_pardo.hpp>

namespace quaff { namespace model
{
  struct  build_network
        : boost::proto::
          or_ < boost::proto::
                when< boost::proto::terminal<boost::proto::_>
                    , convert_seq ( boost::proto::_value
                                  , pid_(boost::proto::_state)
                                  , boost::proto::_data
                                  )
                    >                  
              , boost::proto::
                when< boost::proto::bitwise_and < boost::proto::_
                                                , boost::proto::_
                                                >
                    , convert_pardo ( boost::proto::_left
                                    , boost::proto::_right
                                    , boost::proto::_state
                                    , boost::proto::_data
                                    )
                    >
              >
  {};
} }

#endif
