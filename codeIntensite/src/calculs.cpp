#include "calculs.h"

#include <iostream>
#include <sstream> 
#include <fstream>
#include <math.h> 

using namespace std;
 

double indicatriceCarre(double u1, double u2, double c){
	return ( (u1 < c) && (-u1 < c) && (u2 < c) && (-u2 < c) ) ? 1 : 0;
}

double indicatriceRond(double u1, double u2, double r){
	return ( (u1*u1 + u2*u2)/4 <= r*r ) ? 1 : 0;
}

double gaussienne(double u1, double u2, double sigma){
	return exp(-(u1*u1 + u2*u2)/(2*sigma*sigma));
}

void calcul(Rectangle &surface, int m, vector<Position> &point, double c, double r, double sigma, string nomDossier){

	int i=0;
	int j=0;
	int k=0;
	double x=0;
	double y=0;
	double dX=0;
	double dY=0;
	int n = (int)(point.size());
	double pasX = (surface.getXmax()-surface.getXmin())/(m-1);
	double pasY = (surface.getYmax()-surface.getYmin())/(m-1);

	double intensiteCarre = 0;
	double intensiteRond = 0;
	double intensiteGaussienne = 0;
	double intensiteGaussienneCorr = 0;

	const double pi = 3.14159265358979323846;

	ofstream fichierCarre((nomDossier+"/Carre.txt").c_str(), ios::out | ios::trunc);  
	ofstream fichierRond((nomDossier+"/Rond.txt").c_str(), ios::out | ios::trunc);
	ofstream fichierGauss((nomDossier+"/Gauss.txt").c_str(), ios::out | ios::trunc);
	ofstream fichierGaussCorr((nomDossier+"/GaussCorr.txt").c_str(), ios::out | ios::trunc);

        if(!fichierCarre){
		cerr << "Impossible d'ouvrir le fichier pour les intensités avec Carré !" << endl;
	}
	if(!fichierRond){
		cerr << "Impossible d'ouvrir le fichier pour les intensités avec Rond !" << endl;
	}
	if(!fichierGauss){
		cerr << "Impossible d'ouvrir le fichier pour les intensités avec Gauss !" << endl;
	}
	if(!fichierGaussCorr){
		cerr << "Impossible d'ouvrir le fichier pour les intensités avec Gauss !" << endl;
	}

	for(i=0;i<m;i++){

		x = surface.getXmin() + pasX*i;

		for(j=0;j<m;j++){

			y = surface.getYmin() + pasY*j;

			intensiteCarre = 0;
			intensiteRond = 0;
			intensiteGaussienne = 0;
			intensiteGaussienneCorr = 0;

			// pour tous les points de la distribution
			for(k=0; k<n; k++){

				dX = x - point[k].getX();
				dY = y - point[k].getY();

				// le point est-il à la bonne distance?
				intensiteCarre += indicatriceCarre(dX, dY, r);
				intensiteRond += indicatriceRond(dX, dY, r);
				intensiteGaussienne += gaussienne(dX, dY, sigma);
				intensiteGaussienneCorr += gaussienne(dX, dY, sigma)/point[k].getE();
			}
			
			// écriture des calculs
			fichierCarre << intensiteCarre/(c*c) << " ";
			fichierRond << intensiteRond/(pi*r*r) << " ";
			fichierGauss << intensiteGaussienne/(2*pi*sigma) << " ";
			fichierGaussCorr << intensiteGaussienneCorr/(2*pi*sigma) << " ";
		}

		// retour à la ligne
		fichierCarre << endl;
		fichierRond << endl;
		fichierGauss << endl;
		fichierGaussCorr <<endl;
	}

	// fermeture des fichiers
	fichierCarre.close();
	fichierRond.close();
	fichierGauss.close();
	fichierGaussCorr.close();
}


double Romberg(int n, int m, double a, double b, double (*f)(double)){
	int k=0;
	double somme = 0;
	double h = 0;
	int puiss=0;
	
	if(m==0){
		if(n==0){
			return( (b-a)*(f(a)+f(b))/2 );
		}
		else{
			// calcul du 2^(n-1)
			puiss = 1;
			for(k=0;k<n-1;k++){
				puiss = 2*puiss;
			}
			
			//calcul de h
			h = (b-a)/(puiss*2);

			// calcul de la somme
			for(k=1;k<=puiss; k++){
				somme += f( a + (2*k-1)*h );
			}

			return( Romberg(n-1,0,a,b,f)/2 + h*somme );
		}
	}
	else{
		// calcul du 4^(m)
		puiss = 1;
		for(k=0;k<m;k++){
			puiss = 4*puiss;
		}

		return( (puiss*Romberg(n,m-1,a,b,f) - Romberg(n-1,m-1,a,b,f))/(puiss-1) );
	}

}
