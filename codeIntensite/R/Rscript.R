#
# Clean memory
#
rm(list=ls())
library(spatstat)
require(grDevices) # for colours
setwd("/home/clement/Documents/Stage2A/codeIntensite")
source("R/pointPatternAnalysisTools.R")


# on lit les paramètres
params=read.table("./PARAMS/params.txt",header=F,fill=TRUE)


# on récupère le nom du fichier de point utilisé et on l'affiche 
i=1
while(substring(as.character(params[i,1]),1,2)=="//") {
  i=i+1
}
name.file=as.character(params[i,1],1,2)
print.pattern.strauss(name.file)

X=read.point.pattern(name.file)
x11()
par(mfrow=c(2,2))
aaaaa= density(X, sigma=5, kernel="gaussian", edge=TRUE)
plot(density(X, sigma=5, kernel="gaussian", edge=FALSE), main="gauss")
plot(density(X, sigma=5, kernel="gaussian", edge=TRUE), main="gauss corrigé")
plot(density(X, sigma=5, kernel="disc", edge=FALSE), main="disque")
plot(density(X, sigma=5, kernel="disc", edge=TRUE), main="disque corrigé")
title(main="Intensité spatstat",outer=TRUE,line=-2)

# on se place dans le bon dossier
n=dim(params)[1]
dossier=as.character(params[n,1])
setwd(dossier)


# on recupere les valeurs calculées
Carre = read.table("./Carre.txt",header=F)
Rond = read.table("./Rond.txt",header=F)
Gauss = read.table("./Gauss.txt",header=F)
GaussCorr = read.table("./GaussCorr.txt",header=F)

# on transforme en matrice
matriceCarre = as.matrix(Carre)
matriceRond = as.matrix(Rond)
matriceGauss = as.matrix(Gauss)
matriceGaussCorr = as.matrix(GaussCorr)

# on affiche
x11()
par(mfrow=c(2,2))
image(matriceCarre, axes = FALSE, main="Carré")
image(matriceRond, axes = FALSE, main="Disque")
image(matriceGauss, axes = FALSE, main="Gauss")
image(matriceGaussCorr, axes = FALSE, main="Gauss corrigé")
title(main="Intensité",outer=TRUE,line=-2)



#
# boucle infini pour que les courbes ne disparaissent pas
#
somme=0
while(1) {
  somme=somme+1
}

