#ifndef __INSTRUCTION_FARM__HPP__INCLUDED__
#define __INSTRUCTION_FARM__HPP__INCLUDED__

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>

// /////////////////////////////////////////////////////////////////////////////
// Beginning of namespace quaff
// /////////////////////////////////////////////////////////////////////////////
namespace quaff
{
  namespace bm = boost::mpl;

  // ///////////////////////////////////////////////////////////////////////////
  // start_farm meta-function
  // Generates the inline code for starting up a Farm skeleton, ie starting all
  // the non-blocking receive on all slaves and predecessor
  // ///////////////////////////////////////////////////////////////////////////
  template<class IPID, class R,int I, int N> struct start_farm
  {
    static const int pid  = bm::at<IPID,bm::int_<I+1> >::type::value;

    static void Do( bool* busy, R* result, MPI_Request* request,
		    int* requestor, int* workerIn, int* workerOut, int& requestors )
    {
      busy[I] = false;
      result[I].probe( pid, MPI_ANY_TAG, request[requestors]);
      requestor[requestors++] = I;
      workerOut[I] = workerIn[I]  = pid;
      start_farm<IPID,R,I+1,N>::Do(busy,result,request,requestor,workerIn,workerOut,requestors);
    }
  };

  template<class IPID, class R, int N> struct start_farm<IPID,R,N,N>
  {
    static void Do( bool*, R*, MPI_Request*,int*, int*, int*, int& ) {}
  };

  // ///////////////////////////////////////////////////////////////////////////
  // Farm structure - code fragment for Farmer process.
  // ///////////////////////////////////////////////////////////////////////////
  template<class IPID,class OPID,class IT,class OT> struct InstrFarm
  {
    typedef bm::size<IPID> isz;
    typedef bm::size<OPID> osz;

    InstrFarm() {}
    template<class ITT,class OTT>
    inline void operator()(ITT& in, OTT& out)
    {
      // to be C+P
    }

    inline void probe()
    {
      // to be C+P
    }
  };

  // ///////////////////////////////////////////////////////////////////////////
  // MacroFarm structure - meta-function generating InstrFarm code fragment
  // ///////////////////////////////////////////////////////////////////////////
  template<class IT,class OT>
  struct MacroFarm
  {
    template<class IPID, class OPID>
    struct apply
    {
      typedef InstrFarm<IPID,OPID,IT,OT> type;
    };
  };
}
// /////////////////////////////////////////////////////////////////////////////
// End of namespace quaff
// /////////////////////////////////////////////////////////////////////////////

#endif
