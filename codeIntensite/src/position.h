#ifndef __POSITION__
#define __POSITION__

class Position{

   public:
	Position(){};
	~Position(){};
    	Position(double x, double y);
	double getX() const;
	double getY() const;
	double getE() const;
	void setE(double e0);

    protected:
	double x;
	double y;
	double e;
};


#endif
