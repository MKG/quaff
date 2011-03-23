#ifndef __SKELL_BE__PROCESS__SEMANTIC__TOOLS__SPLICE_HPP__INCLUDED__
#define __SKELL_BE__PROCESS__SEMANTIC__TOOLS__SPLICE_HPP__INCLUDED__

// /////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007 for IEF, Universite Paris Sud, ORSAY.
// All rights reserved.
//
// License information are available in the LICENSE file.
//
// /////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/plus.hpp>

// /////////////////////////////////////////////////////////////////////////////
// Beginning of namespace skell
// /////////////////////////////////////////////////////////////////////////////
namespace skell
{
  // ///////////////////////////////////////////////////////////////////////////
  // spmd_size_of meta-function
  //
  // This meta-function retrieves the spmd_size of a process_network. PN rules
  // make it so it's always equals to the any process spmd_size, so we retrieves
  // ID#0 process for this purpsoe.
  //
  // Its parameters are :
  // - the process network to look into
  //
  // Its result is the PN spmd_size.
  // ///////////////////////////////////////////////////////////////////////////
  template<class PROC> struct spmd_size_of
  {
    typedef typename bm::at<PROC,bm::int_<0> >::type process;
    typedef typename process::spmd_size               type;
  };

  // ///////////////////////////////////////////////////////////////////////////
  // splice_prefix meta-function
  //
  // This meta-function build up a new processus by updating its spmd_block
  // size.
  //
  // Its parameters are :
  // - the processus to be modified
  // - the spmd size of both process networks to be spliced
  //
  // Its result is the updated processus.
  // ///////////////////////////////////////////////////////////////////////////
  template<class PROC,class W1,class W2> struct splice_prefix
  {
    // Extract processus infos
    typedef typename PROC::pid                              pid;
    typedef typename PROC::index                            index;
    typedef typename PROC::spmd_size                        spmd_size;
    typedef typename PROC::descriptor                       desc;
    typedef typename PROC::input_type                       input_type;
    typedef typename PROC::output_type                      output_type;

    // Get updates index & size
    typedef typename bm::plus<W1,W2>::type                  new_size;
    
    // Build updated processus
    typedef processus<pid,index,new_size,desc,input_type,output_type>  type;
  };
  
  // ///////////////////////////////////////////////////////////////////////////
  // splice_suffix meta-function
  //
  // This meta-function build up a new processus by updating its spmd_block
  // size and index.
  // Its parameters are :
  // - the processus to be modified
  // - the spmd size of both process networks to be spliced
  //
  // Its result is the updated processus.
  // ///////////////////////////////////////////////////////////////////////////
  template<class PROC,class W1,class W2> struct splice_suffix
  {
    // Extract processus infos
    typedef typename PROC::pid                              pid;
    typedef typename PROC::index                            index;
    typedef typename PROC::spmd_size                        spmd_size;
    typedef typename PROC::descriptor                       desc;
    typedef typename PROC::input_type                       input_type;
    typedef typename PROC::output_type                      output_type;

    // Get updates index & size
    typedef typename bm::plus<W1,W2>::type                  new_size;
    typedef typename bm::plus<index,W1>::type               new_index;
    
    // Build updated processus
    typedef processus<pid,new_index,new_size,desc,input_type,output_type>  type;
  };
}

// /////////////////////////////////////////////////////////////////////////////
// End of namespace skell
// /////////////////////////////////////////////////////////////////////////////
    
#endif // __SKELL_BE__PROCESS__SEMANTIC__TOOLS__SPLICE_HPP__INCLUDED__

