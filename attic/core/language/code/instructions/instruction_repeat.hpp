#ifndef __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_REPEAT_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_REPEAT_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/instructions/instruction_repeat.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
    namespace details
  {
    ////////////////////////////////////////////////////////////////////////////
    /// @brief "Repeat" function object
    /// This function object acts as the implementation of the "Repeat" macro
    /// instructions who performs a for loop over a macro-instructions list.
    ////////////////////////////////////////////////////////////////////////////
    template<class Instr,long Iter> class Repeat
    {
      public:

      template<class I,class O,class M>
      inline void run(I& i, O& o, M& m)
      {
        for(int idx=0;idx<Iter;++idx)
        {
          if(process_status()) execute<Instr>::Do(mCode,i,o,m);
        }
      }

      template<class Stream> inline void probe( Stream& str)
      {
        char buffer[32];
        sprintf(buffer,"[RepeatFn @(0x%X) %d]",int(&mCode), int(Iter));
        str += buffer;
      }

      private:
      mutable Instr mCode;
    };
  }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief "Repeat" macro instructions class
  /// This macro generates a list of instructions by duplicating a given list
  /// of macro-instructions
  //////////////////////////////////////////////////////////////////////////////
  template<class Macros,long Iter> struct MacroRepeat
  {
    template<class IPID, class OPID> struct apply
    {
      typedef typename implement<Macros,IPID,OPID>::type    instrs;
      typedef bm::vector< details::Repeat<instrs, Iter> >   type;
    };
  };
}

#endif

