#ifndef __CALCULS__
#define __CALCULS__

#include "rectangle.h"
#include "points.h"
#include "quadrillage.h"

void calculK(std::vector<double> &R, std::vector<Point> &point, double aire);
void calculG(std::vector<double> &R, std::vector<Point> &point, double aire);
void calculF(std::vector<double> &R, std::vector<Quadrillage> &quadri);
void calculJ();

#endif
