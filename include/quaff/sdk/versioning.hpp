/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_CONFIG_VERSIONING_HPP_INCLUDED
#define QUAFF_SDK_CONFIG_VERSIONING_HPP_INCLUDED

#include <boost/system/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#define QUAFF_VERSION_MESSAGE _library_version_mismatch_

////////////////////////////////////////////////////////////////////////////////
// Define a library version
////////////////////////////////////////////////////////////////////////////////
#define QUAFF_USE_LIBRARY_VERSION(S,V)                    \
namespace quaff { namespace config                        \
{                                                         \
  bool BOOST_SYSTEM_DECL                                  \
  BOOST_PP_CAT(S,BOOST_PP_CAT(QUAFF_VERSION_MESSAGE,V))() \
  {                                                       \
    return true;                                          \
  }                                                       \
} }                                                       \
/**/

////////////////////////////////////////////////////////////////////////////////
// Register a version for the library using a given symbol absed on feature list
////////////////////////////////////////////////////////////////////////////////
#define QUAFF_REGISTER_LIBRARY_VERSION(S,V)                 \
namespace quaff { namespace config                          \
{                                                           \
  bool BOOST_SYSTEM_DECL                                    \
  BOOST_PP_CAT(S,BOOST_PP_CAT(QUAFF_VERSION_MESSAGE,V))();  \
  bool const BOOST_PP_CAT(check_,BOOST_PP_CAT(S,V)) =       \
  BOOST_PP_CAT(S,BOOST_PP_CAT(QUAFF_VERSION_MESSAGE,V))();  \
} }                                                         \
/**/

#endif
