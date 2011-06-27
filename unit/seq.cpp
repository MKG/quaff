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
#include <quaff/sdk/meta/name_of.hpp>
#include <quaff/sdk/meta/named_action.hpp>

double sample_function(int i)
{
  return 1./i;
}

int main()
{
  {
    quaff::meta::action<double(*)(int)>
    sample_action = sample_function;

    double res = sample_action(8);
    std::cout << res << "\n";
    std::cout << quaff::meta::name_of(sample_action) << "\n";

  }

  {
    quaff::meta::named_action<double(*)(int)>
    sample_action(sample_function,"sample_function");

    double res = sample_action(8);
    std::cout << res << "\n";
    std::cout << quaff::meta::name_of(sample_action) << "\n";
  }

  return 0;
}
