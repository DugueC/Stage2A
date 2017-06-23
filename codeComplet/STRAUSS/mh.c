#include "mh.h"

void StandardMH::birth( double t, Pattern& D )
{
   Event *e = prior->newEvent();
   double area = prior->getArea();
   
   double w = whran.uniform();
   if( ( D.getSize() + 1 ) * whran.uniform() < 
       ( prior->cond_intens(D,e) * area ) )
   { 
      //tvec.add( new Transition( e, t, 1, w ) );
      D.add( e );
   }
   else { delete e; }
}

void StandardMH::death( double t, Pattern& D )
{
   if( D.getSize() > 0 ) {
      Event *e = D.random_rmv();
      double area = prior->getArea();

      double w = whran.uniform();
      if( ( area * prior->cond_intens( D, e) ) * whran.uniform() < 
          D.getSize() + 1 ) {
          delete e; //tvec.add( new Transition( e, t, 0, w ) );
      }
      else { D.add( e ); }
   }
}

void StandardMH::extend( Pattern& D, double& time )
{
   double t = 0.0;

   do {
      if ( t + 1.0e-7 > time ) break;

      double whr = whran.uniform();
      if( whr < 0.5 ) {
         birth( t, D );
      }
      else {
         death( t, D );
      }
      t += 1.0;
   } while (1);
}

void StandardMH::init( Pattern& D )
{
   double lambda = prior->getArea() ;
   lambda *= prior->ubnd();

   int n = whran.poisson( lambda );

   D.setSize(0);
   for( int i=0; i<n; i++) {
      Event *e = prior->newEvent();
      D.add(e);
   }
}

void StandardMH::sim( Pattern& D ) 
{
   double t = getTime();

   tvec.setPattern(D);

   extend( D, t );

   totalJumps = time;
   totalTime = t;
}


AdaptedMH :: AdaptedMH( Prior *p, double cpb, double cpd, double cpp,
      double cps,double cpba,int ctime) : Sampler(p)
{
  setTime(ctime);
  pb=cpb;
  pd=cpd;
  pp=cpp;
  ps=cps;
  pba=cpba;

}

void AdaptedMH::init( Pattern& D )
{
   double lambda = prior->getArea() ;
   lambda *= prior->ubnd();

   int n = whran.poisson( lambda );

   D.setSize(0);
   for( int i=0; i<n; i++) {
      Event *e = prior->newEvent();
      D.add(e);
   }
}

void AdaptedMH::save( Pattern& D, Pattern& E )
{
   int i,szE=E.getSize();

   if(szE>0)
   {
     D.setSize(0);
     for( i=0; i<szE; i++) {
       Event *e = prior->newEvent();
       e=E.getEvent(i);
       D.add(e);
     }
   }
}


void AdaptedMH::birth( double t, Pattern& D )
{
   double u=whran.uniform(),
          w=whran.uniform();
   int n=D.getSize();

   Event *f;

   double pt=0.0,
          area=prior->getArea(),
          p_birth,p_death,ratio;

   Pattern A;
   int na=prior->countEventsToAdapt(D,A);

   Event *e;

   if(u<pba)
   	{
        if(na>0)
        	{
          int pos=prior->selectEventToAdapt(D,A);

          e=D.getEvent(pos);
          f=prior->newAdapted(e);

          pt=prior->computeProposalTailored(D,f);
		    p_birth= (pb*pba*pt/na)+(pb*(1.0-pba)/area);
          p_death=pd/(n+1.0);

          prior->setProperties(D,f);

          ratio=p_death*prior->cond_intens(D,f)/p_birth;

          if(w < ratio)
       			D.add(f);
          else
   	  		{
         		prior->deleteProperties(D,f);
					delete f;
            }

         }
      }
   else
   	{
        f=prior->newEvent();
        if (na>0)
        	{
          pt=prior->computeProposalTailored(D,f);
		    p_birth= (pb*pba*pt/na)+(pb*(1.0-pba)/area);
         }
        else
          p_birth=(pb*(1.0-pba)/area);

        p_death=pd/(n+1.0);

        prior->setProperties(D,f);

        ratio=p_death*prior->cond_intens(D,f)/p_birth;

        if(w < ratio)
       			D.add(f);
        else
   	  		{
         		prior->deleteProperties(D,f);
					delete f;
            }
      }


}

