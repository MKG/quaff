/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__RUNTIME__RUNTIME_HPP__INCLUDED__
#define __QUAFF__CORE__RUNTIME__RUNTIME_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
////////////////////////////////////////////////////////////////////////////////

// MPI based machines
#if defined(CONFIG_MPI_DETECTED)
  #include <quaff/core/runtime/mpi/base.hpp>
  #include <quaff/core/runtime/mpi/communication.hpp>
// pThread based machines
#elif defined(CONFIG_PTHREAD_MPI_DETECTED)
// Cell based architectures
#elif defined(CONFIG_MPI_CBE_MPI_DETECTED)
  #include <quaff/core/runtime/cbe/base.hpp>
  #include <quaff/core/runtime/mpi/communication.hpp>
#else
  #error "QUAFF - Unsupported communication layer"
#endif

namespace quaff
{
  static inline void init(int& argc, char**& argv) { runtime::Init(argc,argv); }
  static inline void finalize()                    { runtime::Finalize();      }

  static inline int  process_rank()         { return runtime::Rank();       }
  static inline bool is_root_process()      { return runtime::Rank() == 0;  }
  static inline int  process_count()        { return runtime::Size();       }

  static inline bool process_status()       { return runtime::GetStatus();  }
  static inline void update_status(bool s)  { runtime::SetStatus(s);        }
  static inline void shutdown()             { runtime::SetStatus(false);    }

  static inline void synchronize()          { runtime::Synchronize();       }

  struct comm
  {
    static const int any_tag = runtime::any_tag;
    static const int Data    = 0xF00D;
    static const int Stop    = 0xDEAD;
    static const int Status  = 0xC0DE;
    static const int Probe   = 0xBABE;
  };
}

#endif
