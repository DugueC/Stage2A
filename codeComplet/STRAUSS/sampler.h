#ifndef _sampler_
#define _sampler_ 1

#include "prior.h"
#include <cstdlib>

class Sampler {
 protected:
   Prior *prior;
   TransitionList tvec;
   double totalTime;
   int totalJumps;
 
   virtual void birth( double t, Pattern& D );
   virtual void death( double t, Pattern& D );
   virtual void extend( Pattern& D, double& time ) = 0;
 public:
   //Sampler( Prior *prior, char *name_file );
   Sampler( Prior* prior);

   virtual ~Sampler();
 
   virtual void init( Pattern& D ) = 0; 
   virtual void setPrior( Prior *prior ) { this->prior = prior; }
   virtual void sim( Pattern& D ) = 0;
   virtual void report() const = 0;
   void clean();
   
   void setTime( int ctime ) { totalTime = (double)ctime; }
   // void setJumps( int cjumps ) { totalJumps = cjumps; }
   double getTime() { return totalTime; }
   int getJumps() { return totalJumps; }
   //void printTimeJumps();
};

/*

Typical use:

   Prior *prior = new Model( ... );
   whran.setSeed( ... );
   Sampler *sampler = new Algorithm( prior );
   Pattern sample;

   for( int i=0; i<100; i++ ) {
      sampler->init( sample );
      // Radu? 
      // tvec.setPattern( sample );
      sampler->sim( sample );
      prior->printSample( sample, filename );
      sampler->clean();
      sample.destroy():
   }

For the Gibbs sampler, the initialisation sets sample to 
a deterministic state, so init( .. ) is better placed 
before the for loop and sample does not need to be destroyed.

*/

#endif
