#include <iostream>
#include <math.h>
#include "d2o_globals.h"

double N_theo(int cell,double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target);

void run_loader(int run);

void run_graph(int run,int short_target) //takes a run file and converts it to xmgrace input
{
ofstream graphfile;
graphfile.open ("graphs/run_graph_xmgrace_input.dat");

int user_choice;
float m = 0;
int u = 0;

run_loader(run);

cout << "You have chosen to graph run " << run; 
cout << "; did you want to graph the simulation or the experimental data?\n";
cout << "1.  Simulated data.\n";
cout << "2.  Experimental data.\n";
cout << "0.  Quit. \n";
cin >> user_choice;

if (user_choice == 1)
  {
  while(m < 88) //ignoring last ring
    {
    u = floor(m);
    graphfile << m << " " << n_sim[u] << endl;
    //cout << m << " " << n_sim[u] << endl; //comment out to silence output
    m = m + 0.01;
    }
  }
if (user_choice == 2)
  {
  while(m < 88) //ignoring last ring
    {
    u = floor(m);
    graphfile << m << " " << n[u] << endl;
    //cout << m << " " << n[u] << endl; //comment out to silence output
    m = m + 0.01;
    }
  }

cout << "Output sent to: graphs/run_graph_xmgrace_input.dat.\n";
graphfile.close();
return;
}

void equation_79_graph(double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target)
{
ofstream graphfile;
graphfile.open ("graphs/equation_79_sol_xmgrace_input.dat");


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

//graph output, choose histogram you want
float m = 0;
int u = 0;
while(m < 88) //ignoring last ring
  {
  u = floor(m);
  n_est[u] = N_theo(u,A,a1,a2,a3,a4,e2,e3,e4,c1,c2,d1,d2,short_target);
  graphfile << m << " " << n_est[u] << endl;
  //cout << m << " " << n_est[u] << endl; //comment out to silence output
  m = m + 0.01;
  }
graphfile.close();
return;
}

void equation_79_graph_error(int run,int background_cor,double normalize)
{
ofstream error_graphfile;
error_graphfile.open ("graphs/equation_79_w_errors_sol_xmgrace_input.dat");
ofstream error_sim_graphfile;
error_sim_graphfile.open ("graphs/equation_79_w_errors_sol_sim_xmgrace_input.dat");

//Note: all simulation data (i.e. a-l) are done with arm 1 up, any runs that do not have arm 1 up must be converted
//Note: simulation gain was 3.5keV/Ch so ADC cut of 500 is the same as a cut of 1750 keVee

//load run into n

run_loader(run);

//let's see what runs look like without the H2O background
if (background_cor == 1)
{
d2o_background_corrector(run);
}

if (normalize != 1)
{
cout << "Normalization enabled, normalizing... \n";
}

for(int ii = 0; ii < 80; ii++) //ignore last ring
  {
  if (n[ii] < 1) continue;
  error_graphfile << float(ii) + 0.5 << " " << n[ii]/normalize << " " << d_n[ii]/normalize << endl;
  if (n_sim[ii] < 1) continue;
  error_sim_graphfile << float(ii) + 0.5 << " " << n_sim[ii] << " " << pow(n_sim[ii],0.5) << endl;
  }

cout << "Experimental output sent to: graphs/equation_79_w_errors_sol_xmgrace_input.dat.\n";
cout << "Simulation output sent to: graphs/equation_79_w_errors_sol_sim_xmgrace_input.dat\n";
error_graphfile.close();
error_sim_graphfile.close();
return;
}
