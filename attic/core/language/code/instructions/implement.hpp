#ifndef __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__IMPLEMENT_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__IMPLEMENT_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/instructions/implement.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  template<class M, class L, class I, class O>
  struct make_instr
  {
    typedef typename M::template apply<I,O>::type base;
    typedef typename bm::copy<base, bm::back_inserter<L> >::type      type;
  };

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Generate a concrete instructions object
  /// implement is a meta-program that turns a macro-instruction type into a
  /// concrete function object that can be effectively called.
  //////////////////////////////////////////////////////////////////////////////
  template<class M, class I, class O>
  struct implement
  {
    typedef typename bm::fold< M
                             , bm::vector<>
                             , make_instr<bm::_2,bm::_1,I,O>
                             >::type                              instrs;
    typedef typename make_tuple<instrs>::type                     type;
  };
}

#endif
