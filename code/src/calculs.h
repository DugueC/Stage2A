#ifndef __CALCULS__
#define __CALCULS__

#include "rectangle.h"
#include "points.h"

void calculDistances(std::vector<Point> &listePoints, Rectangle &surface, double rMax);
void calcul(std::vector<double> &R, std::vector<Point> &point, double aire);

#endif
