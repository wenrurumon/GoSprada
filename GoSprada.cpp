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
double cost(double x){
  double costval = sin(x)*2 + cos(x*2+10);
  return costval;
}

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
double randbang(vector<double> parents){
  int n_parents = parents.size();
  double father = rand() % n_parents;
  double mother = rand() % n_parents;
  double son = (parents[father]+parents[mother])/2;
  return son;
}

//[[Rcpp::export]]
vector<double> reprod(vector<double> parents)
