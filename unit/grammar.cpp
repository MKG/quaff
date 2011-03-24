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

int main()
{
  boost::function<int()> f;
  foo h;

    (quaff::seq(f) | quaff::seq(&g) | quaff::seq(h))
  & (quaff::seq(f) | quaff::seq(&g) )
  & (   (quaff::seq(f) | quaff::seq(&g) )
      , (quaff::seq(f) | quaff::seq(&g) )
    );

  return 0;
}
