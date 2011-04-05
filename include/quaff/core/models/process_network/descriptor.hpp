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

    descriptor(Code const& c) : codelet(c) {}

    void operator()() const
    {
      boost::fusion::at_c<0>(codelet)();
      //*out = codelet( *in );
    }

    Code codelet;
  };
  
  //////////////////////////////////////////////////////////////////////////////
  // Build a descriptor out of its components
  //////////////////////////////////////////////////////////////////////////////
  template<class P,class N,class C>
  descriptor<P,N,C> make_descriptor( P const& , N const&, C const& c )
  {
    descriptor<P,N,C> that(c);
    return that;
  }
} }

#endif
