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
#include <quaff/quaff.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/bind.hpp>
#include <fstream>
 

int g()
{
  static int i(0);

  if(i < 3) i++;
  else
  {
    i = 0;
    quaff::terminate();
  }

  return i;
}

int id(int x) {
return x;
}

void m(int x) {
return;
}



template<class Network> void test(Network const& n) {

//tentative pour récuperer le process
//typedef typename quaff::model::process process;

quaff::meta::transform_if<Network const>(n
                          ,(std::cout << "pid :" 
                                      << Network::process::pid_type::value)
                           ,((Network::process::pid_type::value %2)==0) );}

int x2(int i)
{
  return 2 * i;
}

void h(int i)
{
  std::cout << "h say : " << i << "\n";

}

int main()
{
std::ofstream out("out.dot");
 debug( quaff::source(g) | quaff::seq(x2) | (quaff::sink(h)& quaff::sink(m))  , std::cout );
 graph(quaff::source(g)| quaff::seq(x2)| (quaff::sink(h)& quaff::sink(m)) ,out );  //| quaff::seq(x2) | quaff::sink(h), out );
/*  debug( quaff::source(g) & (quaff::source(g) & quaff::source(g) ), std::cout );

//quaff::semantic::convert<quaff::tag::process_network_>  converter;
//quaff::model::empty_environment                         env;
//quaff::backend::debug_ target;

test( 
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
     );*/
     

  //graph( quaff::source(g) & (quaff::seq(id)& quaff::source(g)) & quaff::sink(m) , out);


 
 // run( quaff::source(g)|quaff::seq(x2) | quaff::sink(h) );
//  run(  quaff::seq(x2) ); //| quaff::sink(h) );

}

