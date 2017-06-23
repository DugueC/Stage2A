#include "event.h"
#include "random.h"

#include <cstdio>
#include <iostream>

double dist( const Point& a, const Point& b )
{
   double dx = b.x - a.x;
   double dy = b.y - a.y;
   return sqrt( dx*dx + dy*dy );
}

ostream& operator <<( ostream & s, Point p )
{
   //return s.form("%f %f",p.x,p.y );
   return s<<p.x<<" "<<p.y;
}

void  Point :: rotate(double theta)
{
 double x_temp,y_temp,ct,st;

 ct=cos(theta);
 st=sin(theta);

 x_temp=x*ct-y*st;
 y_temp=x*st+y*ct;

 x=x_temp;
 y=y_temp;
}

void Pattern::remove( Event *e )
{
   int k = find(e);
   if ( k >= 0 ) {
      int n = getSize();
      Event *last = getEvent(n-1);
      set(k,last);
      setSize(n-1);
   }
}

void Pattern :: clean()
{
 while(getSize()>0)
 {
 	Event *e = position_rmv(0);
        delete e;
 }
}

Event* Pattern :: position_rmv(int pos)
{
   int n = getSize();
   int k = pos;
   Event *e = getEvent(k);
   Event *last = getEvent(n-1);
   set(k,last);
   setSize(n-1);
   return e;
}

Event* Pattern::random_rmv()
{
   int n = getSize();
   int k = whran.discrete_uniform(0,n-1);
   Event *e = getEvent(k);
   Event *last = getEvent(n-1);
   set(k,last);
   setSize(n-1);
   return e;
}

int Pattern::intersect( Pattern A ) const 
{
   int n = getSize();
   Event *f; 

   for( int i=0; i<n; i++ ) {
      f = (Event*) get(i); 
      if( A.find(f) > -1 ) return(1);
   }
   return(0);
}

Transition::Transition( Event *e, double t, short is_birth, double w )
{
   this->e = e;
   this->t = t;
   this->is_birth = is_birth;
   this->w = w;
   prev = NULL;
}

/*void TransitionList::destroy()
{
   Transition *tp = last;

   while ( tp != NULL ) {
      last = last->prev;

       if(T.find(tp->e)!=-1)
        {
          T.remove(tp->e);
          delete tp->e;
        }
      else
        delete tp->e;

      delete tp;

      tp = last;

      size--;
   }

   size=0;

}*/

void TransitionList::destroy()
{

   Transition *tp = last;

   while ( tp != NULL ) {
      last = last->prev;

      if(tp->is_birth==0)
			delete tp->e;

      if((tp->is_birth==1)&&(T.find(tp->e)!=-1))
			{
	 		 T.remove(tp->e);
                         delete tp->e;
			}

      delete tp;
      //size--;

      tp = last;
   }

   size=0;

}
