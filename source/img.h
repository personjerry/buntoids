#ifndef _IMG_
#define _IMG_

#include "shared.h"

#include <SDL/SDL.h>

#include <map>

class Image {
	private:
		SDL_Surface *surface;

	public:
		Image():surface(NULL){}
		void free();
		void load(int);
		void load(std::string);
		void draw(const Sint16,const Sint16);
		void draw_static(const Sint16,const Sint16);
};

extern std::map<int,Image> imglist;
extern std::vector<Image> poseimg;
extern std::vector<Image> rposeimg;
extern std::vector<Image> battleimg;
extern std::vector<Image> iconimg;

void loadimage(const int&);

#endif

