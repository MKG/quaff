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

int sample_source()
{
  std::cout << "yo from the source !\n";
  quaff::terminate();
}

int main()
{
  quaff::debug(  quaff::source(sample_source) & quaff::source(sample_source)
              , std::cout
              );
  std::cout << "\n";

  quaff::debug(  quaff::pardo<2>( quaff::source(sample_source) )
              , std::cout
              );
  std::cout << "\n";

  quaff::run( quaff::source(sample_source) & quaff::source(sample_source) );
  std::cout << "\n";

  quaff::run( quaff::pardo<4>( quaff::source(sample_source) )  );
  std::cout << "\n";

  return 0;
}
