
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <iostream>

using namespace arma;
using namespace Rcpp;
using namespace std;

//Macros
//[[Rcpp::export]]
vector<int> get_position(int i, mat & x){
  vector<int> rlt(2);
  int ncol = x.n_cols, nrow=x.n_rows;
  if (ncol*nrow<i){
    cout << "out of range" << endl;
  }
  int icol = (i-1)/nrow;
  int irow = i - icol*ncol;
  rlt[0] = irow+1; rlt[1] = icol;
  return rlt;
}

//[[Rcpp::export]]
int get_point(vector<int> p, mat & x){
  int nrow=x.n_rows;
  int rlt = (p[1]-1)*nrow+p[0];
  return rlt;
}

//[[Rcpp::export]]
mat randmaze(int nrow, int ncol, double pna, int penval){
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

//Class
class maze{
private:
  mat M;
  int p;
public:
  void init(){
    M = randmaze(5,10,0.1,-99);
  }
  void init(mat m){
    M = m;
  }
  mat display(){
    return M;
  }
};

//Main
int test(mat m){
  maze m1, m2;
  m1.init();
  m2.init(m);
  cout << m1.display() << endl;
  cout << m2.display() << endl;
  return 0;
}

//Export
RCPP_MODULE(unif_module){
  // function("test",&test);
}

