#ifndef __QUAFF__CORE__LANGUAGE__FUNCTION__PIPELINE_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__FUNCTION__PIPELINE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/function/pipeline.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  template<int N, class Seq> struct pipeliner
  {
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,(Seq() | pipeliner<N-1,Seq>::Do(Seq())))
    typedef typename nested::type type;

    static inline type Do( const Seq& s )
    {
      return s | pipeliner<N-1,Seq>::Do(s);
    }
  };

  template<class Seq> struct pipeliner<1,Seq>
  {
    typedef const Seq& type;
    static inline const Seq& Do( const Seq& s) { return s; }
  };

  template<int N, class Seq> static inline
  typename pipeliner<N,Seq>::type pipeline( const Seq& s)
  {
    return pipeliner<N,Seq>::Do(s);
  }

  #define QUAFF_VARARG(z,n,text) text BOOST_PP_CAT(t,n)
  #define QUAFF_VARTPL(z,n,text) text BOOST_PP_CAT(T,n)()

  template<class T0             , class T1             , class T2  = bm::void_
          ,class T3 = bm::void_ , class T4  = bm::void_, class T5  = bm::void_
          ,class T6 = bm::void_ , class T7  = bm::void_, class T8  = bm::void_
          ,class T9 = bm::void_ , class T10 = bm::void_, class T11 = bm::void_
          > struct repeat_pipe;

  #define QUAFF_PIPE(z,n,text)                                            \
  template<BOOST_PP_ENUM_PARAMS(n,class T)>                               \
  struct repeat_pipe<BOOST_PP_ENUM_PARAMS(n,T)>                           \
  {                                                                       \
    typedef BOOST_TYPEOF_TPL(T0()                                         \
                             BOOST_PP_REPEAT_FROM_TO(1,n,QUAFF_VARTPL,|)) \
                             type;                                        \
  };                                                                      \
  template<BOOST_PP_ENUM_PARAMS(n,class T)> static inline                 \
  typename repeat_pipe<BOOST_PP_ENUM_PARAMS(n,T)>::type                   \
  pipeline( BOOST_PP_ENUM_BINARY_PARAMS(n,const T,& t) )                  \
  {                                                                       \
    return t0 BOOST_PP_REPEAT_FROM_TO(1,n,QUAFF_VARARG,|);                \
  }                                                                       \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,12,QUAFF_PIPE,~)
}

 #endif
