//
//  File = ms_error_T.h
//

#ifndef _MS_ERROR_T_H_
#define _MS_ERROR_T_H_

#include "signal_T.h"
//#include "control_T.h"
#include "psmodel.h"

template <class T>
class MeanSquareError : public PracSimModel
{
public:

  MeanSquareError< T >( char* instance_name,
                    PracSimModel* outer_model,
                    Signal<T>* in_signal,
                    Signal<T>* ref_signal);

  ~MeanSquareError<T>(void);
  void Initialize(void);
  int Execute(void);

private:
  //---------------------------------------------
  //  user-specified static parameters

   int Interp_Rate;

  //--------------------------------------------
  //  state variables and derived parameters

  //int Block_Size;
  //double Samp_Intvl;

  //int Max_Buffer_Len;  // numb of locs needed for Max_Delay
  //int Active_Buffer_Len;  // numb of locs needed for Active_Delay

  //T *Start_Of_Buffer;
  //T *End_Of_Buffer;
  //T *Read_Ptr;
  //T *Write_Ptr;
  double Cumul_Ms_Error;
  double Cumul_Ref_Pwr;

  //--------------------------
  //  Signals

  Signal<T> *In_Sig;
  Signal<T> *Ref_Sig;  

};

#endif
