/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/mpl/assert.hpp>
#include <quaff/core/skeleton/seq.hpp>

void g(int) {}

struct foo : quaff::callable
{
  void operator()() {}
};

boost::function<int()> f;

QUAFF_TASK(g_, &g);
QUAFF_TASK(f_, f);
QUAFF_TASK(foo_, foo());

int main()
{

  g_ | f_ | foo_;

  return 0;
}
