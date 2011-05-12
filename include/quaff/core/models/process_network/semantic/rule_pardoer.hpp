/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_RULE_PARDOER_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_RULE_PARDOER_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/semantic/rule_pardoer.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/models/process_network/joint_network.hpp>
#include <quaff/core/dsl/grammar.hpp>
#include <boost/fusion/include/vector_tie.hpp>
////////////////////////////////////////////////////////////////////////////////
// The pardoer_ skeleton build the union of N pardo
// Inputs  : the LHS/RHS skeleton, current state adn target back-end
// Outputs : an environment E = { build(LHS) U build(RHS) }
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace semantic
{
  //////////////////////////////////////////////////////////////////////////////
  // Handle seq node in the process_network IR
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct  process_network_cases::case_<tag::pardoer_>
        : boost::proto::
         when<boost::proto::binary_expr<tag::pardoer_
                                        , boost::proto::_
                                        , boost::proto::_
                                        >
              , convert_pardoer<tag::process_network_>
                ( boost::proto::_left
                , boost::proto::_right
                , boost::proto::_state
                , boost::proto::_data
                )
              >
  {};
} }

namespace quaff { namespace semantic
{    
  template<> struct convert_pardoer<tag::process_network_>
  {
    template<class Sig> struct result;

    template<class This,class LHS,class RHS,class State,class BackEnd>
    struct result<This(LHS,RHS,State,BackEnd)>
    {
      typedef typename boost::proto::detail::uncvref<LHS>::type     lhs;
      typedef typename boost::proto::detail::uncvref<RHS>::type     rhs;
      typedef typename boost::proto::detail::uncvref<State>::type   state;
      typedef typename boost::proto::detail::uncvref<BackEnd>::type back_end;

      static int& lhs_; static rhs& rhs_; 
      static state& st; static back_end& be;
      static convert<tag::process_network_>& converter;
      
      
      /* BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( elhs
                                      , converter(rhs_,st,be)
                                      );
      static typename elhs::type& elhs_;
      typedef typename elhs::type::network_type::input_set  l_iset;
      typedef typename elhs::type::network_type::output_set l_oset;
      
       BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , model::make_environment
        (
            model::make_network< data_type>
            ( boost::fusion::make_vector
              ( model::make_process<l_iset,l_oset>
                ( pid()
                , boost::fusion::make_vector(f_)
                )
              )
              , boost::mpl::set<pid>()
              , boost::mpl::set<pid>()
            )
        , typename pid::next()
        )
      );*/
      
      
      /*
      static typedef elhs_.next_pid() pid;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL 
      ( nested
      , make_environment
        ( elhs_.network()
        , model::pids<pid::begin, pid::begin + lsh>
        ) 
      );*/
                
      //typedef typename nested::type type;
    };
    
   
          
          
    template<class LHS,class RHS,class State,class BackEnd>
    typename result<convert_pardoer(LHS, RHS, State, BackEnd)>::type
    operator()(LHS const& lhs, RHS const& rhs, State& s, BackEnd const& be) const
    {
      convert<tag::process_network_> callee;
      
      // Pre-compute environment to not copy it twice
      BOOST_AUTO(lhe, callee(rhs,s,be)  );
      
      return lhe;
    }
  };
} }

#endif
