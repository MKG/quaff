/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_RULE_PIPE_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_RULE_PIPE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/semantic/rule_pipe
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/models/process_network/chain_network.hpp>
#include <quaff/core/models/process_network/semantic/details/pipe.hpp>

////////////////////////////////////////////////////////////////////////////////
// The pipe_ skeleton build the union of two network and add send/receive
// Inputs  : the LHS/RHS skeleton, current state adn target back-end
// Outputs : an environment E = { build(LHS) U build(RHS) } * {send/recv}
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace semantic
{
  //////////////////////////////////////////////////////////////////////////////
  // Handle seq node in the process_network IR
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct  process_network_cases::case_<boost::proto::tag::bitwise_or>
        : boost::proto::
          when< boost::proto::bitwise_or< boost::proto::_
                                        , boost::proto::_
                                        >
              , convert_pipe<tag::process_network_>
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
  template<> struct convert_pipe<tag::process_network_>
  {
    template<class Sig> struct result;

    template<class This,class LHS,class RHS,class State,class BackEnd>
    struct result<This(LHS,RHS,State,BackEnd)>
    {
      typedef typename boost::proto::detail::uncvref<LHS>::type     lhs;
      typedef typename boost::proto::detail::uncvref<RHS>::type     rhs;
      typedef typename boost::proto::detail::uncvref<State>::type   state;
      typedef typename boost::proto::detail::uncvref<BackEnd>::type back_end;

      static lhs& lhs_; static rhs& rhs_; 
      static state& st; static back_end& be;
      static convert<tag::process_network_>& converter;
      
      // "temporary" environments
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( elhs
                                      , converter(lhs_,st,be)
                                      );
      static typename elhs::type& elhs_;
      
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( erhs
                                      , converter( rhs_, elhs_, be)
                                      );
      static typename erhs::type& erhs_;

      // lhs/rhs in/output types
      typedef typename erhs::type::network_type::input_set  r_iset;
      typedef typename elhs::type::network_type::output_set l_oset;
      
      // Build the environment usign the joint_network
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL 
      ( nested
      , make_environment
        ( chain_network(  elhs_.network()
                        .transform_if ( details::add_send<r_iset,back_end>()
                                      , details::is_inside<l_oset>()
                                      )
                      , erhs_.network()
                      )
        , erhs_.next_pid()
        ) 
      );

      typedef typename nested::type type;
    };

    template<class LHS,class RHS,class State,class BackEnd>
    typename result<convert_pipe(LHS, RHS, State, BackEnd)>::type
    operator()(LHS const& lhs, RHS const& rhs, State& s, BackEnd const& be) const
    {
      typedef result<convert_pipe(LHS, RHS, State, BackEnd)> res_type;
      convert<tag::process_network_> callee;
      
      // Pre-compute environment to not copy it twice
      BOOST_AUTO(lhe, callee(lhs,s,be)  );
      BOOST_AUTO(rhe, callee(rhs,lhe,be));
      
      return
      make_environment( chain_network
                        ( lhe.network()
                          .transform_if ( details::add_send< typename res_type::r_iset
                                                  , BackEnd
                                                  >()
                                        , details::is_inside<typename res_type::l_oset>()
                                        )
                      , rhe.network()
                                )
                              , rhe.next_pid()
                              );
    }
  };
} }

#endif
