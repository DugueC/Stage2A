#include <algorithm>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <string.h>

#include "initialisation.h"
#include "calculs.h"
#include "FGJK.h"

using namespace std;


void FGJK(char fichier[], int tailleQuadri, vector<double> &rK, vector<double> &r, char dossier[]){

	// variables
	vector<Point> listePoints;
	vector<Quadrillage> listeQuadrillage;
	Rectangle surface;


	////// initialisation ///////

	// création de la surface
	surface = creationSurface(fichier);

	// création de la liste de points
	listePoints = creationListePoints(fichier, surface);

	
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
	calculK(rK, listePoints, surface.getAire(), dossier);

	//calcul de J
	calculFGJ(r, listePoints, listeQuadrillage, dossier);

}


vector<double> creationRdeK(char fichier0[], char dossier[]){

	string ligne, mot1, mot2;
	double x=0;
	double y=0;
	double xMax=0;
	double yMax=0;
	double xMin=999999;
	double yMin=999999;


	// ouverture fichier
	ifstream fichier1(fichier0, ios::in);

        if(!fichier1){
		cerr << "Impossible d'ouvrir le fichier contenant les points!" << endl;
        }	


	// lecture fichier par lignes
	while(getline(fichier1, ligne)){ 

		istringstream iss( ligne );

		// lecture du mot 1 + mis dans un int
		getline( iss, mot1, ' ' );
		stringstream ss1(mot1);
		ss1 >> x;
		
		// xMax
		if(x>=xMax) { xMax = x; }
		if(x<=xMin) { xMin = x; }

		// lecture du mot 2 + mis dans un int
		getline( iss, mot2, ' ' );
		stringstream ss2(mot2);
		ss2 >> y;

		// yMax
		if(y>yMax) { yMax = y; }
		if(y<yMin) { yMin = y; }

	}

        fichier1.close();	

		


	// on prend le R maximum égale à "taux"% du plus petit coté
	double rMax = ( xMax-xMin < yMax-yMin ) ? 0.25*(xMax-xMin) : 0.25*(yMax-yMin);

	//cout << "rMaxK : " << rMax << endl;

	

	// gestion fichiers
	char nom[100];
	strcpy (nom,dossier);
  	strcat (nom,"/rayonsK.txt");

	// ouverture en écriture avec effacement du fichier ouvert
        ofstream fichier(nom, ios::out | ios::trunc);  

        if(!fichier){
		cerr << "Impossible d'ouvrir le fichier pour écrire les rayons K !" << endl;
	}

	
	// on remplit la liste et le fichier de sortie
	vector<double> r;
	int i;
	double pas = rMax/512;
	for(i=0;i<513;i++){
		r.push_back(pas*i);
		fichier << pas*i << endl;
	}

	fichier.close();


	return r;
}

vector<double> creationRdeFGJ(char fichier0[], char dossier[]){

	string ligne, mot1, mot2;
	double x=0;
	double y=0;
	double xMax=0;
	double yMax=0;
	double xMin=999999;
	double yMin=999999;


	// ouverture fichier
	ifstream fichier1(fichier0, ios::in);

        if(!fichier1){
		cerr << "Impossible d'ouvrir le fichier contenant les points!" << endl;
        }	


	// lecture fichier par lignes
	int n = 0;
	while(getline(fichier1, ligne)){ 

		istringstream iss( ligne );

		// lecture du mot 1 + mis dans un int
		getline( iss, mot1, ' ' );
		stringstream ss1(mot1);
		ss1 >> x;
		
		// xMax
		if(x>=xMax) { xMax = x; }
		if(x<=xMin) { xMin = x; }

		// lecture du mot 2 + mis dans un int
		getline( iss, mot2, ' ' );
		stringstream ss2(mot2);
		ss2 >> y;

		// yMax
		if(y>yMax) { yMax = y; }
		if(y<yMin) { yMin = y; }
		
		n++;
	}

        fichier1.close();

	

	double rMax = sqrt((xMax - xMin)*(yMax - yMin)/n);
	//cout << "rMaxFGJ : " << rMax << endl << endl;


	// gestion fichiers
	char nom[100];
	strcpy (nom,dossier);
  	strcat (nom,"/rayonsFGJ.txt");

	// ouverture en écriture avec effacement du fichier ouvert
        ofstream fichier(nom, ios::out | ios::trunc);  

        if(!fichier){
		cerr << "Impossible d'ouvrir le fichier pour écrire les rayons FGJ !" << endl;
	}

	
	// on remplit la liste et le fichier de sortie
	vector<double> r;
	int i;
	double pas = rMax/512;
	for(i=0;i<513;i++){
		r.push_back(pas*i);
		fichier << pas*i << endl;
	}

	fichier.close();

	return r;
}

