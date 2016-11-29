#include <iostream>
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>

// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace std;
using namespace arma;

//Cost
//[[Rcpp::export]]
float cost(float x){
  float costval = sin(x)*2 + cos(x*2+10);
  return costval;
}

//[[Rcpp::export]]
float averagecost(vector<float> g){
  float sum = 0;
  int gsize = g.size();
  for(int i = 0; i < gsize; i++){
    sum += cost(g[i]);
  }
  sum = sum / g.size();
  return sum;
}

//[[Rcpp::export]]
float gcost(vector<float> g){
  return averagecost(g);
}
