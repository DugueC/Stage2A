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
	int i=0;
	int n = 0;


	////// initialisation ///////
	t1 = clock();

	// lecture des paramètres
	lectureParams(fichierParam, tailleR, tauxR, tailleQuadri);

	// création de la surface
	surface = creationSurface(fichierParam);

	// création de la liste de points
	listePoints = creationListePoints(fichierParam, surface);
	n = (int)(listePoints.size());

	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout <<  "temps ini: " << temps << " sec" << endl;



	t1 = clock();
	// écriture pour estimation d'intensité
	ofstream fichier("RESULTS/autre.txt", ios::out | ios::trunc);  
	if(!fichier){
		cerr << "Impossible d'ouvrir le fichier pour écrire autre !" << endl << endl;
	}
	fichier << n << endl;
	fichier << surface.getAire() << endl;
	fichier << fichierParam << endl;
	fichier.close();
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps ecriture : " << temps << " sec" << endl;


	t1 = clock();
	// création de la liste des rayons
	rK = creationRdeK(surface);
	r = creationRdeFGJ(n,surface.getAire(),tailleR);
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps creation rayons : " << temps << " sec" << endl;

	t1 = clock();
	// création du quadrillage pour F
	listeQuadrillage = creationQuadrillage(surface,tailleQuadri, listePoints);
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps creation quadrillage: " << temps << " sec" << endl;

	t1 = clock();
	// Calculs distances entre chaque points
	for(i=0;i<n;i++){
		listePoints[i].getListeDistance(listePoints, i, rK.back());
	}
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout <<  "temps calcul distances points: " << temps << " sec" << endl;


	////// Tris //////
	t1 = clock();
	// on trie les points dans l'ordre décroissant de leur distance au bord
	sort(listePoints.begin(), listePoints.end(), greater<Point>());

	// on trie chaque liste de distance de point dans l'odre croissant
	for(i=0;i<n;i++){
		listePoints[i].trierListe();
	}

	// on trie les quadrillages dans l'ordre décroissant de leur distance au bord
	sort(listeQuadrillage.begin(),listeQuadrillage.end(), greater<Quadrillage>());
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "temps tris : " << temps << " sec" << endl << endl;	




	////// Calculs des fonctions
	//calcul de K
	t1 = clock();
	calculK(rK, listePoints, surface.getAire());
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "K calculé : " << temps << " sec" << endl;

	//calcul de G
	t1 = clock();
	calculG(r, listePoints, surface.getAire());
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "G calculé : " << temps << " sec" << endl;

	// calcul de F
	t1 = clock();
	calculF(r, listeQuadrillage);
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "F calculé : " << temps << " sec" << endl;


	// calcul de J
	t1 = clock();
	calculJ();
	t2 = clock();	
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << "J calculéJ : " << temps << " sec" << endl << endl;


	// temps
    	t_fin = clock();
	temps = (float)(t_fin-t_depart)/CLOCKS_PER_SEC;
	cout << endl << "temps total: " << temps << " sec" << endl << endl;

	return 0;
}


