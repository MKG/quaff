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
#include <quaff/core/models/process_network/transform.hpp>
#include <quaff/core/backend/sequential/backend.hpp>
#include <quaff/core/backend/debug/backend.hpp>
#include <quaff/core/skeleton/seq.hpp>
#include <quaff/sdk/type_id.hpp>

void g() { std::cout << "Hello from g" << "\n"; }
void h() { std::cout << "Hello from h" << "\n"; }

template<class X> void probe(X const& x)
{
  quaff::model::build_network mn;
  quaff::model::empty_environment en;
  quaff::backend::debug_ be;
  
  mn( x, en, be )();
} 
 
template<class X> void debug(X const& x)
{
  quaff::model::build_network mn;
  quaff::model::empty_environment en;

  quaff::backend::sequential_ be;
  
  mn( x, en, be )();
}

QUAFF_TASK(g_, &g);
QUAFF_TASK(h_, &h);

int main()
{
  probe( ( ( (g_ & h_) & h_) 
           & (g_       & (g_ & h_) )
         )         
         & ( (g_ & h_) & (g_ & h_) )
       );
}

