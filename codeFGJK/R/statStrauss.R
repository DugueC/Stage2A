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
setwd("/home/clement/Documents/Stage2A/code/R")

#
# Source program functions
#
source("pointPatternAnalysisTools.R")


name.file.stat="../POINTS/stat_strauss_cftp_A.txt"
stat=read.stat.strauss(name.file.stat)
print.stat.strauss(name.file.stat)

#name.file.pattern="../POINTS/Y_strauss_cftp_A.txt"
#print.pattern.strauss(name.file.pattern)

#
# Sauvegarde des resultats et quitter
#
name.file.savedata="res_strauss_A.RData"
save(stat,file=name.file.savedata)
#save.image(name.file.savedata)
#load(name.file.savedata)

#quit()

#
# Analyse exploratoire de X
#
#x11()
#plot(allstats(X),main="Analyse exploratoire - Strauss")



# Read the pattern : Strauss simulation
name.file="../POINTS/Y_strauss_cftp_A1.txt"
X=read.point.pattern(name.file)

# Print the data, crop a small square and scale it in the square [0,1]x[0,1]
x11()
plot(X,cex=0.1,main="Strauss simulation",cols="blue")


#
# Analyse exploratoire de X
#
x11()
plot(allstats(X),main="Analyse exploratoire - Strauss")