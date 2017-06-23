#ifndef _strauss
#define _strauss_ 1

#include "pi.h"

class Strauss : public PairInteraction {
  // Strauss model with intensity parameter K interaction parameter gamma  and range r
  double gamma;
  // sufficient statistics of a realization and average sufficient statistics
  double nt,sr,ant,asr;

 public:
   Strauss( double cK, double gamma, double cr, double cw, double ch );
   double gamma_func(double t) const ;
   void report() const;

   void setParameters(dvector *psi);
   void getStatistics(Pattern& p, dvector *data);
   
   int getTotalInUnitSquare(Pattern& p);
   int getInteractingPairsInUnitSquare(Pattern& p);

   void setGamma(double val){ gamma=val; }
   void saveStatMatrix(const Pattern& p, dmatrix *tX, int i) ;

   bool setProperties ( Pattern& p, const Event *e) { return true; }
   bool deleteProperties ( Pattern& p, const Event *e) { return true; }

   // printing function ...
   void printStatistics(Pattern& p,char *name_file);

};


#endif
