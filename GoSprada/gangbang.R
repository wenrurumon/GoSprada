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
vector<float> seeds(float minx, float maxx, float cutx){
  vector<float> x(cutx+1);
  for(float i = 0; i < cutx+1 ; i++){
    x[i] = minx + i/cutx * (maxx-minx);
  }
  return x;
}

//[[Rcpp::export]]
float randbang(vector<float> parents){
  int n_parents = parents.size();
  float father = rand() % n_parents;
  float mother = rand() % n_parents;
  float son = (parents[father]+parents[mother])/2;
  return son;
}

//[[Rcpp::export]]
SEXP reprod(vector<float> parents, int nkid){
  vector<float> kids(nkid);
  vector<float> kids_cost(nkid);
  for(int i = 0; i<nkid; i++){
    kids[i] = randbang(parents);
    kids_cost[i] = cost(kids[i]);
  }
  return List::create(Named("kids")=kids,Named("kidscost")=kids_cost);
}

//[[Rcpp::export]]
vector<float> reprod2(vector<float> parents, int nkid){
  vector<float> kids(nkid);
  vector<float> kids_cost(nkid);
  for(int i = 0; i<nkid; i++){
    kids[i] = randbang(parents);
    kids_cost[i] = cost(kids[i]);
  }
  float kcost = gcost(kids_cost);
  int countkeep = 0;
  for(int i = 0; i <nkid; i++){
    if(kids_cost[i] < kcost){
      countkeep++;
    }
  }
  vector<float> kids2keep(countkeep);
  int j = 0;
  for(int i = 0; i <nkid; i++){
    if(kids_cost[i] < kcost){
      kids2keep[j] = kids[i];
      j++;
    }
  }
  return kids2keep;
}





