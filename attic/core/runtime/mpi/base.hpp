/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__RUNTIME__BASE_HPP__INCLUDED__
#define __QUAFF__CORE__RUNTIME__BASE_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Communication components for MPI
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  namespace bmi = boost::mpi;

  typedef bmi::status status_t;

  struct runtime
  {
    static const int any_tag = MPI_ANY_TAG;

    // MPI runtime start-up
    static void Init(int& argc, char**& argv)
    {
      environment = new bmi::environment(argc,argv);
      MyRank = world.rank();
      MySize = world.size();
    }

    // MPI runtime shutdown
    static void Finalize()
    {
      if(environment)
      {
        //printf("%x (%d/%d] down\n",environment,MyRank,MySize);
        delete environment;
      }
    }

    // Informations about processus rank and world size
    static int      Rank()            { return MyRank;    }
    static int      Size()            { return MySize;    }
    static bool     GetStatus()       { return MyStatus;  }
    static void     SetStatus(bool s) { MyStatus = s;     }

    // Global Synchronization
    static void     Synchronize() { world.barrier();  }

    // Communication proxy
    template<class T> static inline void Send(int dest, int tag, T const& x)
    {
      world.send(dest,tag,x);
    }

    template<class T> static inline status_t Recv(int src, int tag, T& x)
    {
      return world.recv(src,tag,x);
    }

    private :
    static bmi::environment* environment;
    static bmi::communicator world;
    static int  MyRank;
    static int  MySize;
    static bool MyStatus;
  };
}
#endif
