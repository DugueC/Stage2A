#include "strauss.h"
#include "sbd.h"
#include "../FGJK/FGJK.h"
#include <cstdlib>
#include <cstdio>
#include <vector>

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
   // model
   float K_x=1.0,K_y=1.0,r=0.15,gamma=1.0,beta=30;
   
   // pattern, sufficient statistics and time;    
   char  name_sample_pattern[200]="Y_pattern.txt",
         name_statistics[200]="stat.txt",
	 name_folder[200]="folder";
       
         
   
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
   lval=fscanf(parameters_file,"%s",name_folder);

   fclose(parameters_file);
  }

   whran.setSeed(seed_a,seed_b,seed_c);

   Pattern X;
   Strauss  sm(beta,gamma,r,K_x,K_y);
   sm.report();

   CFTP algo_cftp(&sm);
   algo_cftp.report();



   // gestion fichiers
   char nomF[100];
   strcpy (nomF,name_folder);
   strcat (nomF,"/F.txt");
   remove(nomF);

   char nomG[100];
   strcpy (nomG,name_folder);
   strcat (nomG,"/G.txt");
   remove(nomG);

   char nomJ[100];
   strcpy (nomJ,name_folder);
   strcat (nomJ,"/J.txt");
   remove(nomJ);

   char nomK[100];
   strcpy (nomK,name_folder);
   strcat (nomK,"/J.txt");
   remove(nomK);

   mkdir(name_folder, 0777);

   // on fait la première itération en dehors pour creer les rayons
   algo_cftp.sim(X);
   sm.printSample(X,name_sample_pattern);
   sm.printStatistics(X,name_statistics);

   std::vector<double> rK = creationRdeK(name_sample_pattern, name_folder);
   std::vector<double> rFGJ = creationRdeFGJ(name_sample_pattern, name_folder);

   FGJK(name_sample_pattern, 100, rK, rFGJ, name_folder);
   cout<<"Iteration : "<<"0"<<"\n";
   algo_cftp.clean();


   for(nbi=1;nbi<nbiter;nbi++)
     {
       algo_cftp.sim(X);
       sm.printSample(X,name_sample_pattern);
       sm.printStatistics(X,name_statistics);


// ici mettre le calcul de F, G, J et K : une fonction
// qui calcule les envelopes - comme explique au tableau - v. photo
// chemin du fichier dans name_sample_pattern

       FGJK(name_sample_pattern, 100, rK, rFGJ, name_folder);



       cout<<"Iteration : "<<nbi<<"\n";

       algo_cftp.clean();

     }  
}
