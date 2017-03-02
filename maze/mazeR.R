
rm(list=ls())

###############################
# Setup in R
###############################

#REWARDS
randroad <- function(nr=5,nc=3,npen=-1,edge=TRUE,pen=-99){
  road <- matrix(0,nr-1,nc)
  end <- rep(0,nc)
  end[length(end)/2+1] <- 1
  for(i in 1:(nr-1)){
    if(i%%2==1){road[i,sample(nc,nc+npen)] <- pen}
  }
  road <- rbind(end,road)
  if(edge){
    road <- cbind(rep(pen,nr),road,rep(pen,nr))
  }
  return(road)
}

#STATES
getpoint <- function(p,mat){
  return((p[2]-1)*nrow(mat)+p[1])
}
getposition <- function(p,mat){
  p1 <- ceiling(p/nrow(mat))
  p2 <- p%%nrow(mat)
  p2 <- ifelse(p2==0,nrow(mat),p2)
  return(c(p2,p1))
}

#ACTIONS
checkrange <- function(states,dim=c(Inf,Inf)){
  all(states>0)&all((dim-states)>=0)
}
coremove <- function(i,state=c(0,0)){
  coremove <- cbind(c(-1,1,0,0),c(0,0,-1,1))
  m <- rep(0,4); m[i] <- 1;
  as.numeric(m%*%coremove)+state
}
move <- function(i,state=c(0,0),bias=0,mat=NULL,returnall=TRUE){
  if(is.null(mat)){
    dim = c(Inf,Inf)
  } else {
    dim = dim(mat)
  }
  coremovei <- cbind(c(-1,1,0,0),c(0,0,-1,1))
  probs <- (coremovei %*% t(coremovei))[i,]
  probs[probs==0] <- bias; probs[probs==-1] <- 0; probs[probs==1] <- 1-2*bias
  moves <- lapply(which(probs>0),coremove,state=state)
  moves.sel <- sapply(moves,checkrange,dim=dim)
  if(sum(moves.sel)==0){
    return(NULL)
  }
  rlt <- list(moves=moves[moves.sel],probs=probs[probs>0.0001][moves.sel])
  if(!is.null(mat)){
    mat[is.na(mat)] <- 0
    rlt$score <- sum(sapply(lapply(rlt$moves,getpoint,mat=mat),function(x){mat[x]})*rlt$probs,na.rm=T)  
  }
  if(returnall){
    return(rlt)
  } else {
    return(rlt$score)
  }
}

#TRACK
track <- function(road,start,end,score=NULL){
  if(is.null(score)){
    score <- run(road,bias=0.1,itn=NULL)
  }
  p <- start
  steps <- p
  while(p!=end){
    p.moves <- lapply(1:4,move,state=getposition(p,mat=score),bias=0,mat=score,returnall=TRUE)
    p.nexts <- sapply(do.call(c,lapply(p.moves,function(x){x$moves})),getpoint,mat=score)
    p <- p.nexts[score[p.nexts]==max(score[p.nexts],na.rm=TRUE)]
    p <- p[!is.na(p)][1]
    steps <- c(steps,p) 
  }
  moves <- lapply(steps,getposition,mat=road)
  for (i in 2:length(moves)){
    moves[[i-1]] <- moves[[i]]-moves[[i-1]]
  }
  coremoves <- list(c(-1,0),c(1,0),c(0,-1),c(0,1))
  moves <- c("U","D","L","R")[match(moves[-length(moves)],coremoves)]
  for(i in 1:length(moves)){
    # road[steps[i]] <- moves[i]
    road[steps[i]] <- 1
  }
  return(list(road=road,steps=steps,moves=moves))
}


###############################
# test
###############################

run <- function(road,bias=0,itn=NULL,start=NULL){
  # road <- roadi; bias = .1; disc=0.9; itn <- 100
  states <- which(road==0)
  rj <-  road
  for(i in 1:ifelse(is.null(itn),10000,itn)){
    rt <- rj
    for(statei in states){
      scorei <- sapply(1:4,move,state=getposition(statei,mat=roadi),bias=bias,mat=rt,returnall=FALSE)
      rt[statei] <- max(scorei)
    }
    rj <- rt
    if(is.null(itn)&sum(rj==0,na.rm=T)==0){
      if(!is.null(start)){
        if(road[start]>0){
          break
        }
      } else {
        break
      }
    }
  }
  rj
}

set.seed(12345);roadi <- randroad(20,4,-2,F,NA)
roadi
(score.null <- run(roadi,bias=0.1,itn=10))
starti <- which(roadi==0)[sum(roadi==0,na.rm=T)]
(track.null <- track(roadi,start=starti,end=which(roadi==1),score=score.null))
