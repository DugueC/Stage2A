#
# Function : read a 2d point pattern and return a ppp object
#

read.stat.strauss = function(name.file)
{
  
 sufficient.stat=read.table(name.file,header=F)

 nt=sufficient.stat[,1]
 sr=sufficient.stat[,2]

 nt.mean=cumsum(nt)/(1:length(nt))
 sr.mean=cumsum(sr)/(1:length(sr))

 res=list(nt=nt,nt.mean=nt.mean,nt.summary=summary(nt),sr=sr,sr.mean=sr.mean,sr.summary=summary(sr))

 return(res)
}

print.stat.strauss = function(name.file)
{

stat=read.stat.strauss(name.file)

x11()
par(mfrow=c(1,3))
plot(stat$nt.mean,type="l",col="blue",main="Strauss : average of nt")
plot(stat$sr.mean,type="l",col="blue",main="Strauss : average of sr")
boxplot(stat$nt,stat$sr,main ="Strauss : distribution of nt and sr")

print("Statistiques descriptives : modele de Strauss")
print("Nombre total des points :")
print(stat$nt.summary)
print("Nombre de paires des points a distance r : ")
print(stat$sr.summary)
}


read.point.pattern = function(name.file)
{
  
  data.catalogue=read.table(name.file,header=F)
  xd=data.catalogue[,1]
  yd=data.catalogue[,2]
  
  xmin=min(xd)
  xmax=max(xd)
  ymin=min(yd)
  ymax=max(yd)
  
  wp=owin(c(xmin,xmax),c(ymin,ymax))
  x.pattern=ppp(xd,yd,window=wp)
  
  return(x.pattern)
}

print.pattern.strauss = function(name.file)
{

 X=read.point.pattern(name.file)

 x11()
 plot(X,cex=0.1,main="Strauss model realisation",cols="blue")
}
