#ifndef __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_RECV_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__INSTRUCTIONS__INSTRUCTION_RECV_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/instructions/instruction_recv.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  namespace bm = boost::mpl;

  namespace details
  {
    ////////////////////////////////////////////////////////////////////////////
    /// @brief "Receive" function object
    /// This function object acts as the implementation of the "Receive" macro
    /// instructions. It is instanciated using the static list of input PIDs
    /// of a given process network
    ////////////////////////////////////////////////////////////////////////////
    template<class IPID> struct Receive
    {
      public:
      typedef typename bm::at_c<IPID,0>::type src;

      template<class I,class O,class M>
      inline void run( I& i, O& , M&)
      {
        status_t status;
        receive(src::value, i, comm::any_tag, status);
        update_status( (status.tag() != comm::Stop) );
      }

      template<class Stream> inline void probe( Stream& str)
      {
        char buffer[16];
        sprintf(buffer,"[Recv %d]",src::value);
        str += buffer;
      }
    };
  }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief "Receive" macro instructions class
  //////////////////////////////////////////////////////////////////////////////
  struct MacroRecv
  {
    template<class IPID, class OPID> struct apply
    {
      typedef bm::vector< details::Receive<IPID> > type;
    };
  };
}

#endif
