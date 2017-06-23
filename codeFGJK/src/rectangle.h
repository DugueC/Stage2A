#ifndef __RECTANGLE__
#define __RECTANGLE__

class Rectangle {

   public:
	Rectangle(){};
    	Rectangle(double x1, double x2, double y1, double y2);
	double getXmin() const;
	double getXmax() const;
	double getYmin() const;
	double getYmax() const;
	double distanceSurface(double x, double y) const;
	double getAire() const;

    private:
	double xMin;
	double xMax;
	double yMin;
	double yMax;
};

#endif
