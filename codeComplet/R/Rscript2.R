



rm(list=ls())
setwd("/home/clement/Documents/Stage2A/codeComplet/R")

# on lit les paramètres

params0="../PARAMS/p_str_cftp_C.txt"
#params0="../PARAMS/p_aint_mh_C.txt"
params=read.table(params0,header=F)
n=dim(params)[1]
dossier=as.character(params[n,1])

# on se place dans le bon dossier
setwd(dossier)


#rFGJ0=read.table("./rayonsFGJ.txt",header=F)
#rFGJ=rFGJ0[,1]
#rK0=read.table("./rayonsK.txt",header=F)

f = read.table("./F.txt",header=F)
minF = apply(f,2,min)
maxF = apply(f,2,max)


g = read.table("./G.txt",header=F)
minG = apply(g,2,min)
maxG = apply(g,2,max)

j = read.table("./J.txt",header=F)
minJ = apply(j,2,min)
maxJ = apply(j,2,max)

k = read.table("./K.txt",header=F)
minK = apply(k,2,min)
maxK = apply(k,2,max)



# petites courbes
setwd("/home/clement/Documents/Stage2A/codeFGJK")

sufficient.stat=read.table("./RESULTS/dataset3/F.txt",header=F)
f1=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/dataset3/G.txt",header=F)
g1=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/dataset3/J.txt",header=F)
j1=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/dataset3/K.txt",header=F)
k1=sufficient.stat[,1]


sufficient.stat=read.table("./RESULTS/dataset3/rayonsK.txt",header=F)
rK=sufficient.stat[,1]
sufficient.stat=read.table("./RESULTS/dataset3/rayonsFGJ.txt",header=F)
rFGJ=sufficient.stat[,1]



### figure

x11()
par(mfrow=c(2,2))

# F
yMin = min(min(minF),min(f1))
yMax = max(max(maxF),max(f1))
plot(rFGJ, minF, type="l", col="black", xlab="r", ylab="F(r)", ylim=c(yMin,yMax))
polygon(c(rFGJ,rev(rFGJ)),c(minF,rev(maxF)),col="blue")
lines(rFGJ, maxF, type="l", col="black")
lines(rFGJ, f1, type="l", col="red")
title(main="enveloppe de F")


# G
yMin = min(min(minG),min(g1))
yMax = max(max(maxG),max(g1))
plot(rFGJ, minG, type="l", col="black", xlab="r", ylab="G(r)", ylim=c(yMin,yMax))
polygon(c(rFGJ,rev(rFGJ)),c(minG,rev(maxG)),col="blue")
lines(rFGJ, maxG, type="l", col="black")
lines(rFGJ, g1, type="l", col="red")
title(main="enveloppe de G")


# J
yMin = min(min(minJ),min(j1))
yMax = max(max(maxJ),max(j1))
plot(rFGJ, minJ, type="l", col="black", xlab="r", ylab="J(r)", ylim=c(yMin,yMax))
polygon(c(rFGJ,rev(rFGJ)),c(minJ,rev(maxJ)),col="blue")
lines(rFGJ, maxJ, type="l", col="black")
lines(rFGJ, j1, type="l", col="red")
title(main="enveloppe de J")


# K
yMin = min(min(minK),min(k1))
yMax = max(max(maxK),max(k1))
plot(rK, minK, type="l", col="black", xlab="r", ylab="K(r)", ylim=c(yMin,yMax))
polygon(c(rK,rev(rK)),c(minK,rev(maxK)),col="blue")
lines(rK, maxK, type="l", col="black")
lines(rK, k1, type="l", col="red")
title(main="enveloppe de K")



# intensite
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

