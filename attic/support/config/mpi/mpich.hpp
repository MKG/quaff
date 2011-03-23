/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__MPI__MPICH_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__MPI__MPICH_HPP__INCLUDED__

#include <boost/preprocessor/stringize.hpp>

#if !defined(CONFIG_MPI_DETECTED)
#if defined(MPICH2)
#define CONFIG_MPI_DETECTED
#define CONFIG_MPI_MPICH2

namespace quaff
{
  static inline const char* mpi_string() { return "MPICH" BOOST_PP_STRINGIZE(MPICH_NAME) " " MPICH2_VERSION; }
}
#endif
#endif
#endif
