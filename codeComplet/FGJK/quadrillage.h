#ifndef __QUADRILLAGE__
#define __QUADRILLAGE__

#include "points.h"

class Quadrillage : public Position{

   public:
	Quadrillage(){};
	~Quadrillage(){};
    	Quadrillage(double x, double y, double dist);
	void setDistanceVide(std::vector<Point> &points);
	double getDistanceVide();

    private:
	double distanceVide;
};

#endif
