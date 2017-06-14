#include "position.h"

#include <iostream>
#include <algorithm>

using namespace std;


// constructeur
Position::Position(double x0, double y0, double dist) : x(x0), y(y0), distanceBord(dist) {}

// bord
double Position::getDistBord() const {
	return distanceBord;
}

// X
double Position::getX() const {
	return x;
}
// Y
double Position::getY() const {
	return y;
}

// opérateur pour les tris
bool Position::operator > (const Position& p) const{
	return (distanceBord > p.distanceBord);
}

