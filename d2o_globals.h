#ifndef D2O_CONSTANTS_H 
#define D2O_CONSTANTS_H 

double euler = 2.7182818284590452353602874713526624977572470936999595;
double pi = 3.1415926535897932384626433832795028841971693993751058;

int threshold = 1; //determines minimum ADC value to be considered when solving, norm is to set it to 1 so that it ignores everything less than 1 (i.e. empty or broken bins)
		     //may also set it to ignore pedestal which is 200-400

//intitial domains, guesses come from Kucuker's results (2010):
double max_A = 1;
double min_A = -1;

double max_a1 = 1;
double min_a1 = -1;

double max_a2 = 2;
double min_a2 = -2;

double max_a3 = 1;
double min_a3 = -1;

double max_a4 = 1;
double min_a4 = -1;

double max_e2 = 2;
double min_e2 = -2;

double max_e3 = 1;
double min_e3 = -1;

double max_e4 = 1;
double min_e4 = -1;

double max_c1 = 1;
double min_c1 = -1;

double max_c2 = 1;
double min_c2 = -1;

double max_d1 = 1;
double min_d1 = -1;

double max_d2 = 1;
double min_d2 = -1;

double best_A = 1,best_a1 = 0,best_a2 = 0,best_a3 = 0,best_a4 = 0,best_e2 = 0,best_e3 = 0,best_e4 = 0,best_c1 = 0,best_c2 = 0,best_d1 = 0, best_d2 = 0;

double param[12]; //stores parameters
double d_param[12]; //stores errors for parameters
//guide: A = 0, a1 = 1, a2 = 2, ... (same order as the best_A line)

double best_chi_sq = 1e50,best_red_chi_sq = 1e50; //give ridiculously high initial values

double n_est[88]; //estimated number of hits per detector
double n[88]; //stores hit info being analysed
double d_n[88]; //stores uncertainty in n[88]
double n_sim[88]; //stores sim hit info being analysed
double n_back_sub_sim[88]; //background subtracted version of simulated data

//long target:
double a_long[88]; //isotropic distribution (N00) //ADC cut = 500: //verified
double b_long[88]; //N01 //ADC cut = 500 //verified
double c_long[88]; //N02 //ADC cut = 500 //verified
double d_long[88]; //N03 //ADC cut = 500 //verified
double e_long[88]; //N04 //ADC cut = 500 //verified
double f_long[88]; //N22 //ADC cut = 500 //verified
double g_long[88]; //N23 //ADC cut = 500 //verified
double h_long[88]; //N24 //ADC cut = 500 //verified
double i_long[88]; //N11 //ADC cut = 500 //verified
double j_long[88]; //N12 //ADC cut = 500 //verified
double k_long[88]; //N11'//ADC cut = 500 //mistake found and corrected; now verified
double l_long[88]; //N12' //ADC cut = 500 //verified
double run_sim[88]; //arm 1 is up //adc cut at 500
double run_sim_light_cut[88]; //with cut at ADC = 515
double run_sim_transverse_shift[88]; //with target moved to y + 3mm
double run_sim_longitudinal_shift[88]; //with target moved x + 3mm
double run_sim_beam_alignment[88]; //with neutron generators moved down y - 3mm
double run_sim_detector_position[88]; //with detector moved theta + 0.423degrees

//run simulations
double run142_back_sub_sim[88];
double run143_back_sub_sim[88];
double run149_back_sub_sim[88];
double run150_back_sub_sim[88];
double run152_back_sub_sim[88];
double run153_back_sub_sim[88];
double run154_back_sub_sim[88];
double run155_back_sub_sim[88];
double run157_back_sub_sim[88];
double run158_back_sub_sim[88];
double run159_back_sub_sim[88];
double run142_sim[88];
double run143_sim[88];
double run149_sim[88];
double run150_sim[88];
double run152_sim[88];
double run153_sim[88];
double run154_sim[88];
double run155_sim[88];
double run157_sim[88];
double run158_sim[88];
double run159_sim[88];



