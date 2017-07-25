#include "position.h"

using namespace std;


// constructeur
Position::Position(double x0, double y0) : x(x0), y(y0) {}

// X
double Position::getX() const {
	return x;
}
// Y
double Position::getY() const {
	return y;
}

double Position::getE() const {
	return e;
}

void Position::setE(double e0){
	e = e0;
}

