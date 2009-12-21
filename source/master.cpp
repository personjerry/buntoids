#include "shared.h"
#include "map.h"
#include "pokemon.h"
#include "col.h"
#include "video_sdl.h"
#include "input.h"
#include "file.h"
#include "sound.h"
#include "master.h"
#include "move.h"

void master_init() {
	srand(convert<unsigned int>(time(NULL)));
	sdlvideo_init();
        move_init();
  	pokemon_init();
	openal_init();
	col_init();
	loadgame();
}

void master_update() {
	input_update();
	openal_update();
	col_update();
	player.update();
	for(size_t i=0; i<bots.size(); ++i) {
		bots[i].update();
	}
	sdlvideo_update();
}

void master_kill() {
	openal_kill();
	sdlvideo_kill();
	SDL_Quit();
}

