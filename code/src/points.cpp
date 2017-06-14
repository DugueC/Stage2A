#include "points.h"

#include <iostream>
#include <algorithm>

using namespace std;


// constructeur
Point::Point(double x0, double y0, double dist) : Position(x0,y0,dist) {}


// liste distances
void Point::getListeDistance(vector<Point> &listePoints, int i, double rMax){

	int j = 0;
	double dX = 0;
	double dY = 0;
	double distance = 0;

	int n = (int)(listePoints.size());
	double rMax2 = rMax*rMax;

	for(j=0;j<n;j++){
		if(j!=i){
			// calcul distances
			dX = listePoints[j].getX() - x;
			dY = listePoints[j].getY() - y;

 			distance  = dX*dX + dY*dY ;

			// si la distance est plus petite que rMax
			if( distance <= rMax2 ){

				// ajout dans la liste du point d'indice i
				listeDistancePoints.push_back( distance );
			}

		}	
	}
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
