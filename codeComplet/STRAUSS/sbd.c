#include "sbd.h"

void CFTP::extend( Pattern& D, double& time )
{
   double totalbr = prior->xrange() * prior->yrange() ;
   totalbr *= prior->ubnd();
   int totaldr;

   double t = time;
   //if( time > -1.0/totalbr ) time = -100.0/totalbr;
   if( time > -.9999 ) time = -1.0;
   else time *= 2.0;

   do {
      totaldr = D.getSize();
      t -= whran.exponential( totalbr + totaldr );
      if ( t < time ) break;

      double whr = whran.uniform();
      if( (totalbr+totaldr)*whr < totalbr ) {
         birth( t, D );
      }
      else {
         death( t, D );
      }
   } while (1);
}

void CFTP::forwards( Pattern& U, Pattern& L ) const
{
   short is_birth;
   Event *e;

   double wu, wl;
   Transition *trans = tvec.getLast();
   for( ; trans != NULL; trans = trans->getPrevious() ) {
      is_birth = trans->is_birth;
      e = trans->e;

      if( !is_birth ) { // forwards birth = backwards death
	 if( prior->monotone() ) {
	   wu = prior->cond_intens( U, e ) / prior->ubnd();
	   wl = prior->cond_intens( L, e ) / prior->ubnd();
	   if( wu +(1e-7)< wl ) { printf("non-monotone %f %f",wu,wl); exit(1); }
	 }
	 else {
	   wu = prior->cond_intens( L, e ) / prior->ubnd();
	   wl = prior->cond_intens( U, e ) / prior->ubnd();

	   if( wu +(1e-7)< wl ) { printf("repulsive non-monotone %f %f",wu,wl); exit(1); }
	 }

	 double w = trans->w;
	 if ( (w < wu) ) { U.add( e ); }
	 if ( (w < wl) ) { L.add( e ); } 
      }
      else { U.remove(e); L.remove(e); }
   }
}

void CFTP::init( Pattern& D )
{
   double lambda = prior->xrange() * prior->yrange() ;
   lambda *= prior->ubnd();

   int n = whran.poisson( lambda );

   D.setSize(0);
   for( int i=0; i<n; i++) {
      Event *e = prior->newEvent();
      D.add(e);
   }
}

void CFTP::sim( Pattern& D ) 
{
   if( prior->monotone() == 2 ) {
      printf("CFTP: sampler not applicable\n");
      exit(1);
   }

   double time = 0.0;
   int merged = 0;

   init(D);
   tvec.setPattern(D);

   do { 
      extend( D, time );

      Pattern L;
      Pattern U = D;


      forwards(U, L );



      merged = ( U.getSize() == L.getSize() );

   

      if ( merged ) D = U;
   } while ( ! merged );

   totalTime = time;
   totalJumps = tvec.getSize();
}

void CFTP :: computeAverageSufficientStatistics(dvector *result, int nbsamples)
{
 int i,size=result->getSize();
 dvector temp;
 temp.setVector(size);
 double fact=1.0/(double)nbsamples;
 Pattern X;

 result->initZeros();

 for(i=0;i<nbsamples;i++)
    {
     sim(X);
     prior->getStatistics(X,&temp);
     result->add(&temp);
     clean();
    }

 result->multiplyScalar(fact);
}


void BirthDeath::birth( double t, Pattern& D )
{
   Event *e = prior->newEvent();
   double w = whran.uniform();

   if( prior->ubnd() * whran.uniform() < prior->cond_intens( D, e) ) { 
      tvec.add( new Transition( e, t, 1, w ) ); 
      D.add(e);
   }
   else { delete e; }
}

void BirthDeath::extend( Pattern& D, double& time )
{
   double totalbr = prior->xrange() * prior->yrange() ;
   totalbr *= prior->ubnd();
   int totaldr;
   double t = 0.0;

   do {
      totaldr = D.getSize();

      t += whran.exponential( totalbr + totaldr );
      if ( t > time ) break;

      double whr = whran.uniform();
      if( (totalbr+totaldr)*whr < totalbr ) {
         birth( t, D );
      }
      else {
         death( t, D );
      }
   } while (1);
}

void BirthDeath::init( Pattern& D )
{
   double lambda = prior->xrange() * prior->yrange() ;
   lambda *= prior->ubnd();

   int n = whran.poisson( lambda );

   D.setSize(0);
   for( int i=0; i<n; i++) {
      Event *e = prior->newEvent();
      D.add(e);
   }
}

void BirthDeath::sim( Pattern& D ) 
{
   extend( D, time );
   totalTime = time;
   totalJumps = tvec.getSize();
}

