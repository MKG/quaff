/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_INSTRUCTIONS_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_INSTRUCTIONS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/instructions.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace instruction
{
  template<class Function     , class BackEnd>  struct call;
  template<class Destinations , class BackEnd>  struct send;
  template<class Sources      , class BackEnd>  struct receive;
  template<class Function     , class BackEnd>  struct manage_farm;

} }

#endif
