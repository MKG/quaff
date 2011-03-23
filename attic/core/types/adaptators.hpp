/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#if !BOOST_PP_IS_ITERATING

#ifndef __QUAFF__CORE__TYPES__ADAPTATORs_HPP__INCLUDED__
#define __QUAFF__CORE__TYPES__ADAPTATORs_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/types/adaptators.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/void.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/logical/or.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, QUAFF_PP_CONFIG_MAX_ARITY)
#define BOOST_PP_FILENAME_1 <quaff/core/types/adaptators.hpp>
#include BOOST_PP_ITERATE()

#endif

#elif BOOST_PP_ITERATION_DEPTH() == 1

#define BOOST_PP_ITERATION_LIMITS (0, QUAFF_PP_CONFIG_MAX_ARITY)
#define BOOST_PP_FILENAME_2 <quaff/core/types/adaptators.hpp>
#include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2

#define BOOST_PP_ITERATION_LIMITS (0, QUAFF_PP_CONFIG_MAX_ARITY)
#define BOOST_PP_FILENAME_3 <quaff/core/types/adaptators.hpp>
#include BOOST_PP_ITERATE()

#else
#if ( BOOST_PP_FRAME_ITERATION(1)+BOOST_PP_FRAME_ITERATION(2)+BOOST_PP_FRAME_ITERATION(3) <= QUAFF_PP_CONFIG_MAX_ARITY )

namespace quaff
{
  #define ITER_1 BOOST_PP_FRAME_ITERATION(1)
  #define ITER_2 BOOST_PP_FRAME_ITERATION(2)
  #define ITER_3 BOOST_PP_FRAME_ITERATION(3)

  #define _L_GET(z, n, text)  bt::get<n>(text)
  #define _L_XGET(z, n, text) bt::get<BOOST_PP_INC(n)>(text)

  #if ( BOOST_PP_FRAME_ITERATION(2) != 0 )
  template<class FunctionType, FunctionType Function, class Ret>
  struct adaptator<FunctionType,Function,bm::void_,Ret,ITER_1,ITER_2,ITER_3>
  {
    typedef typename build_input_list<FunctionType>::type             input_types;
    typedef typename build_output_list<FunctionType,bm::false_>::type output_types;
    typedef typename build_remanent_list<FunctionType>::type          remanent_types;
    typedef FunctionType          function_type;

    void operator()(  input_types&    BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_1),BOOST_PP_IDENTITY(i), BOOST_PP_EMPTY)(),
                      output_types&   BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_2),BOOST_PP_IDENTITY(o), BOOST_PP_EMPTY)(),
                      remanent_types& BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_3),BOOST_PP_IDENTITY(m), BOOST_PP_EMPTY)()
                   ) const
    {
      bt::get<0>(o) = Function( BOOST_PP_ENUM(ITER_1, _L_GET, i)
                                BOOST_PP_COMMA_IF(BOOST_PP_AND(ITER_1,BOOST_PP_OR(BOOST_PP_DEC(ITER_2),ITER_3)))
                                BOOST_PP_ENUM( BOOST_PP_DEC(ITER_2), _L_XGET, o)
                                BOOST_PP_COMMA_IF( BOOST_PP_AND(BOOST_PP_DEC(ITER_2),ITER_3) )
                                BOOST_PP_ENUM(ITER_3, _L_GET, m)
                              );
    }
  };

  template<class FunctionType, FunctionType Function, class Ret, class Functor>
  struct adaptator<FunctionType,Function,Functor,Ret,ITER_1,ITER_2,ITER_3>
  {
    typedef typename build_input_list<FunctionType>::type             input_types;
    typedef typename build_output_list<FunctionType,bm::true_>::type  output_types;
    typedef typename build_remanent_list<FunctionType>::type          remanent_types;
    typedef FunctionType          function_type;

    void operator()(  input_types&    BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_1),BOOST_PP_IDENTITY(i), BOOST_PP_EMPTY)(),
                      output_types&   BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_2),BOOST_PP_IDENTITY(o), BOOST_PP_EMPTY)(),
                      remanent_types& BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_3),BOOST_PP_IDENTITY(m), BOOST_PP_EMPTY)()
                   ) const
    {
      bt::get<0>(o) = (mFunctor.*Function)( BOOST_PP_ENUM(ITER_1, _L_GET, i)
                                            BOOST_PP_COMMA_IF(BOOST_PP_AND(ITER_1,BOOST_PP_OR(BOOST_PP_DEC(ITER_2),ITER_3)))
                                            BOOST_PP_ENUM( BOOST_PP_DEC(ITER_2), _L_XGET, o)
                                            BOOST_PP_COMMA_IF( BOOST_PP_AND(BOOST_PP_DEC(ITER_2),ITER_3) )
                                            BOOST_PP_ENUM(ITER_3, _L_GET, m)
                                          );
    }
    mutable Functor mFunctor;
  };
  #endif

  template<class FunctionType, FunctionType Function>
  struct adaptator<FunctionType,Function,bm::void_,void,ITER_1,ITER_2,ITER_3>
  {
    typedef typename build_input_list<FunctionType>::type             input_types;
    typedef typename build_output_list<FunctionType,bm::false_>::type output_types;
    typedef typename build_remanent_list<FunctionType>::type          remanent_types;
    typedef FunctionType          function_type;

    void operator()(  input_types&    BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_1),BOOST_PP_IDENTITY(i), BOOST_PP_EMPTY)(),
                      output_types&   BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_2),BOOST_PP_IDENTITY(o), BOOST_PP_EMPTY)(),
                      remanent_types& BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_3),BOOST_PP_IDENTITY(m), BOOST_PP_EMPTY)()
                   ) const
    {
      Function( BOOST_PP_ENUM(ITER_1, _L_GET, i)
                BOOST_PP_COMMA_IF(BOOST_PP_AND(ITER_1,BOOST_PP_OR(ITER_2,ITER_3)))
                BOOST_PP_ENUM(ITER_2, _L_GET, o)
                BOOST_PP_COMMA_IF( BOOST_PP_AND(ITER_2,ITER_3) )
                BOOST_PP_ENUM(ITER_3, _L_GET, m)
              );
    }
  };

  template<class FunctionType, FunctionType Function, class Functor>
  struct adaptator<FunctionType,Function,Functor,void,ITER_1,ITER_2,ITER_3>
  {
    typedef typename build_input_list<FunctionType>::type             input_types;
    typedef typename build_output_list<FunctionType,bm::true_>::type  output_types;
    typedef typename build_remanent_list<FunctionType>::type          remanent_types;
    typedef FunctionType          function_type;

    void operator()(  input_types&    BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_1),BOOST_PP_IDENTITY(i), BOOST_PP_EMPTY)(),
                      output_types&   BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_2),BOOST_PP_IDENTITY(o), BOOST_PP_EMPTY)(),
                      remanent_types& BOOST_PP_IF( BOOST_PP_NOT_EQUAL(0,ITER_3),BOOST_PP_IDENTITY(m), BOOST_PP_EMPTY)()
                   ) const
    {
      (mFunctor.*Function)( BOOST_PP_ENUM(ITER_1, _L_GET, i)
                            BOOST_PP_COMMA_IF(BOOST_PP_AND(ITER_1,BOOST_PP_OR(ITER_2,ITER_3)))
                            BOOST_PP_ENUM(ITER_2, _L_GET, o)
                            BOOST_PP_COMMA_IF( BOOST_PP_AND(ITER_2,ITER_3) )
                            BOOST_PP_ENUM(ITER_3, _L_GET, m)
                          );
    }
    mutable Functor mFunctor;
  };
}
#endif

#endif
