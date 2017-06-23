#include "areaint.h"

///////////////////////////////////////////////////////
//
// Area Interaction point process with random disks
//
///////////////////////////////////////////////////////

AreaInteraction :: AreaInteraction( double clb, double clg, double cw, double ch, double cr, double cres) :
Prior((clg<0.0)? exp(clb)*exp(-(M_PI*(cr*cr))*clg) : exp(clb), cw, ch )
{
 logbeta = clb;
 loggamma = clg;

 radius = cr;

 resolution = cres;

 int nrows =(int)(cw/resolution),ncols=(int)(ch/resolution);

 grid.setMatrix(nrows,ncols);
 grid.initZeros();
 visited_area.setMatrix(nrows,ncols);
 visited_area.initZeros();
 //area_element=resolution*resolution;
 area_element=resolution*resolution/(M_PI*cr*cr);
}

void AreaInteraction :: makeShape( Pattern& shape, const Event *e ) const
{
 Disk *de = (Disk*)e;
 Event *es;
 Point ptemp,pc=de->getPosition();

 int xrmax,xrmin,yrmax,yrmin,i,j,px,py,step_x=(int)ceil(pc.x/resolution),step_y=(int)ceil(pc.y/resolution);
 double dd;

 xrmax=(int)(radius/resolution);
 yrmax=(int)(radius/resolution);
 xrmin=-xrmax;
 yrmin=-yrmax;

 for(i=xrmin;i<=xrmax;i++)
 for(j=yrmin;j<=yrmax;j++)
  	{
          px=i+ step_x;
          py=j+ step_y;
	  if((px>=0)&&(px<grid.getRows())&&(py>=0)&&(py<grid.getCols()))
		{
	  	 dd=resolution*sqrt((double)(i*i+j*j));

	         if( (dd > radius) == false )
	  		{
		  	 ptemp.set((double)px,(double)py);
		  	 es = new Event(ptemp);
		  	 shape.add(es);
			}
		}
	}
}





double AreaInteraction :: computeInteractionEnergy(const Pattern& shape) const
{
  int i,ns=shape.getSize(),pos_x,pos_y;
  Point p;
  double val,k=0.0;

  for(i=0;i<ns;i++)
  	{
	 p=shape.getEvent(i)->getPosition();

	 pos_x=(int)ceil(p.x);
	 pos_y=(int)ceil(p.y);

	 val=grid.getVal(pos_x,pos_y);

	 if( (val > 1e-12) && (val <(1.0+1e-12)))
	 	k=k+1.0;
	}



  return -k*area_element*loggamma+logbeta;
}

double AreaInteraction :: computeTotalArea() const
{
 int i,j;
 double val,k = 0.0;

 for(i = 0 ; i < grid.getRows(); i++)
 	for(j = 0 ; j < grid.getCols(); j++)
		{
			val = grid.getVal(i,j);
			if(val > 0.0)
				k = k+1.0;
		}

 //k*area_element;
 return k*area_element*(M_PI*radius*radius);
}

double AreaInteraction :: cond_intens( Pattern &p, Event* e ) const
{
 Pattern shape;

 makeShape(shape,e);

 double val=computeInteractionEnergy(shape);

 shape.clean();

 return exp(val);
}



Event* AreaInteraction :: newEvent() const
{
   //Point p( xmin+(xmax-xmin)*whran.uniform(), ymin+(ymax-ymin)*whran.uniform());
   Point p( xrange()*whran.uniform(), yrange()*whran.uniform());
   //double cr=rmin+(rmax-rmin)*whran.uniform();
   double cr= getRadius();

   return new Disk(p,cr);
}

