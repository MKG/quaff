#ifndef __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_SEND_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_SEND_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/instructions/instruction_send.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  namespace bm = boost::mpl;

  namespace details
  {
    ////////////////////////////////////////////////////////////////////////////
    /// @brief "Send" function object
    /// This function object acts as the implementation of the "Send" macro
    /// instructions. It is instanciated using the static list of output PIDs
    /// of a given process network
    ////////////////////////////////////////////////////////////////////////////
    template<class OPID> struct Send
    {
      public:
      typedef typename bm::at_c<OPID,0>::type dest;

      template<class I,class O,class M>
      inline void run( I&, O& o,M& )
      {
        int tag = process_status() ? comm::Data : comm::Stop;
        send(dest::value,o,tag);
      }

      template<class Stream> inline void probe( Stream& str)
      {
        char buffer[16];
        sprintf(buffer,"[Send %d]",dest::value);
        str += buffer;
      }
    };
  }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief "Send" macro instructions class
  //////////////////////////////////////////////////////////////////////////////
  struct MacroSend
  {
    template<class IPID, class OPID> struct apply
    {
      typedef bm::vector< details::Send<OPID> > type;
    };
  };
}

#endif
