#ifndef __INI__
#define __INI__

#include <string>
#include <vector>
#include "rectangle.h"
#include "position.h"

void lectureParams(std::string &fichier, std::string &nomDossier, int &m, double &c, double &r, double &sigma);
Rectangle creationSurface(std::string fichier0);
std::vector<Position> creationListePoints(std::string fichier0, Rectangle &surface);

#endif
