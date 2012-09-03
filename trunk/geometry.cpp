#ifndef GEOMETRY_CPP_INCLUDED
#define GEOMETRY_CPP_INCLUDED

#include "geometry.h"

bool inIntBounds(int val, int bl, int bh) {
	return (val >= bl && val < bh);
}

bool inRect(int x, int y, int x0, int y0, int w, int h) {
	return (inIntBounds(x, x0, x0 + w) && inIntBounds(y, y0, y0 +w));
}

int sign(int a) {
	return (a > 0) - (a < 0);
}

int side(int x1, int y1, int x2, int y2, int x, int y) {
	return sign((y2 - y1) * (x - x1) - (y - y1) * (x2 - x1));
}

int intersectTest1(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int a = sign(side(x1, y1, x2, y2, x3, y3)),
		b = sign(side(x1, y1, x2, y2, x4, y4));

	if (!(a || b)) 
		return -1;
	if (a == b)
		return 0;
	else
		return 1; 
}

int intersectTest2(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	if ( (inIntBounds(x3, x1, x2) && inIntBounds(y3, y1, y2)) ||
			(inIntBounds(x4, x1, x2) && inIntBounds(y4, y1, y2)) )
		return true;
	else
		return false;
}

bool intersects(pointi p11, pointi p12, pointi p21, pointi p22) {
	int it11, it12, it2;
	it11 = intersectTest1(p11.x, p11.y, p12.x, p12.y, p21.x, p21.y, p22.x, p22.y);
	it12 = intersectTest1(p21.x, p21.y, p22.x, p22.y, p11.x, p11.y, p12.x, p12.y);
	bool intersect = false;
	if (it11 == 1 && it12 == 1) {
		intersect = true;        
	} else if (it11 == -1 && it12 == -1){
		if (intersectTest2(p11.x, p11.y, p12.x, p12.y, p21.x, p21.y, p22.x, p22.y)) 
			intersect = true;
	}	
	return intersect;
}
pointi PointI(int x, int y) {
	pointi res;
	res.x = x;
	res.y = y;

	return res;
}

#include <math.h>
pointi rotatePoint(pointi pc, pointi p, double angle) {
	int new_x = pc.x + (p.x - pc.x) * cos(angle) - (p.y - pc.y) * sin(angle);
	int new_y = pc.y + (p.x - pc.x) * sin(angle) - (p.y - pc.y) * cos(angle);
	return PointI(new_x, new_y);
}

double deg(double rad) {
	return rad * (180 / PI);
}

#endif

