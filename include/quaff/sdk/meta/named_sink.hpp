/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_NAMED_SINK_HPP_INCLUDED
#define QUAFF_SDK_META_NAMED_SINK_HPP_INCLUDED

#include <quaff/sdk/meta/sink.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/named_sink.hpp
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace meta
{
  template<class Callable>
  struct  named_sink : sink<Callable>
  {
    typedef sink<Callable> parent;

    named_sink() {}

    named_sink( Callable const& f, std::string const& n )
                : parent(f), id(n) {}

    inline std::string const& name() const { return id; }

    private :
    std::string id;
  };
} }

#endif
