/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_SEQUENTIAL_INSTRUCTIONS_SEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_SEQUENTIAL_INSTRUCTIONS_SEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/sequential/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff { namespace instruction
{
  template<class Destinations>
  struct send<Destinations,backend::sequential_>
  {
    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const&
                    , Input&
                    , Output& out
                    , Context& context
                    ) const
    {
      Destinations d;
      if(boost::fusion::at_c<1>(context)[Pid::begin])
      {
        boost::fusion::for_each(d,post<Output,Context>(out,context));
      }
      else
        boost::fusion::for_each(d,propagate(&boost::fusion::at_c<1>(context)[0]));
    }

    struct propagate
    {
      typedef void result_type;
      bool* status_;

      propagate(bool* s) : status_(s) {}

      template<class P>
      void operator()(P const&) const { status_[P::begin] = false; }
    };

    template<class Output,class Context>
    struct post
    {
      typedef void result_type;

      post(Output& d, Context& c) : data_(d), context_(c) {}
      template<class P>
      void operator()(P const&) const
      {
        boost::fusion::at_c<2*P::begin>(boost::fusion::at_c<0>(context_)) = data_;
      }

      Output& data_;
      Context& context_;
    };
  };
} }

#endif
