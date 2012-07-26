#ifndef OCT_2010_FLUX_DATA_H 
#define OCT_2010_FLUX_DATA_H 

#include "oct_2010_flux_data.cc"

double n_t_old(double cal_fact, double d_cal_fact,double veto_counts,double five_pad_counts, double bunches); //number of gammas at target - adapted from ratecorr.pl - agrees with ratecorr.pl to within error; error agrees to only first digit

double cal_count(double n_m, double bunches, double est_gammas, double true_efficiency, double veto_efficiency);

double n_t(double f_m, double d_f_m, double n_v,double n_b,double n_m, double c_b, double d_c_b); //number of gammas at target 

double abs(double x) //for some reason the math.h file isn't working
  {
  if(x >= 0) return x;
  else return -1*x;
  };

void target_flux_calculator();

#endif
