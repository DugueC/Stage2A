#include <iostream>
#include <sstream> 
#include <fstream>

#include "initialisation.h"

using namespace std;


void lectureParams(string &fichier, int &n, double &taux){	
	ifstream params("PARAMS/params.txt", ios::in);

	if(!params){
               cerr << "Impossible d'ouvrir le fichier de paramètres !" << endl;
        }

	string ligne;
	int i=0;

	// lecture fichier par lignes
	while(getline(params, ligne)){
		if( (ligne[0] != 0) && (ligne[0] != '/') ){
			if(i==0){
				fichier = ligne;
			}
			if(i==1){
				stringstream ss1(ligne);
				ss1 >> n;
			}
			if(i==2){
				stringstream ss2(ligne);
				ss2 >> taux;
			}
			i++;
		}
	}

	cout << endl;
	cout << "fichier: " << fichier << endl;
	cout << "n: " << n << endl;
	cout << "taux: " << taux << endl;
	cout << endl;
}

void initialisation(vector<Point> &listePoints, Rectangle &surface, vector<double> &r){

	//// lecture des paramètres
	string fichier0;
	int n;
	double taux;
	lectureParams(fichier0, n, taux);


	// ouverture fichier
	ifstream fichier(fichier0.c_str(), ios::in);

        if(!fichier){
		cerr << "Impossible d'ouvrir le fichier contenant les points!" << endl;
        }


	//// ceation de la liste de points
	
	// variables
 	string ligne, mot1, mot2;
	double x=0,y=0;
	double xMax=0, yMax=0;
	double xMin=999999, yMin=999999;

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

		// ajout du point à la liste
		Point p(x,y);
		listePoints.push_back(p);
	}

        fichier.close();



	//// création de la surface
	Rectangle rectangle(xMin,xMax,yMin,yMax);
	surface  = rectangle;



	//// création de la liste des rayons

	// on prend le R maximum égale à "taux"% du plus petit coté
	double rMax = ( xMax-xMin < yMax-yMin ) ? taux*(xMax-xMin) : taux*(yMax-yMin);

	// on remplit la liste
	int i;
	double pas = rMax/(n-1);
	for(i=0;i<n;i++){
		r.push_back(pas*i);
	}
}
