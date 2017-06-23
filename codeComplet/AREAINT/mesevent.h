#ifndef _mesevent_
#define _mesevent_ 1

#include "event.h"

class LabelledEvent : public Event {
   int label;
 public:
   LabelledEvent( Point pc, int lc );
   int getLabel() const { return label; }
   void setLabel( int lc ) { label = lc; }
   void report() const;
};

class MarkedEvent : public Event {
   float mark;
 public:
   MarkedEvent( Point pc, double mc );
   double getMark() const { return mark; }
   void setMark( double mc ) { mark =  mc; }
   void report() const;
};

#endif
