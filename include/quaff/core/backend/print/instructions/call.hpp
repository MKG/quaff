/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_PRINT_INSTRUCTIONS_CALL_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_PRINT_INSTRUCTIONS_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/print/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>

namespace quaff { namespace instruction
{
  template<class Function>
  struct call<Function,backend::print_>
  {
    typedef typename Function::input_type   input_type;
    typedef typename Function::output_type  output_type;

    call(Function const& f) : mFunction(f) {}

    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const& p
                    , Input&
                    , Output&
                    , Context& os
                    ) const
    {
    
    //creer fichier correspoondant a la fonction
    std::ofstream incl("incl.txt", std::ios::out | std::ios::app);
    std::ofstream var("var.txt", std::ios::out | std::ios::app);
    std::ofstream gen("gen.txt", std::ios::out | std::ios::app);
    incl << "#include <" << "???" << ".h>\n";
    
    //création de la variable de recuperation
        if (! boost::is_same<typename Output::type,boost::mpl::void_>::value )
        {
          var <<  "\t" << type_id<typename Output::type>() << " do" << p << ";\n";
        }
       
        
        //création de la variable d'entree
        if (! boost::is_same<typename Input::type,boost::mpl::void_>::value)
          {
            var << "\t" << type_id<typename Input::type>() << " di" << p << ";\n";
          }
    
    gen << "\t";
    // affichage variable sortie
    if (! boost::is_same<typename Output::type,boost::mpl::void_>::value)
          {
             gen << "do" << p << " = ";
          }   



     gen  <<  (void*)(&mFunction) << "(";
         
     if (! boost::is_same<typename Input::type,boost::mpl::void_>::value)
          {
            
            gen  << "di" << p ;
          }
     
     
    gen  << ");\n";
    
    
    incl.close();
    var.close();
    gen.close();
         
    }

    Function  mFunction;
  };
} }

#endif
