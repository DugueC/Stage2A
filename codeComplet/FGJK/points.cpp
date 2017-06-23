#include "points.h"

#include <iostream>
#include <algorithm>

using namespace std;


// constructeur
Point::Point(double x0, double y0, double dist) : Position(x0,y0,dist) {}


// liste distances
void Point::getListeDistance(vector<Point> &point, int i, double rMax){

	int j = 0;
	double dX = 0;
	double dY = 0;
	double distance = 0;

	int n = (int)(point.size());
	double rMax2 = rMax*rMax;

	for(j=i+1;j<n;j++){
		// calcul distances
		dX = point[j].getX() - x;
		dY = point[j].getY() - y;

 		distance  = dX*dX + dY*dY ;

		// si la distance est plus petite que rMax on ajoute la distance
		if( distance <= rMax2 ){
			listeDistancePoints.push_back( distance );
			point[j].ajoutDistance( distance );
		}

	
	}
}

void Point::ajoutDistance(const double & d){
	listeDistancePoints.push_back( d );
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
