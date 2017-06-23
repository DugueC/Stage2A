#include "disk.h"
#include <math.h>

Disk :: Disk( Point cp, double cr) : Event(cp)
{
 radius=cr;
}

bool Disk :: testIntersection ( const Disk *ds ) const
{
  double d=dist(getPosition(),ds->getPosition()),
         dlim=getRadius()+ds->getRadius();
  bool condition=false;

  if (d < dlim)
  	condition=true;

  return condition;
}

bool Disk :: testInclusionCenter(const Disk *ds) const
{
  double d=2.0,//=dist(getPosition(),ds->getPosition()),
         dlim1=getRadius(),dlim2=ds->getRadius();
  bool condition=false;

  if ( (d < dlim1) || (d < dlim2) )
  	condition=true;

  return condition;
}


void Disk :: report() const
{
   cout << "Random Disk ...\n";
   cout << "Centre: " << getPosition()<< "\n";
   cout << "Radius: " << getRadius() << "\n";
}

/*void Disk :: setDataShape(Pattern& shape, dataEpid *data)
{
  int xr,yr;
  double cr=ceil(getRadius()),score;
  xr=(int)cr;
  yr=(int)cr;

  Point centre=getPosition(),p;
  centre.x=trunc(centre.x);
  centre.y=trunc(centre.y);
  int cx=(int)centre.x,
      cy=(int)centre.y;

  MarkedEvent *me;

  bool condition_data=false,
       condition_border=false,
       condition_distance=false;
  int nbfs;

  for(int i=-xr+cx;i<=xr+cx;i++)
   for(int j=-yr+cy;j<=yr+cy;j++)
    	{
	 condition_border=(i >= 0) && (i < data->getXDim()) && (j >= 0) && (j < data->getYDim());
	 if(condition_border==true)
	  {
	  	nbfs=(int)data->getVal(i,j,0);
		condition_data=(nbfs > 0);

		if(condition_data==true)
		 {
			 p.x=(double)i;
			 p.y=(double)j;
			 condition_distance = (( distance(centre,p) > getRadius() ) == false );

			 if(condition_distance==true)
			  {
				for(int k=1;k<=nbfs;k++)
				 {
					score=data->getVal(i,j,k);
					me = new MarkedEvent(p,score);
              				shape.add(me);
				 }
			  }
		}
	  }
      	}
}

double Disk :: computeEnergyDataShape(Pattern& shape)
{
 int nbf=shape.getSize();
 MarkedEvent *me;
 double mark, val = 0.0;

 if(nbf > 4)
  {
   	for(int i=0;i<nbf;i++)
	 {
	 	me=(MarkedEvent*)shape.getEvent(i);
		mark = me->getMark();
		val = val + mark;
	 }

	 val=val/(double)nbf;
  }

 return val;
}*/







