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

//[[Rcpp::export]]
int main(){
  return 0;
}

//Class Player
class player{
private:
  vector<int> know, hold;
public:
  void init(){
    vector<int> know(0), hold(0);
  }
  void init(vector<int> x, vector<int> y){
    know = x;
    hold = y;
  }
  vector<int> display_know(){
    return know;
  }
  vector<int> display_hold(){
    return hold;
  }
};

//[[Rcpp::export]]
vector<int> test(int x1, vector<int> x2, vector<int> x3){
  if(x1==1){
    player p1;
    p1.init();
    return p1.display_know();
  } else if(x1==2){
    player p1;
    p1.init();
    return p1.display_hold();
  } else if(x1==3){
    player p1;
    p1.init(x2,x3);
    return p1.display_know();
  } else if(x1==4){
    player p1;
    p1.init(x2,x3);
    return p1.display_hold();
  }
  vector<int> x;
  return x;
}