bool AreaInteraction :: setProperties ( Pattern& p, const Event *e)
{
  Pattern shape;

  makeShape(shape,e);

  Point ps;
  int i,j;
  double val;

  for(int k=0;k<shape.getSize();k++)
	{
		ps = shape.getEvent(k)->getPosition();
		i=(int)ceil(ps.x);
		j=(int)ceil(ps.y);
		val=grid.getVal(i,j);
		grid.setVal(i,j,val+1.0);
	}

  shape.clean();

}
bool AreaInteraction :: deleteProperties ( Pattern& p, const Event *e)
{
  Pattern shape;

  makeShape(shape,e);

  Point ps;
  int i,j;
  double val;

  for(int k=0;k<shape.getSize();k++)
	{
		ps = shape.getEvent(k)->getPosition();
		i=(int)ceil(ps.x);
		j=(int)ceil(ps.y);

		val=grid.getVal(i,j);
		grid.setVal(i,j,val-1.0);
	}


  shape.clean();
}



void AreaInteraction :: report() const
{
   printf("Area interaction process on ");
   printf("[0, %.3f] x [0, %.3f] ", xrange(), yrange());
   printf("with range %.3f\n", range());
   printf(" intensity parameter %.3f\n", getLogBeta());
   printf(" interaction parameter %.3f\n", getLogGamma());
   printf(" area element %.3f\n",area_element);
   printf(" total area   %.4f\n",getArea());


}

void AreaInteraction :: printParameters( char *name_file ) const
{
   FILE *list_file;
   if( (list_file=fopen(name_file,"at")) == NULL ) {
      cout << "ERROR : opening file in printParameters()";
      cout << name_file << " \n";
      exit(1);
   }

   fprintf( list_file, "%f %f\n", getLogBeta(), getLogGamma() );
   fclose(list_file);
}


void AreaInteraction :: printSample( const Pattern& p, char *name_file ) const
{
   FILE *list_file;
   if( (list_file=fopen(name_file,"wt")) == NULL ) {
      cout << "ERROR : opening file in printSample()";
      cout << name_file << " \n";
      exit(1);
   }

   Disk *de;

   int sz = p.getSize();
   if( sz > 0 ) {
      for( int i=0; i<sz; i++ )
      	{
	 de = (Disk*)p.getEvent(i);
         fprintf( list_file, "%f %f %f\n",de->getX(), de->getY(),de->getRadius() );
	}
   }

   fclose(list_file);
}

void AreaInteraction :: printStatistics( Pattern& p, char *name_file ) const
{
   FILE *list_file;
   if( (list_file=fopen(name_file,"at")) == NULL ) {
      cout << "ERROR : opening file in printStatistics()";
      cout << name_file << " \n";
      exit(1);
   }

   //if( p.getSize() > 0 ) {
   //fprintf( list_file, "%d %.3f\n", getTotal(p), computeTotalArea() );
   //}

   fprintf( list_file, "%d %.3f %.3f\n", getTotal(p), -computeTotalArea()/(M_PI*radius*radius), -computeTotalArea() );

   fclose(list_file);
}

void AreaInteraction :: printGrid( char *name_file) const
{
	grid.saveMatrix(name_file);
}

void AreaInteraction :: setVisitedArea ( )
{
  double val_grid,val_visited;

  for(int i = 0 ; i < grid.getRows() ; i++)
  	for(int j = 0 ; j < grid.getCols() ; j++)
		{
			val_grid=grid.getVal(i,j);
			if(val_grid > 1e-12)
				{
					val_visited=visited_area.getVal(i,j)+1.0;
					visited_area.setVal(i,j,val_visited);
				}
		}


}

void AreaInteraction :: getVisitedArea(dmatrix *mat)
{
 visited_area.getMat(mat);
}

void AreaInteraction :: initZerosVisitedArea()
{
 visited_area.initZeros();
}

void AreaInteraction :: printVisitedArea( char *name_file) const
{
	visited_area.saveMatrix(name_file);
}

void AreaInteraction :: setParameters(dvector *psi)
{
  double lgb=psi->getVal(0),lgg=psi->getVal(1);

  setLogBeta(lgb);
  setLogGamma(lgg);
}


void AreaInteraction :: getStatistics(Pattern& p, dvector *data)
{
 double  val1=(double)getTotal(p),
         val2=computeTotalArea()/(M_PI*radius*radius);

 data->setVal(0,val1);
 data->setVal(1,-val2);

}


