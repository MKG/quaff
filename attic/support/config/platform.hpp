/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__SUPPORT__CONFIG__PLATFORM_HPP__INCLUDED__
#define __QUAFF__SUPPORT__CONFIG__PLATFORM_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Platform configuration file.
///
/// platform.hpp contains macro that detect the current platform used to
/// compile an application through a set of preprocessor defines. Feel free
/// to add any specific platform support by adding the correct file in the
/// plug_in/config/platform/ folder.
////////////////////////////////////////////////////////////////////////////////

//#include <quaff/plug_in/support/config/platform/platform.hpp>

#include <quaff/support/config/platform/nix.hpp>
#include <quaff/support/config/platform/windows.hpp>
#include <quaff/support/config/platform/macos.hpp>
#include <quaff/support/config/platform/none.hpp>

#endif
