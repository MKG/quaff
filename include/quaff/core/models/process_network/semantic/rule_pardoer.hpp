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
#include <boost/fusion/include/at_c.hpp>

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
      
      
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( erhs
                                      , converter( rhs_, st, be)
                                      );
      static typename erhs::type& erhs_;

      static typename erhs::type::network_type::nodes_type vec;
     //typedef boost::fusion::at_c<0>(vec) p;
     
     //typedef boost::fusion::at_c<0>(typename erhs::type::network_type::nodes_type())::input_type isi;
     //typedef typename boost::fusion::at_c<0>(vec)::input_type plop;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(p
                                      , boost::fusion::at_c<0>(vec));
                                      
     typedef typename p::type& plop;
     //typedef typename p::type plip;
     

     //static typename boost::fusion::at_c<0>(typename erhs::type::network_type::nodes_type)& p;
     BOOST_TYPEOF_NESTED_TYPEDEF_TPL(input_type
                                      , p::input_type);
     //static typename input_type::type& inty;
     
     BOOST_TYPEOF_NESTED_TYPEDEF_TPL(output_type
                                    , p::output_type); 
                                    
     //typedef typename input_type::type& input_type_;                               
     //typedef typename output_type::type& output_type_;
     
     
     //static typename output_type::type& outty;
     //static typename p::pid_type pid;
     typedef typename p::type::pid_type ppp; 
     //typedef typename p::type pog;
     
     //typedef typename p::input_type in_type;
     //typedef typename p::output_type out_type;
     //typedef typename plop.pid_type() pid;
     //BOOST_TYPEOF_NESTED_TYPEDEF_TPL(coco
     //                               , p::type::code() );
                                       
     //BOOST_TYPEOF_NESTED_TYPEDEF_TPL(cocoul
     //                               , plop );
     static typename p::type& cocoul_ ;
                                                                     
     //static typename coco::type& codelet; 
     typedef typename p::type::codelet_type code_type;
     //static code_type& code;
     typedef boost::fusion::vector2< input_type, output_type>  data_type;
      
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , model::make_environment 
        (
            model::make_network< data_type>
            ( boost::fusion::make_vector
              /*( model::make_process<input_type, output_type
                                    , boost::mpl::int_<8>  >
                ( ppp()
                , cocoul_.code_
                )
              )*/
             // (model::process<typename extends< ppp, boost::mpl::int_<8>  >::type
              (model::process< typename model::extends<ppp,boost::mpl::int_<8>  >::type
                              , code_type
                              , input_type
                              , output_type
                              >
                             (cocoul_.code_))
              , boost::mpl::set< ppp >()
              , boost::mpl::set< ppp >()
            )
        , typename ppp::next()
        )
      );
      
      // Build the environment usign the joint_network
      /*BOOST_TYPEOF_NESTED_TYPEDEF_TPL 
      ( nested
      , make_environment
        (  erhs_.network()
        //, model::extends<erhs_.next_pid, lhs_>()
        , model::extends<typename erhs::type::pid_type::type , boost::mpl::int_<8> >() //erhs_.next_pid()
        ) 
      );*/

      typedef typename nested::type type;
      
    };
    
   
          
        
    template<class LHS,class RHS,class State,class BackEnd>
    typename result<convert_pardoer(LHS, RHS, State, BackEnd)>::type
    operator()(LHS const& lhs, RHS const& rhs, State& s, BackEnd const& be) const
    {
      typedef result<convert_pardoer(LHS, RHS, State, BackEnd)> res_type;

      convert<tag::process_network_> callee;
      
      // Pre-compute environment to not copy it twice
      //BOOST_AUTO(lhe, callee(rhs,s,be)  );
      
      return make__environment 
        (model::make_network< res_type::data_type>
            ( boost::fusion::make_vector
              (model::process< typename model::extends<typename res_type::ppp, boost::mpl::int_<8>  >::type
                              , typename res_type::code_type
                              , typename res_type::input_type
                              , typename res_type::output_type
                              > (typename res_type::plop::code() ) )
              , boost::mpl::set< typename res_type::ppp >()
              , boost::mpl::set< typename res_type::ppp >()
            )
        , typename res_type::ppp::next()
        );
    }
  };
} }

#endif
