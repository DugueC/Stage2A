#ifndef __POINTS__
#define __POINTS__

#include <vector>

class Point{

   public:
	Point(){};
    	Point(double x, double y);
	void setDistBord(double bord);
	double getDistBord() const;
	double getX() const;
	double getY() const;
	void ajouterDistance(double d);
	double getDistanceDuPoint(int i);
	void trierListe();
	void printListe();
	int getSizeListe() const;
	~Point();
	bool operator > (const Point& p) const;

    private:
	double x;
	double y;
	double distanceBord;
	std::vector<double> listeDistancePoints;
};


#endif
