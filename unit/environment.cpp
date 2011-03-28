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
#include <boost/function.hpp>
#include <boost/utility/result_of.hpp>
#include <quaff/core/models/process_network/transform.hpp>
#include <quaff/core/skeleton/seq.hpp>
#include <quaff/sdk/type_id.hpp>

void g() { std::cout << "Hello from g" << "\n"; }
typedef void (*ptrfun)();

template<class X> void run(X const& x)
{
  quaff::model::make_network mn;
  quaff::model::empty_environment en;

  std::cout << quaff::type_id(mn( x, en )) << "\n";
  mn( x, en )();
}

int main()
{
  run( quaff::seq(&g) );
}
