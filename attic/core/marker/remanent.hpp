/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__MARKER__REMANENT_HPP__INCLUDED__
#define __QUAFF__CORE__MARKER__REMANENT_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/marker/remanent.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  /*****************************************************************************
   * data wrapper. Used as container for remanent data or parameters
   ****************************************************************************/
  template<class T> class remanent
  {
    public:

    remanent() {}
    remanent( const T& v ): val(v) {}

    template<class U> remanent( const remanent<U>& v ) : val(v()) {}

    template<class U> remanent& operator=( const remanent<U>& v )
    {
      val = v.val;
      return *this;
    }

    remanent& operator=( const T& v ) { val = v; return *this; }

    operator       T&()       { return val; }
    operator const T&() const { return val; }

    T*        operator->()        { return &val; }
    T const*  operator->() const  { return &val; }

          T& operator()()       { return val; }
    const T& operator()() const { return val; }

    private:
    T val;
  };
}

#endif

