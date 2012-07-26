//Glen, June 27 2012
//function designed to calculate absolute cross section
//based on Ward's thesis, page 116-117

#include <iostream>
#include <math.h>
#include "oct_2010_hit_data.h"
#include "oct_2010_flux_data.h"
#include "d2o_run_loader.h"
#include "d2o_globals.h"
#include "d2o_background_corrector.h"

void total_cross_section(int run, int background, double n_sim_events)
{

double xsec = 0; //total_cross_section
double xsec_sq = 0; //sum of the square of the cross sections
double d_xsec = 0; //standard deviation
const double a_density = .05516; //NIST webbook (in mols/cm^3) //*note*: 2 D in D2O
const double d_a_density = .00007; 

double hits = 0; //total number of detector hits in run
double d_hits = 0;
double hits_sim = 0; //total number of detector hits in simulation
double d_hits_sim = 0;

int short_target = 0;
int cells_used = 0;

int user_choice;

if(run < 155) 
  {
  short_target = 0;
  cout << "Run " << run << " is a long target run\n";
  }
else 
  {
  short_target = 1; 
  cout << "Run " << run << " is a short target run\n";
  }

run_loader(run);

//background correct run
  if (background == 1)
    {
    d2o_background_corrector(run);
    }


for(int ii = 0;ii < 80;ii++)
  {
  if(n[ii] < 1 || n_sim[ii] < 1) 
    {
    //cout << "Cell " << ii + 1 << " is empty, skipping to next cell...\n";
    continue;
    }
  //xsec = xsec + n_sim_events*n[ii]/(n_sim[ii]*flux*a_density*tar_length);
  //xsec_sq = xsec_sq + pow((n_sim_events*n[ii]/(n_sim[ii]*flux*a_density*tar_length)),2);
  if (background == 1)
    {
    hits_sim = hits_sim + n_back_sub_sim[ii];
    d_hits_sim = d_hits_sim + pow(n_back_sub_sim[ii],0.5);
    //cout << "xsec for cell " << ii + 1 << " = " << n_sim_events*n[ii]/(n_back_sub_sim[ii]*flux*a_density*tar_length) << endl; //debug
    }
  else if (background == 0)
    {
    hits_sim = hits_sim + n_sim[ii];
    d_hits_sim = d_hits_sim + pow(n_sim[ii],0.5);
    //cout << "xsec for cell " << ii + 1 << " = " << n_sim_events*n[ii]/(n_sim[ii]*flux*a_density*tar_length) << endl; //debug
    }
  else
    {
    cerr << "ERROR: invalid entry for background.\n";
    return;
    }
  hits = hits + n[ii];
  d_hits = d_hits + d_n[ii];
  cells_used++;
  }
  //xsec = xsec/cells_used;
  //xsec_sq = xsec_sq/(cells_used);
  //thin target approximation:
  d_xsec = pow(pow(d_hits*n_sim_events/(hits_sim*flux*a_density*tar_length),2) +
               pow(d_flux*n_sim_events*hits/(hits_sim*flux*flux*a_density*tar_length),2) +
               pow(d_hits_sim*n_sim_events*hits/(hits_sim*hits_sim*flux*a_density*tar_length),2) +
               pow(d_a_density*n_sim_events*hits/(hits_sim*flux*a_density*a_density*tar_length),2) +
               pow(d_tar_length*n_sim_events*hits/(hits_sim*flux*a_density*tar_length*tar_length),2)
               ,0.5);


  //special block for testing exp uncertainties
  cout << "Number of neutrons detected:" << hits << "; contribution to cross-section uncertainty: " << d_hits*n_sim_events/(hits_sim*flux*a_density*tar_length) << endl;
  cout << "Gamma flux: " << flux << "; contribution to cross-section uncertainty: " << d_flux*n_sim_events*hits/(hits_sim*flux*flux*a_density*tar_length) << endl;
  cout << "Number of neutrons detected in simulation: " << hits_sim << " +/- " << d_hits_sim*n_sim_events*hits/(hits_sim*hits_sim*flux*a_density*tar_length) << endl;
  cout << "Atomic density: " << a_density << "; contribution to cross-section uncertainty:  " << d_a_density*n_sim_events*hits/(hits_sim*flux*a_density*a_density*tar_length) << endl;
  cout << "Target length: " << tar_length << "; contribution to cross-section uncertainty:  " << d_tar_length*n_sim_events*hits/(hits_sim*flux*a_density*tar_length*tar_length) << endl;
  cout << "Also; n_sim_events/hits_sim = " << n_sim_events/hits_sim << endl;
  cout << "The number of gammas at the target was calculated to be: " << flux << " +/- " << d_flux << endl;

  xsec = n_sim_events*hits/(hits_sim*flux*a_density*tar_length); 

  
 
  cout << "The total cross-section is: " << xsec << " +/- " << d_xsec << " cm^2/mol \n";
  cout << "Used " << cells_used << " cells for analysis.\n";
}

