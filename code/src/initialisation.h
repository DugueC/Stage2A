#ifndef __INI__
#define __INI__

#include "rectangle.h"
#include "points.h"
#include "quadrillage.h"


void lectureParams(std::string &fichier, int &n, double &taux, int &tailleQuadri);
Rectangle creationSurface(std::string fichier0);
std::vector<Point> creationListePoints(std::string fichier0, Rectangle &surface);
std::vector<double> creationR(Rectangle &surface, int tailleR, double tauxR);
std::vector<Quadrillage> creationQuadrillage(Rectangle &surface, int tailleQuadri, std::vector<Point> &listePoints);

#endif
