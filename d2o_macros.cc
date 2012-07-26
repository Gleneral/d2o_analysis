//Glen Pridham
//April 26, 2010
//Generates a bunch of sources all firing together
//probability distribution is given for area (i.e. theta and phi) but generated only in terms of phi biasing; a better approximation would require that some biasing for theta was also present (though I'm not sure how to do it, nor that it would be worth the effort)
//Note: you can always take more slices for a better approximation

//Strategy: do it all in CM frame then convert back to lab frame at very end (by converting cosine and sine of theta in the CM frame into lab frame)

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "d2o_globals.h"
using namespace std;

double cm_cos(double theta) //converts theta given in the lab frame to cos(theta) in CM frame
{
double m_n = 939.565346; //mass of neutron (MeV/c^2) (K Nakamura et al, J Phys, G 37, 07021, 2010)
double m_p = 938.272013; //mass of proton (MeV/c^2) (K Nakamura et al, J Phys, G 37, 07021, 2010
double m_d = m_p + m_n - 2*1.112283; //mass of deuterium (MeV/c^2) (used binding energy per nucleon from 2003 AME mass.mas03; AMDC)
double E_photon = 18; //energy of photon (MeV)
double beta = E_photon/(E_photon + m_d);
double gamma = pow(1 - beta*beta,-0.5);
double cos_t;
cos_t = pow(1 + gamma*gamma*tan(theta)*tan(theta),-0.5);
//fix sign
if (theta > 0.5*pi) cos_t = -cos_t;
return cos_t;
}

double cm_sin(double theta) //converts theta given in the lab frame to cos(theta) in CM frame
{
double sin_t;
sin_t = pow(1 + cm_cos(theta)*cm_cos(theta),0.5);
return sin_t;
}

