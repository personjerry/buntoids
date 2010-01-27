#include "map.h"
#include "shared.h"
#include "bot.h"
#include "col.h"
#include "input.h"
#include "sound.h"
#include "video_sdl.h"
#include "pokemon.h"

#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <queue>

SDL_Surface *screen;

SDL_Surface *text=NULL, *text2=NULL;
TTF_Font *font;
TTF_Font *bfont;

bool r_menu=0;
bool r_pokemenu=0;
bool r_battle=0;
bool battle=0;
int menu_choice=0;
int poke_choice=0;
int battle_choice=0;
std::string menu_text;

int fading;

std::queue<std::string> lines;

const static SDL_Color white={255,255,255,0};

bool info_dialog(std::string& say) {

	static bool split=true;
	if(split) {
		split=false;
		player.talking=true;
		player.turn(player.direction());

		std::istringstream speech(say);
		std::string final,tmp;
		while(speech>>tmp) {
			if(final.size()+tmp.size()>25) {
				lines.push(final);
				final.clear();
			}
			final+=tmp+" ";
		}

		if(lines.size() || final.size())
			lines.push(final);
	}

	KEY_E_DOWN=false;

	if(!lines.size()) {
		player.talking=false;
		split=true;

		if(text)
			SDL_FreeSurface(text);

		text=NULL;

		if(text2)
			SDL_FreeSurface(text2);

		text2=NULL;

		return true;
	}

	soundevents.push_back(new Sound(soundbuffers[0]));
	soundevents.back()->play();

	if(text)
		SDL_FreeSurface(text);

	text=TTF_RenderUTF8_Blended(font,lines.front().c_str(),white);
	lines.pop();

	if(text2) {
		SDL_FreeSurface(text2);
		text2=NULL;
	}

	if(lines.size()) {		
		text2=TTF_RenderUTF8_Blended(font,lines.front().c_str(),white);
		lines.pop();
	}

	return false;
}

void dialog(Bot& person) {
	person.turn(player.direction());
	person.talking=true;
	if(info_dialog(person.say())) {
		person.talking=false;
		soundevents.push_back(new Sound(soundbuffers[1]));
		soundevents.back()->play();
	}
}

void sdlvideo_init() {
	TTF_Init();

	font=TTF_OpenFont("data/sans.ttf",10);
	if(!font)
		error(TTF_GetError());
	
	bfont=TTF_OpenFont("data/battle.ttf",16);
	if(!bfont)
		error(TTF_GetError());

	screen=SDL_SetVideoMode(Video::width*Video::scale,Video::height*Video::scale,0,/*SDL_DOUBLEBUF|*/(Video::fullscreen?SDL_FULLSCREEN:0));
	SDL_WM_SetCaption("Pokemon","Pokemon");

	//player
	for(int i=100; i<110; ++i)
		loadimage(i);

	//Bot
	for(int i=110; i<130; ++i)
		loadimage(i);

	//GUI
	for(int i=500; i<513; ++i)
		loadimage(i);
}

