/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__TYPES__ADAPTATOR_HPP__INCLUDED__
#define __QUAFF__CORE__TYPES__ADAPTATOR_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/types/count.hpp
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/void.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>

namespace quaff
{
  /*****************************************************************************
   * User function adaptator - Turn a free function into a dispatchable function
   * Object. Valid user functions should match the following prototype :
   *
   * RET f( [ [const] IN[&] in]*, [OUT& out]*, [ remanent<T>& m]* )
   *
   * where [] means optional element and * means 0 or N repetition.
   * Types of input, output and remanent types should be default-constructible
   * copyable and should either take care of their own memory allocation or be
   * a POD. Return types are either any types or data<T> for stream source.
   ****************************************************************************/
  template< class         FunctionType,
            FunctionType  Function,
            class         Functor   = bm::void_,
            class         Return    = typename bf::result_type<FunctionType>::type,
            int           Input     = count_input<FunctionType>::value,
            int           Output    = count_output<FunctionType,Functor>::value,
            int           Remanent  = count_remanent<FunctionType>::value
          >
  struct adaptator;
}

#ifndef QUAFF_PP_CONFIG_MAX_ARITY
#define QUAFF_PP_CONFIG_MAX_ARITY 10
#endif

#endif
