/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_DSL_GRAMMAR_HPP_INCLUDED
#define QUAFF_CORE_DSL_GRAMMAR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/grammar/definition.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <quaff/sdk/meta/is_callable.hpp>

namespace quaff { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // tags for quaff specific functions
  //////////////////////////////////////////////////////////////////////////////
  struct map_ {};
  struct farm_ {};
  struct pardoer_{};
} }

namespace quaff { namespace dsl
{

  //////////////////////////////////////////////////////////////////////////////
  // A valid sequential_skeleton expression is :
  //  - a terminal holding a boost::function;
  //  - a sequence of terminal to be chained;
  //
  // TODO: - Add a arity check on comma
  //////////////////////////////////////////////////////////////////////////////
  struct  sequential_skeleton
        : boost::proto
          ::or_ < boost::proto
                  ::and_< boost::proto::terminal<boost::proto::_>
                        , boost::proto
                          ::if_< meta::is_callable<boost::proto::_value>() >
                        >
                , boost::proto::comma < sequential_skeleton
                                      , sequential_skeleton
                                      >
                
                >
  {};
  


  //////////////////////////////////////////////////////////////////////////////
  // A data-parallel skeleton is :
  // - a sequential_skeleton
  // - a map using a sequential skeleton
  //////////////////////////////////////////////////////////////////////////////
  struct  data_parallel_skeleton
        : boost::proto::or_ < sequential_skeleton
                            , boost::proto::unary_expr< tag::map_
                                                      , sequential_skeleton
                                                      >
                            
                            >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // A valid skeleton expression is :
  //  - a data_parallel skeleton;
  //  - a full parallel execution using operator &;
  //  - a pipelined execution using operator |;
  //  - a farm<N> skeleton;
  //  - a pardo<N> skeleton;
  //////////////////////////////////////////////////////////////////////////////
  struct  skeleton
        : boost::proto::or_ <  data_parallel_skeleton
                            , boost::proto::bitwise_and<skeleton,skeleton>
                            , boost::proto::bitwise_or<skeleton,skeleton>
                            , boost::proto::binary_expr<tag::farm_
                                                        , boost::proto::_
                                                        , skeleton
                                                        >
                            , boost::proto::binary_expr<tag::pardoer_
                                                        , boost::proto::_
                                                        , skeleton
                                                        >
                            >
  {};
} }

#endif
