#include "quadrillage.h"

using namespace std;

Quadrillage::Quadrillage(double x0, double y0, double dist) : Position(x0,y0,dist) {}

void Quadrillage::setDistanceVide(vector<Point> &point){
	
	int i=0;
	int n = (int)(point.size());
	double dX = 0;
	double dY = 0;
	double distance = 0;
	double dmin = 999999;

	for(i=0;i<n;i++){
		// calcul distances au carré
		dX = x - point[i].getX();
		dY = y - point[i].getY();

		distance = dX*dX + dY*dY;

		if(dmin > distance){
			dmin = distance ;
		}
	}

	distanceVide = dmin;
}

double Quadrillage::getDistanceVide(){
	return distanceVide;
}

