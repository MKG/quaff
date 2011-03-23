#ifndef __QUAFF__CORE__LANGUAGE__FUNCTION__SCM_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__FUNCTION__SCM_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/function/scm.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  template<class Map, class S, class C, class M> struct scm_result
  {
    static const long R = Map::real_size-1;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,(scm_master<Map>(S(),C(),M()) * pardo<R>( scm_worker<Map>(C()))))
    typedef typename nested::type type;
  };

  template<int V, int R, class S, class C, class M>
  static inline typename scm_result<mapping<V,R>,S,C,M>::type
  scm( const S& s,const C& c,const M& m )
  {
    return scm_master< mapping<V,R> >(s,c,m) * pardo<R-1>( scm_worker< mapping<V,R> >(c) );
  }

  template<int R, class S, class C, class M>
  static inline typename scm_result<mapping<R,R>,S,C,M>::type
  scm( const S& s,const C& c,const M& m )
  {
    return scm_master< mapping<R,R> >(s,c,m) * pardo<R-1>( scm_worker< mapping<R,R> >(c) );
  }
}

 #endif
