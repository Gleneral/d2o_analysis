#ifndef D2O_GRAPH_H 
#define D2O_GRAPH_H 

#include "d2o_graph.cc"

void run_graph(int run,int short_target);

void equation_79_graph(double A,double a1,double a2,double a3,double a4,double e2,double e3,double e4,double c1,double c2,double d1,double d2,int short_target = 0);

void equation_79_graph_error(int run = -10,int background_cor = 0,double normalize = 1);

#endif
