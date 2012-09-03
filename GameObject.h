#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include <vector>
#include "geometry.h"
#include "SDL/SDL.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_image.h"

// visual obj
class VisualGameObject {
public:
	static bool collides(VisualGameObject *obj1, VisualGameObject *obj2);

	VisualGameObject(const char *sprite_path, const char *vert_path);
	VisualGameObject(const char *sprite_path);
	~VisualGameObject();
	void setCenter(pointi center);
	void rotate(double angle);
	void scale(double factor);
	void reset_scale();
	void move(pointi dcoord);
	void move_to(pointi pos);
	bool collides(VisualGameObject *obj);
	void plot(SDL_Surface *screen);
	int getX() { return obj_x; }
	int getY() { return obj_y; }
	int getW() { return out_surface->w; }
	int getH() { return out_surface->h; }

	std::vector<pointi>& controlVertexVector();
private:
	double abs_angle;
	double abs_scale;
	int obj_x, obj_y;	
	pointi obj_origcenter; // const
	pointi obj_realcenter;
	SDL_Surface *obj_surface; // only scale & move
	SDL_Surface *out_surface;
	std::vector<pointi> border_vertex;
	void init(const char *sprite_path, const char *vert_path);
};

#endif

