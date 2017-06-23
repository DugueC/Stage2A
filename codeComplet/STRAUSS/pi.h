#ifndef _pi_
#define _pi_ 1

#include "prior.h"

class PairInteraction : public Prior{
  double r;
public:
  PairInteraction(double cK,double cr,double cw,double ch);

  virtual double dissimilarity(const Event *e, const Event *f) const;
  virtual double beta_func(const Event *e) const {return ubnd();} ;
  virtual double gamma_func(double t) const {return 1.0;} ;
  
  int monotone() const {return 0;};
  double  range() const { return r;};
  double cond_intens( Pattern& p, Event* e ) const;
  double cond_intens_data( Pattern& p, Event* e, dmatrix *data ) const
         {cout<<"ERROR : cond_intens_data() not implemented yet !\n";
          return 0.0;
         }; 

  // printing function ...
  void printStatistics(const Pattern& p,char *name_file) const;

  double getRadius(){ return r; };
  void setRadius(double cr){ r = cr; };
  double getArea() const { return xrange()*yrange(); }

   
  // sufficient statistics ...
  int getInteractingPairs(const Pattern& p) const;
};

#endif