//short target:
double a_short[88]; //isotropic distribution (N00) //ADC cut = 500: //verified
double b_short[88]; //N01 //ADC cut = 500 //verified
double c_short[88]; //N02 //ADC cut = 500 //verified
double d_short[88]; //N03 //ADC cut = 500 //verified
double e_short[88]; //N04 //ADC cut = 500 //verified
double f_short[88]; //N22 //ADC cut = 500 //verified
double g_short[88]; //N23 //ADC cut = 500 //verified
double h_short[88]; //N24 //ADC cut = 500 //verified
double i_short[88]; //N11 //ADC cut = 500 //verified
double j_short[88]; //N12 //ADC cut = 500 //verified
double k_short[88]; //N11'//ADC cut = 500 //mistake found and corrected; now verified
double l_short[88]; //N12' //ADC cut = 500 //verified

//experimental data:
double run142[88]; //cut at 1750keVee; arm 3 is on top //verified
double run142_light_cut[88];
double run142_psd_cut[88];
double d_run142[88]; //uncertainty
double run143[88]; //cut at 1750keVee; arm 3 is up //verified
double run143_light_cut[88];
double run143_psd_cut[88];
double d_run143[88]; //uncertainty
double run149[88]; //cut at 1750 keVee //arm 2 on top //verified
double d_run149[88]; //uncertainty in run149
double run149_light_cut[88]; //arm on top is 2 //verified for: 1803, 2000 and 2500 keVee
double run149_psd_cut[88]; //cut at ADC = 500 //psd cut at -2 (flipped coin) //verified
double run150[88]; //cut at 1750keVee //arm on top is 2 //verified
double run150_light_cut[88];
double run150_psd_cut[88];
double d_run150[88]; //uncertainty
double run152[88]; //cut at ADC = 500 //arm on top is 4 //verified
double run152_light_cut[88];
double run152_psd_cut[88];
double d_run152[88]; //uncertainty
double run153[88]; //1750keVee cut, arm 4 is up, 1/2 gamma flux //verified
double run153_light_cut[88];
double run153_psd_cut[88];
double d_run153[88]; //uncertainty
double run154[88]; //this is an H2O run, sort of like the background neutrons //adc cut is 1750 //arm 4 is up //verified
double run154_light_cut[88];
double run154_psd_cut[88];
double d_run154[88];
double run155[88]; //short target, 1750keVee cut, arm 4 is up //verified
double run155_light_cut[88];
double run155_psd_cut[88];
double d_run155[88]; //uncertainty
double run157[88]; //short target, 1750keVee cut, arm 4 is up //verified
double run157_light_cut[88];
double run157_psd_cut[88];
double d_run157[88]; //uncertainty
double run158[88]; //arm 2 is up, 1750 keVee cut, short target //verified
double run158_light_cut[88];
double run158_psd_cut[88];
double d_run158[88]; //uncertainty
double run159[88];
double run159_psd_cut[88];
double run159_light_cut[88];
double d_run159[88];
double long_ave[88];//average for all long target (from oct_2010_parameters.ods)
double long_st_dev[88];

double n_t_run142;
double d_n_t_run142;
double n_t_run143;
double d_n_t_run143;
double n_t_run149;
double d_n_t_run149;
double n_t_run150;
double d_n_t_run150;
double n_t_run152;
double d_n_t_run152;
double n_t_run153;
double d_n_t_run153;
double n_t_run154;
double d_n_t_run154;
double n_t_run155;
double d_n_t_run155;
double n_t_run157;
double d_n_t_run157;
double n_t_run158;
double d_n_t_run158;
double n_t_run159;
double d_n_t_run159;

double d_est_gammas = 0; //unfortunately it is easiest to make this a global

double a[88]; //isotropic distribution (N00) 
double b[88]; //N01 
double c[88]; //N02 
double d[88]; //N03 
double e[88]; //N04 
double f[88]; //N22 
double g[88]; //N23
double h[88]; //N24 
double i[88]; //N11 
double j[88]; //N12
double k[88]; //N11'
double l[88]; //N12' 

//flux is number of gammas present at target during run
double flux;
double d_flux = 0;

double tar_length; //target length; long: 10.7cm; short: 4.00cm
double d_tar_length = 0.1; //has small impact on total uncertainty (if <0.1 then trivial) (estimated at 0.1cm)
double short_tar = 2.0;
double long_tar = 10.7;

#endif
