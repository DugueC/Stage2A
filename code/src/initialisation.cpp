#include <iostream>
#include <sstream> 
#include <fstream>

#include "initialisation.h"

using namespace std;


void lectureParams(string &fichier, int &tailleR, double &tauxR, int &tailleQuadri){	
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
				ss1 >> tailleR;
			}
			if(i==2){
				stringstream ss2(ligne);
				ss2 >> tauxR;
			}
			if(i==3){
				stringstream ss2(ligne);
				ss2 >> tailleQuadri;
			}
			i++;
		}
	}

	params.close();

	cout << endl;
	cout << "fichier: " << fichier << endl;
	cout << "taille R: " << tailleR << endl;
	cout << "taux: " << tauxR << endl;
	cout << "quadrillage: " << tailleQuadri << " x "  << tailleQuadri << endl;
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

	return rectangle;
}

vector<Point> creationListePoints(string fichier0, Rectangle &surface){

	vector<Point> listePoints;

	string ligne, mot1, mot2;
	double x=0;
	double y=0;
	double distance=0;

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

		// calcul de la distance du point au bord de la surface
		distance = surface.distanceSurface(x,y); 

		// ajout du point à la liste
		Point p(x,y,distance);
		listePoints.push_back(p);
	}

        fichier.close();

	return listePoints;
}

vector<double> creationR(Rectangle &surface, int tailleR, double tauxR){
	
	vector<double> r;	

	double xMax = surface.getXmax();
	double xMin = surface.getXmin();
	double yMax = surface.getYmax();
	double yMin = surface.getYmin();

	// on prend le R maximum égale à "taux"% du plus petit coté
	double rMax = ( xMax-xMin < yMax-yMin ) ? tauxR*(xMax-xMin) : tauxR*(yMax-yMin);

	cout << "rMax : " << rMax << endl << endl;



	// ouverture en écriture avec effacement du fichier ouvert
        ofstream fichier("RESULTS/rayons.txt", ios::out | ios::trunc);  

        if(!fichier){
		cerr << "Impossible d'ouvrir le fichier pour écrire les rayons !" << endl;
	}

	
	// on remplit la liste et le fichier de sortie
	int i;
	double pas = rMax/(tailleR-1);
	for(i=0;i<tailleR;i++){
		r.push_back(pas*i);
		fichier << pas*i << endl;
	}

	fichier.close();


	return r;
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
			Quadrillage c(x,y,distance);

			// calcul de sa distance vide
			c.setDistanceVide(listePoints);

			// ajout du point à la liste
			listeQuadrillage.push_back(c);
		}

	}

	return listeQuadrillage;	
}

