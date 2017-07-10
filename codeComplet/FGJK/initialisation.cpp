#include <iostream>
#include <sstream> 
#include <fstream>
#include <cmath>

#include "initialisation.h"

using namespace std;


Rectangle creationSurface(char fichier0[]){

	string ligne, mot1, mot2;
	double x=0;
	double y=0;
	double xMax=0;
	double yMax=0;
	double xMin=999999;
	double yMin=999999;


	// ouverture fichier
	ifstream fichier(fichier0, ios::in);

        if(!fichier){
		cerr << "Impossible d'ouvrir le fichier contenant les points!" << endl;
        }	


	// lecture fichier par lignes
	while(getline(fichier, ligne)){ 

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

        fichier.close();

	Rectangle rectangle(xMin,xMax,yMin,yMax);

	return rectangle;
}

vector<Point> creationListePoints(char fichier0[], Rectangle &surface){

	vector<Point> listePoints;

	string ligne, mot1, mot2;
	double x=0;
	double y=0;
	double distance=0;

	// ouverture fichier
	ifstream fichier(fichier0, ios::in);

        if(!fichier){
		cerr << "Impossible d'ouvrir le fichier contenant les points!" << endl;
        }	

	// lecture fichier par lignes
	while(getline(fichier, ligne)){ 

		istringstream iss( ligne );

		// lecture de x
		getline( iss, mot1, ' ' );
		stringstream ss1(mot1);
		ss1 >> x;

		// lecture de y
		getline( iss, mot2, ' ' );
		stringstream ss2(mot2);
		ss2 >> y;

		// calcul de la distance du point au bord de la surface
		distance = surface.distanceSurface(x,y); 

		// ajout du point à la liste
		Point p(x,y,distance);
		listePoints.push_back(p);
	}

        fichier.close();

	return listePoints;
}


vector<Quadrillage> creationQuadrillage(Rectangle &surface, int m, vector<Point> &listePoints){

	vector<Quadrillage> listeQuadrillage;
	
	int i=0;
	int j=0;
	double x=0;
	double y=0;
	double distance = 0;

	double pasX = (surface.getXmax()-surface.getXmin())/(m-1);
	double pasY = (surface.getYmax()-surface.getYmin())/(m-1);
	
	for(i=0;i<m;i++){

		x = surface.getXmin() + pasX*i;

		for(j=0;j<m;j++){

			y = surface.getYmin() + pasY*j;

			// calcul de la distance du point au bord de la surface
			distance = surface.distanceSurface(x,y); 

			// création du point
			Quadrillage q(x,y,distance);

			// calcul de sa distance vide
			q.setDistanceVide(listePoints);

			// ajout du point à la liste
			listeQuadrillage.push_back(q);
		}

	}

	return listeQuadrillage;	
}

