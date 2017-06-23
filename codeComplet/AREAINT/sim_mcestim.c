#include "amp.h"
#include "sbd.h"
#include "mh.h"
#include "areaint.h"


#include <cstdlib>
#include <cstdio>

int main(int argc, char *argv[])
{

   // number of iterations
   int seed_a,seed_b,seed_c,
       time_mh_x,
       nbiter_theta,time_mh_theta,lval;

   float K_x=1.0,K_y=1.0,r=0.15,resolution,
         log_beta_x=3.0,log_gamma_x=-0.1,
         temp_1,temp_2,pb,pd;

   dvector minVal(2),maxVal(2),data_y(2),theta(2),delta(2);

   // pattern, sufficient statistics and time;
   char name_theta[200]="theta_mcestim.txt";

   FILE *parameters_file;
   char inutil[200];

   // reading the parameters
   if (argc!=2)
   {
    cout<<"ATTENTION : sim_mcestim <parameters file> !!!\n";
    exit(1);
   }

  else
  {
   parameters_file=fopen(argv[1],"rt");
   if (parameters_file==NULL)
   {
     cout<<"ERROR: Opening file "<<argv[1]<<" !\n";
     exit(1);
   }

   //
   // Seeds ...
   //
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&seed_a);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&seed_b);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&seed_c);

   //
   // Area Interaction's assumptions ...
   //
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&K_x);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&K_y);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&r);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&resolution);
   

   //
   // Process Y : observed data ...
   //
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_1);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_2);
   data_y.setVal(0,(double)temp_1);
   data_y.setVal(1,(double)temp_2);
  
   //
   // Process X : auxiliary variable and initial values for theta ...
   //
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&log_beta_x);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&log_gamma_x);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&pb);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&pd);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&time_mh_x);
   theta.setVal(0,(double)log_beta_x);
   theta.setVal(1,(double)log_gamma_x);

   //
   //  Range values for theta ...
   //
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_1);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_2);
   minVal.setVal(0,(double)temp_1);
   minVal.setVal(1,(double)temp_2);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_1);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_2);
   maxVal.setVal(0,(double)temp_1);
   maxVal.setVal(1,(double)temp_2);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_1);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&temp_2);
   delta.setVal(0,(double)temp_1);
   delta.setVal(1,(double)temp_2);

   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%s",name_theta);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&time_mh_theta);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&nbiter_theta);

   fclose(parameters_file);
  }

   whran.setSeed(seed_a,seed_b,seed_c);

   /////////////////////////////////////////
   //
   // Starting here ...
   //
   ///////////////////////////////////////////

   //
   // Sometimes we do not observe the realisation of the process Y we want to estimate, we simulate
   // it instead ...
   //
   // Strauss  sm_y(exp(log_beta_y),exp(log_gamma_y),r,K_x,K_y);
   // CFTP algo_y(&sm_y,name_tj_y);
   // Pattern Y;
   // algo_y.computeAverageSufficientStatistics(&data_y,nbiter_y)
   //


   //
   // Theta and Process X : used for estimating Y ...
   //
   AreaInteraction  aint_x(log_beta_x,log_gamma_x,K_x,K_y,r,resolution);
   AdaptedMH algo_x(&aint_x,pb,pd,0.0,0.0,0.0,time_mh_x);
   //StandardMH algo_x(&sm_x,time_mh_x);
   //AnnealingMH algo_x(&sm_x,0.5,0.5,0.0,0.0,0.0,time_mh_x,1.0,name_tj_x) ;
   Pattern X;

   AuxiliaryModelPrior amp(&aint_x,&algo_x,&theta,&minVal,&maxVal,&data_y,time_mh_theta,&delta);

   cout<<"Theta and Process X ...\n";
   algo_x.report();
   aint_x.report();
   amp.report();

 
   int nbi_theta;

   for(nbi_theta=0;nbi_theta<nbiter_theta;nbi_theta++)
    {
      algo_x.sim(X);
      amp.setDataX(X);
      amp.metropolisWalk();
      amp.updatePrior();
      amp.printTheta(name_theta);
   
      cout<<"Iteration Theta: "<<nbi_theta<<"\n";
      cout<<"Theta parameters :\n";
      amp.printTheta();

      cout<<"Pattern X : "<<"nt = "<<aint_x.getTotal(X)<<", area = "<<aint_x.computeTotalArea()<<endl;
    }


 }
