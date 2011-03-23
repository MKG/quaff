#ifndef __CONFIG__STDLIB__STRING_HPP__INCLUDED__
#define __CONFIG__STDLIB__STRING_HPP__INCLUDED__

// /////////////////////////////////////////////////////////////////////////////
// NT2 -- Copyright (c) 2007 for LASMEA UMR 6602 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available on http://nt2.sourceforge.net
// /////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/support/config/stdlib/string.hpp
/// @brief std independant string class
///
/// inner_string provides a thinner version of std::string which is
/// unusable on some platform.
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  //////////////////////////////////////////////////////////////////////////////
  /// @class inner_stringk
  /// @brief lightweight string class
  ///
  // inner_string provides a better version of std::string, which is badly
  // written and makes NT2 dies of shame when compiled on the IBM CELL BE
  // processor
  //////////////////////////////////////////////////////////////////////////////
  template<class T> class inner_string
  {
    public:
    typedef T                 char_type;
    typedef const char_type&  const_reference;
    typedef char_type&        reference;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Default constructor
    ///
    /// Default string constructor that instanciates a empty matrix.
    ///
    /// @pre None.
    /// @post the string instance is void
    ////////////////////////////////////////////////////////////////////////////
    inner_string() : mData(NULL),mAllocated(0),mSize(0) {}

    ////////////////////////////////////////////////////////////////////////////
    /// @brief sub-string constructor
    /// @param str
    /// @param pos   from
    /// @param n     length (default str.size() - pos)
    ////////////////////////////////////////////////////////////////////////////
    inner_string(const inner_string& str, size_t pos = 0,size_t n = size_t(~0))
    {
      size_t sz = str.size();
      size_t l  = pos>=sz ? sz-1 : sz- pos;
      size_t cp = n>0 ? (n>l ? l : n) : l;
      build(cp,str.c_str()+pos);
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief copy constructor from char_type* and length
    /// @param s char_type * to be copied
    /// @param n size to be limited to
    ////////////////////////////////////////////////////////////////////////////
    inner_string(const char_type* s,size_t n) { build(n,s);         }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief copy constructor from char_type*
    /// @param s char_type * to be copied
    ////////////////////////////////////////////////////////////////////////////
    inner_string(const char_type* s)          { build(strlen(s),s); }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief filling with given element of char_type at given size
    /// @param c char_type  to be used
    /// @param n size to be limited to
    ////////////////////////////////////////////////////////////////////////////
    inner_string(size_t n, const char_type& c)
    {
      allocate(n);
      for(int i=0;i<mSize;i++) mData[i] = c;
      mData[mSize] ='\0';
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief filling with contiguous iterator range
    /// @param b  beginning
    /// @param e  end
    ////////////////////////////////////////////////////////////////////////////
    template<class IT> inner_string(IT b, IT e)
    {
      size_t i=0;
      IT cur = b;
      allocate(e-b+1);
      while(cur!=e)
      {
        mData[i] = *cur;
        i++;
        cur++;
      }
      mData[mSize] ='\0';
    }

    ~inner_string()
    {
      release();
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief affectation from self type
    /// @param src inner_string to be assigned
    ////////////////////////////////////////////////////////////////////////////
    inner_string& operator=(const inner_string& src)
    {
      if(this != &src )
      {
        if(src.size() < mAllocated)
        {
          mSize = src.size();
          memcpy(mData,src.c_str(),mSize*sizeof(char_type));
        }
        else
        {
          release();
          build(src.size(),src.c_str());
        }
      }
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief affectation from char_type*
    /// @param s char_type* to be assigned
    ////////////////////////////////////////////////////////////////////////////
    inner_string& operator=(const char_type* s)
    {
      if(strlen(s) < mAllocated)
      {
        mSize = strlen(s);
        memcpy(mData,s,mSize*sizeof(char_type));
      }
      else
      {
        release();
        build(strlen(s),s);
      }
      return *this;
    }
    ////////////////////////////////////////////////////////////////////////////
    /// @brief affectation from char_type
    /// @param c char_type to be assigned
    ////////////////////////////////////////////////////////////////////////////
    inner_string& operator=(char_type c)
    {
      if (mAllocated)
      {
        mSize = 1;
        mData[0] = c;
      }
      else
      {
        release();
        build(1,c);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief c_str char * equivalent (shared)
    ////////////////////////////////////////////////////////////////////////////
    const char_type* c_str() const { return mData; }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief size    number of elements
    ////////////////////////////////////////////////////////////////////////////
    size_t size()     const { return mSize;       }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief length    number of elements
    ////////////////////////////////////////////////////////////////////////////
    size_t length()   const { return size();      }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief max_size    capacity allocated
    ////////////////////////////////////////////////////////////////////////////
    size_t max_size() const { return mAllocated;  }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief capacity    capacity allocated
    ////////////////////////////////////////////////////////////////////////////
    size_t capacity() const { return max_size();  }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief const ith element
    ///
    /// const ith element
    ///
    /// @param i  index from 0
    ////////////////////////////////////////////////////////////////////////////
    const_reference operator[](size_t i) const  { return mData[i]; }//
    reference       operator[](size_t i)        { return mData[i]; }

    inner_string& operator+=( const inner_string& src )
    {
      char_type* tmp;
      size_t sz = mSize+src.size();
      memory_alloc( tmp, sz+1 );
      strncpy(tmp      ,mData,mSize);
      strncpy(tmp+mSize,src.c_str(),src.size());
      release();
      build(sz,tmp);
      memory_desalloc(tmp);
      return *this;
    }

    protected:
    void allocate(size_t n)
    {
      mAllocated  = n + n >> 1;
      memory_alloc( mData, mAllocated );
      mSize       = n;
    }

    void release()
    {
      if(mData) memory_desalloc(mData);
      mAllocated = mSize = 0;
    }

    void build(size_t n,const char_type* s)
    {
      allocate(n);
      strncpy(mData,s,n);
      mData[mSize] ='\0';
    }

    private:
    char_type*  mData;
    size_t      mAllocated;
    size_t      mSize;
  };

  typedef inner_string<char> string;

  template<class T> static inline
  inner_string<T> operator+( const inner_string<T>& a, const inner_string<T>& b )
  {
    inner_string<T> tmp(a);
    tmp += b;
    return tmp;
  }
}

#endif
