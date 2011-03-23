#ifndef __QUAFF__CORE__LANGUAGE__GRAMMAR__DEFINITION_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__GRAMMAR__DEFINITION_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/grammar/definition.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/proto/context.hpp>
#include <boost/proto/transform.hpp>

namespace quaff
{
  namespace bp = boost::proto;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Function object template adaptator
  //////////////////////////////////////////////////////////////////////////////
  template<class FunctionObject>
  struct user_function { typedef FunctionObject type; };

  //////////////////////////////////////////////////////////////////////////////
  // A valid sequential_skeleton expression is :
  //  - a terminal holding a user defined function object;
  //  - a sequence of terminal to be chained;
  //////////////////////////////////////////////////////////////////////////////
  struct seq_skeleton :
  bp::or_< bp::when< bp::terminal< user_function<bp::_> >
                   , environnement<apply_rule<single>(bp::_value), get_pid()>()
                   >
         , bp::when< bp::comma<seq_skeleton,seq_skeleton>
                   , environnement< apply_rule<seq>() , get_pid() >()
                   >
         >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // A data-parallel skeleton is :
  // - a SCM worker
  // - a SCM master
  //////////////////////////////////////////////////////////////////////////////
  struct dp_skeleton :
  bp::or_<seq_skeleton

         ,bp::when< bp::function< bp::terminal< worker_<bp::_> >, seq_skeleton>
                  , environnement<apply_rule<worker>(), get_pid()>()
                  >
         ,bp::when< bp::function< bp::terminal< master_<bp::_> >
                                , seq_skeleton, seq_skeleton, seq_skeleton
                                >
                  , environnement<apply_rule<master>(), get_pid()>()
                  >
         ,bp::when< bp::multiplies<dp_skeleton, skeleton>
                  , environnement<apply_rule<link>(), get_pid()>()
                  >
         >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // A valid skeleton expression is :
  //  - a sequential_skeleton;
  //  - a data-parallel skeleton
  //  - a full parallel execution using operator &;
  //  - a pipelined execution using operator |
  //////////////////////////////////////////////////////////////////////////////
  struct skeleton :
    bp::or_ < dp_skeleton
            , bp::when< bp::bitwise_and<skeleton,skeleton>
                      , environnement<apply_rule<par>(), get_pid()>()
                      >
            , bp::when< bp::bitwise_or<skeleton,skeleton>
                      , environnement<apply_rule<pipe>(), get_pid()>()
                      >
            >
  {};
}

#endif


