/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_SOURCE_HPP_INCLUDED
#define QUAFF_SDK_META_SOURCE_HPP_INCLUDED

#include <quaff/sdk/meta/is_callable.hpp>
#include <boost/function_types/result_type.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/source.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace meta
{
  template<class S> struct source;
  
  //////////////////////////////////////////////////////////////////////////////
  //Turns a R() function into a source Concretized Function Object
  //////////////////////////////////////////////////////////////////////////////
  template<class R> struct  source<R(*)()> : callable
  {
    typedef R(*function_type)();

    typedef boost::mpl::void_ input_type;
    typedef R                 output_type;

    source() {}
    source(function_type const& f) : callee(f) {}

    source& operator=(function_type const& f)
    {
      callee = f;
      return *this;
    }
    
    function_type get_function() const {
      return callee;
    }
    
    inline std::string name_of() const{
      return "<unamed>";
    }

    inline output_type operator()(input_type const&) const { return callee(); }

    private:
    function_type callee;
  };
} }

#endif
