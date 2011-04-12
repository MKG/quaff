 /******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_ACCEPT_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_ACCEPT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Visitor acceptor PFO
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace model
{
  template<class BackEnd,class Data>
  struct accept_
  {
    accept_(BackEnd const& b, Data& d) : backend_(b), data_(d) {}

    template<class Process>
    void operator()(Process const & p) const
    {
      backend_.accept(p,data_);
    }

    BackEnd const&  backend_;
    Data&           data_;
  };
} }

#endif
