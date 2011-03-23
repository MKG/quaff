/******************************************************************************
 *         Copyright 2003-2008 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2007-2008 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2008      LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#ifndef __QUAFF__CORE__MARKER__INPUT_HPP__INCLUDED__
#define __QUAFF__CORE__MARKER__INPUT_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
/// @file
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  /*****************************************************************************
   * data wrapper. Used as container for stream input
   ****************************************************************************/
  template<class T, long Mem = 1> class data
  {
    public:

    data() {}
    data( const T& v ) { val[Mem-1] = v; }

    template<class U,long N> data( const data<U,N>& v )
    {
      val[Mem-1] = v.val[Mem-1];
    }

    template<class U,long N> data& operator=( const data<U,N>& v )
    {
      val[Mem-1] = v.val[Mem-1];
      return *this;
    }

    template<class Archive>
    void serialize( Archive& ar, unsigned int ) { ar & val[Mem-1]; }

    data& operator=( const T& v ) { val[Mem-1] = v; return *this; }

    T&        operator[](const long& i)       { return val[Mem+i-1]; }
    const T&  operator[](const long& i) const { return val[Mem+i-1]; }

    private:
    T val[Mem];
  };
}

  namespace boost
  {
    namespace mpi
    {
      template<class T, long Mem>
      struct is_mpi_datatype<quaff::data<T,Mem> > : mpl::true_ { };
    }

    namespace serialization
    {
      template<class T, long Mem>
      struct tracking_level< quaff::data<T,Mem> >
      {
        typedef mpl::integral_c_tag tag;
        typedef mpl::int_<track_never> type;
        BOOST_STATIC_CONSTANT( int
                             , value = tracking_level::type::value
                             );

        /* tracking for a class  */
        BOOST_STATIC_ASSERT((
            mpl::greater< implementation_level< quaff::data<T,Mem> >
                        , mpl::int_<primitive_type>
                        >::value
                           ));
      };

      template<class T, long Mem>
      struct implementation_level< quaff::data<T,Mem> >
      {
        typedef mpl::integral_c_tag tag;
        typedef mpl::int_< object_serializable > type;
        BOOST_STATIC_CONSTANT( int
                             , value = implementation_level::type::value
                             );
      };
    }
  }

#endif
