/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_FORWARD_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_FORWARD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Model forward declaration for process networks
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace model
{
  template<class Network, class PIDState> struct environment;

  template<class Nodes, class InputSet, class OutputSet, class DataTypes>
  struct network;

  //////////////////////////////////////////////////////////////////////////////
  // a joint_network is the union of two other Network used in some skeleton
  // to simplify the building of the intermediate representation.
  //
  // joint_network models the network concept.
  //////////////////////////////////////////////////////////////////////////////
  template<class Network1,class Network2> struct joint_network;

  //////////////////////////////////////////////////////////////////////////////
  // Process is a concept around PID-localizable code fragment. Depending on
  // Backend, this code fragment may be parallel or not
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // a process is built from a :
  // - a PID which is a pair of IntegralConstant holding the range of PID on
  //   which the actual process code can be executed
  // - a CodeFragment which is a Deferred Calalble Object containing the code
  //   fragment ot be executed
  //
  // process also acts as unary Deferred Callable Object
  //////////////////////////////////////////////////////////////////////////////
  template< class PIDRange
          , class CodeFragment
          , class InputType
          , class OutputType
          >
  struct process;
} }

#endif
