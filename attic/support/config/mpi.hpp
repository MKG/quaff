/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__MPI_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__MPI_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Architecture configuration file.
///
/// Performs the inclusion of all supported architecture include files
////////////////////////////////////////////////////////////////////////////////

#if defined(CONFIG_SUPPORT_MPI)
#define MPICH_SKIP_MPICXX
#include <boost/mpi.hpp>

#include <quaff/support/config/mpi/mpich.hpp>
#include <quaff/support/config/mpi/openmpi.hpp>

#elif defined(CONFIG_ARCH_CELL_BE)
#include <mpi/mpi.hpp>
#include <quaff/support/config/mpi/cbempi.hpp>
#endif

#endif
