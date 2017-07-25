#include <iostream>
#include <time.h>

#include "initialisation.h"
#include "calculs.h"
#include <sys/stat.h>
#include <math.h> 

using namespace std;

double Romberg2(int n, int m, double a, double b, double (*f)(double,double), double y, double sigma, double xi, double yi);
double Romberg3(int n, int m, double a, double b, int n2, int m2, double a2, double b2, double (*f)(double,double,double),double sigma, double xi, double yi);
double test(double x, double y, double z);

int main(){

	// variables
	vector<Position> listePoints;
	Rectangle surface;

	string fichierParam;
	string nomDossier;
	int m = 0;
	double c = 0;
	double r = 0;
	double sigma = 0;



	// lecture des paramètres
	lectureParams(fichierParam, nomDossier, m, c, r, sigma);

	// creation du dossier
	mkdir(nomDossier.c_str(), 0777);

	// création de la surface
	surface = creationSurface(fichierParam);

	// création de la liste de points
	listePoints = creationListePoints(fichierParam, surface);

	// calculs des erreurs
	int n = (int)(listePoints.size());
	int iter = 5;
	int i = 0;
	double e = 0;
	double xMin = surface.getXmin();
	double xMax = surface.getXmax();
	double yMin = surface.getYmin();
	double yMax = surface.getYmax();

	for(i=0; i<n; i++){
		e =  Romberg3(iter, iter, yMin, yMax, iter, iter, xMin, xMax, gaussienne, sigma, listePoints[i].getX(), listePoints[i].getY());
		//cout  << "e: " << e << endl;
		listePoints[i].setE(e);
	}

	// calculs des intensités
	calcul(surface, m, listePoints, c, r, sigma, nomDossier);


	//double ccc = Romberg2(iter,iter,0,1.25,cosX2);
	//double ccc = Romberg3(iter, iter,1, 3, iter, iter, 0, 2, test, 0);

	//cout << endl << "ccc: " << ccc << endl;
	
	return 0;
}



double test(double x, double y, double z){
     return 3*x*y + y*y + z;
}

double Romberg2(int n, int m, double a, double b, double (*f)(double,double,double), double y, double sigma, double xi, double yi){
	int k=0;
	int puiss=0;
	double somme = 0;
	double h = 0;
	
	if(m==0){
		if(n==0){
	
			return( (b-a)*(f((xi-a),(yi-y),sigma)+f((xi-b),(yi-y),sigma))/2 );
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
				somme += f( (xi-(a + (2*k-1)*h)), (yi-y), sigma );
			}

			return( Romberg2(n-1,0,a,b,f,y,sigma,xi,yi)/2 + h*somme );
		}
	}
	else{
		// calcul du 4^(m)
		puiss = 1;
		for(k=0;k<m;k++){
			puiss = 4*puiss;
		}

		return( (puiss*Romberg2(n,m-1,a,b,f,y,sigma,xi,yi) - Romberg2(n-1,m-1,a,b,f,y,sigma,xi,yi))/(puiss-1) );
	}

}

double Romberg3(int n, int m, double a, double b, int n2, int m2, double a2, double b2, double (*f)(double,double,double), double sigma, double xi, double yi){
	int k=0;
	double somme = 0;
	double h = 0;
	int puiss=0;
	
	if(m==0){
		if(n==0){
			return( (b-a)*(Romberg2(n2,m2,a2,b2,f,a,sigma,xi,yi)+Romberg2(n2,m2,a2,b2,f,b,sigma,xi,yi))/2 );
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
				somme += Romberg2(n2,m2,a2,b2,f, (a + (2*k-1)*h), sigma,xi,yi );
			}

			return( Romberg3(n-1,0,a,b,n2,m2,a2,b2,f,sigma,xi,yi)/2 + h*somme );
		}
	}
	else{
		// calcul du 4^(m)
		puiss = 1;
		for(k=0;k<m;k++){
			puiss = 4*puiss;
		}

		return( (puiss*Romberg3(n,m-1,a,b,n2,m2,a2,b2,f,sigma,xi,yi) - Romberg3(n-1,m-1,a,b,n2,m2,a2,b2,f,sigma,xi,yi))/(puiss-1) );
	}

}

/*double Romberg2(int n, int m, double a, double b, double (*f)(double,double,double), double y, double sigma){
	int k=0;
	double somme = 0;
	double h = 0;
	int puiss=0;
	
	if(m==0){
		if(n==0){
			return( (b-a)*(f(a,y,sigma)+f(b,y,sigma))/2 );
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
				somme += f( (a + (2*k-1)*h), y, sigma );
			}

			return( Romberg2(n-1,0,a,b,f,y,sigma)/2 + h*somme );
		}
	}
	else{
		// calcul du 4^(m)
		puiss = 1;
		for(k=0;k<m;k++){
			puiss = 4*puiss;
		}

		return( (puiss*Romberg2(n,m-1,a,b,f,y,sigma) - Romberg2(n-1,m-1,a,b,f,y,sigma))/(puiss-1) );
	}

}

double Romberg3(int n, int m, double a, double b, int n2, int m2, double a2, double b2, double (*f)(double,double,double), double sigma){
	int k=0;
	double somme = 0;
	double h = 0;
	int puiss=0;
	
	if(m==0){
		if(n==0){
			return( (b-a)*(Romberg2(n2,m2,a2,b2,f,a,sigma)+Romberg2(n2,m2,a2,b2,f,b,sigma))/2 );
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
				somme += Romberg2(n2,m2,a2,b2,f, (a + (2*k-1)*h), sigma );
			}

			return( Romberg3(n-1,0,a,b,n2,m2,a2,b2,f,sigma)/2 + h*somme );
		}
	}
	else{
		// calcul du 4^(m)
		puiss = 1;
		for(k=0;k<m;k++){
			puiss = 4*puiss;
		}

		return( (puiss*Romberg3(n,m-1,a,b,n2,m2,a2,b2,f,sigma) - Romberg3(n-1,m-1,a,b,n2,m2,a2,b2,f,sigma))/(puiss-1) );
	}

}*/
