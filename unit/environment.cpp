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
 
template<class X> void run(X const& x)
{
  quaff::semantic::convert<quaff::tag::process_network_> mn;
  quaff::model::empty_environment en;
  
  mn( x, en, quaff::current_backend ).network().run(quaff::current_backend);
}

int g()
{
  static int i(0);
  std::cout << "i: " << i << "\n";

  if(i < 10) i++;
  else
  {
    i = 0;
    quaff::terminate();
  }

  return i;
}

int main()
{
  run(  ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & (( quaff::source(g) & quaff::source(g) ) & quaff::source(g))
     );

  debug(  ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & ( quaff::source(g) & quaff::source(g) ) & quaff::source(g)
      & (( quaff::source(g) & quaff::source(g) ) & quaff::source(g))
     );
}

