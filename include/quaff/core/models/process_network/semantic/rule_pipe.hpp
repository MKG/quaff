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
/// @file quaff/core/models/process_network/semantic/environment.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/core/models/process_network/concat_network.hpp>

////////////////////////////////////////////////////////////////////////////////
// The pipe_ skeleton build the concatenation of two network
// Inputs  : the LHS skeleton, current state adn target back-end
// Outputs : an environment E = { build(RHS) }
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace semantic
{
  //////////////////////////////////////////////////////////////////////////////
  // Handle seq node in the process_network IR
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct  process_network_cases::case_<boost::proto::tag::bitwise_or>
        : boost::proto::
          when< boost::proto::bitwise_or < boost::proto::_
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
                                      , converter(lhs_ ,st,be)
                                      );
      static typename elhs::type& elhs_;
      
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( erhs
                                      , converter( rhs_ , st, be)
                                      );
      static typename erhs::type& erhs_;

      
      
      // Build the environment usign the joint_network
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL 
      ( nested
      ,converter(make_network(join_process
                    (elhs_.network.process(), erhs_.network.process()),
                      elhs_.network.input_set,
                      erhs_.network.output_set)
                      ,st, be
                      )
      );

      typedef typename nested::type type;
    };

    template<class LHS,class RHS,class State,class BackEnd>
    typename result<convert_pipe(LHS, RHS, State, BackEnd)>::type
    operator()(LHS const& lhs, RHS const& rhs, State& s, BackEnd const& be) const
    {
      convert<tag::process_network_> callee;
      
      // Pre-compute environment to not copy it twice
      BOOST_AUTO(lhe, callee(lhs,s,be)  );
      BOOST_AUTO(rhe, callee(rhs,s,be));
      
      return make_environment ( converter(join_process
                              (lhe.network().process,rhe.network().process),
                                s,
                                be)
                              , rhe.next_pid()
                              );
    }
  };
} }

#endif
