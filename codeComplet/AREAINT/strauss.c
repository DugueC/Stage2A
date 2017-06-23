#include "strauss.h"

Strauss::Strauss(double cK, double gamma, double cr, double cw, double ch)
   : PairInteraction(cK, cr,cw, ch)
{
   this->gamma = gamma;
}

double Strauss :: gamma_func(double t) const 
{
  if(t<0.9999)
    return gamma;
  else
    return 1.0;
}


void Strauss::report() const
{
   printf("Stauss process on ");
   printf("[0, %f] x [0, %f] ", xrange(), yrange());
   printf("with range %.3f", range());
   printf(" intensity parameter %.5f", ubnd());
   printf(" and interaction potential %.5f\n", gamma);
}

void Strauss :: setParameters(dvector *psi)
{
  double b=exp(psi->getVal(0)),g=exp(psi->getVal(1));

  setK(b);
  setGamma(g);
}


void Strauss :: getStatistics(Pattern& p, dvector *data)
{
 //double  val1=(double)getTotal(p),
 //        val2=(double)getInteractingPairs(p);

 double  val1=(double)getTotalInUnitSquare(p),
         val2=(double)getInteractingPairsInUnitSquare(p);


 data->setVal(0,val1);
 data->setVal(1,val2);

}

void Strauss :: printStatistics( Pattern& p, char *name_file)
{
   FILE *list_file;
 
   int sz = p.getSize();
 
   if( sz > 0 ) {
      if( (list_file=fopen(name_file,"at")) == NULL ) {
         cout << "ERROR : opening file in printStatistics()";
         cout << name_file <<" \n";
         exit(1);
      }
 
      //fprintf( list_file, "%d %d\n", getTotal(p), getInteractingPairs(p) );
      fprintf( list_file, "%d %d\n", getTotalInUnitSquare(p), getInteractingPairsInUnitSquare(p) );
      
      fclose(list_file); 
   }
}



int Strauss :: getTotalInUnitSquare(Pattern& p)
{
  int sz = p.getSize();
  int total = 0;

  bool cond;

  for( int i=0; i<sz-1; i++ )
      {
       cond=p.getEvent(i)->inUnitSquare();
       if (cond==true)
          total++;
      }

   return total;
}

int Strauss :: getInteractingPairsInUnitSquare(Pattern& p)
{
   int sz = p.getSize();
   int pairs = 0;

   bool cond,cond_i;

   for( int i=0; i<sz-1; i++ )
      {
       cond_i=p.getEvent(i)->inUnitSquare();
       for( int j= i+1; j<sz; j++ ) {
       cond=cond_i && p.getEvent(j)->inUnitSquare();
       if (cond==true)
	      if( dissimilarity( p.getEvent(i), p.getEvent(j) ) < 0.9999 )
	          pairs++;
      }
   }

   return pairs;
}

void Strauss :: saveStatMatrix(const Pattern& p, dmatrix *tX, int i) 
{
   double val1=(double)getTotal(p),
          val2=(double)getInteractingPairs(p);
   tX->setVal(i,0,val1);
   tX->setVal(i,1,val2);
}


