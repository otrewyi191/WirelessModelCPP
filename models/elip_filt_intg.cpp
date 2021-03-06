//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//  File = elip_filt_intg.cpp
//
//  Elliptical Filter
//

//#include <math.h>
//#include "misdefs.h"
#include "parmfile.h"
#include "elip_filt_intg.h"
#include "elliptical_proto.h"
//#include "filter_types.h"
extern ParmFile *ParmInput;

#ifdef _DEBUG
  extern ofstream *DebugFile;
#endif

//======================================================
//  constructor

EllipticalFilterByInteg::EllipticalFilterByInteg( char *instance_name,
                                  PracSimModel *outer_model,
                                  Signal<float> *in_sig,
                                  Signal<float> *out_sig )
                  :AnalogFilterByInteg( instance_name,
                               outer_model,
                               in_sig,
                               out_sig )
{
  MODEL_NAME(EllipticalFilterByInteg);
  OPEN_PARM_BLOCK;
  // Most of the parameters needed to specify an elliptical filter
  // are common to all the classic types and are therefore
  // read by the AnalogFilter base class.
  //
  // separate values for 'Passband_Ripple' and 'Stopband_Ripple' are
  // specific to elliptical so they are read here in the derived class
  

  if( !Bypass_Enabled)
    {
    GET_DOUBLE_PARM(Passband_Ripple_In_Db);
    GET_DOUBLE_PARM(Stopband_Ripple_In_Db);
    GET_DOUBLE_PARM(Norm_Hz_Stop_Edge);
    Selec_Factor = Norm_Hz_Pass_Edge / Norm_Hz_Stop_Edge;
    // construct a elliptical prototype
    Lowpass_Proto_Filt = new EllipticalPrototype( Prototype_Order, 
                                                  Passband_Ripple_In_Db,
                                                  Stopband_Ripple_In_Db,
                                                  Selec_Factor);
    Lowpass_Proto_Filt->DumpBiquads(DebugFile); 
    Lowpass_Proto_Filt->GetDenomPoly(false);
    }
  return;
}
//template <class T>
//EllipticalFilterByInteg<T>::~EllipticalFilterByInteg(){};
//template EllipticalFilterByInteg<float>;
//template EllipticalFilterByInteg<std::complex<float> >;
