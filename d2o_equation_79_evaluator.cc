//This program attempts to solve equation 7.9 in Ward's Thesis (Wurtz 2010)
//Works by altering one parameter at a time and finding best fit, then repeats over all of them to refine the answer
//Chi squared test is based on Pearson's cumulative test (asymptotically approaches chi squared)
//Number of free parameters is number of cells used minus number of parameters (12)
//General format of uncertainties is that they include the number of normal hits and therefore must have the unaltered run subtracted, unless they have a d in front that signifies they are an absolute error

//PROBLEM: FIX THE OUTPUT FILES, they keep overwriting and so they're always empty!
	//Temp. solution: only call the runs one at a time

//a = 1/A = x1
//b = a1 = x2
//c = a2 = x3
//d = a3 = x4
//e = a4 = x5
//f = e2 = x6
//g = e3 = x7
//h = e4 = x8

//using graphfile, input has been verified for the following histograms: a, b, c, d, e, f, h, i, j, k, l, run149

//So, 'a' represents 0, 'b' represents 1, 'c' represents 2 and so forth.

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "oct_2010_hit_data.h"
#include "d2o_run_loader.h"
#include "d2o_background_corrector.h"
#include "d2o_globals.h"
#include "d2o_graph.h"

using namespace std;

double chi_sq(double obs[88],double theo[88],double d_theo[88]); //for use with 88 cell histograms

//note: when calling this function I use the uncertainty in the observed NOT the uncertainty in the theoretical

double red_chi_sq(double obs[88],double theo[88],double d_theo[88],int free_param); //for use with 88 cell histograms

double N_theo(int cell,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target);

double param_error(int param_pick,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2, int short_target);

void param_picker(int param_pick, int short_target); //the workhorse for this file

void param_test(int param_to_test, int short_target);

void equation_79_evaluator(int run,int background_cor);

