#include "video_sdl.h"
#include "map.h"
#include "img.h"

#include <SDL/SDL_image.h>

#include <sstream>

std::map<int,Image> imglist;
std::vector<Image> poseimg;
std::vector<Image> rposeimg;
std::vector<Image> battleimg;
std::vector<Image> iconimg;

void Image::load(std::string id) {
	std::string file("data/gfx/"+id+Format::image);

	SDL_Surface *tmp=IMG_Load(file.c_str());
	if(!tmp)
		error("image \""+file+"\" not found");
        
        surface=(tmp->format->BitsPerPixel==32?SDL_DisplayFormatAlpha(tmp):SDL_DisplayFormat(tmp));

	SDL_FreeSurface(tmp);
}

void Image::load(int id) {
	std::ostringstream ss;
	ss<<id;
	std::string file("data/gfx/"+ss.str()+Format::image);

	SDL_Surface *tmp=IMG_Load(file.c_str());
	if(!tmp)
		error("image \""+file+"\" not found");

	surface=(tmp->format->BitsPerPixel==32?SDL_DisplayFormatAlpha(tmp):SDL_DisplayFormat(tmp));

	SDL_FreeSurface(tmp);
}

void Image::draw(const Sint16 x, const Sint16 y) {
	SDL_Rect pos;

	if(Map.size()>8) {
		pos.x=Sint16(x-player.x()+16*(Video::width/4)/10);
		pos.y=Sint16(y-player.y()+16*(Video::height/4)/10);
	}
	else {
		pos.x=Sint16(x+16);
		pos.y=Sint16(y+8);
	}

	SDL_BlitSurface(surface,&surface->clip_rect,screen,&pos);
}

void Image::draw_static(const Sint16 x, const Sint16 y) {
	SDL_Rect pos={x,y,0,0};
	SDL_BlitSurface(surface,&surface->clip_rect,screen,&pos);
}

void Image::free() {
	SDL_FreeSurface(surface);
	surface = NULL;
}

void loadimage(const int &id) {
	Image tmp;
	tmp.load(id);
	imglist[id]=tmp;
}

