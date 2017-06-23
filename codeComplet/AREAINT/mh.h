#ifndef _mh_
#define _mh_ 1

#include "sampler.h"

class StandardMH : public Sampler {
   void birth( double t, Pattern& D );
   void death( double t, Pattern& D );
   void extend( Pattern& D, double& time );
   int time;
 public:
   StandardMH( Prior *p, int ctime ) :
   Sampler(p) { time = ctime; }

   void init( Pattern& D );
   void sim( Pattern& D );
   void report() const { printf("Standard Metropolis-Hastings\n"); }

   double getTime() const { return (double)time; }
   void setTime(int ctime){ time = ctime; }
};

class AdaptedMH : public Sampler {
   void birth( double t, Pattern& D );
   void death( double t, Pattern& D );
   void changePos( double t, Pattern& D );
   void changeShape( double t, Pattern& D );
   void extend( Pattern& D, double& time );

   int time;
 public:

   double pb,pd,pp,ps,pba;


   AdaptedMH( Prior *p, double cpb, double cpd, double cpp, double cps,double cpba,int ctime) ;

   void init( Pattern& D );
   void save( Pattern& D, Pattern& E );
   void sim( Pattern& D );
   void report() const { cout<<"Adapted Metropolis-Hastings" << endl;
			 cout<<"with the proposal probabilities" << endl;
			 cout<<pb<< endl;
                         cout<<pd<< endl;
                         cout<<pp<< endl;
                         cout<<ps<< endl;
			 cout<<pba<< endl;

			 cout<<"and the time for generating a sample ";
			 cout<<getTime()<< endl;

			 cout<<"Prior ..."<< endl;
			 prior->report();
			}
   double getTime() const { return (double)time; }
   void setTime(int ctime){ time = ctime; }


};

class AnnealingMH : public AdaptedMH {
   void birth( double t, Pattern& D );
   void death( double t, Pattern& D );
   void changePos( double t, Pattern& D );
   void changeShape( double t, Pattern& D );
   
   double T ;


 public:
   AnnealingMH( Prior *p, double cpb, double cpd, double cpp, double cps,double cpba,
              int ctime, double cT ) ;

   double getTemperature() const { return T; }
   void setTemperature(double cT){ T = cT; }

   void report() const { cout<<"Simulated anealing based on AdaptedMH ..." << endl;
   			 cout<<"with the proposal probabilities : " << endl;
		         cout<<pb<<"\n";
                         cout<<pd<<"\n";
                         cout<<pp<<"\n";
                         cout<<ps<<"\n";
                         cout<<pba<<"\n";

			 cout<<"the time for generating a sample : ";
			 cout<<getTime()<<"\n";

			 cout<<"and the initial temperature : ";
			 cout<<getTemperature()<<"\n";

			 cout<<"Prior ...\n";
			 prior->report();
                       }
};





#endif
