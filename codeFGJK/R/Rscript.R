#
# Clean memory
#
rm(list=ls())

#
# Load necessary libraries
#
library(spatstat)

#
# Set working directory
#
setwd("/home/clement/Documents/Stage2A/codeFGJK")

#
# Source program functions
#
source("./R/pointPatternAnalysisTools.R")


#
# Récupération des valeurs des fonctions
#
sufficient.stat=read.table("./RESULTS/F.txt",header=F)
f=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/G.txt",header=F)
g=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/J.txt",header=F)
j=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/K.txt",header=F)
k=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/rayonsK.txt",header=F)
rK=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/rayonsFGJ.txt",header=F)
rFGJ=sufficient.stat[,1]
#sr=sufficient.stat[,2]

#
# Estimation de l'intensité
#
sufficient.stat=read.table("./RESULTS/autre.txt",header=F)
n=as.numeric(as.character(sufficient.stat[1,1]))
W=as.numeric(as.character(sufficient.stat[2,1]))


lambda = n/W
Fpois = 1-exp(-lambda*pi*rFGJ*rFGJ)
Jpois = rep(1,length(rFGJ))
Kpois = pi*rK*rK


#
# Affichage des fonctions
#

x11()
par(mfrow=c(2,2))

# F
yMin = min(f[1],Fpois[1])
yMax = max(f[length(f)],Fpois[length(f)])
plot(rFGJ, f, type="l", col="blue", xlab="r", ylab="F(r)", ylim=c(yMin,yMax))
lines(rFGJ, Fpois, lty=2, col=2)
title(main="Fonction F")
legend(0, 0.98*yMax, legend=c("F calcul", "F poisson"), col=c("blue", "red"), lty=1:2, cex=0.8)

# G
yMin = min(g[1],Fpois[1])
yMax = max(g[length(g)],Fpois[length(g)])
plot(rFGJ, g, type="l", col="blue", xlab="r", ylab="G(r)", ylim=c(yMin,yMax))
lines(rFGJ, Fpois, lty=2, col=2)
title(main="Fonction G")
legend(0, 0.98*yMax, legend=c("G calcul", "G poisson"), col=c("blue", "red"), lty=1:2, cex=0.8)

# J
yMin = min(j,Jpois)
yMax = max(j,Jpois)
plot(rFGJ, j, type="l", col="blue", xlab="r", ylab="J(r)", ylim=c(yMin,yMax))
lines(rFGJ,Jpois,lty=2,col=2)
title(main="Fonction J")
legend(0, 0.98*yMax, legend=c("J calcul", "J poisson"), col=c("blue", "red"), lty=1:2, cex=0.8)

# K
yMin = min(k[1],Kpois[1])
yMax = max(k[length(k)],Kpois[length(k)])
plot(rK, k, type="l", col="blue", xlab="r", ylab="K(r)", ylim=c(yMin,yMax))
lines(rK,Kpois,lty=2,col=2)
title(main="Fonction K")
legend(0, 0.98*yMax, legend=c("K calcul", "K poisson"), col=c("blue", "red"), lty=1:2, cex=0.8)




#
# Read the pattern : Strauss simulation
#
#name.file="./POINTS/Y_strauss_cftp_B.txt"
name.file = as.character(sufficient.stat[3,1]) 
X=read.point.pattern(name.file)

#
# Analyse exploratoire de X avec spatstat
#
FFF = Fest(X,r=rFGJ)
GGG = Gest(X,r=rFGJ)
JJJ = Jest(X,r=rFGJ)
KKK = Kest(X,r=rK)


x11()
par(mfrow=c(2,2))
plot(rFGJ,FFF$rs,main="F",type="l",col="blue",xlab="r", ylab="F(r)")
lines(rFGJ, f, lty=2, col=2)
legend(0, 0.98*f[length(f)], legend=c("F spatstat","F calcul"), col=c("blue", "red"), lty=1:2, cex=0.8)

plot(rFGJ,GGG$rs,main="G",type="l",col="blue",xlab="r", ylab="G(r)")
lines(rFGJ, g, lty=2, col=2)
legend(0, 0.98*g[length(g)], legend=c("G spatstat","G calcul"), col=c("blue", "red"), lty=1:2, cex=0.8)

plot(rFGJ,JJJ$rs,main="J",type="l",col="blue",xlab="r", ylab="J(r)")
lines(rFGJ, j, lty=2, col=2)
legend(0, 0.98*JJJ$rs[length(j)], legend=c("J spatstat","J calcul"), col=c("blue", "red"), lty=1:2, cex=0.8)

plot(rK,KKK$border,main="K",type="l",col="blue",xlab="r", ylab="K(r)")
lines(rK, k, lty=2, col=2)
legend(0, 0.98*k[length(k)], legend=c("K spatstat","K calcul"), col=c("blue", "red"), lty=1:2, cex=0.8)

title(main="Spatstat",outer=TRUE,line=-1.5)

#k
#KKK$border
#k2k = abs(k-KKK$borde)
#mean(k2k)
#max(k2k)
#sd(k2k)

#g
#GGG$rs
#g2g = abs(g-GGG$rs)
#mean(g2g)
#max(g2g)
#sd(g2g)

#f
#FFF$rs
#f2f = abs(f-FFF$rs)
#mean(f2f)
#max(f2f)
#sd(f2f)

#j
#JJJ$rs
#j2j = abs(j-JJJ$rs)
#mean(j2j)
#max(j2j)
#sd(j2j)

#
# boucle infini pour que les courbes ne disparaissent pas
#
somme=0
while(1) {
  somme=somme+1
}

# pour rapport
#rr = seq(0,0.34,0.01)
#lambda = 40
#Fpois = 1-exp(-lambda*pi*rr*rr)
#x11()
#par(mfrow=c(2,2))
#yMin = Fpois[1]
#yMax = Fpois[length(Fpois)]
#plot(rr, Fpois, type="l", col="blue", xlab="r", ylab="F(r)", ylim=c(yMin,yMax))
#title(main="Fonction F")