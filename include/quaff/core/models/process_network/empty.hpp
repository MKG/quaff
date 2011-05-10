/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_EMPTY_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_EMPTY_HPP_INCLUDED

#include <quaff/core/models/process_network/pid.hpp>

////////////////////////////////////////////////////////////////////////////////
// Empty environment and network class
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace model
{
  //////////////////////////////////////////////////////////////////////////////
  /// empty process network - to be used in process network transform
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct network< boost::fusion::vector<>
                , boost::mpl::set<> , boost::mpl::set<>
                , boost::mpl::void_
                >
  {
    typedef boost::fusion::vector<> processes;
    typedef boost::mpl::set<>       inputs;
    typedef boost::mpl::set<>       outputs;
  };

  typedef network < boost::fusion::vector<>
                  , boost::mpl::set<> , boost::mpl::set<>
                  , boost::mpl::void_
                  >
  empty_network;

  //////////////////////////////////////////////////////////////////////////////
  // Specialisation for empty environment
  //////////////////////////////////////////////////////////////////////////////
  template<> struct environment<empty_network, pids<0,1> >
  {
    typedef empty_network network_type;
    typedef pids<0,1>      pid_type;

    network_type network()  const { return network_type();  }
    pid_type     pid()      const { return pid_type();      }
  };

  typedef environment<empty_network, pids<0,1> > empty_environment;
} }

#endif
