//June 29, 2012
//Glen
//contains all the flux info for the runs being used

#include <iostream>
#include <math.h>
#include "oct_2010_flux_data.h"
#include "d2o_globals.h"
using namespace std;

//Note: values are only in agreement to 5 significant digits
double n_t_old(double cal_fact, double d_cal_fact,double veto_counts,double five_pad_counts, double bunches); //number of gammas at target - adapted from ratecorr.pl - agrees with ratecorr.pl to within error; error agrees to only first digit //old algorithm

double cal_count(double n_m, double bunches, double est_gammas, double true_efficiency, double veto_efficiency);

double n_t(double f_m, double d_f_m, double n_v,double n_b,double n_m, double c_b, double d_c_b); //number of gammas at target //new algorithm

double abs(double x); //for some reason the math.h file isn't working

void target_flux_calculator();


void target_flux_calculator() //calculates n_t for all of the runs
  {
  double c_b = 1.069; //calibration factor from SPIR 146 (same for all runs)
  double d_c_b = 0.006;

  double cal_fact_run142 = 59.23; //calibration factor for run 142
  double d_cal_fact_run142 = 0.49; //uncertainty in above
  double five_pad_counts_run142 = 285170788; //5-paddle counts during live time for run 142
  double veto_counts_run142 = 242608846; //veto hits during live time for run 142
  double bunches_run142 = 9012853000.0; //number of bunches during live time for run 142
  n_t_run142 = n_t(cal_fact_run142, d_cal_fact_run142, veto_counts_run142 , bunches_run142, five_pad_counts_run142, c_b, d_c_b);
  d_n_t_run142 = d_est_gammas; //note: this MUST follow a call to n_t or it won't give the right number

  double cal_fact_run143 = 59.23; //f_m
  double d_cal_fact_run143 = 0.49; 
  double five_pad_counts_run143 = 219751733; //n_m
  double veto_counts_run143 = 186590686; //n_v 
  double bunches_run143 = 11704557000.0; //n_b
  n_t_run143 = n_t(cal_fact_run143, d_cal_fact_run143, veto_counts_run143 , bunches_run143, five_pad_counts_run143, c_b, d_c_b);
  d_n_t_run143 = d_est_gammas; 

  double cal_fact_run149 = 59.23; 
  double d_cal_fact_run149 = 0.49; 
  double five_pad_counts_run149 = 204178195; 
  double veto_counts_run149 = 175565068; 
  double bunches_run149 = 7247754000.0; 
  n_t_run149 = n_t(cal_fact_run149, d_cal_fact_run149, veto_counts_run149 , bunches_run149, five_pad_counts_run149, c_b, d_c_b);
  d_n_t_run149 = d_est_gammas; 

  double cal_fact_run150 = 59.23; 
  double d_cal_fact_run150 = 0.49; 
  double five_pad_counts_run150 = 195430435; 
  double veto_counts_run150 = 168551093; 
  double bunches_run150 = 7359691000.0; 
  n_t_run150 = n_t(cal_fact_run150, d_cal_fact_run150, veto_counts_run150 , bunches_run150, five_pad_counts_run150, c_b, d_c_b);
  d_n_t_run150 = d_est_gammas; 

  double cal_fact_run152 = 59.23; 
  double d_cal_fact_run152 = 0.49; 
  double five_pad_counts_run152 = 297402006; 
  double veto_counts_run152 = 255714483; 
  double bunches_run152 = 9494683000.0; 
  n_t_run152 = n_t(cal_fact_run152, d_cal_fact_run152, veto_counts_run152 , bunches_run152, five_pad_counts_run152, c_b, d_c_b);
  d_n_t_run152 = d_est_gammas; 

  double cal_fact_run153 = 59.23; 
  double d_cal_fact_run153 = 0.49; 
  double five_pad_counts_run153 = 113043037; 
  double veto_counts_run153 = 95986393; 
  double bunches_run153 = 8582590000.0; 
  n_t_run153 = n_t(cal_fact_run153, d_cal_fact_run153, veto_counts_run153 , bunches_run153, five_pad_counts_run153, c_b, d_c_b);
  d_n_t_run153 = d_est_gammas; 

  double cal_fact_run154 = 59.23; 
  double d_cal_fact_run154 = 0.49; 
  double five_pad_counts_run154 = 238992725; 
  double veto_counts_run154 = 213531707; 
  double bunches_run154 = 9241607000.0; 
  n_t_run154 = n_t(cal_fact_run154, d_cal_fact_run154, veto_counts_run154 , bunches_run154, five_pad_counts_run154, c_b, d_c_b);
  d_n_t_run154 = d_est_gammas; 

  double cal_fact_run155 = 59.02; 
  double d_cal_fact_run155 = 0.57; 
  double five_pad_counts_run155 = 280903920; 
  double veto_counts_run155 = 252429750; 
  double bunches_run155 = 10524120000.0; 
  n_t_run155 = n_t(cal_fact_run155, d_cal_fact_run155, veto_counts_run155 , bunches_run155, five_pad_counts_run155, c_b, d_c_b);
  d_n_t_run155 = d_est_gammas; 

  double cal_fact_run157 = 59.02; 
  double d_cal_fact_run157 = 0.57; 
  double five_pad_counts_run157 = 299747392; 
  double veto_counts_run157 = 274816631; 
  double bunches_run157 = 10992189000.0; 
  n_t_run157 = n_t(cal_fact_run157, d_cal_fact_run157, veto_counts_run157 , bunches_run157, five_pad_counts_run157, c_b, d_c_b);
  d_n_t_run157 = d_est_gammas; 

  double cal_fact_run158 = 59.02; 
  double d_cal_fact_run158 = 0.57; 
  double five_pad_counts_run158 = 282510134; 
  double veto_counts_run158 = 261645003; 
  double bunches_run158 = 10710054000.0; 
  n_t_run158 = n_t(cal_fact_run158, d_cal_fact_run158, veto_counts_run158 , bunches_run158, five_pad_counts_run158, c_b, d_c_b);
  d_n_t_run158 = d_est_gammas; 

  double cal_fact_run159 = 59.02; 
  double d_cal_fact_run159 = 0.57; 
  double five_pad_counts_run159 = 153633539; 
  double veto_counts_run159 = 138353901; 
  double bunches_run159 = 5932928000.0; 
  n_t_run159 = n_t(cal_fact_run159, d_cal_fact_run159, veto_counts_run159 , bunches_run159, five_pad_counts_run159, c_b, d_c_b);
  d_n_t_run159 = d_est_gammas; 

 
  return;
  }

