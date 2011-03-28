/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <boost/function.hpp>
#include <quaff/core/skeleton/seq.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <quaff/core/models/process_network.hpp>

double g(int i) { return 1./(i+1); }

struct mpi_
{
  struct input
  {

  };

  struct output
  {

  };
};

template<class BackEnd>
struct convert_seq
{
  template<class Sig> struct result;

  template<class This, class Expr, class State>
  struct result<This(Expr,State)>
  {
    typedef typename boost::proto::detail::uncvref<Expr>::type   value;
    typedef typename boost::proto::detail::uncvref<State>::type  pid;

    typedef
    quaff::model::descriptor< boost::mpl::vector_c<int>
                            , boost::mpl::vector_c<int>
                            , value
                            , BackEnd
                            >                             descriptor_t;

    typedef quaff::model::processus< pid, descriptor_t>   processus_t;

    typedef quaff::model::network < boost::fusion::vector< processus_t >
                                  , pid
                                  , pid
                                  >                       type;
  };

  template<class Expr,class State>
  typename result<convert_seq(Expr&, State&)>::type
  operator()(Expr& xpr, State& pid)
  {
    typename result<convert_seq(Expr&, State&)>::descriptor_t d(xpr);
    typename result<convert_seq(Expr&, State&)>::processus_t  p(d);
    typename result<convert_seq(Expr&, State&)>::type
    that (boost::fusion::make_vector(p));

    return that;
  }
};

namespace boost { namespace proto
{
  template<class BackEnd> struct is_callable<convert_seq<BackEnd> > : mpl::true_ {};
} }

template<class BackEnd>
struct  graph
      : boost::proto::when< boost::proto::terminal<boost::proto::_>
                          , convert_seq<BackEnd>( boost::proto::_value
                                                , boost::proto::_state
                                                )
                          >
{};

template<class X>
typename boost::result_of< graph<mpi_>(X const&, boost::mpl::int_<0>) >::type
make(X const& x)
{
  graph<mpi_> grr;
  boost::mpl::int_<0> pid;

  return grr(x,pid);
}

int main()
{
  boost::function<double(int)> fg(g);
  std::vector<int>    in(4);
  std::vector<double> out;

  for(int i=0;i<4;++i) in[i] = i;

  make( quaff::seq(fg) )(in, std::back_inserter(out) );

  for(int i=0;i<out.size();++i) std::cout << out[i] << "\n";

  return 0;
}
