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

////////////////////////////////////////////////////////////////////////////////
// the text debug back-end is always available
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/backend/debug/backend.hpp>

#if defined(QUAFF_TARGET_MPI)
#else
#include <quaff/core/backend/sequential/backend.hpp>
#endif

namespace quaff
{
  inline void start()     { current_backend.start(); }
  inline void terminate() { current_backend.terminate(); }
}

#endif
