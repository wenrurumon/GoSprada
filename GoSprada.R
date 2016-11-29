

library(Rcpp)
library(inline)
library(RcppArmadillo)
rm(list=ls());sourceCpp('gosprada.cpp')

#set seeds for the first generation

g1 <- seeds(0,7,14000)

#Reproductions

rlt <- list(g1)
for(i in 2:10){
  rlt[[i]] <- reprod2(rlt[[i-1]],length(rlt[[i-1]]))
}
