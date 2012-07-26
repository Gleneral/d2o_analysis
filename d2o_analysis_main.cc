//main file for d2o_analysis
//July 5, 2012 -Glen
//Output: **be careful: this program will overwrite old info**
//equation_79_w_errors_sol_xmgrace_input.dat - contains run info for xmgrace input
//equation_79_w_errors_sol_sim_xmgrace_input.dat - contains simulated run info for xmgrace input
//equation_79_evaluator_log.txt - keeps a log of important output regarding parameters
//equation_79_sol_xmgrace_input.dat - contains xmgrace input file for parameterization
//run_graph_xmgrace_input.dat - contains xmgrace input for a block chart


#include <iostream>
#include "d2o_total_cross_section.h"
#include "d2o_equation_79_evaluator.h"
#include "oct_2010_hit_data.h"
#include "oct_2010_flux_data.h"
#include "d2o_run_loader.h"
#include "d2o_background_corrector.h"
#include "d2o_globals.h"
#include "d2o_macros.h"
#include "d2o_graph.h"
#include "d2o_param_loader.h"
using namespace std;

int main()
{
int run;
int choice = 1;
char char_choice;
//user inputs:
int background;
int short_tar;
int num_runs = 0; //number of runs used
double normalize = 1;
double user_params[12];
int cells_used;
long picks = 15; 

//data selection - add new data to this block
cout << "Welcome.  The first thing that needs to be done is: load in the data.\n";
cout << "Which data will you be using?\n";
cout << "1.  Photodisintegration of D2O Using 18MeV Linearly Polarized Beam (Oct 2010). \n";
cout << "0.  Quit. \n";
cin >> choice;
switch (choice)
  {
  case 0:
    cout << "You have chosen to quit; goodbye.\n";
    return 0;
  case 1:
    cout << "You have selected the 18MeV D2O run from Oct 2010.\n";
    oct_2010_hit_data();
    target_flux_calculator();
    break;
  default:
    cerr << "ERROR: command not recognized\n";
    return 0;
  }

//menu choices
choice = 1;
while(choice != 0)
  {
  cout << "*-------------------------Menu-------------------------*\n";
  cout << "| What do you want to do?                              |\n";
  cout << "| 1.  Analyse a run.                                   |\n";
  cout << "| 2.  Use run data to generate xmgrace input.          |\n";
  cout << "| 3.  Use parameters to generate xmgrace input.        |\n";
  cout << "| 4.  Analyse the average of two or more runs.         |\n";
  cout << "| 5.  Compute chi sq and reduced chi sq for given fit. |\n";
  cout << "| 6.  Generate a Geant4 GPS macro.                     |\n";
  cout << "| 7.  Generate a block chart with run data.            |\n";
  cout << "| 8.  Process a run using user supplied parameters.    |\n";
  cout << "| 0.  Quit.                                            |\n";
  cout << "*------------------------------------------------------*\n";
  cin >> choice;
  switch (choice)
    {
    case 0:
      cout << "You have chosen to quit; goodbye.\n";
      return 0;
    case 1:
      cout << "Enter run to analyze (enter 0 to go back): ";
      cin >> run;
      if (run == 0) break;
      cout << "Is this a short target? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") short_tar = 1;
      else if (char_choice == * "n") short_tar = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      cout << "Do you want background suppression? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") background = 1;
      else if (char_choice == * "n") background = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      cout << "Analysing... \n";
      equation_79_evaluator(run,background);
      cout << "Parameter information sent to file.\n";
      total_cross_section(run,background);
      d2o_run_macro(param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7],param[8],param[9],param[10],param[11],short_tar);

      break;
    case 2:
      cout << "Enter run to graph (enter 0 to go back): ";
      cin >> run;
      if (run == 0) break;
      cout << "Do you want background suppression? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") background = 1;
      else if (char_choice == * "n") background = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      cout << "Enter normalization factor (parameter A; enter 1 for no normalization):\n";
      cin >> normalize;
      equation_79_graph_error(run,background,normalize);
      cout << "Xmgrace input generated and sent to file ";
      cout << "(equation_79_w_errors_sol_xmgrace_input.dat).\n";
      break;
    case 3:
      cout << "Enter parameters to graph (";
      cout << "the sequence is: A, a1, a2, a3, a4, e2, e3, e4, c1, c2, d1 then d2.):\n";
      for(int ii = 0;ii < 12;ii++) 
        {
        cout << "Enter parameter number " << ii + 1 << ": \n";
        cin >> user_params[ii];
        cout << "You entered: " << user_params[ii] << endl;
        }
      cout << "Is this a short target? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") short_tar = 1;
      else if (char_choice == * "n") short_tar = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      equation_79_graph(user_params[0],user_params[1],user_params[2],user_params[3],user_params[4],user_params[5],user_params[6],user_params[7],user_params[8],user_params[9],user_params[10],user_params[11],short_tar);
      cout << "Xmgrace input generated and sent to file ";
      cout << "(equation_79_sol_xmgrace_input.dat).\n";
      break;
    case 4:
      num_runs = 0;
      cout << "You have selected to average together two or more runs.\n";
      cout << "Do you want background suppression? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") background = 1;
      else if (char_choice == * "n") background = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      run = 1;
      for(int ii = 0;ii < 88;ii++) //reset everything before using
        {
        n[ii] = 0;
        d_n[ii] = 0;
        }
      while (run != 0)
        {
        cout << "Enter the run number you want to include in the average (enter 0 to stop) \n";
        cin >> run;
        if(run == 0) break;
        cout << "Enter normalization factor (parameter A; enter 1 for no normalization):\n";
        cin >> normalize;
        if(normalize <= 0) 
          {
          cerr << "ERROR: normalize factor must be greater than 0.\n";
          continue;
          }
        switch (run)
          {
          case 142:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run142[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run142[ii]/normalize;
              short_tar = 0;
              }
            break;
          case 143:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run143[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run143[ii]/normalize;
              short_tar = 0;
              }
            break;
          case 149:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run149[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run149[ii]/normalize;
              short_tar = 0;
              }
            break;
          case 150:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run150[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run150[ii]/normalize;
              short_tar = 0;
              }
            break;
          case 152:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run152[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run152[ii]/normalize;
              short_tar = 0;
              }
            break;
          case 153:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run153[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run153[ii]/normalize;
              short_tar = 0;
              }
            break;
          case 155:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run155[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run155[ii]/normalize;
              short_tar = 1;
              }
            break;
          case 157:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run157[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run157[ii]/normalize;
              short_tar = 1;
              }
            break;
          case 158:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run158[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run158[ii]/normalize;
              short_tar = 1;
              }
            break;
          case 159:
            for(int ii = 0;ii < 88;ii++)
              {
              n[ii] = n[ii] + run159[ii]/normalize; //total experimental hits for detector ii
              d_n[ii] = d_n[ii] + d_run159[ii]/normalize;
              short_tar = 1;
              }
            break;
          default:
            cerr << "ERROR: run " << run << " not found.\n";
            run = -1;
            break;
          }
        //correct for background
        if(background == 1)
          {
          d2o_background_corrector(run,normalize);
          }    
        if(run == -1) continue;
        cout << "The running average now includes run " << run << endl;
        num_runs++;
        }
      if(num_runs == 0) break;  //in case no runs are entered
      //correct for number of runs
      for(int ii = 0;ii < 88;ii++)
        {
        n[ii] = n[ii]/num_runs;
        d_n[ii] = d_n[ii]/num_runs;
        //cout << "n[" << ii << "] = " << n[ii] << " +/- " << d_n[ii] << endl; //debug line
        } 
      cout << "Done entering runs, now fitting parameters (this will take a while)...\n";
      for(long ii = 1;ii <= picks;ii++)
        {
        for(int ii = 0;ii < 12;ii++) 
          {
          param_picker(ii,short_tar);
          }
        }
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
      for(int ii = 0;ii < 12;ii++) 
        {
        d_param[ii] = param_error(ii,param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7],param[8],param[9],param[10],param[11],short_tar);
        }
      cout << "Run Average for " << num_runs << " run(s)." << endl;
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

      cout << "Sending parameters to graph file (equation_79_sol_xmgrace_input.dat)...\n";
      equation_79_graph(param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7],param[8],param[9],param[10],param[11],short_tar);


      //reset globals:
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
      break;
    case 5:
      cout << "Enter run to analyze (enter 0 to go back): ";
      cin >> run;
      if (run == 0) break;
      run_loader(run); //load in run to get n
      cout << "Is this a short target? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") short_tar = 1;
      else if (char_choice == * "n") short_tar = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      //correct background
      cout << "Do you want background suppression? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") 
        {
        d2o_background_corrector(run);
	background = 1;
        }
      else if (char_choice == * "n") background = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      //enter and test parameters
      cout << "Enter parameters to compare with (";
      cout << "the sequence is: A, a1, a2, a3, a4, e2, e3, e4, c1, c2, d1 then d2.):\n";
      for(int ii = 0;ii < 12;ii++) 
        {
        cout << "Enter parameter number " << ii + 1 << ": \n";
        cin >> user_params[ii];
        cout << "You entered: " << user_params[ii] << endl;
        }
      cells_used = 0;
      //calculate predicted spectrum and reduced chi squared
      for(int ii = 0;ii < 88;ii++) //note: n_est is a global
        {
        if(n[ii] < threshold) continue; //ignore empty cells
        if(ii > 79) //ignore last ring
          {
          n_est[ii] = -1; 
          continue;
          } 
        else
          {
          n_est[ii] = N_theo(ii,user_params[0],user_params[1],user_params[2],user_params[3],user_params[4],user_params[5],user_params[6],user_params[7],user_params[8],user_params[9],user_params[10],user_params[11],short_tar);
          cells_used++;
          }
        }

        cout << "Chi sq (run " << run << ") = ";
        cout << chi_sq(n,n_est,d_n) << endl;
        cout << "Reduced chi sq (run " << run << ") = ";
        cout << red_chi_sq(n,n_est,d_n,cells_used - 12) << endl; //12 fit parameters
      break;
    case 6:
      cout << "What sort of distribution do you want simulated?\n";
      cout << "1. An evaluated run.\n";
      cout << "2. A distribution calculated from specified parameters.\n";
      cout << "3. A probability distribution.\n";
      cin >> run;
      if (run == 1)
        {
        cout << "Enter run to analyze (enter 0 to go back): ";
        cin >> run;
        if (run == 0) break;
        cout << "Is this a short target? (y/n)\n";
        cin >> char_choice;
        if (char_choice == * "y") short_tar = 1;
        else if (char_choice == * "n") short_tar = 0;
        else 
          {
          cout << "ERROR: character not recognized.\n";
          break;
          }        
        cout << "Do you want background suppression? (y/n)\n";
        cin >> char_choice;
        if (char_choice == * "y") background = 1;
        else if (char_choice == * "n") background = 0;
        else 
          {
          cout << "ERROR: character not recognized.\n";
          break;
          }
        cout << "Calculating parameters... \n";
        equation_79_evaluator(run,background);
        d2o_run_macro(param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7],param[8],param[9],param[10],param[11],short_tar);
        }
      if (run == 2)
        {
        cout << "Enter parameters (";
        cout << "the sequence is: A, a1, a2, a3, a4, e2, e3, e4, c1, c2, d1 then d2.):\n";
        for(int ii = 0;ii < 12;ii++) 
          {
          cout << "Enter parameter number " << ii + 1 << ": \n";
          cin >> user_params[ii];
          }
        cout << "Is this a short target? (y/n)\n";
        cin >> char_choice;
        if (char_choice == * "y") short_tar = 1;
        else if (char_choice == * "n") short_tar = 0;
        else 
          {
          cout << "ERROR: character not recognized.\n";
          break;
          }                 
          d2o_run_macro(user_params[0],user_params[1],user_params[2],user_params[3],user_params[4],user_params[5],user_params[6],user_params[7],user_params[8],user_params[9],user_params[10],user_params[11],short_tar);
        }
      if (run == 3) 
       {
        cout << "Which distribution do you want to simulate?\n";
        cout << "P00: 1, P01: 2, ... or P12': 12.\n";
        cin >> run;
        cout << "Is this a short target? (y/n)\n";
        cin >> char_choice;
        if (char_choice == * "y") short_tar = 1;
        else if (char_choice == * "n") short_tar = 0;
        else 
          {
          cout << "ERROR: character not recognized.\n";
          break;
          }
       d2o_distr_macro(run,short_tar);
       }
      break;
    case 7:
      cout << "Enter the run you would like to graph (xmgrace input; 0 to quit): ";
      cin >> run;
      if (run == 0) break;
      cout << "Is this a short target? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") short_tar = 1;
      else if (char_choice == * "n") short_tar = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }    
      run_graph(run,short_tar); 
      break;
    case 8:
      cout << "Do you want to enter the parameters manually or load them for a run?\n";
      cout << "Enter the run you would like to use the parameters of: \n";
      cin >> run;
      cout << "Is this a short target? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") short_tar = 1;
      else if (char_choice == * "n") short_tar = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      cout << "Do you want background suppression? (y/n)\n";
      cin >> char_choice;
      if (char_choice == * "y") background = 1;
      else if (char_choice == * "n") background = 0;
      else 
        {
        cout << "ERROR: character not recognized.\n";
        break;
        }
      cout << "Loading in parameters... \n";
      d2o_param_loader(run,background);
      cout << "Calculating total cross-section...\n";
      total_cross_section(run,background);
      cout << "Building graphs...\n";
      equation_79_graph(param[0],param[1],param[2],param[3],param[4],param[5],param[6],param[7],param[8],param[9],param[10],param[11],short_tar);      
      cout << "Parameter A = " << param[0] << endl;
      cout << "Enter normalization factor for error graph (parameter A; enter 1 for no normalization):\n";
      cin >> normalize;
      equation_79_graph_error(run,background,normalize);
      break;
    default:
      cerr << "ERROR: command not recognized\n";
      break;
    }  
  }
return 0;
}

