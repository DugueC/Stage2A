#include "strauss.h"
#include "sbd.h"
#include <cstdlib>
#include <cstdio>


int main(int argc, char *argv[])
{
   // model
   float K_x=1.0,K_y=1.0,r=0.15,gamma=1.0,beta=30;
   
   // pattern, sufficient statistics and time;    
   char  name_sample_pattern[200]="Y_pattern.txt",
         name_statistics[200]="stat.txt",
         name_time_jumps[200]="time_jumps.txt";
         
   
   // number of iterations and lecture variable
   int nbi,nbiter=10,seed_a,seed_b,seed_c,lval; 
   
   FILE *parameters_file;
   char inutil[200];

   // reading the parameters
   if (argc!=2)
   {
    cout<<"ATTENTION : sim_cftp <parameters file> !!!\n";
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
   
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&seed_a);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&seed_b);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&seed_c);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%d",&nbiter);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&K_x);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&K_y);
 
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&beta);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&gamma);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&r);

   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%s",name_sample_pattern);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%s",name_statistics);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%s",name_time_jumps);
  
   fclose(parameters_file);
  }

   whran.setSeed(seed_a,seed_b,seed_c);

   Pattern X;
   Strauss  sm(beta,gamma,r,K_x,K_y);
   sm.report();

   CFTP algo_cftp(&sm,name_time_jumps);
   algo_cftp.report();

   for(nbi=0;nbi<nbiter;nbi++)
     {
       algo_cftp.sim(X);
       sm.printSample(X,name_sample_pattern);
       sm.printStatistics(X,name_statistics);

       algo_cftp.clean();

       cout<<"Iteration : "<<nbi<<"\n";
     }
   
}
