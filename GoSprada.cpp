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

//[[Rcpp::export]]
double gcost(vector<double> g){
  double sum = 0;
  int gsize = g.size();
  for(int i = 0; i < gsize; i++){
    sum += cost(g[i]);
  }
  sum = sum / g.size();
  return sum;
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
SEXP reprod(vector<double> parents, int nkid){
  vector<double> kids(nkid);
  vector<double> kids_cost(nkid);
  for(int i = 0; i<nkid; i++){
    kids[i] = randbang(parents);
    kids_cost[i] = cost(kids[i]);
  }
  return List::create(Named("kids")=kids,Named("kidscost")=kids_cost);
}

//[[Rcpp::export]]
vector<double> reprod2(vector<double> parents, int nkid){
  vector<double> kids(nkid);
  vector<double> kids_cost(nkid);
  for(int i = 0; i<nkid; i++){
    kids[i] = randbang(parents);
    kids_cost[i] = cost(kids[i]);
  }
  double kcost = gcost(kids_cost);
  int countkeep = 0;
  for(int i = 0; i <nkid; i++){
    if(kids_cost[i] < kcost){
      countkeep++;
    }
  }
  vector<double> kids2keep(countkeep);
  int j = 0;
  for(int i = 0; i <nkid; i++){
    if(kids_cost[i] < kcost){
      kids2keep[j] = kids[i];
      j++;
    }
  }
  return kids2keep;
}


