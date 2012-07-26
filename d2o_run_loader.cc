//July 10, 2012
//Loads in runs based on run number specified

#include <iostream>
#include "d2o_globals.h"

void run_loader(int run)
{
int short_target;
switch (run)
  {
  case 142:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run142[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run142[ii];
      flux = n_t_run142;
      d_flux = d_n_t_run142;
      n_sim[ii] = run142_sim[ii];
      n_back_sub_sim[ii] = run142_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 143:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run143[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run143[ii];
      flux = n_t_run143;
      d_flux = d_n_t_run143;
      n_sim[ii] = run143_sim[ii];
      n_back_sub_sim[ii] = run143_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 149:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run149[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run149[ii];
      flux = n_t_run149;
      d_flux = d_n_t_run149;
      n_sim[ii] = run149_sim[ii];
      n_back_sub_sim[ii] = run149_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 150:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run150[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run150[ii];
      flux = n_t_run150;
      d_flux = d_n_t_run150;
      n_sim[ii] = run150_sim[ii];
      n_back_sub_sim[ii] = run150_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 152:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run152[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run152[ii];
      flux = n_t_run152;
      d_flux = d_n_t_run152; 
      n_sim[ii] = run152_sim[ii];
      n_back_sub_sim[ii] = run152_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 153:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run153[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run153[ii];
      flux = n_t_run153;
      d_flux = d_n_t_run153; 
      n_sim[ii] = run153_sim[ii];
      n_back_sub_sim[ii] = run153_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 154:
    tar_length = long_tar; //this is a long target run
    short_target = 0;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run154[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run154[ii];
      flux = n_t_run154;
      d_flux = d_n_t_run154;
      n_sim[ii] = run154_sim[ii];
      n_back_sub_sim[ii] = 0; 
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 155:
    tar_length = short_tar; //this is a short target run
    short_target = 1;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run155[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run155[ii];
      flux = n_t_run155;
      d_flux = d_n_t_run155;
      n_sim[ii] = run155_sim[ii];
      n_back_sub_sim[ii] = run155_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 157:
    tar_length = short_tar; //this is a short target run
    short_target = 1;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run157[ii]; //total experimental hits for detector ii
      d_n[ii] = d_run157[ii];
      flux = n_t_run157;
      d_flux = d_n_t_run157; 
      n_sim[ii] = run157_sim[ii];
      n_back_sub_sim[ii] = run157_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 158:
    tar_length = short_tar; //this is a short target run
    short_target = 1;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run158[ii]; //ttal experimental hits for detector ii
      d_n[ii] = d_run158[ii];
      flux = n_t_run158;
      d_flux = d_n_t_run158; 
      n_sim[ii] = run158_sim[ii];
      n_back_sub_sim[ii] = run158_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  case 159:
    tar_length = short_tar; //this is a short target run
    short_target = 1;
    for(int ii = 0;ii < 88;ii++)
      {
      n[ii] = run159[ii]; //ttal experimental hits for detector ii
      d_n[ii] = d_run159[ii];
      flux = n_t_run159;
      d_flux = d_n_t_run159; 
      n_sim[ii] = run159_sim[ii];
      n_back_sub_sim[ii] = run159_back_sub_sim[ii];
      }
      cout << "Loading run " << run << ".\n";
    break;
  default:
    cerr << "ERROR: run " << run << " not found.\n";
    return;
  }
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
    cout << "Run " << run << " is a short target run. \n";
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
    cout << "Run " << run << " is a long target run. \n";
  }
return;
}
