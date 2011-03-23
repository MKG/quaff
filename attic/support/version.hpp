/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__VERSION_HPP__INCLUDED__
#define __QUAFF__SUPPORT__VERSION_HPP__INCLUDED__

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  // QUAFF version information
  //////////////////////////////////////////////////////////////////////////////
  static inline const char* version_string() { return PACKAGE_VERSION; }

  //////////////////////////////////////////////////////////////////////////////
  // Code name
  // Starting with V1.0r1, quaff release receives code name.
  //
  //  S - Codename - Features
  // [X]  Alvitr     First production release
  // [@]  Brynhildr  Use boost::mpi
  // [ ]  Hildr      Integrates CELL support
  // [ ]  Olrun      Integrates MPI-free multi-core support
  // [ ]  Pruor      Hardware code generation
  // [ ]  Sigrdrifa  Heterogeneous machines support
  // [ ]  Sigrun
  // [ ]  Svava
  // [ ]  Svanhvit
  //////////////////////////////////////////////////////////////////////////////
  static inline const char* release_string() { return "Brynhildr"; }
}

#endif
