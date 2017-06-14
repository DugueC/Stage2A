#ifndef __POSITION__
#define __POSITION__

class Position{

   public:
	Position(){};
	~Position(){};
    	Position(double x, double y, double dist);
	double getDistBord() const;
	double getX() const;
	double getY() const;
	bool operator > (const Position& p) const;

    protected:
	double x;
	double y;
	double distanceBord;

};


#endif
