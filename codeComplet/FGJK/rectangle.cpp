#include "rectangle.h"

using namespace std;

// constructeur
Rectangle::Rectangle(double x1, double x2, double y1, double y2) : xMin(x1), xMax(x2), yMin(y1), yMax(y2) {}

double Rectangle::getXmin() const {
	return xMin;
}

double Rectangle::getXmax() const {
	return xMax;
}

double Rectangle::getYmin() const {
	return yMin;
}

double Rectangle::getYmax() const {
	return yMax;
}

double Rectangle::distanceSurface(double x, double y) const{
	double d = xMax - x;

	if(d >= (x - xMin)){
		d = x - xMin;
	}
	if(d >= (yMax - y)){
		d = yMax - y;
	}
	if(d >= (y - yMin)){
		d = y - yMin;
	}

	return d;
}

double Rectangle::getAire() const{
	return((xMax - xMin)*(yMax - yMin));
}
