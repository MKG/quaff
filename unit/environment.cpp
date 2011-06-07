/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define FUSION_MAX_VECTOR_SIZE 42 
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

typedef struct forbuf {
  int tab1[42];
  int tab2[42];
  int tab3[42] ;
  int tab4[42];
  } forbuf;
  
int * split(forbuf montab) {
  int * tab;
  return tab;
  }

int * green(int *tab){ //, int *tab2) {
return tab;
}

int * blue(int * tab) {
return tab;
}
int * black(int * tab) {
return tab;
}

forbuf merge (int * tab) {
  forbuf montab;
  return montab;
  }  


int x2(int i)
{
  return 2 * i;
}

int idi(int i)
{
  return i;
  }

void h(float i)
{
  std::cout << "h say : " << i << "\n";

}

int main()
{
  std::ofstream file("graph.dot");
  std::ofstream ex1("ex1.dot");
  std::ofstream ex2("ex2.dot");
  scmp(quaff::SOURCE(g) | quaff::SEQ(x2) |(quaff::SEQ(blue) & quaff::SEQ(blue))| quaff::SEQ(black) | quaff::SINK(h), std::cout );
  graph(quaff::SOURCE(g) | quaff::SEQ(x2) |(quaff::SEQ(blue) & quaff::SEQ(blue))| quaff::SEQ(black) | quaff::SINK(h), file);
  
  graph(quaff::SOURCE(g) | (quaff::SEQ(blue) & quaff::SEQ(blue))| quaff::SEQ(black) | quaff::SINK(h), ex1);
  graph(quaff::SOURCE(g) | quaff::SEQ(x2)&quaff::SEQ(split) |(quaff::SEQ(blue) & quaff::SEQ(green))| quaff::SEQ(black) | quaff::SINK(h), ex2);
  
//debug(pardo(boost::mpl::int_<42>(),quaff::seq(x2)), std::cout );
//scmp(quaff::SEQ(x2) |(quaff::SEQ(blue) & quaff::SEQ(blue)), std::cout );
  //run(quaff::SEQ(split) | quaff::SEQ(x2) | quaff::SINK(h)) //, std::cout );
 // run( quaff::source(g) | quaff::seq(x2, "x2")& quaff::seq(idi, "idi") | quaff::sink(h) );
 // graph( quaff::source(g) | quaff::seq(x2, "x2")& quaff::seq(idi, "idi") | quaff::sink(h), file);
 //run( quaff::source(g) | quaff::seq(x2, "x2")& quaff::seq(idi, "idi") & quaff::seq(x2, "x2")| quaff::sink(h) );
 //graph( quaff::source(g) | quaff::seq(x2, "x2")& quaff::seq(idi, "idi") & quaff::seq(x2, "x2") | quaff::sink(h), file);
 // graph( quaff::seq(split) | (quaff::seq(green) & quaff::seq(green) & quaff::seq(green) & quaff::seq(green)|(quaff::seq(blue)&quaff::seq(blue)))| (quaff::seq(black)&quaff::seq(black))| quaff::seq(merge), file );

  
}

