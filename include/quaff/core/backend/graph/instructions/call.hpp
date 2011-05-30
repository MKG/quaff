/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_CORE_BACKEND_GRAPH_INSTRUCTIONS_CALL_HPP_INCLUDED
#define QUAFF_CORE_BACKEND_GRAPH_INSTRUCTIONS_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/backend/graph/instructions/call.hpp
////////////////////////////////////////////////////////////////////////////////
#include <quaff/sdk/type_id.hpp>

namespace quaff { namespace instruction
{
  template<class Function>
  struct call<Function,backend::graph_>
  {
    typedef typename Function::input_type   input_type;
    typedef typename Function::output_type  output_type;

    call(Function const& f) : mFunction(f) {}

    template<class Pid, class Input, class Output, class Context>
    void operator() ( Pid const& p, Input&, Output&, Context& os ) const
    {

     os  << "p" << p << " [label=\"p" << p
         << "\\n fonction " << (void*)(&mFunction) << "\" ];\n\t";

     handle_input<Input>( p ,os
                        , typename boost::is_same < typename Input::type
                                                  , boost::mpl::void_
                                                  >::type()
                        );

     handle_output<Output>( p ,os
                          , typename boost::is_same < typename Output::type
                                                    , boost::mpl::void_
                                                    >::type()
                          );
    }

    template<class Input, class Pid, class Context> inline void
    handle_input( Pid const& p, Context& os, boost::mpl::true_ const& ) const
    {
      os  << "dd"  << " -- p" << p << ";\n\t";
    }

    template<class Input, class Pid, class Context> inline void
    handle_input( Pid const& p, Context& os, boost::mpl::false_ const& ) const
    {
      os  << "di" << p << " [shape=box label=\""
                      << type_id<typename Input::type>()
                      << "\"];\n\t";
      os << "di" << p << " -- p" << p << ";\n\t";
    }

    template<class Output, class Pid, class Context> inline void
    handle_output( Pid const& p, Context& os, boost::mpl::true_ const& ) const
    {
        os << "p" << p << " -- df [dir=forward arrowsize=2];\n\t";
    }

    template<class Output, class Pid, class Context> inline void
    handle_output( Pid const& p, Context& os, boost::mpl::false_ const& ) const
    {
      os << "do" << p << " [shape=box label=\""
                    << type_id<typename Output::type>()
                    << "\"];\n\t";
      os << "p" << p << " -- do" << p << " [dir=forward];\n\t";
    }

    Function  mFunction;
  };
} }

#endif
