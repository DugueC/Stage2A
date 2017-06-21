#ifndef __INI__
#define __INI__

#include "rectangle.h"
#include "points.h"
#include "quadrillage.h"


void lectureParams(std::string &fichier, int &n, double &taux, int &tailleQuadri);
Rectangle creationSurface(std::string fichier0);
std::vector<Point> creationListePoints(std::string fichier0, Rectangle &surface);
std::vector<double> creationRdeK(Rectangle &surface);
std::vector<double> creationRdeFGJ(int n, double W, int tailleR);
std::vector<Quadrillage> creationQuadrillage(Rectangle &surface, int tailleQuadri, std::vector<Point> &listePoints);

#endif
