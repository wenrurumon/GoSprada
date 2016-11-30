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

//macro

vec csum(const mat & X){
  int nCols = X.n_cols;
  vec out(nCols);
  for(int i = 0; i < nCols; i++){
    out(i) = sum(X.col(i));
  }
  return(out);
}
vec rsum(const mat & X){
  int nRows = X.n_rows;
  vec out(nRows);
  for(int i = 0; i < nRows; i++){
    out(i) = sum(X.row(i));
  }
  return(out);
}

//[[Rcpp::export]]
vector<int> gamescore(mat x){
  vector<int> score(8);
  vec cscore = csum(x);
  vec rscore = rsum(x);
  int diag1 = x[0] + x[4] + x[8];
  int diag2 = x[2] + x[4] + x[6];
  for(int i=0; i < 3; i++){
    score[i] = cscore[i];
    score[i+3] = rscore[i];
  }
  score[7] = diag1; score[8] = diag2;
  return score;
}

