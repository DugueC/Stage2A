#ifndef __INI__
#define __INI__

#include "rectangle.h"
#include "points.h"
#include "quadrillage.h"

Rectangle creationSurface(char fichier0[]);
std::vector<Point> creationListePoints(char fichier0[], Rectangle &surface);
std::vector<Quadrillage> creationQuadrillage(Rectangle &surface, int tailleQuadri, std::vector<Point> &listePoints);

#endif
