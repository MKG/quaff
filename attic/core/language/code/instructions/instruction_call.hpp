#ifndef __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_CALL_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_CALL_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/instructions/instruction_call.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  namespace details
  {
    ////////////////////////////////////////////////////////////////////////////
    /// @brief "CallFn" function object
    /// This function object acts as the implementation of the "CallFn" macro
    /// instructions. It is instanciated using the type of the user-defined
    /// function adaptator created by the seq() constructor.
    ////////////////////////////////////////////////////////////////////////////
    template<class Function>  class Call
    {
      public:
      typedef Function                                function_type;
      typedef typename function_type::input_types     input_types;
      typedef typename function_type::output_types    output_types;
      typedef typename function_type::remanent_types  remanent_types;

      inline void run(input_types& i, output_types& o, remanent_types& m)
      {
        if(process_status()) mFunction(i,o,m);
      }

      template<class Stream> inline void probe( Stream& str)
      {
        char buffer[32];
        sprintf(buffer,"[Call @(0x%X)]",int(&mFunction));
        str += buffer;
      }

      private:
      mutable Function mFunction;
    };
  }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief "CallFn" macro instructions class
  //////////////////////////////////////////////////////////////////////////////
  template<class Function> struct MacroCall
  {
    template<class IPID, class OPID> struct apply
    {
      typedef bm::vector< details::Call<Function> > type;
    };
  };
}

#endif
