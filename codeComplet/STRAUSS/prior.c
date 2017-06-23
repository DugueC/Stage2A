#include "prior.h"

Prior::Prior( double cK, double cw, double ch )
{
   K = cK; 
   width = cw;
   height = ch;
   markbins = -1;
   cellvolume = -1.0;

   setVolAdapt();

}


EventPointer Prior::newEvent() const
{
   Point p( width*whran.uniform(), height*whran.uniform());
   return new Event(p);
}

EventPointer Prior::newAdapted(const Event *f) const
{
   Point p( width*whran.uniform(), height*whran.uniform());
   return new Event(p);
}


EventPointer Prior::newChangedPos(const Event *f) const
{
   Point p=f->getPosition();
   return new Event(p);
}

EventPointer Prior::newChangedShape(const Event *f) const
{
   Point p=f->getPosition();
   return new Event(p);
}


void Prior::printParameters( char *name_file ) const
{
   FILE *list_file;
   if( (list_file=fopen(name_file,"at")) == NULL ) {
      cout << "ERROR : opening file in printParameters()";
      cout << name_file << " \n";
      exit(1);
   }
 
   fprintf( list_file, "%f %f\n", ubnd(), range() );
   fclose(list_file);
}


void Prior::printSample( const Pattern& p, char *name_file ) const
{
   FILE *list_file;
   if( (list_file=fopen(name_file,"wt")) == NULL ) {
      cout << "ERROR : opening file in printSample()";
      cout << name_file << " \n";
      exit(1);
   }

   int sz = p.getSize();
   if( sz > 0 ) {
      //fprintf( list_file, "%d\n",sz);
      for( int i=0; i<sz; i++ ) 
         fprintf( list_file, "%f %f\n",
	    p.getEvent(i)->getX(), p.getEvent(i)->getY() );

      fclose(list_file); 
   }
}

void Prior::printStatistics( Pattern& p, char *name_file ) const 
{
   FILE *list_file;
   if( (list_file=fopen(name_file,"at")) == NULL ) {
      cout << "ERROR : opening file in printStatistics()";
      cout << name_file << " \n";
      exit(1);
   }
 
   if( p.getSize() > 0 ) {
      fprintf( list_file, "%d\n", getTotal(p) );
      fclose(list_file); 
   }
}


int Prior::getTotal(const Pattern& p) const
{
   return p.getSize();
}



int Prior :: countEventsToAdapt( Pattern& D, Pattern& A ) const
{
  int n=D.getSize(),i,k=0;

  for(i=0;i<n;i++)
  	{
    Event *e=D.getEvent(i);
    //if(testReadyToAdapt(e)==true)
    A.add(e);
   }

  return A.getSize();
}


int Prior :: selectEventToAdapt( Pattern& D, Pattern& A ) const
{
  int n=D.getSize(),nta=A.getSize(), pos_A=-1,pos_D=-1;

  bool condition=false;


  if(nta>0)
   	{
  			pos_A=whran.discrete_uniform(0,nta-1);
         pos_D=D.find(A.getEvent(pos_A));
      }
  
  return pos_D;
}

void Prior :: setParameters(dvector *psi)
{
   double val=psi->getVal(0);
   setK(val);
}

void Prior :: getStatistics(Pattern& p, dvector *data)
{
 float nt=(float)p.getSize();
 data->setVal(0,nt);
}


void Prior :: saveStatMatrix(const Pattern& p, dmatrix *tX, int i)
{
   float val=(float)getTotal(p);
   tX->setVal(i,0,val);
}

