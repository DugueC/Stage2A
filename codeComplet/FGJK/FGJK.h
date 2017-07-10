#ifndef __FGJK__
#define __FGJK__

#include <vector>

void FGJK(char fichier[], int tailleQuadri, std::vector<double> &rK, std::vector<double> &r, char dossier[]);
std::vector<double> creationRdeK(char fichier[], char dossier[]);
std::vector<double> creationRdeFGJ(char fichier[], char dossier[]);

#endif
