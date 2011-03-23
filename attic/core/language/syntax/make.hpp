#ifndef __QUAFF__CORE__LANGUAGE__SYNTAX__MAKE_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SYNTAX__MAKE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/common.hpp
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/int.hpp>
#include <boost/mpl/void.hpp>
#include <boost/proto/proto.hpp>

namespace quaff
{
  template<typename Expr>
  struct make_network : boost::result_of<skeleton(  Expr
                                                  , empty_environnement
                                                  , bm::void_
                                                  )
                                        > {};
}

#endif
