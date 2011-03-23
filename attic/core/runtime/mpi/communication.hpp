/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__RUNTIME__COMMUNICATION_HPP__INCLUDED__
#define __QUAFF__CORE__RUNTIME__COMMUNICATION_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief MPI communication interface
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  // send any boost::serializable type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  static inline void send( int dst, const T& val, int tag )
  {
    runtime::Send(dst,tag,val);
  }

  //////////////////////////////////////////////////////////////////////////////
  // send a complete variable set
  //////////////////////////////////////////////////////////////////////////////
  static inline void send( int , bt::null_type, int ) {}

  template<class H,class T> static inline
  void send( int dest, const bt::cons<H,T>& x, int tag)
  {
    send(dest,x.get_head(),tag);
    send(dest,x.get_tail(),tag);
  }

  //////////////////////////////////////////////////////////////////////////////
  // receive any boost::serializable type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> static inline
  void receive( int src, T& val, int tag, status_t& stat)
  {
    stat = runtime::Recv(src,tag,val);
  }

  //////////////////////////////////////////////////////////////////////////////
  // receive a complete variable set
  //////////////////////////////////////////////////////////////////////////////
  static inline void receive( int, bt::null_type, int, status_t& ) {}

  template<class H,class T> static inline
  void receive( int src, bt::cons<H,T>& x, int tag, status_t& s)
  {
    receive(src,x.get_head(),tag,s);
    receive(src,x.get_tail(),tag,s);
  }
}
#endif

