#include "calculs.h"

#include <iostream>

using namespace std;


void calculDistances(vector<Point> &listePoints, Rectangle &surface, double rMax){

	int i = 0;
	int j = 0;
	double dX = 0;
	double dY = 0;
	double distance = 0;

	int n = (int)(listePoints.size());

	for(i=0;i<n;i++){
		// distances au bords
		distance = surface.distanceSurface( listePoints[i].getX(), listePoints[i].getY() ); 
		listePoints[i].setDistBord(distance);


		// distance entre points
		for(j=0;j<n;j++){
			if(i!=j){
				// calcul distances
				dX = listePoints[j].getX() - listePoints[i].getX();
				dY = listePoints[j].getY() - listePoints[i].getY();
	
				//distance  = sqrt( dX*dX + dY*dY ) ;
 				distance  = dX*dX + dY*dY ;

				// si la distance est plus petite que rMax
				if( distance <= rMax ){
					// ajout dans la liste du point d'indice i
					listePoints[i].ajouterDistance( distance );
				}

			}	
		}	
	}
}


void calcul(vector<double> &R, vector<Point> &point, double aire){
	
	int k = 0; //indiceDeR
	int i = 0; //nbPointsDansZone
	int j = 0; //nbPointsDansBoulesDeRayonR
	double r = 0;
	double r2= 0;
	int n = (int)( point.size() );
	int nR= (int)( R.size() );

	int sommeK = 0;
	int sommeG = 0;

	// pour chaque r
	for(k=0;k<nR;k++){

		r = R[k];
		r2= r*r;
		sommeK = 0;
		sommeG = 0;
		i = 0;

		// pour chaque point
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

		//cout << "K(" << r << ") = " << sommeK*aire/((n-1)*i) << "  ( pi*r^2 = " << 3.14*r*r << " )" << endl;

		// probleme division de 2 int
		cout << "G(" << r << ") = " << 1.0*sommeG/i << "  " << sommeG << "  " << i << endl;
	}
}
