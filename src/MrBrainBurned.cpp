#include <iostream>
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <math.h>
#include <algorithm>

// [[Rcpp::depends(RcppArmadillo)]]
using namespace Rcpp;
using namespace std;
using namespace arma;

//main
int main(){
  cout << "Main Function" << endl;
  return 0;
}

//pool
class pooling{
private:
  vector<int> pool;
public:
  void init(vector<int> x){
    pool = x;
  }
  void kick(int x){
    pool.erase(std::remove(pool.begin(), pool.end(), x), pool.end());
  }
  vector<int> output(){
    return pool;
  }
};

//[[Rcpp::export]]
vector<int> p1(vector<int> x){
  pooling p;
  p.init(x);
  p.kick(10);
  return p.output();
}
  
  
//export
RCPP_MODULE(m){
  using namespace Rcpp;
  function("test", &p1);
  function("main", &main);
}
