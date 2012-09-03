#include "GameObject.h"
#include <fstream>

using namespace std;

bool VisualGameObject::collides(VisualGameObject *obj1, VisualGameObject *obj2) {
	if (
		inRect(obj1->getX(), obj1->getY(), obj2->getX(), obj2->getY(), obj2->getW(), obj2->getH()) ||
		inRect(obj1->getX() + obj1->getW(), obj1->getY(), obj2->getX(), obj2->getY(), obj2->getW(), obj2->getH()) ||
		inRect(obj1->getX(), obj1->getY() + obj1->getH(), obj2->getX(), obj2->getY(), obj2->getW(), obj2->getH()) ||
		inRect(obj1->getX() + obj1->getW(), obj1->getY() + obj1->getH(), obj2->getX(), obj2->getY(), obj2->getW(), obj2->getH())
	) {
		vector<pointi> vert1 = obj1->controlVertexVector();
		vector<pointi> vert2 = obj2->controlVertexVector();
		for (int i = 0; i < vert1.size() - 2; ++i) {
			for (int j = 0; j < vert2.size() - 2; ++j) {
				if (intersects(vert1[i], vert1[i + 1], vert2[j], vert2[j + 1])) 
					return true;				
			}
		}
	} else
		return false;
}

bool VisualGameObject::collides(VisualGameObject *obj) {
	return VisualGameObject::collides(this, obj);
}

void VisualGameObject::init(const char *sprite_path, const char *vert_path) {
	if (vert_path) {
		ifstream vstream;
		vstream.open(vert_path);
		while (!vstream.eof()) {
			int vx, vy;
			vstream >> vx >> vy;
			border_vertex.push_back(PointI(vx, vy));
		}
		border_vertex.push_back(border_vertex.front());
		vstream.close();
	}

	obj_surface = NULL;
	SDL_RWops *rwop;
	rwop = SDL_RWFromFile(sprite_path, "rb");
	obj_surface = IMG_LoadPNG_RW(rwop);
	if(!obj_surface) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	obj_x = obj_y = 0;
	obj_origcenter = obj_realcenter = PointI(0, 0);
	abs_angle = .0;
	abs_scale = 1.0;
}


VisualGameObject::VisualGameObject(const char *sprite_path, const char *vert_path) {
	init(sprite_path, vert_path);
}

VisualGameObject::VisualGameObject(const char *sprite_path) {
	init(sprite_path, NULL);
	border_vertex.push_back(PointI(0, 0));
	border_vertex.push_back(PointI(0, obj_surface->h));
	border_vertex.push_back(PointI(obj_surface->w, obj_surface->h));
	border_vertex.push_back(PointI(obj_surface->w, 0));
	border_vertex.push_back(PointI(0, 0));
}

VisualGameObject::~VisualGameObject() {
	SDL_FreeSurface(obj_surface);
}

vector<pointi>& VisualGameObject::controlVertexVector() {
	return border_vertex;
}

void VisualGameObject::setCenter(pointi center) {
	obj_origcenter = obj_realcenter = center;
}
#include <iostream>
using namespace std;
void VisualGameObject::plot(SDL_Surface *screen) {
	SDL_Rect plot_pos;
	plot_pos.x = obj_x;
	plot_pos.y = obj_y;
	//cout << "width = " << out_surface->width;
	SDL_BlitSurface(out_surface, NULL, screen, &plot_pos);
	SDL_Flip(screen);
}

void VisualGameObject::move(pointi dcoord) {
	obj_x += dcoord.x;
	obj_y += dcoord.y;
	obj_realcenter.x += dcoord.x;
	obj_realcenter.y += dcoord.y;
}

void VisualGameObject::move_to(pointi pos) {
	int dx = pos.x - obj_realcenter.x;
	int dy = pos.y - obj_realcenter.y;
	obj_realcenter = pos;
	obj_x += dx;
	obj_y += dy;
	cout << obj_realcenter.x << " " << obj_realcenter.y << endl;
	cout << obj_x << " " << obj_y << endl;
}

void VisualGameObject::scale(double factor) {
	obj_x = obj_realcenter.x + (obj_x - obj_realcenter.x) * factor;
	obj_y = obj_realcenter.y + (obj_y - obj_realcenter.y) * factor; 
	SDL_Surface *new_surf = zoomSurface(obj_surface, factor, factor, SMOOTHING_ON);
	SDL_FreeSurface(obj_surface);
	obj_surface = new_surf; 
	out_surface = obj_surface;
	abs_scale *= factor;
}

void VisualGameObject::reset_scale() {
	this->scale(1.0 / abs_scale);
	abs_scale = 1;
}

void VisualGameObject::rotate(double angle) {
	abs_angle += angle;
	out_surface = rotozoomSurface(obj_surface, abs_angle, 1, SMOOTHING_OFF);
	pointi new_realcenter = rotatePoint(PointI(obj_x, obj_y), obj_realcenter, angle);
	pointi delta_center = obj_realcenter - new_realcenter;
	pointi cornerpoint = PointI(obj_x - (double)obj_surface->h * sin(angle), obj_y);
	cornerpoint += delta_center;
	obj_x = cornerpoint.x;
	obj_y = cornerpoint.y;
}

