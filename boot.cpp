#include <iostream>
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>

// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace std;

//Modules
double cost(double x){
  double costval = sin(x)*2 + cos(x*2+10);
  return costval;
}

//Function Export
RCPP_MODULE(unif_module){
  function("cost",&cost);
}