void d2o_run_macro(double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target) 
{
  cout << "Parameters being used are: ";
  cout << "A = " << A;
  cout << "; a1 = " << a1;
  cout << "; a2 = " << a2;
  cout << "; a3 = " << a3;
  cout << "; a4 = " << a4;
  cout << "; e2 = " << e2;
  cout << "; e3 = " << e3;
  cout << "; e4 = " << e4;
  cout << "; c1 = " << c1;
  cout << "; c2 = " << c2;
  cout << "; d1 = " << d1;
  cout << "; d2 = " << d2 << endl;

  string outfilename;
  cout << "Please enter the name of the macro file you wish to create (no spaces): ";
  cin >> outfilename;

  //output files 
  ofstream outfile;
  outfile.open (outfilename.c_str());


  //important note: when biasing, all variables range from [0,1] so for theta, biast = 0.1 really means biasing thetamax*0.1 = pi/10

  //note: theta is calculated by geant4 using theta = arccos(1-2*random) where random belongs to [0,1] and is selected from the histogram provided
  //note: phi is calculated by geant4 using phi = 2*pi*random
  
  double small_number = 1e-10; //this is to prevent really rounding erros in the small_u algorithm
 
  double biasp = 0, biast = 0; //note that cos_theta = 2*sqrt(u) - 1
  //theta = arccos(2*sqrt(u) - 1)
  //biast = theta/thetamax = theta/pi
  double u = -1; //u is weighted number, u belongs to [0,1]
		//u is probability of being found in little square
		
  int ii = 0; //dummy variable to count number of loop iterations
  double n; //interval size
  double sum = 0; //sum of all the weighting to ensure that the total probability is 1 (or close to it)
  double slice = 1000.0; //number of slices I take of probability distribution
//Note: there is ~10000*slice lines of code outputted
//Note: be careful, text editors can open a finite number of lines 
//Note: crashed last time I tried to copy and paste 10 million lines of code in gedit (3 million works though)
//Solution: use gvim!
  n = 1/slice;

  double source = 10; //number of slices of source I take for beam attenuation

  //determine the length of the source
  double halfx; //halfx of entire source short: 1.0cm, long: 5.35cm (Serpil's thesis)
  if (short_target == 1) halfx = 1.0;
  else halfx = 5.35;

  double x;
  double radius = 1.27; //radius of source is same as beam

  double intensity =  1; //default
  double atten = 0; //attenuation loss (ends up being 17% in last source)

  int run_check = 0; //double checks number of runs

  double t1,t2,p1,p2; //angles t: theta and p: phi
  double K,p; //kinetic energy (MeV), momentum (MeV/c)

  double m_n = 939.565346; //mass of neutron (MeV/c^2) (K Nakamura et al, J Phys, G 37, 07021, 2010)
  double m_p = 938.272013; //mass of proton (MeV/c^2) (K Nakamura et al, J Phys, G 37, 07021, 2010
  double m_d = m_p + m_n - 2*1.112283; //mass of deuterium (MeV/c^2) (used binding energy per nucleon from 2003 AME mass.mas03; AMDC)
  double E_photon = 18; //energy of photon (MeV)
  double beta = E_photon/(E_photon + m_d);
  double gamma = pow(1 - beta*beta,-0.5);

  //Note: I take c = 1 (speed of light in vacuum)

  double small_u; //just there to find the smallest u
  
  double offset;

  double k00,k01,k02,k03,k04,k22,k23,k24,k11,k12,k110,k120;

  cout << "Number of histogram slices taken: " << slice << endl;
  cout << "Number of attenuation slices taken: " << source << endl;
  if (halfx < 1.001 && halfx > 0.999)
    {
    cout << "Current target is: short (2.0cm)\n";
    }
  else if (halfx < 5.351 && halfx > 5.349)
    {
    cout << "Current target is: long (10.7cm)\n";
    }
  else 	
    {
    cerr << "ERROR: target length not recognized; output was not sent to file.\n";
    exit(1);
    }
  cout << "Working... \n";

  outfile << "#Glen Pridham; produced using d2o_coefficients.cc\n";
  outfile << "#delete any existing sources \n";
  outfile << "/gps/source/clear\n";
  outfile << "\n/gps/source/multiplevertex 0\n"; //so that vertice fire is weighted (if this is set to 1 then all verteces will fire all the time)


  //first loop is just to figure out the offset
  small_u = 0;
  offset = 0;
  x = -halfx + halfx/source;
  while(x < halfx) //determines position of source slice
  {
  t1 = 0;
  atten = pow(euler,-0.01843673502*(halfx + x));
  //cout << "euler = " << euler << "; atten = " << atten << endl; //debug line
    while(t1 < 3.14) //careful with this threshold, make sure you don't get any negative probabilities!
    {
    t2 = t1 + pi/slice;
     
    //energy at theta (as given by kinematics)
    //note: this includes a transformation to the CM frame and back to the lab frame

    //p' = sqrt(E'^2 + ((m_p^2 - m_n^2)/(E'))^2 - 2*(m_p^2 + m_n^2)) 
    p = 0.5*pow((pow((gamma*m_d + gamma*E_photon*(1 - beta)),2) + pow((m_p*m_p - m_n*m_n)/(gamma*m_d + gamma*E_photon*(1 - beta)),2) - 2*(m_p*m_p + m_n*m_n)),0.5); //this is p in the CM frame

    K = gamma*pow(p*p + m_n*m_n,0.5) + beta*gamma*p*cm_cos(t1 + 0.5*pi/slice) - m_n; //don't forget to subtract rest mass!


    biasp = n;
    sum = 0;
    while(biasp < 1.001)
     {


     //how GPS picks values from histogram:
      p1 = 2*pi*(biasp - n);
      p2 = 2*pi*biasp;
 
      //big number out front is to try and prevent rounding errors (all probability density functions are normalized by G4 GPS)
    
      k00 = -0.25/pi*(cm_cos(t2) - cm_cos(t1))*(p2-p1);
      k01 = -0.125/pi*(cm_cos(t2)*cm_cos(t2) - cm_cos(t1)*cm_cos(t1) + 2.*cm_cos(t2) - 2.*cm_cos(t1))*(p2-p1); 
      k02 = -0.125/pi*((cm_cos(t2) - cm_cos(t1))*(p2 - p1) + (pow(cm_cos(t2),3) - pow(cm_cos (t1),3))*(p2 - p1));
      k03 = -0.125/pi*(2.*(cm_cos(t2) - cm_cos(t1)) + 1.25*(pow(cm_cos(t2),4) - pow(cm_cos(t1),4)) - 1.5*(cm_cos(t2)*cm_cos(t2) - cm_cos(t1)*cm_cos(t1)))*(p2 - p1);
      k04 = -0.03125/pi*(11.*(cm_cos(t2) - cm_cos(t1)) + 7*(pow(cm_cos(t2),5) - pow(cm_cos(t1),5)) - 10*(pow(cm_cos(t2),3) - pow(cm_cos(t1),3)))*(p2 - p1);
      k22 = -(0.0833333333/pi)*(3*(cm_cos(t2) - cm_cos(t1))*(p2 - p1 + 0.5*sin(2*p2) - 0.5*sin(2*p1)) - 0.5*(pow(cm_cos(t2),3) - pow(cm_cos(t1),3))*(sin(2*p2) - sin(2*p1)));
      k23 = -(0.04166666667/pi)*(6*(cm_cos(t2)-cm_cos(t1))*(p2 - p1) + 15*(0.5*pow(cm_cos(t2),2) - 0.5*pow(cm_cos(t1),2) - 0.25*pow(cm_cos(t2),4) + 0.25*pow(cm_cos(t1),4))*0.5*(sin(2*p2) - sin(2*p1)));
      k24 = -(0.025/pi)*(10.*(cm_cos(t2)-cm_cos(t1))*(p2 - p1) + 7.5*(2.66666667*(pow(cm_cos(t2),3) - pow(cm_cos(t1),3)) - (cm_cos(t2) - cm_cos(t1)) - 1.4*(pow(cm_cos(t2),5) - pow(cm_cos(t1),5)))*0.5*(sin(2*p2) - sin(2*p1)));
      k11 = 0.25/pi*(-1*(cm_cos(t2) - cm_cos(t1))*(p2 - p1) + (0.5*t2 - 0.5*t1 - 0.25*sin(2*t2) + 0.25*sin(2*t1))*(sin(p2) - sin(p1)));
      k12 = 0.0833333333/pi*(2.*(pow(cm_sin(t2),3) - pow(cm_sin(t1),3))*(sin(p2) - sin(p1)) - 3*(cm_cos(t2) - cm_cos(t1))*(p2 - p1));
      k110 = 0.25/pi*(-1*(cm_cos(t2) - cm_cos(t1))*(p2 - p1) - (0.5*t2 - 0.5*t1 - 0.25*sin(2*t2) + 0.25*sin(2*t1))*(cos(p2) - cos(p1))); //this corresponds to k = 11 '
      k120 = 0.0833333333/pi*(-1.0*2.*(pow(cm_sin(t2),3) - pow(cm_sin(t1),3))*(cos(p2) - cos(p1)) - 3*(cm_cos(t2) - cm_cos(t1))*(p2 - p1)); //this corresponds to k = 12 '

      //debug lines
      if(k00 < 0) cout << "k00 < 0\n";
      if(k01 < 0) cout << "k01 < 0\n";
      if(k02 < 0) cout << "k02 < 0\n";
      if(k03 < 0) cout << "k03 < 0\n";
      if(k04 < 0) cout << "k04 < 0\n";
      if(k22 < 0) cout << "k22 < 0\n";
      if(k23 < 0) cout << "k23 < 0\n";
      if(k24 < 0) cout << "k24 < 0\n";
      if(k11 < 0) cout << "k11 < 0\n";
      if(k12 < 0) cout << "k12 < 0\n";
      if(k110 < 0) cout << "k110 < 0\n";
      if(k120 < 0) cout << "k120 < 0\n";
 
      u = 1000000.*A*((1 - a1 - a2 - a3 - a4 - 3*e2 - 6*e3 - 10*e4 - c1 - 1.5*c2 - d1 - 1.5*d1)*k00 + a1*k01 + a2*k02 + a3*k03 + a4*k04 + 3*e2*k22 + 6*e3*k23 + 10*e4*k24 + c1*k11 + 1.5*c2*k12 + d1*k110 + 1.5*d1*k120) + offset;   
    

      if (u < small_u) small_u = u; //automatically correct for offset
    
   
      biasp = biasp + n;
      ii = ii + 1;    
//    if(i % 100 == 0) cout << "biasp = " << biasp << "... \n"; //just there to show it hasn't crashed

      sum = sum + u;  
     }

    t1 = t1 + pi/slice;
    }
  x = x + 2*halfx/source;
  }
  
  if (small_u < 0) offset =  -1*small_u + small_number; //this should 0, but occasinally won't be because of uncertainty or because of missing parameters in expansion 
  else offset = 0;
  small_u = 0;
  cout << "Offset = " << offset << endl;
  x = -halfx + halfx/source;
  while(x < halfx) //determines position of source slice
  {
  t1 = 0;
  atten = pow(euler,-0.01843673502*(halfx + x));
  //cout << "euler = " << euler << "; atten = " << atten << endl; //debug line
    while(t1 < 3.14) //careful with this threshold, make sure you don't get any negative probabilities!
    {
    t2 = t1 + pi/slice;
  
    //if (k == 10) intensity = 0.5*(1 + cos(t1 + 0.5*pi/slice));
    
    //build new source
    outfile << "/gps/source/add " << intensity << endl;
    outfile << "/gps/pos/centre " << x << " -0.1 0 \n"; //origin is 0 -0.1 0
    outfile << "/gps/pos/type Volume \n";
    outfile << "/gps/pos/shape Cylinder \n";
    outfile << "/gps/pos/radius " << radius << endl;
    outfile << "/gps/pos/halfz " << halfx/source << endl;
    outfile << "/gps/pos/rot1 0 0 1  \n"; //rotate shape to match simulation
    outfile << "/gps/pos/rot2 0 1 0 \n";
    outfile << "/gps/particle neutron \n";
    outfile << "/gps/ang/rot1 0 0 1  \n"; //rotate axes to match Ward's choice of theta/phi (doesn't change shape's orientation)
    outfile << "/gps/ang/rot2 0 1 0 \n";
    outfile << "/gps/ang/type iso \n";
    outfile << "/gps/ang/maxphi 6.28318 \n";
     
    //energy at theta (as given by kinematics)
    //p' = sqrt(E'^2 + ((m_p^2 - m_n^2)/(E'))^2 - 2*(m_p^2 + m_n^2)) 
    p = 0.5*pow((pow((gamma*m_d + gamma*E_photon*(1 - beta)),2) + pow((m_p*m_p - m_n*m_n)/(gamma*m_d + gamma*E_photon*(1 - beta)),2) - 2*(m_p*m_p + m_n*m_n)),0.5); //this is p in the CM frame

    K = gamma*pow(p*p + m_n*m_n,0.5) + beta*gamma*p*cm_cos(t1 + 0.5*pi/slice) - m_n; //don't forget to subtract rest mass!


    outfile << "/gps/ene/mono " << K << " MeV\n";
    //cout << "K = " << K << "; theta = " << t1 + 0.5*pi/slice << endl; //debug line


    //set correct range
    outfile << "/gps/ang/mintheta " << t1 << endl;
    outfile << "/gps/ang/maxtheta " << t2 << endl;
  
    outfile << "/gps/hist/type biasp \n";


    biasp = n;
    sum = 0;
    while(biasp < 1.001)
     {


     //how GPS picks values from histogram:
      p1 = 2*pi*(biasp - n);
      p2 = 2*pi*biasp;
 
      //big number out front is to try and prevent rounding errors (all probability density functions are normalized by G4 GPS)
    
      k00 = -0.25/pi*(cm_cos(t2) - cm_cos(t1))*(p2-p1);
      k01 = -0.125/pi*(cm_cos(t2)*cm_cos(t2) - cm_cos(t1)*cm_cos(t1) + 2.*cm_cos(t2) - 2.*cm_cos(t1))*(p2-p1); 
      k02 = -0.125/pi*((cm_cos(t2) - cm_cos(t1))*(p2 - p1) + (pow(cm_cos(t2),3) - pow(cm_cos (t1),3))*(p2 - p1));
      k03 = -0.125/pi*(2.*(cm_cos(t2) - cm_cos(t1)) + 1.25*(pow(cm_cos(t2),4) - pow(cm_cos(t1),4)) - 1.5*(cm_cos(t2)*cm_cos(t2) - cm_cos(t1)*cm_cos(t1)))*(p2 - p1);
      k04 = -0.03125/pi*(11.*(cm_cos(t2) - cm_cos(t1)) + 7*(pow(cm_cos(t2),5) - pow(cm_cos(t1),5)) - 10*(pow(cm_cos(t2),3) - pow(cm_cos(t1),3)))*(p2 - p1);
      k22 = -(0.0833333333/pi)*(3*(cm_cos(t2) - cm_cos(t1))*(p2 - p1 + 0.5*sin(2*p2) - 0.5*sin(2*p1)) - 0.5*(pow(cm_cos(t2),3) - pow(cm_cos(t1),3))*(sin(2*p2) - sin(2*p1)));
      k23 = -(0.04166666667/pi)*(6*(cm_cos(t2)-cm_cos(t1))*(p2 - p1) + 15*(0.5*pow(cm_cos(t2),2) - 0.5*pow(cm_cos(t1),2) - 0.25*pow(cm_cos(t2),4) + 0.25*pow(cm_cos(t1),4))*0.5*(sin(2*p2) - sin(2*p1)));
      k24 = -(0.025/pi)*(10.*(cm_cos(t2)-cm_cos(t1))*(p2 - p1) + 7.5*(2.66666667*(pow(cm_cos(t2),3) - pow(cm_cos(t1),3)) - (cm_cos(t2) - cm_cos(t1)) - 1.4*(pow(cm_cos(t2),5) - pow(cm_cos(t1),5)))*0.5*(sin(2*p2) - sin(2*p1)));
      k11 = 0.25/pi*(-1*(cm_cos(t2) - cm_cos(t1))*(p2 - p1) + (0.5*t2 - 0.5*t1 - 0.25*sin(2*t2) + 0.25*sin(2*t1))*(sin(p2) - sin(p1)));
      k12 = 0.0833333333/pi*(2.*(pow(cm_sin(t2),3) - pow(cm_sin(t1),3))*(sin(p2) - sin(p1)) - 3*(cm_cos(t2) - cm_cos(t1))*(p2 - p1));
      k110 = 0.25/pi*(-1*(cm_cos(t2) - cm_cos(t1))*(p2 - p1) - (0.5*t2 - 0.5*t1 - 0.25*sin(2*t2) + 0.25*sin(2*t1))*(cos(p2) - cos(p1))); //this corresponds to k = 11 '
      k120 = 0.0833333333/pi*(-1.0*2.*(pow(cm_sin(t2),3) - pow(cm_sin(t1),3))*(cos(p2) - cos(p1)) - 3*(cm_cos(t2) - cm_cos(t1))*(p2 - p1)); //this corresponds to k = 12 '

      //debug lines
      if(k00 < 0) cout << "k00 < 0\n";
      if(k01 < 0) cout << "k01 < 0\n";
      if(k02 < 0) cout << "k02 < 0\n";
      if(k03 < 0) cout << "k03 < 0\n";
      if(k04 < 0) cout << "k04 < 0\n";
      if(k22 < 0) cout << "k22 < 0\n";
      if(k23 < 0) cout << "k23 < 0\n";
      if(k24 < 0) cout << "k24 < 0\n";
      if(k11 < 0) cout << "k11 < 0\n";
      if(k12 < 0) cout << "k12 < 0\n";
      if(k110 < 0) cout << "k110 < 0\n";
      if(k120 < 0) cout << "k120 < 0\n";
 
      u = 1000000.*A*((1 - a1 - a2 - a3 - a4 - 3*e2 - 6*e3 - 10*e4 - c1 - 1.5*c2 - d1 - 1.5*d1)*k00 + a1*k01 + a2*k02 + a3*k03 + a4*k04 + 3*e2*k22 + 6*e3*k23 + 10*e4*k24 + c1*k11 + 1.5*c2*k12 + d1*k110 + 1.5*d1*k120) + offset;   
    

      if (u < small_u) small_u = u; //automatically correct for offset
    
   
      outfile << "/gps/hist/point" << " " << biasp << " " << u << endl;
      biasp = biasp + n;
      ii = ii + 1;    
//    if(i % 100 == 0) cout << "biasp = " << biasp << "... \n"; //just there to show it hasn't crashed

      sum = sum + u;  
     }
    outfile << "/gps/source/intensity " << sum*atten << endl;//fixes intensity (because GPS normalizes its histograms)

    t1 = t1 + pi/slice;
    }
  x = x + 2*halfx/source;
  }

  outfile << "\n#name the experiment\n";
  outfile << "/lucid/name " << outfilename << endl;
  outfile << "/lucid/filename " << outfilename << endl;
  outfile << "\n/lucid/event/disable ideal_neutron\n";
  outfile << "\n/run/beamOn 50000000\n";
  outfile << "\n/control/shell gzip -f /home/Glen/g4work/bin/Linux-g++/" << outfilename << "0001\n";
  outfile << "\n#End of file\n";

  cout << "Done.\n"; 

  cout << "Smallest u was: " << small_u << endl;

  //close files
  outfile.close();
return;
}

