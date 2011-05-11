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
      boost::fusion::at_c<1>(n)<< "#include <iostream>\n #include <quaff/quaff.hpp>\n \
 #include <boost/type_traits/is_integral.hpp \n #include <boost/bind.hpp>\n \
#include <fstream>\n\n";

      boost::fusion::at_c<1>(n)<< "int main() {\n";
      boost::fusion::at_c<0>(n).accept(*this,boost::fusion::at_c<1>(n));

     //for_each( boost::fusion::at_c<0>(n).code(),
      //        boost::fusion::at_c<1>(n)<< "dd" << " -- di" << boost::fusion::at_c<0>(n)::pid_type::value  << " [dir=back arrowsize=3];\n\t");
      boost::fusion::at_c<1>(n)<< "return 0;\n }\n";
    }

    // How to run a process
    template<class Process, class Data>
    void accept(Process const& p,Data& os) const
    {
      typedef typename Process::pid_type pid;
      boost::mpl::identity<typename Process::input_type>  ins;
      boost::mpl::identity<typename Process::output_type> outs;
      
      

      boost::fusion::
      for_each( p.code()
              , meta::run (pid(), ins, outs, os )
              
              );
     
    }
    
    /*template<class Pid,class I,class O,class D> inline
  runner<Pid,I,O,D> run(Pid const& p , I& i, O& o, D& d)

    // Some helpers
    template<class In, class Out,class Data> struct runner
    {
      In& in; Out& out; Data& data; 
      runner(In& i, Out& o, Data& d, int p) : in(i), out(o), data(d)
      {
        //inclure le fichier correspoondant à la fonction !!

      
        //création de la variable de recuperation
        if (!type_id<typename Out::type>().compare("mpl_::void_"))
        {
        }
        else
        {
           d <<  "\t" << type_id<typename Out::type>() << " do" << p << ";\n";
        } 
        
        //création de la variable d'entree
        if (!type_id<typename In::type>().compare("mpl_::void_"))
          {
           //vide
          }
        else
          {
            d << "\t" << type_id<typename In::type>() << " di" << p << ";\n";
          }
        
         
          
              

       // d   << "do" << p << " -- df [dir=forward arrowsize=2];\n\t";
      
      }
      template<class Code> void operator()(Code const& op) const
      {
        op( in,out, data );
      }
    };


    template<class I,class O,class D>
    runner<I,O,D> run(I& i, O& o, D& d, int t) const
    {
      runner<I,O,D> that(i,o,d,t);
      return that;
    }*/
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
