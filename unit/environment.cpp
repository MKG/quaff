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

int x2(int i)
{
  return 2 * i;
}

void h(float i)
{
  std::cout << "h say : " << i << "\n";

}

int main()
{
  std::ofstream file("graph.dot");
debug(pardo(boost::mpl::int_<42>(),quaff::seq(x2)), std::cout );

 // debug(quaff::source(g) | pardo(8,quaff::seq(x2)) | quaff::sink(h), std::cout );
  //run( quaff::source(g) | quaff::seq(x2) | quaff::sink(h) );
  //graph( quaff::source(g) | quaff::seq(x2) | quaff::sink(h), file );
  //print(quaff::source(g) | quaff::seq(x2) | quaff::sink(h), std::cout );
}

