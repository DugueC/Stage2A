#include "mesevent.h"

LabelledEvent::LabelledEvent( Point pc, int lc ) :
   Event( pc )
{
   label = lc;
}

void LabelledEvent::report() const
{
   cout << "Point: " << position << "\n";
   cout << "Label: " << getLabel() << "\n";
}

MarkedEvent::MarkedEvent( Point pc, double mc ) :
   Event( pc )
{
   mark = mc; //mark = (float) mc;
}

void MarkedEvent::report() const
{
   cout << "Point: " << position << "\n";
   cout << "Label: " << getMark() << "\n";
}
