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
  /*****************************************************************************
   * Turns builtin Callable Object into Callable Action by reinjecting their
   * return type as a reference argument.
   ****************************************************************************/
  template<class Function>
  struct  action : callable
  {
    typedef Function  function_type;
    typedef void      result_type;

    action() {}
    action(Function const& f) : callee(f) {}

    action& operator=(Function const& f)
    {
      callee = f;
      return *this;
    }

    /***************************************************************************
     * Don't handle perfect forwarding fully to avoid 2^n PP stuff
     * We basically play on the fact the arguments will never be temporaries
     * but will leaves in some arguments fusion sequence.
     **************************************************************************/
    #define M0(z,n,t)                                               \
    template<class R, BOOST_PP_ENUM_PARAMS(n,class A)> inline void  \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a), R& r) const   \
    {                                                               \
      r = callee(BOOST_PP_ENUM_PARAMS(n,a));                        \
    }                                                               \
    /**/

    template<class R> inline void operator()(R& r) const { r = callee(); }
    BOOST_PP_REPEAT_FROM_TO(1,QUAFF_MAX_FUNCTION_ARITY,M0,~)

    #undef M0


    private:
    Function callee;
  };

} }

#endif
