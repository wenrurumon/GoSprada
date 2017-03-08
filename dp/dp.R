
rm(list=ls())
library(Rcpp)
library(RcppArmadillo)
setwd('/home/huzixin/Documents/maze')
rs <- function(){eval(parse(text="sourceCpp('mazeR.cpp')"))}
rs()

##########################
# Rpart
##########################

#Setup a traffic condition with 3 lanes and several blocks
matfull <- matrix(0,8,3)
for(i in c(2,4,6)){
	set.seed(12345);matfull[i,sample(3,2)] <- -1
}
matx <- matfull[1:5,]; matx[1] <- 10

#given the road status within sight, export the optimal roate
dp_insight <- function(mat,startp){
	itn <- 100
	i <- 0
	while(mat[startp]<=0&i<itn){
		i <- i+1
		#seach the candidate paths
		candidates <- which(mat==0)
		candidates_score <- lapply(candidates,act_score_all,x=mat)
		#recored the candidates searched
		candidates2 <- which(sapply(candidates_score,function(x){any(ifelse(is.na(x),0,x)>0)}))
		candidates2_score <- sapply(candidates_score[candidates2],function(x){
			x <- ifelse(is.na(x),0,x)
			max(x)*0.8 + sum(x)/3*0.2
			})
		#update the score matrix
		mat[candidates[candidates2]] <- candidates2_score
	}
	return(mat)
}

#Assume we can only see the road status 3 rows in front of us.
see <- function(pxy,traffic=matfull){
	rowi <- pxy[1]
	if(rowi>4){
		traffic[1:(rowi-4),] <- NA
	}
	target_row <- which(rowSums(is.na(traffic))==0)[1]
	target_col <- which(traffic[target_row,]==max(traffic[target_row,],na.rm=T))
	traffic[target_row,target_col] <- 10
	pi <- pos2poi(pxy,traffic)
	list(pi=pi,traffic=traffic)		
}
move <- function(seei){
	mati <- dp_insight(seei$traffic,seei$pi)
	scorei <- act_score_all(seei$pi,mati)
	#sapply(1:4,function(x){act_score(x,seei$pi,mati)})
	which(scorei==max(scorei,na.rm=T))
}
think <- function(pxy,traffic){
	seei <- see(pxy,traffic)
	seei$movei <- move(seei)
	seei
}


######################################
# Go
######################################

pi <- c(8,2)
steps <- list(think(pi,matfull))
i <- 1
while(i<100){
	i <- i+1
	pi <- act(steps[[i-1]]$movei,pi)
	if(pi[1]==1){break}
	steps[[i]] <- think(pi,matfull)
}
