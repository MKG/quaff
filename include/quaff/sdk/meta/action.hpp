/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_ACTION_HPP_INCLUDED
#define QUAFF_SDK_META_ACTION_HPP_INCLUDED

#include <quaff/sdk/meta/is_callable.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/action.hpp
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * By default, handle up to 16 arguments in action function
 ******************************************************************************/
#ifndef QUAFF_MAX_FUNCTION_ARITY
#define QUAFF_MAX_FUNCTION_ARITY 17
#endif

namespace quaff { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // action takes some Callable and adapt it to the Concretized Function Object
  // we require.
  //////////////////////////////////////////////////////////////////////////////
  template<class Callable> struct  action;
  

  //////////////////////////////////////////////////////////////////////////////
  // Plain C function of the form O (*)(I)
  //////////////////////////////////////////////////////////////////////////////
  template<class Output, class Input>
  struct  action<Output (*) (Input) > : callable
  {
    typedef Output  (*function_type)(Input);

    typedef Input     input_type;
    typedef Output    output_type;

    action() {}
    action(function_type const& f) : callee(f) {}
    
    function_type get_function() const {
      return callee;
    }

    action& operator=(function_type const& f)
    {
      callee = f;
      return *this;
    }
    
    inline std::string name_of() const{
      return "<unamed>";
    }

    inline Output operator()(Input in) const
    {
      return callee(in);
    }

    private:
    function_type callee;
  };
  
  template<class Output, class Input>
  struct  named_action : action<Output (*) (Input) >
  {
    typedef Output  (*function_type)(Input);

    typedef Input     input_type;
    typedef Output    output_type;
    
    named_action() {}

    named_action(action<Output (*) (Input) > const& a, std::string const& n) 
    : callee(a.get_function()), name(n) {}
    
    inline std::string name_of() const{
      return name;
    }
    
    private :
    std::string name;
    function_type callee;
  };
  
} }

#endif
