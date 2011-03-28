/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_DESCRIPTOR_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_DESCRIPTOR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/descriptor.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/include/at.hpp>

namespace quaff { namespace model
{
  template<class Prior, class Next, class Code>
  struct descriptor
  {
    typedef Prior     prior;
    typedef Next      next;
    typedef Code      code;

    descriptor() {}
    descriptor(Code const& c) : codelet(c) {}

    template<std::size_t N>
    typename boost::fusion::result_of::at_c<Code const, N>::type
    get() const
    {
      return boost::fusion::at_c<N>(codelet);
    }

    template<std::size_t N>
    typename boost::fusion::result_of::at_c<Code, N>::type
    get()
    {
      return boost::fusion::at_c<N>(codelet);
    }

    void operator()() const
    {
      boost::fusion::at_c<0>(codelet)();
      //*out = codelet( *in );
    }

    Code codelet;
  };

  template<std::size_t N,class P, class Nx, class C>
  typename boost::fusion::result_of::at_c<C const, N>::type
  instr_(descriptor<P,Nx,C> const & d)
  {
    return d.template get<N>();
  }

  template<std::size_t N,class P, class Nx, class C>
  typename boost::fusion::result_of::at_c<C, N>::type
  instr_(descriptor<P,Nx,C> & d)
  {
    return d.template get<N>();
  }
} }

#endif
