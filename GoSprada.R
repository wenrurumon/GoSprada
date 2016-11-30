
library(Rcpp)
library(inline)
library(RcppArmadillo)
rm(list=ls());sourceCpp('gosprada.cpp')

#set seeds for the first generation

g1 <- seeds(0,7,10000)

#Reproductions

rlt <- list(g1)
for(i in 2:10){
  print(i)
  rlt[[i]] <- reprod2(rlt[[i-1]],length(rlt[[i-1]])*2)
  print(gcost(rlt[[i]]))
}
sapply(rlt,gcost)

plot.ts(sapply(seeds(0,7,10000),cost))
min(sapply(seeds(0,7,10000),cost))
min(sapply(rlt[[length(rlt)]],cost))
