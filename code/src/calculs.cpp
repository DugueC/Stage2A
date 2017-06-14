#include "calculs.h"

#include <iostream>
#include <sstream> 
#include <fstream>

using namespace std;

void calculKG(vector<double> &R, vector<Point> &point, double aire){
	
	int k = 0; //indiceDeR
	int i = 0; //nbPointsDansZone
	int j = 0; //nbPointsDansBoulesDeRayonR
	double r = 0;
	double r2= 0;
	int n = (int)( point.size() );
	int nR= (int)( R.size() );

	int sommeK = 0;
	int sommeG = 0;


	// ouverture en écriture avec effacement du fichier ouvert
        ofstream fichierK("RESULTS/K.txt", ios::out | ios::trunc);  
	ofstream fichierG("RESULTS/G.txt", ios::out | ios::trunc);  

        if(!fichierK){
		cerr << "Impossible d'ouvrir le fichier pour écrire K !" << endl;
	}
        if(!fichierG){
		cerr << "Impossible d'ouvrir le fichier pour écrire G !" << endl;
	}


	// pour chaque r
	for(k=0;k<nR;k++){

		r = R[k];
		r2= r*r;
		sommeK = 0;
		sommeG = 0;
		i = 0;

		// pour chaque point dans la zone de sureté
		while( ( point[i].getDistBord() >= r) && (i < n) ){

			// K : on compte le nombre de point dans le cercle de rayon R autour du point
			j=0;
			while( (j < point[i].getSizeListe()) && ( point[i].getDistanceDuPoint(j) <= r2) ){ 
				j++;
			}
			sommeK += j;

			// G : on incrémente si le point a un voisin dans le cercle de rayon R
			if( (point[i].getSizeListe() != 0) && (point[i].getDistanceDuPoint(0) <= r2) ){
				sommeG++;
			}

			//incrémentation du nombre de point dans la zone de sureté
			i++;
		}

		fichierK << sommeK*aire/((n-1)*i) << endl;
		fichierG << 1.0*sommeG/i << endl;
	}

	fichierK.close();
	fichierG.close();
}



void calculF(vector<double> &R, vector<Quadrillage> &quadri){
	
	int k = 0; //indiceDeR
	int i = 0; //nbPointsDansZone
	
	double r = 0;
	double r2= 0;
	int n = (int)( quadri.size() );
	int nR= (int)( R.size() );

	int sommeF = 0;


	ofstream fichierF("RESULTS/F.txt", ios::out | ios::trunc);  

        if(!fichierF){
		cerr << "Impossible d'ouvrir le fichier pour écrire F !" << endl;
	}


	// pour chaque r
	for(k=0;k<nR;k++){

		r = R[k];
		r2= r*r;
		sommeF = 0;
		i = 0;

		// pour chaque quadrillage dans la zone de sureté
		while((i < n) && (quadri[i].getDistBord() > r) ){

			// F : on incrémente si le quadrillage a un voisin dans le cercle de rayon R
			if( quadri[i].getDistanceVide() <= r2 ){
				sommeF++;
			}
			
			//incrémentation du nombre de point dans la zone de sureté
			i++;
		
		}

		fichierF << 1.0*sommeF/i << endl;
	}

	fichierF.close();
}

void calculJ(){
	ifstream fichierF("RESULTS/F.txt", ios::in);
	ifstream fichierG("RESULTS/G.txt", ios::in);
	ofstream fichierJ("RESULTS/J.txt", ios::out | ios::trunc);  

        
	if(!fichierF){
               cerr << "Impossible d'ouvrir le fichier F !" << endl;
        }
	if(!fichierG){
               cerr << "Impossible d'ouvrir le fichier G !" << endl;
        }
	if(!fichierJ){
		cerr << "Impossible d'ouvrir le fichier pour écrire J !" << endl;
	}


	string ligneF,ligneG;

	double F;
	double G;


        while( getline(fichierF, ligneF) && getline(fichierG, ligneG) ){
		
		stringstream ssF(ligneF);
		ssF >> F;

		stringstream ssG(ligneG);
		ssG >> G;

		if(F==1){
			fichierJ << "inf" << endl;
		}
		else{
			fichierJ << (1-G)/(1-F) << endl;
		}
        }

	fichierF.close();
	fichierG.close();
	fichierJ.close();
	

}
