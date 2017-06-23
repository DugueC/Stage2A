#ifndef _prior_
#define _prior_ 1

#include "event.h"



class Prior {
   double K;              // local stability bound
   double width, height;  // cube in which model is defined

 protected:
   double cellvolume;    // in case of discretisation in equal cells
   int markbins;         // bins for marks as follows:
			                // 0 is the code for absence of points,
			                // other mark bins labelled 1, 2, ..., markbins
                         // for points sec, markbins = 1, the default

   double adaptedvolume ; // in case of adaped MH dynamics

 public:
   Prior( double cK, double cw, double ch );

   virtual double cond_intens( Pattern& p, Event* e ) const = 0;
   virtual double cond_intens_data( Pattern& p, Event* e, dmatrix *data ) const = 0;


   virtual int monotone() const = 0;
      // 0 for repulsive, 1 for attractive, 2 otherwise

   double ubnd() const { return K; }
   double xrange() const { return width; }
   double yrange() const { return height; }
   virtual double getArea() const { cout<<"PRIOR : getArea() !!!\n" ; return xrange()*yrange(); }

   virtual double range() const = 0;
   virtual void report() const = 0;

   virtual void printParameters( char *name_file ) const; 
      // by default the ubnd and range
   virtual void printSample( const Pattern& p, char *name_file ) const;
   virtual void printStatistics( Pattern& p, char *name_file ) const;
      // by default the total number of points
   int getTotal( const Pattern& p ) const;
   
   virtual Event *newEvent() const;
   virtual Event *newAdapted(const Event *f) const;
   virtual Event *newChangedPos (const Event *f) const;
   virtual Event *newChangedShape (const Event *f) const;

   virtual void   setVolAdapt() { adaptedvolume=width*height; }
   virtual double getVolAdapt() const { return adaptedvolume; }

   virtual double computeProposalTailored(Pattern& D, Event *f) const {return 0.0;};

   virtual bool testReadyToAdapt(Event *e) const {return true;}
   virtual int  selectEventToAdapt( Pattern& D, Pattern& A ) const;
   virtual int  countEventsToAdapt( Pattern& D, Pattern& A ) const;

   virtual bool setProperties ( Pattern& D, const Event *e) {cout<<"PRIOR : setProperties()\n";return true;}
   virtual bool deleteProperties ( Pattern& D, const Event *e) {cout<<"PRIOR : deleteProperties()\n";return true;}

   /////////////////////////////////////////////
   //
   // Parameter estimation ....
   //
   ////////////////////////////////////////////
   virtual void setParameters(dvector *psi);
   virtual void getStatistics(Pattern& p, dvector *data);

   void setK(double cK){ K = cK; }
   virtual void saveStatMatrix(const Pattern& p, dmatrix *tX, int i) ;
     

};

#endif
