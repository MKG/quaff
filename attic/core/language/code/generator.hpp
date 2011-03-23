#ifndef __QUAFF__CORE__LANGUAGE__CODE__GENERATOR_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__GENERATOR_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>

namespace quaff
{
  // ///////////////////////////////////////////////////////////////////////////
  // probe meta-programm for process network
  // ///////////////////////////////////////////////////////////////////////////
  template<class DT, int I, int S> struct visitor
  {
    static inline void Run()
    {
      bm::at_c<DT,I>::type::run();
      visitor<DT,I+1,S>::Run();
    }

    template<class Stream> static inline void Probe( Stream& str )
    {
      bm::at_c<DT,I>::type::probe(str);
      visitor<DT,I+1,S>::Probe(str);
    }
  };

  template<class D,int S> struct visitor<D,S,S>
  {
    static inline void Run() {}
    template<class Stream> static inline void Probe( Stream& ) {}
  };

  // ///////////////////////////////////////////////////////////////////////////
  // run meta-programm for processus
  // ///////////////////////////////////////////////////////////////////////////
  template<class C> struct execute;

  template<class H, class T>
  struct execute< bt::cons<H,T> >
  {
    template<class IT,class OT, class MT>
    static inline void Do( bt::cons<H,T>& code, IT& in, OT& out, MT& mem )
    {
      (code.get_head()).run(in,out,mem);
      execute<T>::Do(code.get_tail(),in,out,mem);
    }
  };

  template<> struct execute<bt::null_type>
  {
    template<class IT,class OT, class MT>
    static inline void Do( bt::null_type, IT&, OT&, MT&) {}
  };

  // ///////////////////////////////////////////////////////////////////////////
  // probe meta-programm for processus
  // ///////////////////////////////////////////////////////////////////////////
  template<class C> struct inspect;

  template<class H, class T>
  struct inspect< bt::cons<H,T> >
  {
    template<class Stream>
    static inline void Do( bt::cons<H,T>& code, Stream& str )
    {
      (code.get_head()).probe(str);
      inspect<T>::Do(code.get_tail(),str);
    }
  };

  template<> struct inspect<bt::null_type>
  {
    template<class Stream>
    static inline void Do( bt::null_type, Stream& ) {}
  };
}
#endif
