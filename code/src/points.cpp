#include "points.h"

#include <iostream>
#include <algorithm>

using namespace std;


// constructeur
Point::Point(double x0, double y0) : x(x0), y(y0) {}

// bord
void Point::setDistBord(double d){
	distanceBord = d;
}
double Point::getDistBord() const {
	return distanceBord;
}

// X
double Point::getX() const {
	return x;
}
// Y
double Point::getY() const {
	return y;
}

// liste distances
void Point::ajouterDistance(double dist){
	listeDistancePoints.push_back(dist);
}
double Point::getDistanceDuPoint(int i){
	return listeDistancePoints[i];
}

void Point::trierListe(){
	sort(listeDistancePoints.begin(), listeDistancePoints.end());
}

void Point::printListe(){
	int i;
	for(i=0;i<(int)(listeDistancePoints.size());i++){
		cout << listeDistancePoints[i] << endl;
	}
}

int Point::getSizeListe() const {
	return listeDistancePoints.size();
}

bool Point::operator > (const Point& p) const{
	return (distanceBord > p.distanceBord);
}

//destructeur
Point::~Point(){}