double n_t_old(double cal_fact, double d_cal_fact,double veto_counts,double five_pad_counts, double bunches)
{
double true_efficiency = 1./cal_fact;
double err_true_efficiency = true_efficiency * (d_cal_fact/cal_fact);

// first guess
double est_gammas = five_pad_counts / true_efficiency;
est_gammas = -bunches / true_efficiency * log(1.0 - five_pad_counts/bunches);
//est_gammas = bunches/true_efficiency*log((bunches - veto_counts)/(bunches - veto_counts - five_pad_counts))/1.069;
//cout << "est_gammas = " << est_gammas << endl; //debug

double step_size = 0.05 * est_gammas;
double dir = +1.0;

double veto_efficiency = veto_counts / est_gammas;
double diff1 = five_pad_counts - cal_count(five_pad_counts, bunches, est_gammas, true_efficiency, veto_efficiency);
est_gammas += step_size * dir;
double diff2 = five_pad_counts - cal_count(five_pad_counts, bunches, est_gammas, true_efficiency, veto_efficiency);

while(abs(diff2)/five_pad_counts > 0.0001)
	{
        //cout << "est_gammas = " << est_gammas << endl; //debug
	if(diff1*diff2 < 0.)
		{
		// sign changed
		// so go the other direction in smaller steps
		step_size /= 3.;
		dir = -dir;
		}
	else
		{
		if(abs(diff2) > abs(diff1) )
			{
			//wrong direction
			dir = -dir;
			}
		}
	est_gammas += step_size * dir;
        diff1 = diff2;
	veto_efficiency = veto_counts / est_gammas;
	diff2 = five_pad_counts - cal_count(five_pad_counts, bunches, est_gammas, true_efficiency, veto_efficiency);
	}

// estimate the error in number of gammas
double dummy1 = 1./true_efficiency;
double dummy2 = five_pad_counts/(true_efficiency*true_efficiency);
double dummy3 = (1.-true_efficiency)/4./(true_efficiency*true_efficiency) * (five_pad_counts*five_pad_counts) / bunches;
double err_est_gammas = pow(
	(dummy1)*(dummy1) *five_pad_counts
	+ (dummy2*err_true_efficiency)*(dummy2*err_true_efficiency)
	,0.5);
double err_veto_efficiency = veto_efficiency *
	sqrt( (err_est_gammas / est_gammas)*(err_est_gammas / est_gammas) + 1./veto_counts);

err_est_gammas = pow(
	(dummy1)*(dummy1) *five_pad_counts
	+ (dummy2*err_true_efficiency)*(dummy2*err_true_efficiency)
	+ (dummy3*err_veto_efficiency)*(dummy3*err_veto_efficiency)
        ,0.5
	);
d_est_gammas = err_est_gammas;
return est_gammas;
}

double cal_count(double five_pad_counts, double bunches, double est_gammas, double true_efficiency, double veto_efficiency)
	{
	five_pad_counts = bunches * exp(-est_gammas * (1. - true_efficiency) * veto_efficiency / bunches)
		* (1.0 - exp(-est_gammas * true_efficiency / bunches) );
	return five_pad_counts;
	}



double n_t(double f_m, double d_f_m, double n_v,double n_b,double n_m, double c_b, double d_c_b) //number of gammas at target 
  {
  double n_t;
  double n_gamma;
  n_gamma = f_m*n_b*log((n_b - n_v)/(n_b - n_v - n_m)); //equation (15) in SPIR-146
  n_t = n_gamma/c_b; //equation (18) in SPIR-146
  //now calculate uncertainty
  d_est_gammas = pow(pow((n_gamma/(c_b*f_m))*d_f_m,2) + pow((f_m*n_b/((n_b-n_v-n_m)*c_b))*pow(n_m,0.5),2) + pow((f_m*n_b*n_m/((n_b - n_v)*(n_b-n_v-n_m)*c_b))*pow(n_v,0.5),2) + pow(n_gamma/(c_b*c_b)*d_c_b,2),0.5);
  return n_t;
  }
