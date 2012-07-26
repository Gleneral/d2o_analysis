//July 10, 2012
//Glen
//contains a function that tries to correct any given run for background

#include <iostream>
#include <math.h>
#include "oct_2010_flux_data.h"
#include "d2o_globals.h"

void d2o_background_corrector(int run,double normalize)
{
cout << "Background correction enabled, subtracting H2O run (normalized) . \n";
for(int ii = 0;ii < 88;ii++)
  {
  if (n[ii] > 0)
    {
    n[ii] = n[ii] - (run154[ii]*flux/n_t_run154)/normalize;
    d_n[ii] = abs(d_n[ii]) + abs((d_run154[ii]/n_t_run154*flux)/normalize);
    if (n[ii] < 0)
      {
      cout << "Warning: background subtraction has produced a negative number of events on cell " << ii + 1 << endl;
      cout << "Setting this cell to -1.\n";
      n[ii] = -1;
      }
    }
  else
    {
    n[ii] = -1;
    }
  }
return;
}
