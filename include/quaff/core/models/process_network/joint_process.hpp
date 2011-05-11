/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_JOINT_PROCESS_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_JOINT_PROCESS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/join_process.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/joint_view.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <quaff/core/models/process_network/accept.hpp>

namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  // joint process structure
  // Static datatype representing the union of two processes .
  //////////////////////////////////////////////////////////////////////////////
  template<class Process1,class Process2>
  struct joint_process
  {
    ////////////////////////////////////////////////////////////////////////////
    // input and output type of a joint network is the joint view
    // of the underlying sequence of both original networks
    ////////////////////////////////////////////////////////////////////////////
    typedef  typename Process1::pid_type  pid_type;
                               
    typedef  typename Process1::input_type input_type;

    typedef  typename Process2::output_type  output_type;

    typedef typename boost::mpl::
            copy < typename  Process2::codelet_type
                 , boost::mpl::back_inserter<typename Process1::codelet_type>
                 >::type                    codelet_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build a joint process from two other processes
    ////////////////////////////////////////////////////////////////////////////
    joint_process ( Process1 const& p1, Process2 const& p2 )
                  : process1(p1), process2(p2) 
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Pass backend over backend
    ////////////////////////////////////////////////////////////////////////////
    template<class BackEnd,class Data>
    void accept(BackEnd const& b, Data& d) const
    {
      b.accept(*this.process1,d);
      b.accept(*this.process2,d);
    }

    Process1 process1;
    Process2 process2;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Join two processes 
  //////////////////////////////////////////////////////////////////////////////
  template<class LHS,class RHS> inline
  joint_process<LHS,RHS> join_process( LHS const& p1, RHS const& p2 )
  {
    joint_process<LHS,RHS> that(p1,p2);
    return that;
  }
} }

#endif
