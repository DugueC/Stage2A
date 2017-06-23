#ifndef _amp_
#define _amp_ 1



#include "prior.h"
#include "sampler.h"


//////////////////////////////////////////////////////////////////////////
//
// AuxiliaryModelPrior : class for sampling the using auxiliary variables
//
//////////////////////////////////////////////////////////////////////////

class AuxiliaryModelPrior {

   Prior   *prior   ; // prior for the auxiliary variable
   Sampler *algo    ; // sampler for the auxiliary variable

   public :

   dvector theta,delta,
           minVal,maxVal,  // parameters
	   dy;             // data
   int time_theta;
	   
   Pattern x;
   dvector dx; // data auxiliary variable
           
   int size  ; // size of vector parameter

   //public:
   AuxiliaryModelPrior( Prior *p, Sampler *algo, dvector *cvalInit, dvector *cminVal, 
                        dvector *cmaxVal,dvector *cdy, int ctime_theta, dvector *cdelta);

   void proposeTheta();
   void proposeAuxiliar();
   void metropolisWalk();

   double computeRatioDensity(dvector *data, dvector *theta_final, dvector *theta_initial);
   double computeRatioProposalDensity(dvector *data_n, dvector *theta_n, dvector *data_o, dvector *theta_o);
   
   void setDataX(Pattern& p){ prior->getStatistics(p,&dx); };
   void setDataY(Pattern& p, Prior *s){ s->getStatistics(p,&dy); };

   void updatePrior(){ prior->setParameters(&theta); };
   

   void printTheta(char *name_file);
   void printTheta() { theta.printVector();  }
   void printDataX() { dx.printVector(); }
   void printDataY() { dy.printVector(); }
   
   void report() ;
};



#endif
