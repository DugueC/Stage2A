#include <iostream>
#include <time.h>
#include <algorithm>

#include "initialisation.h"
#include "calculs.h"

#include <sstream> 
#include <fstream>

using namespace std;


int main(){
	
	// temps
	clock_t t_depart, t_fin, t1, t2;
	float temps;
	t_depart = clock();


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

	// écriture pour estimation d'intensité
	ofstream fichier("RESULTS/autre.txt", ios::out | ios::trunc);
	if(!fichier){
		cerr << "Impossible d'ouvrir le fichier pour écrire autre !" << endl << endl;
	}
	fichier << n << endl;
	fichier << surface.getAire() << endl;
	fichier << fichierParam << endl;
	fichier.close();


	// création des listes des rayons
	rK = creationRdeK(surface);
	r = creationRdeFGJ(n,surface.getAire(),tailleR);


	
	// création du quadrillage pour F -> long (0.5)
	t1 = clock();
	listeQuadrillage = creationQuadrillage(surface,tailleQuadri, listePoints);
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps creation quadrillage: " << temps << " sec" << endl;

	// Calculs distances entre chaque points
	t1 = clock();
	calculDistances(listePoints, rK.back());
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps calculs distance: " << temps << " sec" << endl;	




	////// Tris //////
	
	// on trie les points dans l'ordre décroissant de leur distance au bord
	sort(listePoints.begin(), listePoints.end(), greater<Point>());


	// on trie chaque liste de distance de point dans l'odre croissant
	t1 = clock();
	triDistances(listePoints);
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps tris distances: " << temps << " sec" << endl;

	// on trie les quadrillages dans l'ordre décroissant de leur distance au bord
	sort(listeQuadrillage.begin(),listeQuadrillage.end(), greater<Quadrillage>());

	


	////// Calculs des fonctions


	//calcul de K
	t1 = clock();
	calculK(rK, listePoints, surface.getAire());
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << endl << "K calculé : " << temps << " sec" << endl;

	//calcul de G
	t1 = clock();
	calculFGJ(r, listePoints, listeQuadrillage);
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "J calculé : " << temps << " sec" << endl;



	// temps
    	t_fin = clock();
	temps = (float)(t_fin-t_depart)/CLOCKS_PER_SEC;
	cout << endl << "temps total: " << temps << " sec" << endl << endl;


	return 0;
}


