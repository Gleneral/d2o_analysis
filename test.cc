//for testing functions

#include <iostream>
#include "oct_2010_flux_data.h"
#include "d2o_total_cross_section.h"
using namespace std;

int main ()
{
oct_2010_hit_data();
target_flux_calculator();
total_cross_section(142, 1);
return 0;
}
