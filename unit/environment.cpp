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
#include <quaff/core/backend.hpp>
#include <quaff/core/skeleton/seq.hpp>
#include <quaff/core/skeleton/source.hpp>
#include <quaff/core/skeleton/sink.hpp>

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

void h(int i)
{
  std::cout << "h say : " << i << "\n";
}

int main()
{
  debug( quaff::source(g) | quaff::seq(x2) | quaff::sink(h), std::cout );
  run( quaff::source(g) | quaff::seq(x2) | quaff::sink(h) );
}

