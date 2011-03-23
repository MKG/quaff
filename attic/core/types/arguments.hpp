/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__TYPES__ARGUMENTS_HPP__INCLUDED__
#define __QUAFF__CORE__TYPES__ARGUMENTS_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/types/arguments.hpp
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_same.hpp>

namespace quaff
{
  namespace bf = boost::function_types;

  template<class T>
  struct strip : boost::remove_const<typename boost::remove_reference<typename boost::remove_const<T>::type >::type > {};

  /*****************************************************************************
   * Build a tuple of all remanent parameters for a given function
   ****************************************************************************/
  template<class FunctionType> struct build_remanent_list
  {
    typedef typename bf::parameter_types<FunctionType>::type params;
    typedef typename bm::reverse_fold< params, bt::null_type,
                               bm::if_<is_remanent<bm::_2>,
                               bt::cons< strip<bm::_2>, bm::_1 >
                              ,bm::_1>
                     >::type type;
  };

  /*****************************************************************************
   * Build a tuple of all input parameters for a given function
   ****************************************************************************/
  template<class FunctionType> struct build_input_list
  {
    typedef typename bf::parameter_types<FunctionType>::type params;
    typedef typename bm::reverse_fold< params, bt::null_type
                                     , bm::if_<is_an_input<bm::_2>
                                     , bt::cons< strip<bm::_2>,bm::_1 >
                                     , bm::_1>
                     >::type type;
  };

  /*****************************************************************************
   * Build a tuple of all output parameters for a given function
   ****************************************************************************/
  template<class FunctionType, class IsFunctor>
  struct build_output_list
  {
    typedef typename bf::parameter_types<FunctionType>::type  param_type;
    typedef typename bf::result_type<FunctionType>::type      return_type;

    typedef typename bm::if_< IsFunctor,
                          typename bm::pop_front<param_type>::type,
                          param_type
                        >::type                           params;

    typedef typename bm::reverse_fold<params,
                                  bt::null_type,
                                  bm::if_<is_an_output<bm::_2>,
                                      bt::cons< strip<bm::_2> ,bm::_1 >,
                                      bm::_1
                                     >
                                 >::type                  base;

    typedef typename bm::if_< boost::is_same<return_type,void>,
                          base,
                          bt::cons< typename strip<return_type>::type,base>
                        >::type                           type;
  };
}
#endif

