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
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/set.hpp>

#include <boost/type_traits/is_integral.hpp>
#include <boost/bind.hpp>
 
int g()
{
  static int i(0);
  std::cout << " - i = " << i << "\n";

  if(i < 3) i++;
  else
  {
    i = 0;
    quaff::terminate();
  }

  return i;
}

int main()
{
  debug( quaff::source(g) & (quaff::source(g) & quaff::source(g) ), std::cout );
  run( quaff::source(g) & (quaff::source(g)& quaff::source(g)) & quaff::source(g) );
}

