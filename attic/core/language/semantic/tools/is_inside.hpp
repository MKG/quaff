#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__IS_INSIDE_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__IS_INSIDE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/tools/is_inside.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>

namespace quaff
{
  namespace bm = boost::mpl;

  // /////////////////////////////////////////////////////////////////////////////
  // position : retrieve an iterator on PROC in LST
  // /////////////////////////////////////////////////////////////////////////////
  template<class PROC, class LST> struct position_of
  {
    typedef typename PROC::pid                pid;
    typedef typename bm::begin<LST>::type     beg;
    typedef typename bm::end<LST>::type       ends;
    typedef typename bm::find<LST,pid>::type  type;
  };

  // /////////////////////////////////////////////////////////////////////////////
  // is_outside : check if a process of PID pid is outside a list of PID LST
  // /////////////////////////////////////////////////////////////////////////////
  template<class PROC, class LST> struct is_outside
  {
    typedef typename position_of<PROC,LST>::type        inside;
    typedef typename position_of<PROC,LST>::ends        ends;
    typedef typename boost::is_same<inside,ends>::type  base;
    typedef bm::bool_<base::value>                      type;
  };

  // /////////////////////////////////////////////////////////////////////////////
  // is_inside : check if a process of PID pid is inside a list of PID LST
  // /////////////////////////////////////////////////////////////////////////////
  template<class PROC, class LST> struct is_inside
  {
    typedef typename is_outside<PROC,LST>::type     base;
    typedef bm::bool_<!base::value>                 type;
  };

  // /////////////////////////////////////////////////////////////////////////////
  // relative_at : evaluates the distance between a PROC in LST and LST::begin
  // /////////////////////////////////////////////////////////////////////////////
  template<class PROC, class LST> struct relative_at
  {
    typedef typename bm::begin<LST>::type             beg;
    typedef typename position_of<PROC,LST>::type      inside;
    typedef typename bm::distance<beg, inside>::type  type;
  };
}

#endif
