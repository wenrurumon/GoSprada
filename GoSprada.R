

setwd('C:/Users/WenluluSens/Documents/Project/learnr/rcpp')
library(Rcpp)
library(inline)
library(RcppArmadillo)
rm(list=ls());sourceCpp('test.cpp')

#

g1 <- seeds(0,7,14000)

getg <- function(g){
  g2 <- reprod(g,length(g))
  g2$kids[g2$kidscost<=quantile(g2$kidscost)[2]]
}

rlt <- list(g1)
for(i in 2:10){
  rlt[[i]] <- reprod2(rlt[[i-1]],length(rlt[[i-1]]))
}
