/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_PRINT_BACKEND_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_PRINT_BACKEND_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/print/backend.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/identity.hpp>
#include <quaff/sdk/type_id.hpp>
#include <quaff/sdk/meta/run.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <fstream>
#include <string>

namespace quaff { namespace backend
{
  struct print_
  {
    print_() {}

    void terminate() const {}
    void start()     const {}

    // How to run a network
    template<class T>
    void accept( T const& n ) const
    {
      //creation des fichiers
      std::ofstream incl("incl.txt", std::ios::out | std::ios::trunc);
      std::ofstream var("var.txt", std::ios::out | std::ios::trunc);
      std::ofstream gen("gen.txt", std::ios::out | std::ios::trunc);
      incl << "#include <iostream>\n#include <quaff/quaff.hpp>\n#include <boost/type_traits/is_integral.hpp \n#include <boost/bind.hpp>\n#include <fstream>\n\n";

      
      gen.close();
      var.close();
      incl.close();
      
      //lancement du reste
      boost::fusion::at_c<0>(n).accept(*this,boost::fusion::at_c<1>(n));
      
      
      //ecriture finale
      std::ifstream inclu("incl.txt", std::ios::in);
      std::ifstream vari("var.txt", std::ios::in);
      std::ifstream gener("gen.txt", std::ios::in);
      std::string ligne;
      while(getline(inclu, ligne))
      boost::fusion::at_c<1>(n) << ligne << "\n"; //std::endl;
      boost::fusion::at_c<1>(n) << "int main() {\n";
      while(getline(vari, ligne))
      boost::fusion::at_c<1>(n) << ligne <<  "\n"; //std::endl;
      while(getline(gener, ligne))
      boost::fusion::at_c<1>(n) << ligne << "\n"; // std::endl;
      boost::fusion::at_c<1>(n) << "return 0;\n }\n";
      gener.close();
      vari.close();
      inclu.close();
    }

    // How to run a process
    template<class Process, class Data>
    void accept(Process const& p,Data& os ) const
    {
      typedef typename Process::pid_type pid;
      boost::mpl::identity<typename Process::input_type>  ins;
      boost::mpl::identity<typename Process::output_type> outs;
      
      

      boost::fusion::
      for_each( p.code()
              , meta::run (pid(), ins, outs, os )
              
              );
     
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Generate a debug on the standard output
////////////////////////////////////////////////////////////////////////////////
template<class X, class Stream> void print(X const& xpr, Stream& os)
{
  quaff::semantic::convert<quaff::tag::process_network_>  converter;
  quaff::model::empty_environment                         env;
  quaff::backend::print_ target;

  target.accept ( boost::fusion::vector_tie ( converter(xpr,env,target).network()
                                            , os
                                            )
                );
}

#include <quaff/core/backend/print/instructions/call.hpp>
#include <quaff/core/backend/print/instructions/send.hpp>
#include <quaff/core/backend/print/instructions/receive.hpp>
#endif
