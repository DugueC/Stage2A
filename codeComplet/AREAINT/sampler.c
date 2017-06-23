#include "sampler.h"

Sampler::Sampler( Prior *prior )
{
   this->prior = prior;
   totalTime = 0.0;
   totalJumps = 0;

   list_file=NULL;
}

Sampler::Sampler( Prior *prior, char *name_file )
{
   this->prior = prior;
   totalTime = 0.0;
   totalJumps = 0;

   //if( (list_file=fopen(name_file,"a"))==NULL ) {
   //   cout << "ERROR : opening file " << name_file <<" \n";
   //exit(1);
   //}
}

Sampler::~Sampler()
{
   tvec.destroy();
   if(list_file!=NULL)
   	fclose(list_file);
}

void Sampler::birth( double t, Pattern& D )
{
   Event *e = prior->newEvent();
   D.add( e );
   double w = whran.uniform();
   tvec.add( new Transition( e, t, 1, w ) );
}

void Sampler::death( double t, Pattern& D )
{ 
   if( D.getSize() > 0 ) {
      Event *e = D.random_rmv();
      double w = whran.uniform();
      tvec.add( new Transition( e, t, 0, w ) );
   }
}

void Sampler::clean()
{
   tvec.destroy(); 
}

void Sampler::printTimeJumps()
{
   fprintf(list_file, "%f %d \n", getTime(), getJumps());
   fflush(list_file); 
}
