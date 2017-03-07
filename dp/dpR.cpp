
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <iostream>
#include <algorithm>

using namespace arma;
using namespace Rcpp;
using namespace std;

/*define the actions*/

vector<int> act_core(int i, vector<int> p){
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

//[[Rcpp::export]]
vector<int> act(int i, vector<int> p){
	vector<int> p2 = act_core(i,p);
	return p2;
}

/*define the order and position transformation*/

//[[Rcpp::export]]
vector<int> poi2pos(int i, mat x){
  vector<int> rlt(2);
  int ncol = x.n_cols, nrow=x.n_rows;
  if (ncol*nrow<i){
    cout << "out of range" << endl;
  }
  int icol = (i-1)/nrow;
  int irow = i - icol*nrow;
  rlt[0] = irow; rlt[1] = icol+1;
  return rlt;
}

//[[Rcpp::export]]
int pos2poi(vector<int> p, mat x){
  int ncol = x.n_cols, nrow=x.n_rows, rlt;
  if(p[0]<=0||p[0]>nrow||p[1]<=0||p[1]>ncol){
    rlt = 0;
  } else {
  	rlt = (p[1]-1)*nrow+p[0];
  }
  return rlt;
}

/*Define the feedback from the postion*/

//[[Rcpp::export]]
double act_score(int i, int p, mat x){
	double s2;
	int p2 = pos2poi(act(i,poi2pos(p,x)),x);
	if(p2!=0){
		s2 = x[p2-1];
	}
	double rlt = s2;
	return rlt;
}


//[[Rcpp::export]]
vector<double> act_score_all(int p, mat x){
	vector<double> rlt;
	for(int i=1; i<5; i++){
		double s = act_score(i,p,x);
		rlt.push_back(s);
	}
	return rlt;
}

