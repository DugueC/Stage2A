#include <iostream>
#include <time.h>
#include <algorithm>

#include "initialisation.h"
#include "calculs.h"

using namespace std;



int main(){
	
	// temps
	clock_t t1 = clock();



	// variables
	vector<Point> listePoints;
	Rectangle surface;
	vector<double> r;


	// on initialise les variables en fonction des paramètres
	initialisation(listePoints,surface,r);


	// on calcul les distance des points entre eux et aux bords
	calculDistances(listePoints, surface, r.back());


	// on trie les points en fonction de leur distance au bord
	sort(listePoints.begin(), listePoints.end(), greater<Point>());


	// on trie chaque liste de distance de point
	int i;
	for(i=0;i<(int)(listePoints.size());i++){
		listePoints[i].trierListe();
	}


	//calcul de K et G
	calcul(r, listePoints, surface.getAire());



	// temps
    	clock_t t2 = clock();
	float temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	cout << endl << "temps: " << temps << "sec" << endl << endl;

	return 0;
}


