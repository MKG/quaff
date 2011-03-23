#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__LINK_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__LINK_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/tools/link.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  /// @brief link a list of SCM workers to their respective master
  //////////////////////////////////////////////////////////////////////////////
  template<class PROCS, class PID> struct link_to_master
  {
    template<class PROC, class ID> struct add_pid
    {
      // Extract processus elements
      typedef typename PROC::pid            pid;
      typedef typename PROC::descriptor     desc;
      typedef typename PROC::input_types    in;
      typedef typename PROC::output_types   out;
      typedef typename PROC::remanent_types rem;

      // extract descriptor elements
      typedef typename desc::macro          macro;
      typedef typename desc::kind           kind;

      // Insert master PID into i/o list
      typedef descriptor<ID,ID,macro,kind>      new_desc;
      typedef processus<pid,new_desc,in,out,rem> type;
    };

    typedef typename bm::transform<PROCS, add_pid<bm::_1,PID> >::type type;
  };
}

#endif
