#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__ENVIRONEMENT_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__ENVIRONEMENT_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/environnement.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>

namespace quaff
{
  namespace bp = boost::proto;

  //////////////////////////////////////////////////////////////////////////////
  // Forward declaration for semantic actions
  //////////////////////////////////////////////////////////////////////////////
  struct skeleton;
  template<class FunctionObject>  struct user_function;
  template<typename Expr>         struct skeleton_expression;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Semantic environnement
  //////////////////////////////////////////////////////////////////////////////
  template<class CurrentPN,class CurrentPID>
  struct environnement
  {
    typedef CurrentPN   type; // Current process network
    typedef CurrentPID  pid;  // Current PID
  };

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Empty semantic environnement
  //////////////////////////////////////////////////////////////////////////////
  typedef environnement<empty_network, bm::int_<0> > empty_environnement;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief PID retrieval
  /// proto transform that retrieves the PID from a given environnement
  //////////////////////////////////////////////////////////////////////////////
  struct get_pid : bp::callable
  {
    template<class Sig> struct result;

    template<class This,class Expr, class State,class Visitor>
    struct result< This(Expr,State,Visitor)>
    {
      typedef typename State::pid type;
    };
  };

  //////////////////////////////////////////////////////////////////////////////
  /// @brief partial network evalaution
  /// Evaluate an AST as a partial process network
  //////////////////////////////////////////////////////////////////////////////
  template<typename Expr, typename Environnement>
  struct transform_network : boost::result_of<skeleton( Expr
                                                      , Environnement
                                                      , bm::void_
                                                      )
                                             > {};
}

#endif

