#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

const double PI = 3.14159265; 
struct pointi {
	int x, y;
	void operator +=(pointi val) {
		this->x += val.x;
		this->y += val.y;
	}
	void operator -=(pointi val) {
		this->x -= val.x;
		this->y -= val.y;
	}
	pointi operator -(pointi val) {
		pointi pt;
		pt.x = this->x - val.x;
		pt.y = this->y - val.y;
		return pt;
	}
	pointi operator +(pointi val) {
		pointi pt;
		pt.x = this->x + val.x;
		pt.y = this->y + val.y;
		return pt;
	}
};

extern pointi PointI(int x, int y);
extern bool inIntBounds(int val, int bl, int bh);
extern bool inRect(int x, int y, int x0, int y0, int w, int h) ;
extern bool intersects(pointi p11, pointi p12, pointi p21, pointi p22);
extern pointi rotatePoint(pointi pc, pointi p, double angle);
extern double deg(double rad);

#endif

