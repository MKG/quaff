/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_NAMED_SOURCE_HPP_INCLUDED
#define QUAFF_SDK_META_NAMED_SOURCE_HPP_INCLUDED

#include <string>
#include <quaff/sdk/meta/source.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/named_source.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace meta
{
  template<class Callable>
  struct  named_source : source<Callable>
  {
    typedef source<Callable> parent;
    
    named_source() {}

    named_source(Callable const& f, std::string const& n)
                : parent(f), id(n) {}
    
    inline std::string name() const { return id; }
    
    private :
    std::string id;
  };
} }

#endif
