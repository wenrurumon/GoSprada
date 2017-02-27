
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <iostream>

using namespace arma;
using namespace Rcpp;
using namespace std;

//Main

vector<int> get_position(int i, mat & x){
  vector<int> rlt(2);
  int ncol = x.n_cols, nrow=x.n_rows;
  if (ncol*nrow<i){
    cout << "out of range" << endl;
  }
  int irow = (i-1)/nrow;
  int icol = i - irow*ncol;
  rlt[0] = irow+1; rlt[1] = icol;
  return rlt;
}

//Function Exprt
RCPP_MODULE(unif_module){
  function("get_position",&get_position);
  function("cost",&cost);
}
