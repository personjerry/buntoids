#include "shared.h"
#include "video_sdl.h"
#include "sound.h"
#include "file.h"
#include "input.h"
#include "pokemon.h"
#include "music.h"
#include "battle.h"

#include <SDL/SDL.h>

bool KEY_E_DOWN=false;
bool KEY_W_DOWN=false;
bool KEY_A_DOWN=false;
bool KEY_S_DOWN=false;
bool KEY_D_DOWN=false;

// If this is != NULL then we are inside a battle
Battle *battle_obj = NULL;

bool check_movement()
{
	bool key = false;
	
	if (KEY_W_DOWN)
	{
		if(!player.talking)
			player.start(8);
		key = true;
	}
	else if (KEY_A_DOWN)
	{
		if(!player.talking)
			player.start(4);
		key = true;
	}
	else if (KEY_S_DOWN)
	{
		if(!player.talking)
			player.start(16);
		key = true;
	}
	else if (KEY_D_DOWN)
	{
		if(!player.talking)
			player.start(2);
		key = true;
	}
	return key;
}

void input_update() {
	SDL_Event event;

	if (r_battle) {
	    // battle_input takes care of calling SDL_PollEvent
		int ret = battle_obj->battle_input();

		if (ret == 1) {
		    // Battle ended
		
			// Doing this makes the program stop responding to input (although
			// it's still possible to enter the battle screen
			//info_dialog(menu_text);
			battle = false;
			r_battle = false;
		
			// FIXME: Random music, should be the music of the area the player
			// is in.
			newSong("01.ogg");

			// Crush the battle
			delete battle_obj;
			battle_obj = NULL;
			}
		}

	else {
		while(SDL_PollEvent(&event)) {
			switch(event.key.keysym.sym) {
			case SDLK_f: //Cheats... only for dev testing of course.
				r_battle=true;
				battle=true;

				// Fight against a Bulbasaur
				battle_obj = new Battle(true, party[0], monsters[0]);
			default:
				break;
			}
			switch(event.type) {

			}
			if(r_menu) {
				switch(event.type) {
				case SDL_QUIT: Game::run=false; break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					case SDLK_w:	if(menu_choice) --menu_choice; else menu_choice=6;		break;

					case SDLK_s:	if(menu_choice<6) ++menu_choice; else menu_choice=0;	break;

					case SDLK_e:
						switch(menu_choice) {
						case 1:
							r_menu=false;
							r_pokemenu=true;
							menu_text = "Select a pokemon.";
							info_dialog(menu_text);
							soundevents.push_back(new Sound(soundbuffers[0]));
							soundevents.back()->play();
							break;
						case 4:
							savegame();
							soundevents.push_back(new Sound(soundbuffers[0]));
							soundevents.back()->play();
							r_menu=false;
							break;
						case 6: Game::run=false; break;
						}
						break;

					case SDLK_SPACE:	r_menu=false;		break;
					default:break;
					}
				}
			}
			else if(r_pokemenu) {
				switch(event.type) {
				case SDL_QUIT: Game::run=false; break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					case SDLK_w:	if(poke_choice) --poke_choice; else poke_choice=5;		break;

					case SDLK_s:	if(poke_choice<5) ++poke_choice; else poke_choice=0;	break;

					case SDLK_e:
						switch(menu_choice) {
							// "VIEW POKEMON" NOT IMPLEMENTED YET!
						default:
							break;
						}
						break;

					case SDLK_SPACE:
						r_pokemenu=false;
						if(!battle)
						{
							r_menu = true;

						}
						else
						{
							r_battle = true;
						}
						menu_text = "";
						info_dialog(menu_text);
						break;
					default:break;
					}
				}
			}
			else {
				switch(event.type) {
				case SDL_QUIT: Game::run=false; break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					case SDLK_a:	
						KEY_A_DOWN = true;
						if(!player.talking) 
							player.start(4);
						break;

					case SDLK_w:	
						KEY_W_DOWN = true;
						if(!player.talking)
							player.start(8);
						break;

					case SDLK_s:	
						KEY_S_DOWN = true;
						if(!player.talking) 
							player.start(16);	
						break;

					case SDLK_d:		
						KEY_D_DOWN = true;
						if(!player.talking) 
							player.start(2);	
						break;

					case SDLK_e:		KEY_E_DOWN=true;	break;

					case SDLK_SPACE:
						if(!player.talking) {
							player.stop();
							r_menu=true;
							soundevents.push_back(new Sound(soundbuffers[0]));
							soundevents.back()->play();
						}
						break;
					default: break;
					}
					break;

				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
					case SDLK_a:	
						KEY_A_DOWN = false;
						if(player.direction()==4 && !check_movement()) 
						{
							player.stop();
						}
						break;

					case SDLK_w:	
						KEY_W_DOWN = false;
						if(player.direction()==8 && !check_movement())
						{
							player.stop();
						}
						break;

					case SDLK_s:	
						KEY_S_DOWN = false;
						if(player.direction()==16 && !check_movement()) 
						{
							player.stop();
						}
						break;

					case SDLK_d:	
						KEY_D_DOWN = false;
						if(player.direction()==2 && !check_movement())
						{
							player.stop();	
						}
						break;

					case SDLK_e:		KEY_E_DOWN=false;							break;
					default: break;
					}
					break;
				}
			}
		}
	}
}

