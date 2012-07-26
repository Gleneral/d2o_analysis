#ifndef D2O_EQUATION_79_EVALUATOR_H 
#define D2O_EQUATION_79_EVALUATOR_H 

#include "d2o_equation_79_evaluator.cc"

double chi_sq(double obs[88],double theo[88],double d_theo[88]); //for use with 88 cell histograms

//note: when calling this function I use the uncertainty in the observed NOT the uncertainty in the theoretical

double red_chi_sq(double obs[88],double theo[88],double d_theo[88],int free_param); //for use with 88 cell histograms

double N_theo(int cell,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target);

double param_error(int param_pick,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target);

void param_picker(int param_pick = -1,int short_target = 0); //the workhorse for this file

void param_test(int param_to_test = -1, int short_target = 0);

void equation_79_evaluator(int run = -1,int background_cor = 0);

void run_loader(int run);

#endif
