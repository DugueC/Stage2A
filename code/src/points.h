#ifndef __POINTS__
#define __POINTS__

#include <vector>

#include "position.h"

class Point : public Position{

   public:
	Point(){};
	~Point(){};
    	Point(double x, double y, double dist);
	void getListeDistance(std::vector<Point> &listePoints, int i, double rMax);
	double getDistanceDuPoint(int i);
	void trierListe();
	void printListe();
	int getSizeListe() const;

    private:
	std::vector<double> listeDistancePoints;
};


#endif
