/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_PID_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_PID_HPP_INCLUDED

#include <boost/mpl/range_c.hpp>
////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/pid
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace model
{
  /////////////////////////////////////////////////////////////////////////////
  // Define a Pid range [begin PID, end PID[
  /////////////////////////////////////////////////////////////////////////////
  template<std::size_t B, std::size_t E>
  struct pids
  {
    typedef boost::mpl::range_c<std::size_t,B,E> range_type;

    BOOST_STATIC_CONSTANT( std::ptrdiff_t, size   = E-B );
    BOOST_STATIC_CONSTANT( std::ptrdiff_t, begin  = B   );
    BOOST_STATIC_CONSTANT( std::ptrdiff_t, end    = E   );

    typedef pids<B-size,E-size> prev;
    typedef pids<B+size,E+size> next;
    

    bool contains(int p) const
    {
      return (B<=p) && (p<E);
    }
  };

  template<std::size_t B, std::size_t E>
  std::ostream& operator<<(std::ostream& os, pids<B,E> const& )
  {
    return os << B;
  }
  
  template<class PID, int N>
  struct extend
  {
  typedef PID pid;
  typedef pids< PID::begin, PID::begin+N > type;
  extend(PID const& p, int const& n): pid(p) {}
  };
  
} }

#endif
