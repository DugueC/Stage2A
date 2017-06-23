#include "sampler.h"

Sampler::Sampler(Prior* prior)
{
   this->prior = prior;
   totalTime = 0.0;
   totalJumps = 0;
}

Sampler::~Sampler()
{
   tvec.destroy();
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

//void Sampler::printTimeJumps()
//{
//   fprintf(list_file, "%f %d \n", getTime(), getJumps());
//   fflush(list_file); 
//}
