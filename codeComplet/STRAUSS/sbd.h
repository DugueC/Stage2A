#ifndef _sbd_
#define _sbd_ 1

#include "sampler.h"

class CFTP : public Sampler {
   void extend( Pattern& D, double& time );
   void forwards( Pattern& U, Pattern& L ) const;
 public:
   //CFTP( Prior *p, char *name_file ) : Sampler(p, name_file) { }
   CFTP( Prior *p ) : Sampler(p) { }
   void init( Pattern& D );
   void sim( Pattern& D );
   void report() const { cout<<"Coupling from the past \n"; }
   void computeAverageSufficientStatistics(dvector *result, int nbsamples);
};

class BirthDeath : public Sampler {
   void birth( double t, Pattern& D );
   void extend( Pattern& D, double& time );
   double time;
 public:
   //BirthDeath( Prior *p, double ctime, char *name_file ) : Sampler(p, name_file) { time = (float) ctime; }
   BirthDeath( Prior *p, double ctime) : Sampler(p) { time = (float) ctime; }
   void init( Pattern& D );
   void sim( Pattern& D );
   void report() const { printf("Spatial birth and death\n"); }
};

#endif
