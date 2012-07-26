D2O Analysis
Glen Pridham, July 2012
Contact: g.pridham@usask.ca

Welcome to the d2o_analysis program.  This program is designed to execute all of the necessary software (with the help of xmgrace, BFROOT and Geant4) to extract the total cross-section and differential cross-section of deuterium.  

Note: README.odt is in a more readable format and contains all of the same information as this file.

To install:
make d2o_analysis_main

To run:
d2o_analysis_main

Files (in alphabetical order)
File name
Purpose
Function(s)
arm_corrector.cc
Contains functions that convert a histogram of detector hits with one arm orientation to a different orientation.
void arm_cor_4_to_1, void arm_cor_3_to_1,  void arm_cor_2_to_1.
d2o_analysis_main.cc
Contains the main() function for the program; this includes the main menu.
int main.
d2o_background_corrector.cc 
Contains a function that subtracts off run154 from the provided run number.  
void d2o_background_corrector.
d2o_background_corrector.h
Header file for d2o_background_corrector.cc .
d2o_equation_79_evaluator.cc
Contains functions necessary to parameterize given run and determine the uncertainty in these parameters.  The name derives from equation 7.9 in Wurtz (2010).
void equation_79_evaluator, double chi_sq, double red_chi_sq, double N_theo, double param_error, void param_picker, void param_test.
d2o_equation_79_evaluator.h
Header file for d2o_equation_79_evaluator.cc.
d2o_globals.h 
Contains all of the global variables for the program.
None.
d2o_graph.cc
Contains the functions that generate xmgrace input files.  Output files are sent to graphs/ directory.
void run_graph, void equation_79_graph, void equation_79_graph_error.
d2o_graph.h
Header file for d2o_graph.cc.
d2o_macros.cc
Contains functions that generate Generalize Particle Source macro files for simulation using the  Geant4 Blowfish simulation.
void d2o_run_macro, void d2o_distr_macro.
d2o_macros.h
Header file for d2o_macros.cc.
d2o_param_loader.cc
Shortcut for loading in known parameters.
void d2o_param_loader.
d2o_param_loader.h
Header file for d2o_param_loader.cc.
d2o_run_loader.cc
Loads in all of the known experimental and simulated date for provided run number.
void run_loader(int run).
d2o_run_loader.h
Header file for d2o_run_loader.cc.
d2o_total_cross_section.cc
Computes the total cross-section for a provided run, with uncertainty.  Note: the current algorithm averages the cross-section over all of the detectors.  The algorithm used is equation 7.33 in Wurtz (2010).
void total_cross_section.
d2o_total_cross_section.h
Header file for d2o_total_cross_section.cc.
graphs/
Directory that contains the outputted graph files (from d2o_graph.cc) in xmgrace format.
macros/
Directory designed to store generated macro files (from d2o_macros.cc) in Geant4 Generalized Particle Source format.  Note: files will not automatically be stored in this directory, they will be stored in the home (d2o_analysis) directory.
oct_2010_flux_data.cc
Contains the flux data for the October 2010 runs at Higs. 
double n_t_old, double cal_count, double n_t, double abs, void target_flux_calculator.
oct_2010_flux_data.h
Header file for oct_2010_flux_data.cc.
oct_2010_hit_data.cc
Contains the hit data for the October 2010 runs at Higs and the associated simulation data.  Note: all histograms are arm corrected (using arm_corrector.cc).
void oct_2010_hit_data.
oct_2010_hit_data.h
Header file for oct_2010_hit_data.cc.
output_files/
Directory containing the logs for error and parameter guessing. 
README.odt
This file.
README.txt
Text version of this file.
test.cc
Independent main() function used for testing functions without having to run the entire program.  Altering this file has no impact on the rest of the program.
Whatever you want it to contain.

A note about adding new programs: compiling this software is somewhat obtuse and cumbersome because the source files often call one another.  If you add something new and are having trouble compiling, the simplest solution is to simply add forward declaration(s) where necessary (e.g. see d2o_graph.cc).

A note about updating: in order to update this software with new experimental data, you must:
1. Convert the detector hit data for your simulations and experimental data to histograms/variables and use them to generate a new source file.
2. Add the appropriately named histograms to d2o_globals.h.
3. Call the histograms/variables in d2o_run_loader.cc.
4. Insert a call in d2o_analysis_main.cc (at the very top).
5. Update run numbers where necessary.


Key Histograms and Variables (in no particular order)
Name
Purpose
Scope
int short_target
If 1 then short_target is enabled (that is the target length is 2cm), if 0 then short_target is disabled (that is the target length is 10.7cm).
Function.
double A, double a1, double a2, double a3, double a4, double e2, double e3, double e4, double c1, double c2, double d1, double d2.
These are the parameters from the expansion of the differential cross-section, see Wurtz (2010) for more information.
Function.
double param[12].
Global version of above, in same order.  param[0] = A, param[1] = a1, ... , param[12] = d2.
Global.
double d_param[12].
Uncertainties associated with above parameters.
Global.
double a[88], double b[88], double c[88], ... , double l[88].
Simulated detector hits for probability function.  a[88] represents P00, b[88] represents P01, ... , l[88] represents P12' (usual order).  See d2o_globals.h for more info.
Global.
double n[88].
When d2o_run_loader.cc is called, it loads in the experimental detector hit data into this histogram.  I.e. this histogram contains the number of neutron hits in detectors 1 through 88 for the run you are currently processing.
Global.
double d_n[88].
Uncertainties associated with above histogram.
Global.
double n_sim[88].
Same as n[88] except that it calls simulation data instead of experimental data.
Global.
double n_back_sub_sim[88].
Same as n_sim[88] except that this data has been corrected for background subtraction.
Global.


A note about loading in new data:
All information is stored in histograms.  Alter d2o_run_loader.cc to change data used.  Updated data  from Oct 2010 should simply go to oct_2010_flux_data.cc and oct_2010_hit_data.cc.  Note that substantial run number updating will be necessary for new data sets.

