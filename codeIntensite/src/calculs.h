#ifndef __CALCULS__
#define __CALCULS__

#include <string>
#include <vector>
#include "rectangle.h"
#include "position.h"

double indicatriceCarre(double u1, double u2, double c);
double indicatriceRond(double u1, double u2, double r);
double gaussienne(double u1, double u2, double sigma);
void calcul(Rectangle &surface, int m, std::vector<Position> &point, double c, double r, double sigma, std::string nomDossier);
double Romberg(int n, int m, double a, double b, double (*f)(double));
#endif
