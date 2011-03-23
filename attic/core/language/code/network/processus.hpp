#ifndef __QUAFF__CORE__LANGUAGE__CODE__NETWORK__PROCESSUS_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__CODE__NETWORK__PROCESSUS_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/code/network/processus.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  /// @brief processus abstract data type
  ///
  /// processus statically defines a datatype representing a processus in a
  /// process network. processus is formally defined by :
  /// <ul>
  ///  <li> <b>ID</b>: the processus unqiue PID; </li>
  ///  <li> <b>DESC</b>: the processus descriptor.</li>
  /// </ul>
  /// <br/>
  /// For implementation details, the following types are added to the formal
  /// description:
  /// <ul>
  ///  <li> <b>IT</b>: concrete ype of the input data of the processus;</li>
  ///  <li> <b>OT</b>: concrete ype of the output data of the processus;</li>
  ///  <li> <b>MT</b>: concrete ype of the memorized data of the processus.</li>
  /// </ul>
  //////////////////////////////////////////////////////////////////////////////
  template<class ID,class DESC,class IT,class OT,class MT>
  struct processus
  {
    typedef ID      pid;
    typedef DESC    descriptor;
    typedef IT      input_types;
    typedef OT      output_types;
    typedef MT      remanent_types;

    typedef processus<ID,DESC,IT,OT,MT> type;
    typedef typename descriptor::type code;

    static inline void run()
    {
      if( process_rank() == pid::value )
      {
        IT i; OT o; MT m;
        code c;
        do
        {
          execute<code>::Do(c,i,o,m);
        } while( process_status() );
      }
    }

    template<class Stream> static inline void probe( Stream& str )
    {
      char buffer[16];
      code c;
      sprintf(buffer,"[%d] : ",pid::value);
      str += buffer;
      inspect<code>::Do(c,str);
      str += "\n";
    }
  };
}

#endif
