#ifndef __QUAFF__CORE__LANGUAGE__SYNTAX__SEQ_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SYNTAX__SEQ_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/syntax/seq.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  namespace result_of
  {
    template<class T> struct nested_type
    {
      typedef BOOST_TYPEOF_TPL(&T::operator()) type;
    };

    template< class T,
              class FT    = typename nested_type<T>::type,
              FT Function = &T::operator()
            > struct seq
    {
      typedef adaptator<FT,Function,T>                              adaptee;
      typedef typename bp::terminal< user_function<adaptee> >::type term;
      typedef skeleton_expression< term >                           type;
    };
  }

  #define function(F) boost::mpl::void_,BOOST_TYPEOF(&F),&F
  #define seq(X)      quaff::result_of::seq<X>::type()
}

#endif

