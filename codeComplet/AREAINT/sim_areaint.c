#include "areaint.h"
#include "sbd.h"
#include "mh.h"
#include <cstdlib>
#include <cstdio>


int main(int argc, char *argv[])
{
   // model
   float K_x=1.0,K_y=1.0,r=0.1,resolution=0.01,gamma=1.0,beta=30,
          pb=0.5,pd=0.5;
   
   // pattern, sufficient statistics and time;    
   char  name_sample_pattern[200]="Y_pattern.txt",
         name_statistics[200]="stat.txt";
         
   // number of iterations and lecture variable
   int nbi,nbiter=10,time,seed_a,seed_b,seed_c,lval;
   
   FILE *parameters_file;
   char inutil[200];

   // reading the parameters
   if (argc!=2)
   {
    cout<<"ATTENTION : sim_areaint <parameters file> !!!\n";
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
   lval=fscanf(parameters_file,"%d",&time);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&pb);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&pd);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&K_x);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&K_y);
   lval=fscanf(parameters_file,"%s",inutil);
   lval=fscanf(parameters_file,"%e",&resolution);
 
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
  
  
   fclose(parameters_file);
  }

   whran.setSeed(seed_a,seed_b,seed_c);

   Pattern X;
   AreaInteraction aint(beta,gamma,K_x,K_y,r,resolution);
   aint.report();

   //StandardMH algo(&aint,time);
   AdaptedMH algo(&aint,pb,pd,0.0,0.0,0.0,time);
   algo.report();

   for(nbi=0;nbi<nbiter;nbi++)
     {
       algo.sim(X);
       aint.printSample(X,name_sample_pattern);
       aint.printStatistics(X,name_statistics);
//
// ... c'est ici que le calcul d'enveloppe doit venir ...
//

       cout<<"Iteration : "<<nbi<<"\n";
       cout<<"Area pattern :";
       
       cout<<"nt = "<<aint.getTotal(X)<<", area = "<<aint.computeTotalArea()<<endl;

     }
   
}
