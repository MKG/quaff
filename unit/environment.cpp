/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <quaff/core/backend.hpp>
#include <quaff/core/skeleton/seq.hpp>
#include <quaff/core/skeleton/source.hpp>
#include <quaff/sdk/meta/transform_if.hpp>
 
template<class X> void run(X const& x)
{
  quaff::semantic::convert<quaff::tag::process_network_> mn;
  quaff::model::empty_environment en;
  
  quaff::current_backend.accept(mn(x,en,quaff::current_backend).network());
}

int g()
{
  static int i(0);
  std::cout << "i: " << i << "\n";

  if(i < 10) i++;
  else
  {
    i = 0;
    quaff::terminate();
  }

  return i;
}



template<class Network> void test(Network const& n) {

//tentative pour récuperer le process
//typedef typename quaff::model::process process;

quaff::meta::transform_if<Network const>(n
                          ,(std::cout << "pid :" 
                                      << Network::process::pid_type::value)
                           ,((Network::process::pid_type::value %2)==0) );
}

int main()
{
  debug( quaff::source(g) & (quaff::source(g) & quaff::source(g) ), std::cout );
quaff::semantic::convert<quaff::tag::process_network_>  converter;
quaff::model::empty_environment                         env;
quaff::backend::debug_ target;

/*test( 
    converter(( quaff::source(g) & (quaff::source(g) & quaff::source(g) )),env,target).network()
     );*/

/*  std::ofstream out("out.txt");
  debug(  ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & (( quaff::source(g) & quaff::source(g) ) & quaff::source(g))
      , out
      );*/

/*
  debug(  ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & (( quaff::source(g) & quaff::source(g) ) & quaff::source(g))
     );
     */
}