void equation_79_evaluator(int run,int background_cor)
{

//output files  
ofstream logfile;
logfile.open ("output_files/equation_79_evaluator_log.txt");

double step = 0.0001; //step size
long picks = 15; //number of times it rechecks solution


logfile << "Step size: " << step << "; number of rechecks: " << picks << endl;


int num_combo = 10; //number of combinations wanted for output

//switches: (1 is on, 0 is off)
int check = 0;
int neg_correct = 0;
int short_target;

//automatically set short_target switch
if(run < 155 && run > 0) short_target = 0;
else if (run == -1) short_target = 1;
else short_target = 1; 

// a_j = N00 for jth detector
// b_j = N01 for jth detector
// c_j = N02 for jth detector
// d_j = N03 for jth detector
// e_j = N04 for jth detector
// f_j = N22 for jth detector
// g_j = N23 for jth detector
// h_j = N24 for jth detector
// i_j = N11 for jth detector
// j_j = N12 for jth detector
// k_j = N11' for jth detector
// l_j = N12' for jth detector

//runxxx[j] = (j + 1)th detector of run xxx

//Note: all simulation data (i.e. a-l) are done with arm 1 up, any runs that do not have arm 1 up must be converted
//Note: simulation gain was 3.5keV/Ch so ADC cut of 500 is the same as a cut of 1750 keVee

//load run into n

run_loader(run);

double d_n_est[88];


//let's see what runs look like without the H2O background
if (background_cor == 1)
{
d2o_background_corrector(run);
}
else cout << "Background correction disabled.\n";

//fitting algorithm
//randomly picks a set of parameters from their domains, compares the chi squared value and then reduces the domain near the best solution
for(long ii = 1;ii <= picks;ii++)
{
  for(int ii = 0;ii < 12;ii++) 
  {
  param_picker(ii,short_target);
  //update log file
  }
  logfile << "Best chi squared: " << best_chi_sq << "; best reduced chi squared: " << best_red_chi_sq << endl;
  logfile << "A = " << best_A << "\na1 = " << best_a1 << "\na2 = " << best_a2 << "\na3 = " << best_a3 << "\na4 = " << best_a4 << "\ne2 = " << best_e2 << "\ne3 = " << best_e3 << "\ne4 = " << best_e4 << "\nc1 = " << best_c1 << "\nc2 = " << best_c2 << "\nd1 = " << best_d1 << "\nd2 = " << best_d2 << endl;
}

cout << "Finished determining parameters, now determining errors...\n";

double A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2;
A = best_A;
a1 = best_a1;
a2 = best_a2;
a3 = best_a3;
a4 = best_a4;
e2 = best_e2;
e3 = best_e3;
e4 = best_e4;
c1 = best_c1;
c2 = best_c2;
d1 = best_d1;
d2 = best_d2;
param[0] = best_A;
param[1] = best_a1;
param[2] = best_a2;
param[3] = best_a3;
param[4] = best_a4;
param[5] = best_e2;
param[6] = best_e3;
param[7] = best_e4;
param[8] = best_c1;
param[9] = best_c2;
param[10] = best_d1;
param[11] = best_d2;

//compute errors in parameters
for(int ii = 0;ii < 12;ii++) 
  {
  d_param[ii] = param_error(ii,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
  }

logfile << "Run: " << run << endl;
logfile << "Threshold = " << threshold << endl;
logfile << "Best chi squared: " << best_chi_sq << "; best reduced chi squared: " << best_red_chi_sq << endl; 
logfile << "A = " << param[0] << " +/- " << d_param[0] << ";\n";
logfile << "a1 = " << param[1] << " +/- " << d_param[1] << ";\n";
logfile << "a2 = " << param[2] << " +/- " << d_param[2] << ";\n";
logfile << "a3 = " << param[3] << " +/- " << d_param[3] << ";\n";
logfile << "a4 = " << param[4] << " +/- " << d_param[4] << ";\n";
logfile << "e2 = " << param[5] << " +/- " << d_param[5] << ";\n";
logfile << "e3 = " << param[6] << " +/- " << d_param[6] << ";\n";
logfile << "e4 = " << param[7] << " +/- " << d_param[7] << ";\n";
logfile << "c1 = " << param[8] << " +/- " << d_param[8] << ";\n";
logfile << "c2 = " << param[9] << " +/- " << d_param[9] << ";\n";
logfile << "d1 = " << param[10] << " +/- " << d_param[10] << ";\n";
logfile << "d2 = " << param[11] << " +/- " << d_param[11] << ";\n";

cout << "Run: " << run << endl;
cout << "Threshold = " << threshold << endl;
cout << "Best chi squared: " << best_chi_sq << "; best reduced chi squared: " << best_red_chi_sq << endl; 
cout << "A = " << param[0] << " +/- " << d_param[0] << ";\n";
cout << "a1 = " << param[1] << " +/- " << d_param[1] << ";\n";
cout << "a2 = " << param[2] << " +/- " << d_param[2] << ";\n";
cout << "a3 = " << param[3] << " +/- " << d_param[3] << ";\n";
cout << "a4 = " << param[4] << " +/- " << d_param[4] << ";\n";
cout << "e2 = " << param[5] << " +/- " << d_param[5] << ";\n";
cout << "e3 = " << param[6] << " +/- " << d_param[6] << ";\n";
cout << "e4 = " << param[7] << " +/- " << d_param[7] << ";\n";
cout << "c1 = " << param[8] << " +/- " << d_param[8] << ";\n";
cout << "c2 = " << param[9] << " +/- " << d_param[9] << ";\n";
cout << "d1 = " << param[10] << " +/- " << d_param[10] << ";\n";
cout << "d2 = " << param[11] << " +/- " << d_param[11] << ";\n";

cout << "Excel input (A a1 a2 a3 ... d1 d2 d_A d_a1 ... d_d1 d_d2: \n";
for(int ii = 0;ii < 12;ii++)
  {
  cout << param[ii] << " ";
  }
for(int ii = 0;ii < 12;ii++)
  {
  cout << d_param[ii] << " ";
  }
cout << "\n";

//verify errors

logfile << "Verify the error in the parameters: " << endl;
int cells_used = 0;
double n_est[88];

//calculate predicted spectrum and reduced chi squared
for(int ii = 0;ii < 88;ii++) 
  {
  if(n[ii] < threshold) continue; //ignore empty cells
  if(ii > 79) //ignore last ring
    {
    n_est[ii] = -1; 
    continue;
    }
  else
    {
    n_est[ii] = N_theo(ii,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
    }
  }
cells_used = 0;
logfile << "chi_sq(a1) = " << chi_sq(n,n_est,d_n) << endl;
cout << "chi_sq(a1) = " << chi_sq(n,n_est,d_n) << endl;
for(int ii = 0;ii < 88;ii++) 
  {
  if(n[ii] < threshold) continue; //ignore empty cells
  if(ii > 79) //ignore last ring
    {
    n_est[ii] = -1; 
    continue;
    }
  else
    {
    n_est[ii] = N_theo(ii,A,a1 + d_param[1],a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
    }
  }
logfile << "chi_sq(a1+da1) = " << chi_sq(n,n_est,d_n) << endl;
cout << "chi_sq(a1+da1) = " << chi_sq(n,n_est,d_n) << endl;
cells_used = 0;

equation_79_graph(param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7],param[8],param[9],param[10],param[11],0);
equation_79_graph_error(run,background_cor,1);


//****stopped updating here****
//check solution
if(check == 1)
{
float ave_error = 0;
  for(int ii = 0;ii < 80;ii++) 
  {
  if(n[ii] > 0)
  {
  n_est[ii] = N_theo(ii,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
  logfile << "Estimate for hits on detector " << ii + 1 << ": " << n_est[ii] << "; actual: " << n[ii] << "; Percent error: " << abs(1.0 - double(n_est[ii])/double(n[ii]))*100.0 << "%\n";
  ave_error = ave_error + abs(((1.0 - double(n_est[ii])/double(n[ii]))/88.0));
  }
  }
logfile << "Average percent error: " << ave_error*100 << "%\n";
}

//for(int dummy = 0; dummy < 88; dummy++)
//{
//cout << float(dummy) + .5 << " " << n[dummy] << " " << long_st_dev[dummy] << endl;
//}

//reset globals
best_A = 0;
best_a1 = 0;
best_a2 = 0;
best_a3 = 0;
best_a4 = 0;
best_e2 = 0;
best_e3 = 0;
best_e4 = 0;
best_c1 = 0;
best_c2 = 0;
best_d1 = 0;
best_d2 = 0;

best_chi_sq = 1e50;
best_red_chi_sq = 1e50; //give ridiculously high initial values


//close files
logfile.close();
}

double chi_sq(double obs[88],double theo[88],double d_obs[88]) //for use with 88 cell histograms
{
//note: when calling this function I use the uncertainty in the observed NOT the uncertainty in the theoretical
double chi_sq = 0;
double d_theo[88];
for(int ii = 0;ii < 88;ii++)
  {
  if(obs[ii] < threshold) continue;
  if(theo[ii] == -1) continue;
  d_theo[ii] = pow(theo[ii],0.5); //uncertainty is purely statistical
  chi_sq = chi_sq + (obs[ii] - theo[ii])*(obs[ii] - theo[ii])/((d_theo[ii]*d_theo[ii] + d_obs[ii]*d_obs[ii])); 
  }
return chi_sq;
}

double red_chi_sq(double obs[88],double theo[88],double d_obs[88],int free_param) //for use with 88 cell histograms
{
double red_chi_sq = 0;
double d_theo[88];
for(int ii = 0;ii < 88;ii++)
{
  if(obs[ii] < threshold) continue;
  if(theo[ii] == -1) continue;
  d_theo[ii] = pow(theo[ii],0.5); //uncertainty is purely statistical
  red_chi_sq = red_chi_sq + (obs[ii] - theo[ii])*(obs[ii] - theo[ii])/((d_theo[ii]*d_theo[ii] + d_obs[ii]*d_obs[ii])*double(free_param)); 
  //cerr << "double(free_param)/2.0 = " << double(free_param)/2.0 << "; free_param = " << free_param << endl;
}
return red_chi_sq;
}

double N_theo(int cell,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target)
{
double N_theo;
//load in simulated data
if (short_target == 1)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_short[ii];
    b[ii] = b_short[ii];
    c[ii] = c_short[ii];
    d[ii] = d_short[ii];
    e[ii] = e_short[ii];
    f[ii] = f_short[ii];
    g[ii] = g_short[ii];
    h[ii] = h_short[ii];
    i[ii] = i_short[ii];
    j[ii] = j_short[ii];
    k[ii] = k_short[ii];
    l[ii] = l_short[ii];    
    }
  }
else
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_long[ii];
    b[ii] = b_long[ii];
    c[ii] = c_long[ii];
    d[ii] = d_long[ii];
    e[ii] = e_long[ii];
    f[ii] = f_long[ii];
    g[ii] = g_long[ii];
    h[ii] = h_long[ii];
    i[ii] = i_long[ii];
    j[ii] = j_long[ii];
    k[ii] = k_long[ii];
    l[ii] = l_long[ii];    
    }
  }

