#ifndef _disk_
#define _disk_ 1

#include "mesevent.h"

class Disk : public Event {
 protected:
   double radius;
 public:
   Disk( Point cp, double cr);

   double getRadius()  const { return radius; }
   void setRadius( double cr ){ radius=cr; };

   bool testIntersection(const Disk *ds) const;
   bool testInclusionCenter(const Disk *ds) const;

   void report() const;


};




#endif
