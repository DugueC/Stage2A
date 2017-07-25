#
# Read the pattern : Strauss simulation
#
name.file="./POINTS/Y_strauss_cftp_B.txt"
X=read.point.pattern(name.file)

#
# Analyse exploratoire de X
#
x11()
plot(allstats(X),main="Analyse exploratoire - Strauss")

radius=seq(0,0.1, by=0.002)
Fobs=Fest(X,r=radius)
x11()
#plot(radius,Fobs$cs,type="l",col="blue")
plot(Fobs$rs,type="l",col="blue")
Fobs$cs
str(Fobs)
?Fest

radius = rFGJ
F2=Fest(X,r=rFGJ)
F2$rs
x11()
plot(F2$rs,type="l",col="blue")
str(F2)

F3=Fest(X)
F3$rs
F3$r
plot(F3$rs,type="l",col="blue")

K2=Kest(X)
str(K2)
?Kest
K2$border
K2$r

G2=Gest(X)
str(G2)
?Gest
G2$rs
G2$r
plot(G2$rs,type="l",col="blue")

J2=Jest(X)
str(J2)
?Jest
J2$rs
J2$r
plot(J2$rs,type="l",col="blue")

aaa=allstats(X)
aaa$`F function`$r
aaa$`G function`$r
aaa$`J function`$r
aaa$`K function`$r

radius=seq(0,0.1, by=0.002)
bbb=allstats(X,r=radius)

x11()
plot(allstats(X),main="Analyse exploratoire - Strauss")
?allstats

FFF = Fest(X,r=rFGJ)
GGG = Gest(X,r=rFGJ)
JJJ = Jest(X,r=rFGJ)
KKK = Kest(X,r=rK)

x11()
par(mfrow=c(2,2))
plot(rFGJ,FFF$rs,main="F",type="l",col="blue")
plot(rFGJ,GGG$rs,main="G",type="l",col="blue")
plot(rFGJ,JJJ$rs,main="J",type="l",col="blue")
plot(rK,KKK$border,main="K",type="l",col="blue")

str(FFF)
#