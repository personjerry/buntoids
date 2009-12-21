#include "timer.h"

void timer::start() {
	start_ticks=SDL_GetTicks();
}

int timer::get_ticks() {
	return SDL_GetTicks()-start_ticks;
}

