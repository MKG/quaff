#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__SEMANTIC_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__SEMANTIC_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/semantic.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/language/semantic/common.hpp>
#include <quaff/core/language/semantic/tools/tools.hpp>

////////////////////////////////////////////////////////////////////////////////
/// Semantic data types and HOF
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/language/semantic/environnement.hpp>
#include <quaff/core/language/semantic/apply_rule.hpp>

////////////////////////////////////////////////////////////////////////////////
/// Basic skeletons related rules
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/language/semantic/rule_single.hpp>
#include <quaff/core/language/semantic/rule_seq.hpp>
#include <quaff/core/language/semantic/rule_par.hpp>
#include <quaff/core/language/semantic/rule_pipe.hpp>

////////////////////////////////////////////////////////////////////////////////
/// SCM related rules
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/language/semantic/rule_worker.hpp>
#include <quaff/core/language/semantic/rule_master.hpp>
#include <quaff/core/language/semantic/rule_link.hpp>

#endif


