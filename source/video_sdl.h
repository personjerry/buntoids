#ifndef _VIDEO_SDL_
#define _VIDEO_SDL_

#include "img.h"

#include <string>

extern SDL_Surface *screen;

extern bool r_menu;
extern bool r_pokemenu;
extern bool r_battle;
extern bool battle;
extern int menu_choice;
extern int poke_choice;
extern int move_choice;
extern std::string menu_text;

extern int fading;

bool info_dialog(std::string&);
void dialog(Bot&);

void sdlvideo_init();
void sdlvideo_update();
void sdlvideo_kill();

#endif

