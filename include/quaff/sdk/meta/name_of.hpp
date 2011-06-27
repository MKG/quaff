/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_NAME_OF_HPP_INCLUDED
#define QUAFF_SDK_META_NAME_OF_HPP_INCLUDED

#include <quaff/sdk/meta/named_sink.hpp>
#include <quaff/sdk/meta/named_action.hpp>
#include <quaff/sdk/meta/named_source.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/name_of.hpp
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace meta
{
  template<class Callable>
  inline std::string name_of(Callable const&)
  {
    return "unnamed";
  }

  template<class Callable>
  inline std::string name_of(named_action<Callable> const& c)
  {
    return c.name();
  }

  template<class Callable>
  inline std::string name_of(named_sink<Callable> const& c)
  {
    return c.name();
  }

  template<class Callable>
  inline std::string name_of(named_source<Callable> const& c)
  {
    return c.name();
  }
} }

#endif
