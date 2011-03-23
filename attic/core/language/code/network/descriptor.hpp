#ifndef __QUAFF__CORE__LANGUAGE__CODE__NETWORK__DESCRIPTOR_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__NETWORK__DESCRIPTOR_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/network/descriptor.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/size.hpp>

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  /// @brief descriptor abstract data type
  ///
  /// descriptor statically encodes a processus descriptor data type.
  /// This descriptor is formally defined by :<br/>
  ///  <ul>
  ///  <li><b>IPID</b>: a list of preceding PID;</li>
  ///  <li><b>OPID</b>: a list of following PID;</li>
  ///  <li><b>CODE</b>: a list of macro-instructions;</li>
  ///  <li><b>KIND</b>: a asynchonous status flag.</li>
  ///  </ul>
  ///////////////////////////////////////////////////////////////////////////////
  template<class IPID, class OPID,class CODE, class KIND>
  struct descriptor
  {
    typedef IPID i_pids;
    typedef OPID o_pids;
    typedef CODE macro;
    typedef KIND kind;

    typedef typename bm::size<macro>::type                size;
    typedef typename implement<macro,i_pids,o_pids>::type type;
  };
}

#endif
