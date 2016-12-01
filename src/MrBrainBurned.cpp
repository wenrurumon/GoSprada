#include <iostream>
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>
#include <algorithm>
#include <vector>

// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace std;
using namespace arma;

//[[Rcpp::Export]]
int main(){
  cout << "Main Function" << endl;
  return 0;
}

//pool

class pooling{
private:
  vector<int> pool, player1, player2;
public:
  void init(){
    for (int i = 0; i < 13; i++){
      pool.insert(pool.end(),4,i+1);
    }
    vector<int> player1, player2;
  }
  vector<int> outpool(){
    return pool;
  }
  vector<int> outp1(){
    return player1;
  }
  vector<int> outp2(){
    return player2;
  }
  void carding(int x){
    int psize = pool.size();
    int pick = rand() % psize;
    if(x == 1){
      player1.insert(player1.end(),pick);
    } else {
      player2.insert(player2.end(),pick);
    }
    pool.erase(pool.begin+pick);
  }
};

//[[Rcpp::export]]
SEXP test(){
  pooling x;
  x.init();
  return List::create(_["P"]=x.outpool(),
                      _["p1"]=x.outp1(),
                      _["p2"]=x.outp2())
}

//[[Rcpp::export]]
SEXP test2(){
  pooling x;
  x.init();
  x.carding(1);
  return List::create(_["P"]=x.outpool(),
                      _["p1"]=x.outp1(),
                      _["p2"]=x.outp2())
}




