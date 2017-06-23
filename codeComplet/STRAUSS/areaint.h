#ifndef _areaint_
#define _areaint_ 1


#include "disk.h"
#include "prior.h"

///////////////////////////////////////////////////////
//
// Area Interaction point process with random disks
//
///////////////////////////////////////////////////////


class AreaInteraction : public Prior {
   double logbeta,loggamma,rmin,rmax,resolution,area_element,
          xmin,xmax,ymin,ymax,area_domain;                  // a number between 0 and 1 ...

   dmatrix grid,visited_area;



 public:
   AreaInteraction( double clb, double clg, double cw, double ch, double crmin, double crmax, double cres);

   void makeShape(Pattern& shape, const Event *e) const;
   double computeInteractionEnergy(const Pattern& shape) const;

   double computeTotalArea() const;

   double cond_intens( Pattern &p, Event* e ) const;
   double cond_intens_data( Pattern& p, Event* e, dmatrix *data ) const
         {cout<<"ERROR : cond_intens_data() not implemented yet !\n";
          return 0.0;
         };

   void report() const;

   Event *newEvent() const;
   Event *newChangedPos (const Event *f) const;
   Event *newChangedShape (const Event *f) const;

   bool setProperties ( Pattern& p, const Event *e) ;
   bool deleteProperties ( Pattern& p, const Event *e) ;

   int monotone() const { return( loggamma > 0 ); }
   double range() const { return 2.0*rmax; }
   double getArea() const { return area_domain; }

   double getLogBeta() const { return logbeta; }
   double getLogGamma() const { return loggamma; }
   void setLogBeta(double clb) { logbeta = clb; }
   void setLogGamma(double clg){ loggamma = clg; }
   double getResolution() const { return resolution; }
   double setResolution(double cres){ resolution = cres; }
   double getAreaElement()const{return area_element; }

   int getXGrid() const { return grid.getRows(); }
   int getYGrid() const { return grid.getCols(); }

   void printParameters( char *name_file ) const;
   void printSample( const Pattern& p, char *name_file ) const;
   void printStatistics( Pattern& p, char *name_file ) const;

   void printGrid( char *name_file ) const;

   void getVisitedArea(dmatrix *mat);
   void initZerosVisitedArea();
   void setVisitedArea();
   void printVisitedArea( char *name_file ) const;

   void setParameters(dvector *psi);
   void getStatistics(Pattern& p, dvector *data);




};





#endif
