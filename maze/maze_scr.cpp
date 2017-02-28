
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
  rlt[0] = irow; rlt[1] = icol+1;
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

class moves{
private:
  int xrow, xcol;
public:
  void init(){
    xrow=0;
    xcol=0;
  }
  void init(int x_,int y_){
    xrow = x_;
    xcol = y_;
  }
  void moveup(){
    xrow = xrow-1;
  }
  void movedown(){
    xrow = xrow+1;
  }
  void moveleft(){
    xcol = xcol-1;
  }
  void moveright(){
    xcol = xcol+1;
  }
  vector<int> display(){
    vector<int> rlt(2);
    rlt[0] = xrow; rlt[1] = xcol;
    return rlt;
  }
};

//Main
int test(mat m){
  maze m2;
  m2.init(m);
  cout << m2.display() << endl;
  
  return 0;
}

//Export
RCPP_MODULE(unif_module){
  // function("test",&test);
}

