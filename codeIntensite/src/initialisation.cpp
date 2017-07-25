#include <iostream>
#include <sstream> 
#include <fstream>

#include "initialisation.h"

using namespace std;


void lectureParams(std::string &fichier, std::string &nomDossier, int &m, double &c, double &r, double &sigma){
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
				ss1 >> m;
			}
			if(i==2){
				stringstream ss2(ligne);
				ss2 >> c;
			}
			if(i==3){
				stringstream ss3(ligne);
				ss3 >> r;
			}
			if(i==4){
				stringstream ss4(ligne);
				ss4 >> sigma;
			}
			if(i==5){
				nomDossier = ligne;
			}
			i++;
		}
	}

	params.close();

	cout << endl;
	cout << "fichier: " << fichier << endl;
	cout << "dossier: " << nomDossier << endl;
	cout << "m: " << m << endl;
	cout << "c: " << c << endl;
	cout << "r: " << r << endl;
	cout << "sigma: " << sigma << endl;
	cout << endl;
}


Rectangle creationSurface(string fichier0){

	string ligne, mot1, mot2;
	double x=0;
	double y=0;
	double xMax=0;
	double yMax=0;
	double xMin=999999;
	double yMin=999999;


	// ouverture fichier
	ifstream fichier(fichier0.c_str(), ios::in);

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

	cout << "xMin : " << xMin << endl;
	cout << "xMax : " << xMax << endl;
	cout << "yMin : " << yMin << endl;
	cout << "yMax : " << yMax << endl << endl;

	Rectangle rectangle(xMin,xMax,yMin,yMax);

	//cout << "aire : " << rectangle.getAire() << endl << endl;

	return rectangle;
}

vector<Position> creationListePoints(string fichier0, Rectangle &surface){

	vector<Position> listePoints;

	string ligne, mot1, mot2;
	double x=0;
	double y=0;

	// ouverture fichier
	ifstream fichier(fichier0.c_str(), ios::in);

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

		// ajout du point à la liste
		Position p(x,y);
		listePoints.push_back(p);
	}

        fichier.close();

	return listePoints;
}

