/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007 & onward IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef QUAFF_SDK_META_TRANSFORM_IF_HPP_INCLUDED
#define QUAFF_SDK_META_TRANSFORM_IF_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/sdk/meta/transform_if.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/apply.hpp>
#include <quaff/sdk/meta/strip.hpp>
#include <boost/fusion/include/transform.hpp>

namespace quaff { namespace details
{
  template<class Transform, class Predicate>
  struct transform_if_impl
  {
    template<class Sig> struct result;

    template<class This,class Element>
    struct  result<This(Element)>
    {
      typedef typename meta::strip<Element>::type base;
      typedef typename boost::mpl::
              if_ < typename boost::mpl::apply<Predicate, base>::type
                  , typename boost::result_of<Transform(base)>::type
                  , base
                  >::type type;
    };

    transform_if_impl( Transform const& t ) : transform_(t) {}

    template<class Element> inline
    typename result<transform_if_impl(Element const&)>::type
    operator()(Element const& e) const
    {
      return eval(e,typename boost::mpl::apply<Predicate,Element>::type());
    }

    private:
    template<class Element> inline
    typename result<transform_if_impl(Element const&)>::type
    eval(Element const& e, boost::mpl::false_ const &) const
    {
      return e;
    }

    template<class Element> inline
    typename result<transform_if_impl(Element const&)>::type
    eval(Element const& e, boost::mpl::true_ const &) const
    {
      return transform_(e);
    }

    Transform const& transform_;
  };
} }

namespace quaff { namespace result_of
{
  template<class S,class T, class P>
  struct  transform_if
        : boost::fusion::result_of::
          transform < S const
                    , details::transform_if_impl< T
                                                , typename  boost::mpl::
                                                            lambda<P>::type
                                                >
                    >
  {};
}}

namespace quaff { namespace meta
{
  template<class S,class T, class P>
  typename quaff::result_of::transform_if<S,T,P>::type
  transform_if( S const& s, T const& t, P const& p)
  {
    details::transform_if_impl<T,typename boost::mpl::lambda<P>::type> callee(t);
    return boost::fusion::transform(s,callee);
  }
} }

#endif
