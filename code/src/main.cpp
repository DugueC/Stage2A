#include <iostream>
#include <time.h>
#include <algorithm>

#include "initialisation.h"
#include "calculs.h"

using namespace std;



int main(){
	
	// temps
	clock_t t1 = clock();


	// variables
	vector<Point> listePoints;
	vector<Quadrillage> listeQuadrillage;
	Rectangle surface;
	vector<double> r;

	string fichierParam;
	int tailleR=0;
	double tauxR=0;
	int tailleQuadri=0;
	int i=0;
	int n = 0;


	////// initialisation ///////

	// lecture des paramètres
	lectureParams(fichierParam, tailleR, tauxR, tailleQuadri);

	// création de la surface
	surface = creationSurface(fichierParam);

	// création de la liste de points
	listePoints = creationListePoints(fichierParam, surface);
	n = (int)(listePoints.size());

	// création de la liste des rayons
	r = creationR(surface,tailleR,tauxR);

	// création du quadrillage pour F
	listeQuadrillage = creationQuadrillage(surface,tailleQuadri, listePoints);

	// Calculs distances entre chaque points
	for(i=0;i<n;i++){
		listePoints[i].getListeDistance(listePoints, i, r.back());
	}
	


	////// Tris //////

	// on trie les points dans l'ordre décroissant de leur distance au bord
	sort(listePoints.begin(), listePoints.end(), greater<Point>());

	// on trie chaque liste de distance de point dans l'odre croissant
	for(i=0;i<n;i++){
		listePoints[i].trierListe();
	}

	// on trie les quadrillages dans l'ordre décroissant de leur distance au bord
	sort(listeQuadrillage.begin(),listeQuadrillage.end(), greater<Quadrillage>());
	



	////// Calculs des fonctions

	//calcul de K et G
	calculKG(r, listePoints, surface.getAire());
	cout << "K calculé" << endl;
	cout << "G calculé" << endl;

	// calcul de F
	calculF(r, listeQuadrillage);
	cout << "F calculé" << endl;

	// calcul de J
	calculJ();
	cout << "J calculé" << endl;



	// temps
    	clock_t t2 = clock();
	float temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << endl << "temps total: " << temps << " sec" << endl << endl;

	return 0;
}