N_theo = A*((1 - a1 - a2 - a3 - a4 - 3*e2 - 6*e3 - 10*e4 - c1 - 1.5*c2 - d1 - 1.5*d2)*a[cell] + a1*b[cell] + a2*c[cell] + a3*d[cell] + a4*e[cell] + 3*e2*f[cell] + 6*e3*g[cell] + 10*e4*h[cell] + c1*i[cell] + 1.5*c2*j[cell] + d1*k[cell] + 1.5*d2*l[cell]);
return N_theo;
}

void param_picker(int param_pick,int short_target)
{
//cout << "Param_picker has been triggered \n"; //debug line

int cells_used = 0;
double chi_sq_test = 0;
double red_chi_sq_test = 0;
double A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2;
A = best_A;
a1 = best_a1;
a2 = best_a2;
a3 = best_a3;
a4 = best_a4;
e2 = best_e2;
e3 = best_e3;
e4 = best_e4;
c1 = best_c1;
c2 = best_c2;
d1 = best_d1;
d2 = best_d2;
//these pointers will change the memory of the parameter being adjusted
double * param;
double * max_param;
double * min_param;
double * best_param;
double step = 0.0001; //step size
long picks = 15; //number of times it rechecks solution

//load in simulated data
if (short_target == 1)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_short[ii];
    b[ii] = b_short[ii];
    c[ii] = c_short[ii];
    d[ii] = d_short[ii];
    e[ii] = e_short[ii];
    f[ii] = f_short[ii];
    g[ii] = g_short[ii];
    h[ii] = h_short[ii];
    i[ii] = i_short[ii];
    j[ii] = j_short[ii];
    k[ii] = k_short[ii];
    l[ii] = l_short[ii];    
    }
  }
