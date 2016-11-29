#include <iostream>
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>

// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace std;
using namespace arma;

//Intercourse
//[[Rcpp::export]]
vector<double> seeds(double minx, double maxx, double cutx){
  vector<double> x(cutx+1);
  for(double i = 0; i < cutx+1 ; i++){
    x[i] = minx + i/cutx * (maxx-minx);
  }
  return x;
}

//[[Rcpp::export]]
double son(double x, double y){
  double son = (x+y)/2;
  return son;
}

