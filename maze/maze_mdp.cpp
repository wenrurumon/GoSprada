
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <iostream>

using namespace arma;
using namespace Rcpp;
using namespace std;

//[[Rcpp::export]]
void test(mat x){
  vector<int> p (2,100);
  cout << p[0] << endl;
  cout << p[1] << endl;
  cout << x.size() << endl;
}

//Macros
//[[Rcpp::export]]
vector<int> get_position(int i, mat x){
  vector<int> rlt(2);
  int ncol = x.n_cols, nrow=x.n_rows;
  if (ncol*nrow<i){
    cout << "out of range" << endl;
  }
  int icol = (i-1)/nrow;
  int irow = i - icol*ncol;
  rlt[0] = irow; rlt[1] = icol+1;
  return rlt;
}

//[[Rcpp::export]]
int get_point(vector<int> p, mat x){
  int ncol = x.n_cols, nrow=x.n_rows;
  int rlt = (p[1]-1)*nrow+p[0];
  if(p[0]<=0||p[0]>nrow||p[1]<=0||p[1]>ncol){
    rlt = 0;
  }
  return rlt;
}

//[[Rcpp::export]]
mat randmaze(int nrow, int ncol, double pna, double penval){
  mat rlt = zeros(nrow,ncol);
  for(int i=1; i<nrow*ncol-1; i++){
    double rval=(rand()%100), thres= 100 - pna*100;
    if(rval>thres){
      rlt[i] = penval;
    }
  }
  rlt[nrow*ncol-1] = 1;
  return rlt;
}

//[[Rcpp::export]]
vector<int> basemove(int i, vector<int> p){
  switch(i){
  case 1:
    p[0] -= 1;
    break;
  case 2:
    p[0] += 1;
    break;
  case 3:
    p[1] -= 1;
    break;
  case 4:
    p[1] += 1;
    break;
  }
  return p;
}

