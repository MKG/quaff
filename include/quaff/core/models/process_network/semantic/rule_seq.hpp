/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_RULE_SEQ_HPP_INCLUDED
#define QUAFF_CORE_MODELS_PROCESS_NETWORK_SEMANTIC_RULE_SEQ_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/models/process_network/semantic/environment.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/set.hpp>
#include <boost/proto/proto.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <quaff/core/models/process_network/network.hpp>
#include <quaff/core/models/process_network/process.hpp>
#include <quaff/core/models/process_network/descriptor.hpp>
#include <quaff/core/backend/instructions.hpp>

////////////////////////////////////////////////////////////////////////////////
// The seq skeleton adapt a single function of the form: Outputs f( Inputs )
// into an entity able to be used in other skeletons
//
// Inputs  : the current function object f , the current PID p
// Outputs : an environment containing f as the single process of the network
////////////////////////////////////////////////////////////////////////////////
namespace quaff { namespace model
{
  struct convert_seq : boost::proto::callable
  {
    template<class Sig> struct result;

    template<class This,class Function,class Pid, class BackEnd>
    struct result<This(Function,Pid,BackEnd)>
    {
      typedef typename boost::proto::detail::uncvref<Function>::type  function;
      typedef typename boost::proto::detail::uncvref<Pid>::type       pid;
      typedef typename boost::proto::detail::uncvref<BackEnd>::type   back_end;

      static instruction::call<function,back_end>& f_;

      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , make_environment
        (
          make_network( boost::fusion::make_vector
                        ( make_process
                          ( pid()
                          , make_descriptor ( boost::fusion::vector<>()
                                            , boost::fusion::vector<>()
                                            , boost::fusion::make_vector(f_)
                                            )
                          , back_end()
                          )                         
                        )
                      , boost::mpl::set<pid>()
                      , boost::mpl::set<pid>()
                      ) 
        , typename boost::mpl::next<pid>::type()
        )
      );
      
      typedef typename nested::type type;
    };

    template<class Function,class Pid, class BackEnd>
    typename result<convert_seq(Function const&, Pid const&, BackEnd const&)>::type
    operator()(Function const& f, Pid const& pid, BackEnd const& be) const
    {
      instruction::call<Function,BackEnd> f_(f);
      
      return 
      make_environment
      (
        make_network( boost::fusion::make_vector
                      ( make_process
                        ( pid
                        , make_descriptor ( boost::fusion::vector<>()
                                          , boost::fusion::vector<>()
                                          , boost::fusion::make_vector(f_)
                                          )
                        , be
                        )                         
                      )
                    , boost::mpl::set<Pid>()
                    , boost::mpl::set<Pid>()
                    ) 
      , typename boost::mpl::next<Pid>::type()                    
      );
    }
  };
} }

#endif
