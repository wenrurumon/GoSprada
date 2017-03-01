
setwd('C:\\Users\\zhu2\\Documents\\rcpp\\maze')
library(Rcpp)
library(slam)
Rcpp::sourceCpp('maze_part.cpp')

##########################################

mazei <- matrix(0,2,2)
mazei[2,-1] <- -.5; mazei[3,1] <- 10
mazei

##########################################
# Macro
##########################################

move <- function(i,p,mat,bias=0){
  state <- get_position(p,mat)
  coremovei <- cbind(c(-1,1,0,0),c(0,0,-1,1))
  probs <- (coremovei %*% t(coremovei))[i,]
  probs[probs==0] <- bias; probs[probs==-1] <- 0; probs[probs==1] <- 1-2*bias
  p2 <- sapply(lapply(1:length(probs),basemove,p=state),get_point,x=mat)
  cbind(p,p2,probs)[p2*probs>0,,drop=F]
}

move2 <- function(i,p,mat,bias=0){
  state <- get_position(p,mat)
  coremovei <- cbind(c(-1,1,0,0),c(0,0,-1,1))
  probs <- (coremovei %*% t(coremovei))[i,]
  probs[probs==0] <- bias; probs[probs==-1] <- 0; probs[probs==1] <- 1-2*bias
  p2 <- sapply(lapply(1:length(probs),basemove,p=state),get_point,x=mat)
  sel <- (p2*probs>0); p2 <- p2[sel]; probs <- probs[sel]
  if(sum(sel)==0){return(NULL)}
  return(
    cbind(p=sapply(1:sum(sel),function(i){
      get_point(c(p,p2[i]),matrix(0,length(mat),length(mat)))
      }),prob=probs)
  )
}

p_from_array <- function(P.code,nstate,nact){
  P <- array(0,c(nstate,nstate,nact))
  for(i in 1:nact){
    P[,,i][P.code[[i]][,1]] <- P.code[[i]][,2]
  }
  return(P)
}

##########################################
# Test
##########################################

library(MDPtoolbox)
P.code <- lapply(c(0,0.01),function(bias){
  lapply(1:4,function(movei){
    do.call(rbind,lapply(1:length(mazei),move2,i=movei,mat=mazei,bias=bias))
  })
})
P <- lapply(P.code,p_from_array,nstate=length(mazei),nact=4)
R <- apply(P[[1]],3,function(x){x%*%as.vector(mazei)})
mdp_bellman_operator(P[[2]],R,0.9,rep(0,length(mazei)))
mdp_Q_learning(P[[2]],R,1)$policy
