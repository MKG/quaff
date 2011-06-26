/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <fstream>
#include <iostream>
#include <quaff/quaff.hpp>

int h()
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

int f(int i)
{
  return 10*i;
}

void g(int i)
{
  std::cout << i << "\n";
}

int main()
{
//  quaff::debug(  quaff::source(h) | quaff::pipe<3>(quaff::seq(f)) | quaff::sink(g)
//              , std::cout
//              );
//
//  quaff::run( quaff::source(h) | quaff::pipe<3>(quaff::seq(f)) | quaff::sink(g) );

  std::ofstream file("graph.dot");
  graph( quaff::source(h) | quaff::pardo<3>(quaff::seq(f)) | quaff::sink(g), file );
  return 0;
}
