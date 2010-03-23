#include "shared.h"
#include "video_sdl.h"
#include "sound.h"
#include "file.h"
#include "input.h"
#include "pokemon.h"
#include "music.h"

#include <SDL/SDL.h>

bool KEY_E_DOWN=false;
bool KEY_W_DOWN=false;
bool KEY_A_DOWN=false;
bool KEY_S_DOWN=false;
bool KEY_D_DOWN=false;

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

	while(SDL_PollEvent(&event)) {
		switch(event.key.keysym.sym) {
			case SDLK_BACKQUOTE: //Cheats... only for dev testing of course.
                                r_battle=true;
                                battle=true;
                                fight = monsters[0];
                                fight.health /= 2;
				def = party[0];
				newSong("00.ogg");
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
                else if(r_battle) {
			switch(event.type) {
				case SDL_QUIT: Game::run=false; break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						
						case SDLK_w:
						case SDLK_s:
							battle_choice = (((battle_choice % 4) + 1 ) % 2 + ((battle_choice % 4) > 1) * 2)+ (battle_choice>3)*4;
						break;
						
						case SDLK_a:
						case SDLK_d:
							battle_choice = (((battle_choice % 4)+ 2) % 4) + ((battle_choice>3)*4);
						break;

						case SDLK_e:
							switch(battle_choice) {
								
							case 0:
								battle_choice = 4;
							break;
							
							case 1:
							case 3:
								menu_text = "Not implemented yet.";
								info_dialog(menu_text);
							break;
							
							case 2: // delegate choosing pokemon to pokemenu
								r_pokemenu=true;
								r_menu = false;
								menu_text = "Choose a buntoid.";
								info_dialog(menu_text);
                                                        break;
							
                                                         default: // MOVES NOT IMPLEMENTED YET!
							break;
							}
						break;

						case SDLK_SPACE:
							if ( battle_choice < 4)
							{
								r_pokemenu=true;
								r_menu = false;
								menu_text = "Choose a buntoid.";
								info_dialog(menu_text);
							}
							else
							{
								battle_choice = 0;
							}
                                                        break;
							
						default:
							break;
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