void sdlvideo_update() {
	timer fps;
	fps.start();
	SDL_FillRect(screen,0,0);

	for(size_t x=0; x<Map.size(); ++x) {
		for(size_t y=0; y<Map.size(); ++y) {
			int y_padding=0;
			switch(Map[x][y]) {
				case 0: break;
				case 1070:
				case 1390:
				case 1400: y_padding=-8;
				default:
					imglist[Map[x][y]].draw(Sint16(y*16),Sint16(x*16+y_padding));
				break;
			}
		}
	}

	for(size_t i=0; i<bots.size(); ++i) {
		imglist[bots[i].frame].draw(Sint16(bots[i].x()),Sint16(bots[i].y()));
	}

	imglist[player.get_frame()].draw(Sint16(player.x()),Sint16(player.y()));

	if(r_menu) {
		imglist[504].draw_static(82,Sint16(((menu_choice+1)*17)-5));
		imglist[503].draw_static(76,0);
		imglist[105].draw_static(90,63);
	}
        else if(r_pokemenu) {
                imglist[505].draw_static(0,0);
                if(poke_choice==0) {
                        imglist[506].draw_static(4,17);
                }
                else {
                        imglist[507].draw_static(74,Sint16(5+18.4*(poke_choice-1))); 
                }
                
                imglist[508].draw_static(0,0);
                iconimg[party[0].id].draw_static(6,19);
                for (int i = 1; i < 6; i++) {
                      iconimg[party[i].id].draw_static(76,Sint16(6+18.4*(i-1))); 
                }
                
        }
        else if(r_battle) {
		
		imglist[511].draw_static(0,0);
		poseimg[fight.id].draw_static(104,0);
		battleimg[def.id].draw_static(0,42);
		
		if (battle_choice < 4)
		{
			switch(battle_choice)
			{
				case 0:
					imglist[510].draw_static(0,102);
				break;
				case 1:
					imglist[510].draw_static(0,123);				
				break;
				case 2:
					imglist[510].draw_static(42,102);
				break;
				case 3:
					imglist[510].draw_static(42,123);
				break;
				default:
					error("Battle menu error.");
				break;
			}
			imglist[509].draw_static(0,102);

		}
		else
		{
			static Image movesurf;
			static Poke *prev = NULL;
			if (prev != &def)
			{
				prev = &def;
				
				movesurf.set(new SDL_Surface(*imglist[512].get()));	
				
				SDL_Rect pos;
				pos.x = 1;
				pos.y = 0;
				
				SDL_Surface* reblit;
				
				reblit=TTF_RenderUTF8_Blended(bfont,moves[def.moven[0]].name.c_str(),white);
				SDL_BlitSurface(reblit,0,movesurf.get(),&pos);
				pos.x = 82;
				
				reblit=TTF_RenderUTF8_Blended(bfont,moves[def.moven[1]].name.c_str(),white);
				SDL_BlitSurface(reblit,0,movesurf.get(),&pos);
				pos.y = 21;
				
				reblit=TTF_RenderUTF8_Blended(bfont,moves[def.moven[2]].name.c_str(),white);
				SDL_BlitSurface(reblit,0,movesurf.get(),&pos);
				pos.x = 0;
				
				reblit=TTF_RenderUTF8_Blended(bfont,moves[def.moven[3]].name.c_str(),white);
				SDL_BlitSurface(reblit,0,movesurf.get(),&pos);
			}
			movesurf.draw_static(0,102);

		}
                
        }
        

	//Text box
	if(text || text2) {
		imglist[500].draw_static(8,96);
		imglist[lines.size()?501:502].draw_static(142,122);

		SDL_Rect pos={15,102,0,0};
		SDL_BlitSurface(text,&text->clip_rect,screen,&pos);
		pos.y=118;
		SDL_BlitSurface(text2,&text2->clip_rect,screen,&pos);
	}

	//Fading
	static int fadeval;
	if(fadeval<255 && fading==1) {
		fadeval+=12;
		if(fadeval>=250)
			fading=2;
	}
	else if(fadeval && fading==3) {
		fadeval-=12;
		if(fadeval<=0) {
			fading=0;
			player.talking=false;
		}
	}
	if(fading)
		boxRGBA(screen,0,0,160,144,0,0,0,Uint8(fadeval));

	//Scale
	if(Video::scale>1) {
		SDL_Surface *tmp=zoomSurface(screen,Video::scale,Video::scale,0);
		SDL_BlitSurface(tmp,0,screen,0);
		SDL_Flip(screen);
		SDL_FreeSurface(tmp);
	}
	else {
		SDL_Flip(screen);
	}

	if(fps.get_ticks()<1000/FRAMERATE)
		SDL_Delay((1000/FRAMERATE)-fps.get_ticks());
}

void sdlvideo_kill() {
	TTF_CloseFont(font);
	TTF_Quit();
	for(std::map<int,Image>::iterator it=imglist.begin(); it!=imglist.end(); ++it) {
		it->second.free();
	}
}

