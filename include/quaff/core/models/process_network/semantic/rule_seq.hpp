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
#include <boost/proto/proto.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <quaff/core/models/process_network/network.hpp>
#include <quaff/core/models/process_network/process.hpp>
#include <quaff/core/models/process_network/descriptor.hpp>
#include <quaff/core/models/process_network/semantic/apply_rule.hpp>
#include <quaff/core/backend/instructions.hpp>

namespace quaff { namespace tag
{
  struct seq_ {};
} }

namespace quaff { namespace model
{
  template<class BackEnd, class Dummy>
  struct apply_rule<tag::seq_, BackEnd, Dummy>
  {
    template<class Sig> struct result;

    template<class This,class Function,class Pid>
    struct result<This(Function,Pid)>
    {
      typedef typename boost::proto::detail::uncvref<Function>::type  function;
      typedef typename boost::proto::detail::uncvref<Pid>::type       pid;

      typedef instruction::call<function,BackEnd>  instr_type;

      typedef descriptor< boost::fusion::vector<>
                        , boost::fusion::vector<>
                        , boost::fusion::vector<instr_type>
                        >                   descriptor_type;

      typedef process<pid,descriptor_type,BackEnd>  process_type;

      typedef network < boost::fusion::vector<process_type>
                      , boost::mpl::vector<pid>
                      , boost::mpl::vector<pid>
                      >                     type;
    };

    template<class Function,class Pid>
    typename result<apply_rule(Function&, Pid&)>::type
    operator()(Function& f, Pid&) const
    {
		typedef result<apply_rule(Function&, Pid&)> result_;
	
	  typename result_::instr_type i(f);
	  typename result_::descriptor_type d(boost::fusion::make_vector(i));
	  typename result_::process_type p(d);
	  typename result_::type that(boost::fusion::make_vector(p));
      //typename result<apply_rule(Function&, Pid&)>::type  that;

      // Seek the call_ and feed it with the actual function
      //instr_<0>(process_<0>(that).descriptor()) = f;
      return that;
    }
  };
} }

#endif
