#include <iostream>
#include <time.h>
#include <algorithm>

#include "initialisation.h"
#include "calculs.h"

#include <sstream> 
#include <fstream>

using namespace std;


int main(){


	// variables
	vector<Point> listePoints;
	vector<Quadrillage> listeQuadrillage;
	Rectangle surface;
	vector<double> rK;
	vector<double> r;

	string fichierParam;
	int tailleR=0;
	double tauxR=0;
	int tailleQuadri=0;
	int n = 0;


	////// initialisation ///////

	// lecture des paramètres
	lectureParams(fichierParam, tailleR, tauxR, tailleQuadri);

	// création de la surface
	surface = creationSurface(fichierParam);

	// création de la liste de points
	listePoints = creationListePoints(fichierParam, surface);
	n = (int)(listePoints.size());


	// création des listes des rayons
	rK = creationRdeK(surface);
	r = creationRdeFGJ(n,surface.getAire(),tailleR);

	
	// création du quadrillage pour F
	listeQuadrillage = creationQuadrillage(surface,tailleQuadri, listePoints);

	// Calculs distances entre chaque points
	calculDistances(listePoints, rK.back());
	




	////// Tris //////
	
	// on trie les points dans l'ordre décroissant de leur distance au bord
	sort(listePoints.begin(), listePoints.end(), greater<Point>());

	// on trie chaque liste de distance de point dans l'odre croissant
	triDistances(listePoints);

	// on trie les quadrillages dans l'ordre décroissant de leur distance au bord
	sort(listeQuadrillage.begin(),listeQuadrillage.end(), greater<Quadrillage>());





	////// Calculs des fonctions


	//calcul de K
	calculK(rK, listePoints, surface.getAire());

	//calcul de G
	calculFGJ(r, listePoints, listeQuadrillage);

	return 0;
}


