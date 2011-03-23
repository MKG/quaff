#ifndef __QUAFF__CORE__LANGUAGE__FUNCTION__PARDO_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__FUNCTION__PARDO_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/function/pardo.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  template<int N, class Seq> struct pardoer
  {
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,(Seq() & pardoer<N-1,Seq>::Do(Seq())))
    typedef typename nested::type type;

    static inline type Do( const Seq& s )
    {
      return s & pardoer<N-1,Seq>::Do(s);
    }
  };

  template<class Seq> struct pardoer<1,Seq>
  {
    typedef const Seq& type;
    static inline const Seq& Do( const Seq& s) { return s; }
  };

  template<int N, class Seq> static inline
  typename pardoer<N,Seq>::type pardo( const Seq& s)
  {
    return pardoer<N,Seq>::Do(s);
  }

  template<class T0             , class T1             , class T2  = bm::void_
          ,class T3 = bm::void_ , class T4  = bm::void_, class T5  = bm::void_
          ,class T6 = bm::void_ , class T7  = bm::void_, class T8  = bm::void_
          ,class T9 = bm::void_ , class T10 = bm::void_, class T11 = bm::void_
          > struct repeat_pardo;

  #define QUAFF_PARDO(z,n,text)                                           \
  template<BOOST_PP_ENUM_PARAMS(n,class T)>                               \
  struct repeat_pardo<BOOST_PP_ENUM_PARAMS(n,T)>                          \
  {                                                                       \
    typedef BOOST_TYPEOF_TPL(T0()                                         \
                             BOOST_PP_REPEAT_FROM_TO(1,n,QUAFF_VARTPL,&)) \
                             type;                                        \
  };                                                                      \
  template<BOOST_PP_ENUM_PARAMS(n,class T)> static inline                 \
  typename repeat_pardo<BOOST_PP_ENUM_PARAMS(n,T)>::type                  \
  pardo( BOOST_PP_ENUM_BINARY_PARAMS(n,const T,& t) )                     \
  {                                                                       \
    return t0 BOOST_PP_REPEAT_FROM_TO(1,n,QUAFF_VARARG,&);                \
  }                                                                       \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,12,QUAFF_PARDO,~)
}

 #endif

