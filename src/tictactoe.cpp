#include <iostream>
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>

// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace std;
using namespace arma;

//[[Rcpp::export]]
mat gamelog(){
  mat x = randu(3,3);
  int xsize = x.size();
  vector<int> rlt(xsize);
  for(int i = 0; i < xsize; i++){
    int ge_count = 0;
    for(int j = 0; j < xsize; j++){
      if(x[j]>x[i]){
        ge_count += 1;
      }
    }
    rlt[i] = ge_count;
  }
  mat x2 = zeros(2,5);
  for(int i = 0; i < xsize; i++){
    x2[i] = rlt[i]+1;
  }
  return x2;
}

//[[Rcpp::export]]
mat gamerlt(mat xlog){
  mat x = zeros(3,3);
  int xsize = x.size();
  int player = 1;
  for(int i = 0; i<xsize; i++){
    x[xlog[i]-1] = player;
    player = player * -1;
  }
  return x;
}
