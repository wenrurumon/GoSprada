
rm(list=ls())
library(Rcpp)
library(RcppArmadillo)
setwd('/home/huzixin/Documents/maze')
rs <- function(){eval(parse(text="sourceCpp('mazeR.cpp')"))}
rs()

##########################
# Rpart
##########################

mat <- matrix(0,5,3)
mat[2,-1] <- -1; mat[1,1] <- 10
startp <- 10

while(mat[startp]<=0){
	#seach the candidate paths
	candidates <- which(mat==0)
	candidates_score <- lapply(candidates,act_score_all,x=mat)
	#recored the candidates searched
	candidates2 <- which(sapply(candidates_score,function(x){any(x>0)}))
	candidates2_score <- sapply(candidates_score[candidates2],function(x){0.8*max(x)+0.2/3*(sum(x)-max(x))})
	#update the score matrix
	mat[candidates[candidates2]] <- candidates2_score
}

