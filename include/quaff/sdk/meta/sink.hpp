/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_SINK_HPP_INCLUDED
#define QUAFF_SDK_META_SINK_HPP_INCLUDED

#include <quaff/sdk/meta/is_callable.hpp>
#include <boost/function_types/result_type.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/sink.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace meta
{
  template<class S> struct  sink;
  
  //////////////////////////////////////////////////////////////////////////////
  //Turns a void(I) function into a sink Concretized Function Object
  //////////////////////////////////////////////////////////////////////////////
  template<class I> struct  sink<void(*)(I)> : callable
  {
    typedef void(*function_type)(I);

    typedef I                 input_type;
    typedef boost::mpl::void_ output_type;

    sink() {}
    sink(function_type const& f) : callee(f) {}

    sink& operator=(function_type const& f)
    {
      callee = f;
      return *this;
    }
    
    function_type get_function() const {
      return callee;
    }

    inline output_type operator()(input_type const& in) const
    {
      callee(in);
      return output_type();
    }
    
    inline std::string name_of() const{
      return "<unamed>";
    }

    private:
    function_type callee;
  };
  
  template<class I>
  struct  named_sink : sink<void(*)(I) >
  {
    typedef void(*function_type)(I);

    typedef I                 input_type;
    typedef boost::mpl::void_ output_type;
    
    named_sink() {}

    named_sink(sink<void(*)(I)> const& s, std::string const& n) 
    : callee(s.get_function()), name(n) {}
    
    inline std::string name_of() const{
      return name;
    }
    
    private :
    std::string name;
    function_type callee;
  };

} }

#endif
