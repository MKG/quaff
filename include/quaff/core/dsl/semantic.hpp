/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_DSL_SEMANTIC_HPP_INCLUDED
#define QUAFF_CORE_DSL_SEMANTIC_HPP_INCLUDED

#include <boost/proto/proto.hpp>

////////////////////////////////////////////////////////////////////////////////
// Model forward declaration for process networks semantic rules
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace semantic
{
  //////////////////////////////////////////////////////////////////////////////
  // Generic Transform eating up an ASt and outputing an environment of Model
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert;

  //////////////////////////////////////////////////////////////////////////////
  // Rule for converting Seq(F) to a proper environment
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert_seq;

  //////////////////////////////////////////////////////////////////////////////
  // Rule for converting (F1,F2) to a proper environment
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert_chain;

  //////////////////////////////////////////////////////////////////////////////
  // Rule for converting (S1 & S2) to a proper environment
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert_pardo;

  //////////////////////////////////////////////////////////////////////////////
  // Rule for converting (S1 | S2) to a proper environment
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert_pipe;

  //////////////////////////////////////////////////////////////////////////////
  // Rule for converting map(F) to a proper environment
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert_map;

  //////////////////////////////////////////////////////////////////////////////
  // Rule for converting farm(S) to a proper environment
  //////////////////////////////////////////////////////////////////////////////
  template<class Model> struct convert_farm;
} }

////////////////////////////////////////////////////////////////////////////////
// Register all semantic rules as proto transform
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace proto
{
  template<class Model>
  struct  is_callable< quaff::semantic::convert_seq<Model> >
        : mpl::true_ {};

  template<class Model>
  struct  is_callable< quaff::semantic::convert_chain<Model> >
        : mpl::true_ {};

  template<class Model>
  struct  is_callable< quaff::semantic::convert_pardo<Model> >
        : mpl::true_ {};

  template<class Model>
  struct  is_callable< quaff::semantic::convert_pipe<Model> >
        : mpl::true_ {};

  template<class Model>
  struct  is_callable< quaff::semantic::convert_map<Model> >
        : mpl::true_ {};

  template<class Model>
  struct  is_callable< quaff::semantic::convert_farm<Model> >
        : mpl::true_ {};
} }

#endif
