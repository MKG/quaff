/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_BACKEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_BACKEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/backend.hpp
////////////////////////////////////////////////////////////////////////////////

#include <quaff/core/backend/forward.hpp>
#include <quaff/core/backend/debug/backend.hpp>
#include <quaff/core/backend/graph/backend.hpp>

#if defined(QUAFF_TARGET_MPI)
#include <quaff/core/backend/mpi/backend.hpp>
#elif defined(QUAFF_TARGET_SCMP)
#include <quaff/core/backend/scmp/backend.hpp>
#else
#include <quaff/core/backend/sequential/backend.hpp>
#endif

#include <quaff/core/backend/runtime.hpp>

#endif
