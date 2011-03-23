/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__TYPES__SELECTION_HPP__INCLUDED__
#define __QUAFF__CORE__TYPES__SELECTION_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/types/selection.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  /*****************************************************************************
   * Evaluates as mpl::true_ if T is a remanent type.
   ****************************************************************************/
  template<class T> struct is_remanent                       : bm::false_ {};
  template<class T> struct is_remanent< remanent<T>& >       : bm::true_  {};
  template<class T> struct is_remanent< remanent<T> const& > : bm::true_  {};

  /*****************************************************************************
   * Evaluates as mpl::true_ if T is an output type.
   ****************************************************************************/
  template<class T> struct is_an_output                            : bm::false_  {};
  template<class T,long M> struct is_an_output< data<T,M>& >       : bm::false_  {};
  template<class T> struct is_an_output< remanent<T>& >            : bm::false_  {};
  template<class T> struct is_an_output< T& >                      : bm::true_   {};
  template<class T> struct is_an_output< T const& >                : bm::false_  {};

  /*****************************************************************************
   * Evaluates as mpl::true_ if T is an input type.
   ****************************************************************************/
  template<class T>         struct is_an_input                : bm::true_   {};
  template<class T>         struct is_an_input<T&>            : bm::false_  {};
  template<class T>         struct is_an_input<T const&>      : bm::true_   {};
  template<class T,long M>  struct is_an_input< data<T,M>& >  : bm::true_   {};
}

#endif
