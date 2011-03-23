/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__TYPES__COUNT_HPP__INCLUDED__
#define __QUAFF__CORE__TYPES__COUNT_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/types/count.hpp
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/void.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/if.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/is_same.hpp>

namespace quaff
{
  namespace bf = boost::function_types;

  namespace details
  {
    template<class FunctionType> struct count_input_impl
    {
      typedef typename bf::parameter_types<FunctionType>::type params;
      typedef typename bm::fold< params, bm::int_<0>,
                                     bm::if_<is_an_input<bm::_2>,
                                     bm::next<bm::_1>,bm::_1>
                           >::type type;
    };

    template<class FunctionType, class IsFunctor> struct count_output_impl
    {
      typedef typename bf::parameter_types<FunctionType>::type params;
      typedef typename bf::result_type<FunctionType>::type return_type;
      typedef typename bm::if_< boost::is_same<return_type,void>, bm::int_<0>, bm::int_<1> >::type val;

      typedef typename bm::fold< params, val,
                                     bm::if_<is_an_output<bm::_2>,
                                     bm::next<bm::_1>,bm::_1>
                           >::type base;

      typedef bm::int_< base::value-1 > type;
    };

    template<class FunctionType> struct count_output_impl<FunctionType,bm::void_>
    {
      typedef typename bf::parameter_types<FunctionType>::type params;
      typedef typename bf::result_type<FunctionType>::type return_type;
      typedef typename bm::if_< boost::is_same<return_type,void>, bm::int_<0>, bm::int_<1> >::type val;
      typedef typename bm::fold< params, val,
                                     bm::if_<is_an_output<bm::_2>,
                                     bm::next<bm::_1>,bm::_1>
                           >::type type;
    };

    template<class FunctionType> struct count_remanent_impl
    {
      typedef typename bf::parameter_types<FunctionType>::type params;
      typedef typename bm::fold< params, bm::int_<0>,
                                     bm::if_<is_remanent<bm::_2>,
                                     bm::next<bm::_1>,bm::_1>
                           >::type type;
    };
  }
  /*****************************************************************************
   * Evaluates how many 'input' a function prototype have
   ****************************************************************************/
  template<class FunctionType>
  struct count_input : details::count_input_impl<FunctionType>::type {};

  template<class FunctionType, class IsFunctor>
  struct count_output : details::count_output_impl<FunctionType,IsFunctor>::type {};

  template<class FunctionType>
  struct count_remanent : details::count_remanent_impl<FunctionType>::type {};
}

#endif