else
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_long[ii];
    b[ii] = b_long[ii];
    c[ii] = c_long[ii];
    d[ii] = d_long[ii];
    e[ii] = e_long[ii];
    f[ii] = f_long[ii];
    g[ii] = g_long[ii];
    h[ii] = h_long[ii];
    i[ii] = i_long[ii];
    j[ii] = j_long[ii];
    k[ii] = k_long[ii];
    l[ii] = l_long[ii];    
    }
  }

//load in parameter to alter
if (param_pick == 0)
  {
  param = &A;
  best_param = &best_A;
  max_param = &max_A;
  min_param = &min_A;
  }
else if (param_pick == 1)
  {
  param = &a1;
  best_param = &best_a1;
  max_param = &max_a1;
  min_param = &min_a1;
  }
else if (param_pick == 2)
  {
  param = &a2;
  best_param = &best_a2;
  max_param = &max_a2;
  min_param = &min_a2;
  }
else if (param_pick == 3)
  {
  param = &a3;
  best_param = &best_a3;
  max_param = &max_a3;
  min_param = &min_a3;
  }
else if (param_pick == 4)
  {
  param = &a4;
  best_param = &best_a4;
  max_param = &max_a4;
  min_param = &min_a4;
  }
else if (param_pick == 5)
  {
  param = &e2;
  best_param = &best_e2;
  max_param = &max_e2;
  min_param = &min_e2;
  }
else if (param_pick == 6)
  {
  param = &e3;
  best_param = &best_e3;
  max_param = &max_e3;
  min_param = &min_e3;
  }
else if (param_pick == 7)
  {
  param = &e4;
  best_param = &best_e4;
  max_param = &max_e4;
  min_param = &min_e4;
  }
else if (param_pick == 8)
  {
  param = &c1;
  best_param = &best_c1;
  max_param = &max_c1;
  min_param = &min_c1;
  }
else if (param_pick == 9)
  {
  param = &c2;
  best_param = &best_c2;
  max_param = &max_c2;
  min_param = &min_c2;
  }
else if (param_pick == 10)
  {
  param = &d1;
  best_param = &best_d1;
  max_param = &max_d1;
  min_param = &min_d1;
  }
else if (param_pick == 11)
  {
  param = &d2;
  best_param = &best_d2;
  max_param = &max_d2;
  min_param = &min_d2;
  }
else
  {
  cout << "ERROR: param out of range\n";
  return;
  }

