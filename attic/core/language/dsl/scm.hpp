#ifndef __QUAFF__CORE__DSL__SCM_HPP__INCLUDED__
#define __QUAFF__CORE__DSL__SCM_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/dsl/scm.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  ////////////////////////////////////////////////////////////////////////////////
  /// @brief Data-parallel partionning informations
  /// This type holds two integral consatnts values that represent how a given
  /// stream element has to be split in a SCM skeleton and on how many processes
  /// those parts should be distributed.
  ////////////////////////////////////////////////////////////////////////////////
  template<long Virtual, long Real = Virtual> struct mapping
  {
    static const long real_size     = Real;
    static const long virtual_size  = Virtual;
  };

  ////////////////////////////////////////////////////////////////////////////////
  /// @brief Data-parallel worker creation function
  ////////////////////////////////////////////////////////////////////////////////
  template<class Map,class S,class C,class M>
  typename bp::result_of::make_expr<bp::tag::function,master_<Map>,S,C,M>::type
  scm_master(S const &s, C const &c, M const &m)
  {
    return bp::make_expr<bp::tag::function>(master_<Map>(),s,c,m);
  }

  ////////////////////////////////////////////////////////////////////////////////
  /// @brief Data-parallel worker creation function
  ////////////////////////////////////////////////////////////////////////////////
  template<class Map,class Arg>
  typename bp::result_of::make_expr<bp::tag::function,worker_<Map>,Arg>::type
  scm_worker(Arg const &arg)
  {
    return bp::make_expr<bp::tag::function>(worker_<Map>(), arg);
  }
}

#endif

