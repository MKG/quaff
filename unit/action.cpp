/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/function.hpp>
#include <quaff/sdk/meta/action.hpp>

double g(int const& x, char& count) { count = (65+x%26); return 1./x; }

struct foo
{
  float operator()() const { return 3.141591f; }
};

int main()
{
  typedef boost::function<double(int const& x,char&)> f_t;
  f_t f(&g);
  quaff::meta::action< f_t > a = f;
  quaff::meta::action< foo > b = foo();

  double r;
  int i = 3;
  char c;

  a(i,c,r);
  printf("%c -- %f\n", c, r);

  b(r);
  printf("%f\n", r);

  return 0;
}