*param = *min_param;
while(*param <= *max_param)
{
cells_used = 0;

  //calculate predicted spectrum and reduced chi squared
  for(int ii = 0;ii < 88;ii++) 
    {
    if(n[ii] < threshold) continue; //ignore empty cells
    if(ii > 79) //ignore last ring
      {
      n_est[ii] = -1; 
      continue;
      } 
    else
      {
      n_est[ii] = N_theo(ii,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
      cells_used++;
      }
    }
    //cout << "Cells used: " << cells_used << endl; //debug line

    chi_sq_test = chi_sq(n,n_est,d_n);
    
    cout << ""; //****DO NOT DELETE THIS LINE: THE COMPILER NEEDS THIS LINE TO MAKE SENSE OF THE CODE***

    red_chi_sq_test = red_chi_sq(n,n_est,d_n,cells_used - 12);

    //cout << "Chi_sq = " << chi_sq(n,n_est,d_n) << endl; //debug line
    //cout << "Red_chi_sq = " << red_chi_sq(n,n_est,d_n,cells_used - 12) << endl; //debug line

  if (chi_sq_test < best_chi_sq)
    {
    *best_param = *param;
    best_chi_sq = chi_sq_test;
    best_red_chi_sq = red_chi_sq_test; //12 parameters
    //cout << "Storing new parameter: " << *best_param << endl; //debug line
    }

*param = *param + step;  
//cout << "param = " << *param << endl; //debug line
}
//cout << "Best chi squared was: " << best_chi_sq << "; best reducing chi squared was: " << best_red_chi_sq << endl;
return;
}

//returns the uncertainty in the specified parameter
double param_error(int param_pick,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target)
{
//cout << "Param_picker has been triggered \n"; //debug line

//these pointers will change the memory of the parameter being adjusted
double * param;
double * max_param;
double * min_param;
double * best_param;
double error = 0;
double step = 0.0001; //step size
long picks = 15; //number of times it rechecks solution

//load in simulated data
if (short_target == 1)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_short[ii];
    b[ii] = b_short[ii];
    c[ii] = c_short[ii];
    d[ii] = d_short[ii];
    e[ii] = e_short[ii];
    f[ii] = f_short[ii];
    g[ii] = g_short[ii];
    h[ii] = h_short[ii];
    i[ii] = i_short[ii];
    j[ii] = j_short[ii];
    k[ii] = k_short[ii];
    l[ii] = l_short[ii];    
    }
  }
else
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_long[ii];
    b[ii] = b_long[ii];
    c[ii] = c_long[ii];
    d[ii] = d_long[ii];
    e[ii] = e_long[ii];
    f[ii] = f_long[ii];
    g[ii] = g_long[ii];
    h[ii] = h_long[ii];
    i[ii] = i_long[ii];
    j[ii] = j_long[ii];
    k[ii] = k_long[ii];
    l[ii] = l_long[ii];    
    }
  }

//load in parameter to alter
if (param_pick == 0)
  {
  param = &A;
  }
else if (param_pick == 1)
  {
  param = &a1;
  }
else if (param_pick == 2)
  {
  param = &a2;
  }
else if (param_pick == 3)
  {
  param = &a3;
  }
else if (param_pick == 4)
  {
  param = &a4;
  }
else if (param_pick == 5)
  {
  param = &e2;
  }
else if (param_pick == 6)
  {
  param = &e3;
  }
else if (param_pick == 7)
  {
  param = &e4;
  }
else if (param_pick == 8)
  {
  param = &c1;
  }
else if (param_pick == 9)
  {
  param = &c2;
  }
else if (param_pick == 10)
  {
  param = &d1;
  }
else if (param_pick == 11)
  {
  param = &d2;
  }
else
  {
  cout << "ERROR: param out of range\n";
  return 0;
  }

int cells_used;

for(int ii = 0;ii < 88;ii++) 
  {
  if(n[ii] < threshold) continue; //ignore empty cells
  if(ii > 79) //ignore last ring
    {
    n_est[ii] = -1; 
    continue;
    }
  else
    {
    n_est[ii] = N_theo(ii,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
    //cout << "n_est[" << ii << "] = " << n_est[ii] << endl; //debug line
    }
  }

double chi_sq_test = chi_sq(n,n_est,d_n);
double best_chi_sq_test = chi_sq(n,n_est,d_n);

while(chi_sq_test < best_chi_sq + 1 && chi_sq_test > best_chi_sq - 1)
  {
  cells_used = 0;

  if (chi_sq_test > 1000) //sanity check
    {
    cerr << "ERROR: sanity check failed (chi_sq > 1000), quitting param error routine.\n";
    return 0;
    }

  //calculate predicted spectrum and reduced chi squared
  for(int ii = 0;ii < 88;ii++) 
    {
    if(n[ii] < threshold) continue; //ignore empty cells
    if(ii > 79) //ignore last ring
      {
      n_est[ii] = -1; 
      continue;
      }
    else
      {
      n_est[ii] = N_theo(ii,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
      //cout << "n_est[" << ii << "] = " << n_est[ii] << endl; //debug line
      cells_used++;
      }
    }

    chi_sq_test = chi_sq(n,n_est,d_n);
    
    cout << ""; //****DO NOT DELETE THIS LINE: THE COMPILER NEEDS THIS LINE TO MAKE SENSE OF THE CODE***

  *param = *param + step/10.0;  
  error = error + step/10.0;  
  }
return error;
}

void param_test(int param_to_test, int short_target)
{
double step = 0.0001; //step size
long picks = 15; //number of times it rechecks solution
//load in simulated data
if (short_target == 1)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_short[ii];
    b[ii] = b_short[ii];
    c[ii] = c_short[ii];
    d[ii] = d_short[ii];
    e[ii] = e_short[ii];
    f[ii] = f_short[ii];
    g[ii] = g_short[ii];
    h[ii] = h_short[ii];
    i[ii] = i_short[ii];
    j[ii] = j_short[ii];
    k[ii] = k_short[ii];
    l[ii] = l_short[ii];    
    }
  }
