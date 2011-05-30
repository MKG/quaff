/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_DEBUG_BACKEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_DEBUG_BACKEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/debug/backend.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/identity.hpp>
#include <quaff/sdk/meta/run.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace quaff { namespace backend
{
  struct debug_
  {
    void terminate() const {}

    template<class T> void accept( T const& n ) const
    {
      boost::fusion::at_c<0>(n).accept(*this,boost::fusion::at_c<1>(n));
    }

    template<class Process, class Data>
    void accept(Process const& p,Data& os) const
    {
      typedef typename Process::pid_type pid;
      boost::mpl::identity<typename Process::input_type>  ins;
      boost::mpl::identity<typename Process::output_type> outs;

      os << "[ Running on [ " << pid::begin " - " << pid::end << "]\n";
      boost::fusion::
      for_each( p.code()
              , meta::run ( pid(), ins, outs, os )
              );
      os << "[-----------------------------------------]\n";
    }
  };
} }

#include <quaff/core/backend/debug/runtime.hpp>

#endif