void AdaptedMH::death( double t, Pattern& D )
{
   int n=D.getSize();

   if( n > 0 ) {

      double area = prior->getArea(),
             pt,
             p_birth,p_death,ratio,w,c_i;

      Event *e = D.random_rmv();
      c_i=prior->cond_intens(D,e);

      prior->deleteProperties(D,e);

      Pattern A;
      int na=prior->countEventsToAdapt(D,A);



      w = whran.uniform();
      if(na>=1)
      	{
          pt=prior->computeProposalTailored(D,e);
      	 p_birth=((pb*pba*pt)/na) + (pb*(1.0-pba)/area);
         }
      else
      	p_birth=pb*(1.0-pba)/area;

      p_death=pd/n;

      ratio=p_birth/(p_death*c_i);

      if (w < ratio)
      	{
          delete e;
         }
      else
         {
          prior->setProperties(D,e);
          D.add(e);
         }
   }
}


void AdaptedMH::changePos( double t, Pattern& D )
{
   if( D.getSize() > 0 ) {
      Event *e = D.random_rmv();
      double p_i=prior->cond_intens(D,e);

      prior->deleteProperties(D,e);

      Event *f = prior->newChangedPos(e);
      prior->setProperties(D,f);
      double p_f=prior->cond_intens(D,f);

      double w = whran.uniform();
      if(  (p_i* w) < p_f )
      	{
         	D.add( f );
            delete e;
      	}
      else
      	{
           prior->deleteProperties(D,f);
           prior->setProperties(D,e);
           D.add(e);
           delete f;
         }

   }
}

void AdaptedMH::changeShape( double t, Pattern& D )
{
   if( D.getSize() > 0 ) {
      Event *e = D.random_rmv();
      double p_i=prior->cond_intens(D,e);
      prior->deleteProperties(D,e);

      Event *f = prior->newChangedShape(e);
      prior->setProperties(D,f);
      double p_f=prior->cond_intens(D,f);

      double w = whran.uniform();
      if(  (p_i* w) < p_f )
      	{
         	D.add( f );
            delete e;
      	}
      else
      	{
           prior->deleteProperties(D,f);
           prior->setProperties(D,e);
           D.add(e);
           delete f;
         }

   }
}

void AdaptedMH::extend( Pattern& D, double& time )
{
   double t = 0.0;

   do {
      if ( t + 1.0e-7 > getTime() ) break;

      double whr = whran.uniform();

      if( whr < pb )
         birth( t, D );
      else
      	{
           if( whr < (pb+pd) )
             death( t, D );
           else
           	{
              if( whr < ( pb+pd+pp) )
                changePos( t, D );
              else
              	 if( whr < (pb+pd+pp+ps))
                	 changeShape( t, D );
            }

         }
     
      t += 1.0;
   } while (1);
}

void AdaptedMH::sim( Pattern& D )
{
   double t = getTime();

   tvec.setPattern(D);

   extend( D, t );

   totalJumps = time;
   totalTime = t;
}

//////////////////////////////////////////////////////////////////////////////
//
// Simulated Anealing algorithm ...
//
//////////////////////////////////////////////////////////////////////////////
AnnealingMH :: AnnealingMH( Prior *p, double cpb, double cpd, double cpp,
              double cps,double cpba,
              int ctime, double cT) :
              AdaptedMH( p, cpb, cpd, cpp, cps, cpba, ctime)
{
  T = cT ;
}


