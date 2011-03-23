#ifndef __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__SUFFIX_HPP__INCLUDED__
#define __QUAFF__CORE__LANGUAGE__SEMANTIC__TOOLS__SUFFIX_HPP__INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2003-2008 LASMEA UMR 6602 du CNRS.
// Copyright (c) 2007-2008 IEF    UMR 8622 du CNRS.
// All rights reserved.
//
// License information are available in the LICENSE file.
// Additionnal informations are available in the INFOS file.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @file quaff/core/language/semantic/tools/suffix.hpp
////////////////////////////////////////////////////////////////////////////////

namespace quaff
{
  // ///////////////////////////////////////////////////////////////////////////
  // suffix_processus meta-function
  //
  // This meta-function build up a new processus by adding a SendTo
  // macro-code and to add a output PID.
  //
  // Its parameters are :
  // - the processus to be modified
  // - the PID to add to the output list
  //
  // Its result is the updated processus.
  // ///////////////////////////////////////////////////////////////////////////
  template<class PROC,class PID> struct suffix_processus
  {
    // Extract processus infos
    typedef typename PROC::pid                              pid;
    typedef typename PROC::descriptor                       desc;
    typedef typename PROC::input_types                       input_types;
    typedef typename PROC::output_types                      output_types;
    typedef typename PROC::remanent_types                    remanent_types;

    // Extract descriptor infos
    typedef typename desc::i_pids                           i_pids;
    typedef typename desc::o_pids                           o_pids;
    typedef typename desc::macro                            macro;
    typedef typename desc::kind                             kind;

    // If kind is regular, adds a new MacroSend macro else don't add anything
    typedef typename bm::if_< boost::is_same<kind,regular>
                            , typename bm::push_back<macro,MacroSend>::type
                            , macro
                            >::type                         new_macro;
    typedef typename bm::push_back<o_pids,PID>::type        new_o_pids;

    // Build updated descriptor
    typedef descriptor<i_pids,new_o_pids,new_macro,kind>    new_desc;

    // Build updated processus
    typedef processus< pid
                     , new_desc
                     , input_types,output_types,remanent_types
                     >                                      type;
  };

  // ///////////////////////////////////////////////////////////////////////////
  // apply_suffix meta-function
  //
  // This meta-function is used by various semantic rules to correctly
  // link processus between process network as defined in the Phi_d
  // function. This link is made by inserting a pid into the output list
  // of the processus and adding a Send macro-code if the processus is a
  // regular one (ie non-farming).
  //
  // ///////////////////////////////////////////////////////////////////////////
  template<class PROC, class SET1, class SET2> struct apply_suffix
  {
    // Is PROC an element of SET1 (ususally o1) ?
    typedef typename is_inside<PROC,SET1>::type         is_inside;

    // Get PROC relative position in the set
    typedef typename position_of<PROC,SET1>::type       position;
    typedef typename relative_at<PROC,SET1>::type       dist;

    // Find the corresponding PROC in SET2 (usually i2)
    typedef typename bm::at<SET2,dist>::type            pid;

    // If PROC is indeed an output of P1:
    // * proceed with the link:
    //  - add a [SendTo] macro to PROC
    //  - add pid to its list of successors
    // Else
    // * return PROC untouched
    typedef typename bm::eval_if< is_inside,
                                  suffix_processus<PROC,pid>,
                                  PROC
                                >::type                 type;
  };
}

#endif
