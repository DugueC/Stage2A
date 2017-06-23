#include "pi.h"

PairInteraction::PairInteraction( double cK, double cr, 
   double cw, double ch ) : Prior(cK,cw,ch)
{
   this->r = cr;
}

double PairInteraction::dissimilarity( const Event *e, const Event *f ) const
{
   double dissim = e->getDistance(f)/range();

   if( dissim < 0.9999 ) return dissim;
   return 1.0;

}

double PairInteraction::cond_intens( Pattern& p, Event* e ) const
{
   int nb_points = p.getSize();
   double proba = beta_func(e);

   for( int i=0; i<nb_points; i++ )
      proba=proba*gamma_func(dissimilarity(e,p.getEvent(i)));

   return proba;
}

int PairInteraction::getInteractingPairs( const Pattern& p ) const
{
   int sz = p.getSize();
   int pairs = 0;

   for( int i=0; i<sz-1; i++ ) 
      for( int j= i+1; j<sz; j++ ) {
	 if( dissimilarity( p.getEvent(i), p.getEvent(j) ) < 0.9999 )
	    pairs++;
   }

   return pairs;
}

void PairInteraction::printStatistics( const Pattern& p, 
   char *name_file) const 
{
   FILE *list_file;
 
   int sz = p.getSize();
 
   if( sz > 0 ) {
      if( (list_file=fopen(name_file,"at")) == NULL ) {
         cout << "ERROR : opening file in printStatistics()";
         cout << name_file <<" \n";
         exit(1);
      }
 
      fprintf( list_file, "%d %d\n", getTotal(p), getInteractingPairs(p) );
      fclose(list_file); 
   }
}

