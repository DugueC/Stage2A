#ifndef _event_
#define _event_ 1

#include "vector.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "random.h"
#include "matcl.h"

using namespace std ;

class Point {
 public:
   double x,y;
   Point() { }
   Point( double x, double y ) { this->x = x; this->y = y; }

   void set(double cx, double cy){ x = cx; y = cy; }
   void  rotate(double theta);
   double norm() const { return sqrt( x*x + y*y ); }


};

double dist( const Point&, const Point& );

inline
Point operator - ( const Point& a ) { return Point( -a.x, -a.y ); }

inline
Point operator + ( const Point& a, const Point& b )
{
   return Point( a.x+b.x, a.y+b.y );
}

inline
Point operator - (const Point& a, const Point& b )
{
   return Point( a.x-b.x , a.y-b.y );
}

inline
bool operator == ( const Point& a, const Point& b ) 
{
   return ( a.x == b.x ) && ( a.y == b.y ); 
}

inline
bool operator != ( const Point& a, const Point& b ) 
{
   return ( a.x != b.x ) || ( a.y != b.y ); 
}

ostream & operator << ( ostream &, Point );

class Event {
 protected:
   Point position;
 public:
   Event( Point p ) { position = p; }
   // Event() { }

   double getX() const { return position.x; };
   double getY() const { return position.y; };
   Point getPosition() const  { return position; }

   virtual void setPosition( Point p ) { position = p; }

   bool inUnitSquare(){ return (position.x>0.25)&&(position.x<1.25)&&(position.y>0.25)&&(position.y<1.25); }

   double getDistance( const Event *e ) const
      { return ::dist( position, e->position ); }

   virtual void report() const 
      { cout << "Point: " << position << "\n"; }
};

typedef Event *EventPointer;

class Pattern: public Vector {
 public:
   EventPointer getEvent( int i ) const
      { return (EventPointer) get(i); }
   void remove( EventPointer e );
   void clean();
   EventPointer random_rmv();
   EventPointer position_rmv(int pos);
   int intersect( Pattern A ) const;

};

class TransitionList;

class Transition {
 private:
   Transition *prev;
 public:
   Event *e;	// event that is deleted or added
   double t;	// transition time
   double w;	// storage of reusable random number
   short is_birth; // forward transition indicator

   Transition( Event *e, double t, short is_birth, double w );
   Transition *getPrevious() { return prev; }
   friend class TransitionList;
};

class TransitionList {
 private:
   Transition* last;
   int size;
   Pattern T;
 public:
   TransitionList() { last = NULL; size = 0; }
   void add( Transition *t ) { t->prev = last; last = t; size++; }
   Transition* getLast() const { return last; }
   int getSize() const { return size; }
   void destroy();

   void setPattern(Pattern &cT){T=cT;}

};


// endif _event_
#endif
