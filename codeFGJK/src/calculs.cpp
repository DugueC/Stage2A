#include "calculs.h"

#include <iostream>
#include <sstream> 
#include <fstream>

using namespace std;


void calculDistances(vector<Point> &point, double rMax){
	int n = (int)(point.size());
	int i;
	for(i=0;i<n-1;i++){
		point[i].getListeDistance(point, i, rMax);
	}
}

void triDistances(vector<Point> &point){
	int n = (int)(point.size());
	int i;
	for(i=0;i<n;i++){
		point[i].trierListe();
	}
}

void calculK(vector<double> &r, vector<Point> &point, double aire){
	int i=0;
	int j=0;
	int k=0;
	int n = (int)( point.size() );
	int nR= (int)( r.size() );
	vector<int> histogramme(nR,0);
	vector<int> bords(nR,0);
	vector<double> r2;

	// ini r2
	for(i=0;i<nR;i++){
		r2.push_back(r[i]*r[i]);
	}

	// pour tous les points
	for(i=0;i<n;i++){
		k=0;
		for(j=0;j<nR;j++){
			// si le point est dans la zone de sureté
			if(point[i].getDistBord() >= r[j]){
				bords[j]++;
				while((k != point[i].getSizeListe()) && (point[i].getDistanceDuPoint(k)<=r2[j]) ){
					k++;
				}
				histogramme[j]+=k;
			}
			else{
				break;
			}
		}
	}


	// ouverture en écriture avec effacement du fichier ouvert
        ofstream fichierK("RESULTS/K.txt", ios::out | ios::trunc);  

        if(!fichierK){
		cerr << "Impossible d'ouvrir le fichier pour écrire K !" << endl;
	}

	// pour chaque r
	for(j=0;j<nR;j++){

		fichierK << histogramme[j]*aire/((n-1)*bords[j]) << endl;
	}


	fichierK.close();
}

void calculFGJ(vector<double> &R, vector<Point> &point, vector<Quadrillage> &quadri){
	int k = 0; //indiceDeR
	int i = 0; //nbPointsDansZone
	int j = 0;
	double r = 0;
	double r2= 0;
	int nP = (int)( point.size() );
	int nQ = (int)( quadri.size() );
	int nR= (int)( R.size() );

	int sommeG = 0;
	int sommeF = 0;
	double G = 0;
	double F = 0;

	// ouverture en écriture avec effacement du fichier ouvert
	ofstream fichierG("RESULTS/G.txt", ios::out | ios::trunc);  
	ofstream fichierF("RESULTS/F.txt", ios::out | ios::trunc);
	ofstream fichierJ("RESULTS/J.txt", ios::out | ios::trunc);

        if(!fichierG){
		cerr << "Impossible d'ouvrir le fichier pour écrire G !" << endl;
	}
        if(!fichierF){
		cerr << "Impossible d'ouvrir le fichier pour écrire F !" << endl;
	}
	if(!fichierJ){
		cerr << "Impossible d'ouvrir le fichier pour écrire J !" << endl;
	}

	// pour chaque r
	for(k=0;k<nR;k++){

		r = R[k];
		r2= r*r;
		sommeG = 0;
		sommeF = 0;
		i = 0;
		j = 0;

		// pour chaque point dans la zone de sureté
		while((i < nP) && ( point[i].getDistBord() >= r)  ){

			// G : on incrémente si le point a un voisin dans le cercle de rayon R
			if( (point[i].getSizeListe() != 0) && (point[i].getDistanceDuPoint(0) <= r2) ){
				sommeG++;
			}

			//incrémentation du nombre de point dans la zone de sureté
			i++;
		}

		// pour chaque quadrillage dans la zone de sureté
		while((j < nQ) && (quadri[j].getDistBord() > r) ){

			// F : on incrémente si le quadrillage a un voisin dans le cercle de rayon R
			if( quadri[j].getDistanceVide() <= r2 ){
				sommeF++;
			}
			
			//incrémentation du nombre de point dans la zone de sureté
			j++;
		
		}

		G = 1.0*sommeG/i;
		F = 1.0*sommeF/j;

		fichierG << G << endl;
		fichierF << F << endl;

		if(F==1){
			fichierJ << "inf" << endl;
		}
		else{
			fichierJ << (1-G)/(1-F) << endl;
		}
		
	}

	fichierG.close();
	fichierF.close();
	fichierJ.close();
}


