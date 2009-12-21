#ifndef _TIMER_
#define _TIMER_

#include <SDL/SDL.h>

class timer {
	private:
		int start_ticks;

    public:
		timer():start_ticks(0){}

		void start();
		int get_ticks();
};

#endif