void d2o_distr_macro(int k,int short_target)
{
  string outfilename;
  cout << "Please enter the name of the macro file you wish to create (no spaces): ";
  cin >> outfilename;

  //output files 
  ofstream outfile;
  outfile.open (outfilename.c_str());
  //important note: when biasing, all variables range from [0,1] so for theta, biast = 0.1 really means biasing thetamax*0.1 = pi/10

  //note: theta is calculated by geant4 using theta = arccos(1-2*random) where random belongs to [0,1] and is selected from the histogram provided
  //note: phi is calculated by geant4 using phi = 2*pi*random
  
  double biasp = 0, biast = 0; //note that cos_theta = 2*sqrt(u) - 1
  //theta = arccos(2*sqrt(u) - 1)
  //biast = theta/thetamax = theta/pi
  double u = -1; //u is weighted number, u belongs to [0,1]
		//u is probability of being found in little square

  int ii = 0; //dummy variable to count number of loop iterations
  double n; //interval size
  double sum = 0; //sum of all the weighting to ensure that the total probability is 1 (or close to it)
  double slice = 1000.0; //number of slices I take of probability distribution
//Note: there is ~10000*slice lines of code outputted
//Note: be careful, text editors can open a finite number of lines 
//Note: crashed last time I tried to copy and paste 10 million lines of code in gedit (3 million works though)
//Solution: use gvim!
  n = 1/slice;

  double source = 10; //number of slices of source I take for beam attenuation
  double x, halfx; //halfx of entire source short: 1.0cm, long: 5.35cm (Serpil's thesis)
  //fix for target length
  if (short_target == 1) halfx = 1.0;
  else halfx = 5.35;

  double radius = 1.27; //radius of source is same as beam

  double intensity =  1; //default
  double atten = 0; //attenuation loss (ends up being 17% in last source)

  int run_check = 0; //double checks number of runs

  double cos_t,t1,t2,p1,p2; //angles t: theta and p: phi
  double K,p; //kinetic energy (MeV), momentum (MeV/c)

  double m_n = 939.565346; //mass of neutron (MeV/c^2) (K Nakamura et al, J Phys, G 37, 07021, 2010)
  double m_p = 938.272013; //mass of proton (MeV/c^2) (K Nakamura et al, J Phys, G 37, 07021, 2010
  double m_d = m_p + m_n - 2*1.112283; //mass of deuterium (MeV/c^2) (used binding energy per nucleon from 2003 AME mass.mas03; AMDC)
  double E_photon = 18; //energy of photon (MeV)
  double beta = E_photon/(E_photon + m_d);
  double gamma = pow(1 - beta*beta,-0.5);
  int debug_count = 0; //for debug

  //Note: I take c = 1 (speed of light in vacuum)

  double k00,k01,k02,k03,k04,k22,k23,k24,k11,k12,k110,k120;

  cout << "k = " << k << endl;
  cout << "Number of histogram slices taken: " << slice << endl;
  cout << "Number of attenuation slices taken: " << source << endl;
  if (halfx < 1.001 && halfx > 0.999)
    {
    cout << "Current target is: short (2.0cm)\n";
    }
  else if (halfx < 5.351 && halfx > 5.349)
    {
    cout << "Current target is: long (10.7cm)\n";
    }
  else 	
    {
    cerr << "ERROR: target length not recognized; output was not sent to file.\n";
    exit(1);
    }
  cout << "Working... \n";

  outfile << "#Glen Pridham; produced using bf_angle_bias_2.cc\n";
  outfile << "#delete any existing sources \n";
  outfile << "/gps/source/clear\n";
  outfile << "\n/gps/source/multiplevertex 0\n"; //so that vertice fire is weighted (if this is set to 1 then all verteces will fire all the time)


  x = -halfx + halfx/source;
  while(x < halfx) //determines position of source slice
  {
  t1 = 0;
  atten = pow(euler,-0.01843673502*(halfx + x));
  //cout << "euler = " << euler << "; atten = " << atten << endl; //debug line
    while(t1 < 3.14) //careful with this threshold, make sure you don't get any negative probabilities!
    {
    t2 = t1 + pi/slice;

    //if (k == 10) intensity = 0.5*(1 + cos(t1 + 0.5*pi/slice));
   
    //build new source
    outfile << "/gps/source/add " << intensity << endl;
    outfile << "/gps/pos/centre " << x << " -0.1 0 \n"; //origin is 0 -0.1 0
    outfile << "/gps/pos/type Volume \n";
    outfile << "/gps/pos/shape Cylinder \n";
    outfile << "/gps/pos/radius " << radius << endl;
    outfile << "/gps/pos/halfz " << halfx/source << endl;
    outfile << "/gps/pos/rot1 0 0 1  \n"; //rotate shape to match simulation
    outfile << "/gps/pos/rot2 0 1 0 \n";
    outfile << "/gps/particle neutron \n";
    outfile << "/gps/ang/rot1 0 0 1  \n"; //rotate axes to match Ward's choice of theta/phi (doesn't change shape's orientation)
    outfile << "/gps/ang/rot2 0 1 0 \n";
    outfile << "/gps/ang/type iso \n";
    outfile << "/gps/ang/maxphi 6.28318 \n";
   
    //energy at theta (as given by kinematics)
    if (t1 + 0.5*pi/slice <= 0.5*pi) cos_t = pow(1 + gamma*gamma*tan(t1 + 0.5*pi/slice)*tan(t1 + 0.5*pi/slice),-0.5); //fix sign
    if (t1 + 0.5*pi/slice > 0.5*pi) cos_t = -pow(1 + gamma*gamma*tan(t1 + 0.5*pi/slice)*tan(t1 + 0.5*pi/slice),-0.5);

    //cout << "Gamma = " << gamma << "; beta = " << beta << endl; //debug

    //cout << "cos_t = " << cos_t << "; t = " << t1 + 0.5*pi/slice << endl; //debug

    //p' = sqrt(E'^2 + ((m_p^2 - m_n^2)/(E'))^2 - 2*(m_p^2 + m_n^2)) 
    p = 0.5*pow((pow((gamma*m_d + gamma*E_photon*(1 - beta)),2) + pow((m_p*m_p - m_n*m_n)/(gamma*m_d + gamma*E_photon*(1 - beta)),2) - 2*(m_p*m_p + m_n*m_n)),0.5); //this is p in the CM frame (p')

    //cout << "p' = " << p; //debug   

    //calculate kinetic energy in lab frame
    K = gamma*pow(p*p + m_n*m_n,0.5) + beta*gamma*p*cos_t - m_n; //don't forget to subtract rest mass!

    //cout << K << endl; //debug
   
    //transform p to lab frame
    //p = p*(1 - cos_t*cos_t + beta*beta*gamma*gamma + 2*beta*gamma*gamma*cos_t + gamma*gamma*cos_t*cos_t); //this is p in the lab frame

    //cout << "; p = " << p << endl; //debug


    outfile << "/gps/ene/mono " << K << " MeV\n";
    //cout << "K = " << K << "; theta = " << t1 + 0.5*pi/slice << endl; //debug line


    //set correct range
    outfile << "/gps/ang/mintheta " << t1 << endl;
    outfile << "/gps/ang/maxtheta " << t2 << endl;

    outfile << "/gps/hist/type biasp \n";
  

    biasp = n;
    sum = 0;
    while(biasp < 1.001)
     {
 

     //how GPS picks values from histogram:
      p1 = 2*pi*(biasp - n);
      p2 = 2*pi*biasp;
  
      //big number out front is to try and prevent rounding errors (all   probability density functions are normalized by G4 GPS)
    
      if (k == 0) u = -1000000.*0.25/pi*(cos(t2) - cos(t1))*n*2.*pi; //equivalent to isotropic

      if (k == 1) u = -1000000.*0.125/pi*(cos(t2)*cos(t2) - cos(t1)*cos(t1) + 2.*cos(t2) - 2.*cos(t1))*n*2.*pi; 

      if (k == 2) u = -1000000.*0.125/pi*((cos(t2) - cos(t1))*(p2 - p1) + (pow(cos(t2),3) - pow(cos(t1),3))*(p2 - p1));

      if (k == 3) u = -1000000.*0.125/pi*(2*(cos(t2) - cos(t1)) + 1.25*(pow(cos(t2),4) - pow(cos(t1),4)) - 1.5*(cos(t2)*cos(t2) - cos(t1)*cos(t1)))*(p2 - p1);

      if (k == 4) u = -1000000*0.03125/pi*(11*(cos(t2) - cos(t1)) + 7*(pow(cos(t2),5) - pow(cos(t1),5)) - 10*(pow(cos(t2),3) - pow(cos(t1),3)))*(p2 - p1);

      if (k == 11) u = 1000000*0.25/pi*(-1*(cos(t2) - cos(t1))*(p2 - p1) + (0.5*t2 - 0.5*t1 - 0.25*sin(2*t2) + 0.25*sin(2*t1))*(sin(p2) - sin(p1)));

      if (k == 12) u = 1000000*0.0833333333/pi*(2*(pow(sin(t2),3) - pow(sin(t1),3))*(sin(p2) - sin(p1)) - 3*(cos(t2) - cos(t1))*(p2 - p1));
    
 
      if (k == 110) u = 1000000*0.25/pi*(-1*(cos(t2) - cos(t1))*(p2 - p1) - (0.5*t2 - 0.5*t1 - 0.25*sin(2*t2) + 0.25*sin(2*t1))*(cos(p2) - cos(p1))); //this corresponds to k = 11 '

      if (k == 120) u = 1000000*0.0833333333/pi*(-1.0*2*(pow(sin(t2),3) - pow(sin(t1),3))*(cos(p2) - cos(p1)) - 3*(cos(t2) - cos(t1))*(p2 - p1)); //this corresponds to k = 12 '

      if (k == 22) u = -1000000.0*(0.0833333333/pi)*(3*(cos(t2) - cos(t1))*(p2 - p1 + 0.5*sin(2*p2) - 0.5*sin(2*p1)) - 0.5*(pow(cos(t2),3) - pow(cos(t1),3))*(sin(2*p2) - sin(2*p1)));
 
      if (k == 23) u = -1000000.*(0.04166666667/pi)*(6*(cos(t2)-cos(t1))*(p2 - p1) + 15*(0.5*pow(cos(t2),2) - 0.5*pow(cos(t1),2) - 0.25*pow(cos(t2),4) + 0.25*pow(cos(t1),4))*0.5*(sin(2*p2) - sin(2*p1)));

      if (k == 24) u = -1000000.*(0.025/pi)*(10*(cos(t2)-cos(t1))*(p2 - p1) + 7.5*(2.66666667*(pow(cos(t2),3) - pow(cos(t1),3)) - (cos(t2) - cos(t1)) - 1.4*(pow(cos(t2),5) - pow(cos(t1),5)))*0.5*(sin(2*p2) - sin(2*p1)));

   
    outfile << "/gps/hist/point" << " " << biasp << " " << u << endl;
    biasp = biasp + n;
    ii = ii + 1;    
//    if(i % 100 == 0) cout << "biasp = " << biasp << "... \n"; //just there to show it hasn't crashed

    sum = sum + u;  
   }
  outfile << "/gps/source/intensity " << sum*atten << endl;//fix intensity (because GPS normalizes its histograms)

  t1 = t1 + pi/slice;
  }
x = x + 2*halfx/source;
}
  
  outfile << "\n#name the experiment\n";
  outfile << "/lucid/name " << outfilename << endl;
  outfile << "/lucid/filename " << outfilename << endl;
  outfile << "\n/lucid/event/disable ideal_neutron\n";
  outfile << "\n/run/beamOn 50000000\n";
  outfile << "\n/control/shell gzip -f /home/Glen/g4work/bin/Linux-g++/" << outfilename << "0001\n";
  outfile << "\n#End of file\n";

  cout << "Done.\n"; 

  //close files
  outfile.close();
return;
}