else
  {
  for(int ii = 0;ii < 88;ii++)
    {
    a[ii] = a_long[ii];
    b[ii] = b_long[ii];
    c[ii] = c_long[ii];
    d[ii] = d_long[ii];
    e[ii] = e_long[ii];
    f[ii] = f_long[ii];
    g[ii] = g_long[ii];
    h[ii] = h_long[ii];
    i[ii] = i_long[ii];
    j[ii] = j_long[ii];
    k[ii] = k_long[ii];
    l[ii] = l_long[ii];    
    }
    cout << "Testing long target runs" << endl;
  }

//load in parameter to test
if (param_to_test == 0)
  {
  cout << "ERROR: A is not testable.\n";
  return;
  }
else if (param_to_test == 1)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = b[ii];
    d_n[ii] = pow(b[ii],0.5);
    }
  }
else if (param_to_test == 2)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = c[ii];
    d_n[ii] = pow(c[ii],0.5);
    }
  }
else if (param_to_test == 3)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = d[ii];
    d_n[ii] = pow(d[ii],0.5);
    }
  }
else if (param_to_test == 4)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = e[ii];
    d_n[ii] = pow(e[ii],0.5);
    }
  }
else if (param_to_test == 5)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = f[ii];
    d_n[ii] = pow(f[ii],0.5);
    }
  }
else if (param_to_test == 6)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = g[ii];
    d_n[ii] = pow(g[ii],0.5);
    }
  }
else if (param_to_test == 7)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = h[ii];
    d_n[ii] = pow(h[ii],0.5);
    }
  }
else if (param_to_test == 8)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = i[ii];
    d_n[ii] = pow(i[ii],0.5);
    }
  }
else if (param_to_test == 9)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = j[ii];
    d_n[ii] = pow(j[ii],0.5);
    }
  }
else if (param_to_test == 10)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = k[ii];
    d_n[ii] = pow(k[ii],0.5);
    }
  }
else if (param_to_test == 11)
  {
  for(int ii = 0;ii < 88;ii++)
    {
    n[ii] = l[ii];
    d_n[ii] = pow(l[ii],0.5);
    }
  }
else
  {
  cout << "ERROR: param out of range\n";
  return;
  }
for(long jj = 1;jj <= picks;jj++)
{
  for(int ii = 0;ii < 12;ii++) 
  {
  if(ii == param_to_test) continue;
  param_picker(ii,short_target);
  }
}
  cout << "For parameter " << param_to_test << endl;
  cout << "Best chi squared: " << best_chi_sq << "; best reduced chi squared: " << best_red_chi_sq << endl;
  cout << "A = " << best_A << "\na1 = " << best_a1 << "\na2 " << best_a2 << "\na3 " << best_a3 << "\na4 " << best_a4 << "\ne2 " << best_e2 << "\ne3 " << best_e3 << "\ne4 " << best_e4 << "\nc1 " << best_c1 << "\nc2 " << best_c2 << "\nd1 " << best_d1 << "\nd2 " << best_d2 << endl;

//reset globals
best_A = 0;
best_a1 = 0;
best_a2 = 0;
best_a3 = 0;
best_a4 = 0;
best_e2 = 0;
best_e3 = 0;
best_e4 = 0;
best_c1 = 0;
best_c2 = 0;
best_d1 = 0;
best_d2 = 0;

best_chi_sq = 1e50;
best_red_chi_sq = 1e50; //give ridiculously high initial values

return;
}
