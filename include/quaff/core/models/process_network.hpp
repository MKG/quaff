/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// This file defines the process network based intermediate representation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Tag markup for identifying current model
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace tag { struct process_network_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// Model forward declaration and entities
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/models/process_network/forward.hpp>
#include <quaff/core/models/process_network/environment.hpp>
#include <quaff/core/models/process_network/network.hpp>
#include <quaff/core/models/process_network/joint_network.hpp>
#include <quaff/core/models/process_network/process.hpp>
#include <quaff/core/models/process_network/empty.hpp>

////////////////////////////////////////////////////////////////////////////////
// Model semantic rules
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/models/process_network/transform.hpp>
#include <quaff/core/models/process_network/semantic/rule_seq.hpp>
#include <quaff/core/models/process_network/semantic/rule_pipe.hpp>
#include <quaff/core/models/process_network/semantic/rule_pardo.hpp>

#endif
