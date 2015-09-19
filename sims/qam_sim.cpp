//
//  File = qam_sim.cpp
//

#define SIM_NAME "QamSim\0"
#define SIM_TITLE "Complex Baseband Simulation for QAM\0"

#include "global_stuff.h" 

#include "m_psk_theory.h"
#include "gausrand.h"
#include "symbgen.h"
#include "symb_remap.h"
#include "add_gaus_noise.h"
//#include "cmpxagn.h"
//#include "mpskidealmod.h"
#include "qam_symbtowave.h"
#include "quadmod.h"
#include "spec_analyzer.h"
#include "qamoptimdem.h"
//#include "m_pskharddem.h"
#include "ser_ctr.h"
#include "siganchr.h"

//=========================================================

int main()
{
#include "sim_preamble.cpp"

  //=========================================================================
  //  Misc special processing

  //-----------------------------------------------------
  // create plot file of theoretical PSD for QPSK signal

//  M_PskPsd(  0.0,  // carrier_freq
//            1.0,  // symb_energy,
//            1.0,  // symb_intvl,
//            -4.0, // beg_freq,
//            4.0,  // end_freq,
//            801,  // num_pts,
//            true, // plot_in_db,
//            "msk_psd_theor.txt\0"); //out_filename

  //-----------------------------------------------------
  // create plot file of BER for ideal QPSK

//  M_PskBer(  -10.0,  // beg_ebno,
//            18.0, // end_ebno,
//            401,  // num_pts,
//            "theor_msk_ber.txt\0");  // out_filename
  //=========================================================================
  //  Allocate signals

  BYTE_SIGNAL(symb_vals);
  BYTE_SIGNAL(mapped_symb_vals);
  FLOAT_SIGNAL(i_baseband_wave);
  FLOAT_SIGNAL(q_baseband_wave);
  COMPLEX_SIGNAL(modulated_signal);
  COMPLEX_SIGNAL(noisy_sig);
  BIT_SIGNAL(symb_clock);
  COMPLEX_SIGNAL(cmpx_integ_sig);
  FLOAT_SIGNAL(power_meas_sig);
  FLOAT_SIGNAL(mag_signal);
  FLOAT_SIGNAL(phase_signal);
  BYTE_SIGNAL(symb_decis);
  BYTE_SIGNAL(symb_err_seq);

  //============================================================
  //  Construct, initialize and connect models

  SymbGener* symb_gen = new SymbGener( "symb_gen\0",
                                      CommSystem,
                                      symb_vals );

//  SymbRemapper* symb_mapper = new SymbRemapper( "symb_mapper\0",
//                                                CommSystem,
//                                                symb_vals,
//                                                mapped_symb_vals);

  QamSymbsToQuadWaves* qam_mod = new QamSymbsToQuadWaves( 
                                                "qam_mod\0",
                                                CommSystem,
                                                symb_vals,
                                                i_baseband_wave,
                                                q_baseband_wave,
                                                symb_clock);

  QuadratureModulator* quad_mod = new QuadratureModulator( "quad_mod\0",
                                                        CommSystem,
                                                        i_baseband_wave,
                                                        q_baseband_wave,
                                                        modulated_signal,
                                                        mag_signal,
                                                        phase_signal);

  AdditiveGaussianNoise<std::complex<float> >* agn_source = 
                  new AdditiveGaussianNoise<std::complex<float> >( 
                                                "agn_source\0",
                                                CommSystem,
                                                modulated_signal,
                                                noisy_sig,
                                                power_meas_sig);

  SpectrumAnalyzer<std::complex<float> >* modulator_spec_an = 
                  new SpectrumAnalyzer<std::complex<float> >( 
                                                  "modulator_spec_an\0",
                                                  CommSystem,
                                                  modulated_signal );

  QamOptimalDemod* qam_demod = new QamOptimalDemod( "qam_demod\0",
                                                    CommSystem,
                                                    noisy_sig,
                                                    symb_clock,
                                                    symb_decis);
  
  SignalAnchor* temp_anchor_1 = new SignalAnchor( "temp_anchor_1\0",
                                                CommSystem,
                                                modulated_signal,
                                                0.0625, //samp_intvl
                                                4096 ); //block_size

  SerCounter* ser_ctr = new SerCounter( "ser_ctr\0",
                                        CommSystem,
                                        symb_vals,
                                        symb_decis,
                                        symb_err_seq );

  //=============================================================
  #include "sim_postamble.cpp"
  return 0;
}  
