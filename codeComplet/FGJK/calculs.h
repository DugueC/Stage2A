#ifndef __CALCULS__
#define __CALCULS__

#include "rectangle.h"
#include "points.h"
#include "quadrillage.h"

void calculDistances(std::vector<Point> &point, double rMax);
void triDistances(std::vector<Point> &point);
void calculK(std::vector<double> &R, std::vector<Point> &point, double aire, char dossier[]);
void calculFGJ(std::vector<double> &R, std::vector<Point> &point, std::vector<Quadrillage> &quadri, char dossier[]);

#endif
