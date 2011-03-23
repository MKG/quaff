#ifndef __QUAFF__CORE__LANGUAGE__CODE__NETWORK__PROCESS_NETWORK_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__NETWORK__PROCESS_NETWORK_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/network/process_network.hpp
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  /// process_network structure
  ///
  /// Static datatype representing a process network. In this representation,
  /// a process network is defined by a triplet <P,I,O>:
  /// - P : a list of processus
  /// - I : a list of input nodes
  /// - O : a list of outputs node
  ///
  //////////////////////////////////////////////////////////////////////////////
  template<class P,class I,class O>
  struct process_network
  {
    typedef P   process;
    typedef I   inputs;
    typedef O   outputs;

    typedef typename bm::size<process>::type  cardinal;

    static inline void run()
    {
      visitor<process,0,cardinal::value>::Run();
    }

    template<class Stream> static inline
    void probe(Stream& str)
    {
      visitor<process,0,cardinal::value>::Probe(str);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  /// @brief empty process network
  //////////////////////////////////////////////////////////////////////////////
  typedef process_network< bm::vector<>
                         , bm::vector<>
                         , bm::vector<> > empty_network;
}

#endif