void AnnealingMH::birth( double t, Pattern& D )
{
   double u=whran.uniform(),
          w=whran.uniform();
   int n=D.getSize();

   Event *f;

   double dv=prior->getVolAdapt(),
          area=prior->getArea(),
          p_birth,p_death,ratio,pt;

   Pattern A;
   int na=prior->countEventsToAdapt(D,A);

   if(u < pba)
      {
       if(na>0)
       	{
          int pos=prior->selectEventToAdapt(D,A);
          Event *e=D.getEvent(pos);
          f=prior->newAdapted(e);

          pt=prior->computeProposalTailored(D,f);
          p_birth= (pb*pba*pt/na)+(pb*(1.0-pba)/area);
	  p_death=pd/(n+1.0);

          prior->setProperties(D,f);

          ratio=p_death*pow(prior->cond_intens(D,f),1.0/getTemperature())/p_birth;

          if(w < ratio)
       		D.add(f);
   	  else
   	   {
         	prior->deleteProperties(D,f);
                delete f;
           }
         }
      }
   else
      {

	 f=prior->newEvent();

         if (na>0)
         	{
             	  pt=prior->computeProposalTailored(D,f);
		  p_birth= (pb*pba*pt/na)+(pb*(1.0-pba)/area);
                }
         else
      		p_birth= pb*(1.0-pba)/area;

         p_death=pd/(n+1.0);

	 prior->setProperties(D,f);

	 ratio=p_death*pow(prior->cond_intens(D,f),1.0/getTemperature())/p_birth;

   	 if(w < ratio)
       		D.add(f);
         else
   	  {
         	prior->deleteProperties(D,f);
         	delete f;
          }
     }
}


void AnnealingMH::death( double t, Pattern& D )
{
   int n=D.getSize();

   if( n > 0 ) {

      double area = prior->getArea(),
             dv=prior->getVolAdapt(),
             p_birth,p_death,ratio,w,c_i,pt;

      Event *e = D.random_rmv();
      c_i=prior->cond_intens(D,e);

      prior->deleteProperties(D,e);

      Pattern A;
      int na=prior->countEventsToAdapt(D,A);



      w = whran.uniform();
      if(na>=1)
      	{
         pt=prior->computeProposalTailored(D,e);
         p_birth=(pb*pba*pt/na) + (pb*(1.0-pba)/area);
         }
      else
      	p_birth=pb*(1.0-pba)/area;

      p_death=pd/n;

      ratio=pow(1/c_i,1.0/getTemperature())*p_birth/p_death;

      if (w < ratio)
      	{
          delete e;
         }
      else
         {
          prior->setProperties(D,e);
          D.add(e);
         }
   }
}

void AnnealingMH::changePos( double t, Pattern& D )
{
   if( D.getSize() > 0 ) {
      Event *e = D.random_rmv();
      double p_i=prior->cond_intens(D,e);
      prior->deleteProperties(D,e);

      Event *f = prior->newChangedPos(e);
      prior->setProperties(D,f);
      double p_f=prior->cond_intens(D,f);

      double w = whran.uniform();
      if(   w < pow(p_f/p_i,1.0/getTemperature()))
      	{
            D.add( f );
            delete e;
      	}
      else
      	{
           prior->deleteProperties(D,f);
           prior->setProperties(D,e);
           D.add(e);
           delete f;
         }

   }
}

void AnnealingMH::changeShape( double t, Pattern& D )
{
   if( D.getSize() > 0 ) {
      Event *e = D.random_rmv();
      double p_i=prior->cond_intens(D,e);
      prior->deleteProperties(D,e);

      Event *f = prior->newChangedShape(e);
      prior->setProperties(D,f);
      double p_f=prior->cond_intens(D,f);

      double w = whran.uniform();
      if(   w < pow(p_f/p_i,1.0/getTemperature()))
      	{
            D.add( f );
            delete e;
      	}
      else
      	{
           prior->deleteProperties(D,f);
           prior->setProperties(D,e);
           D.add(e);
           delete f;
         }

   }
}
