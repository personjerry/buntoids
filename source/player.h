#ifndef _PLAYER_
#define _PLAYER_

#include "timer.h"
#include "bot.h"

class Player : public Movement {
	private:
		int angle,move;
		timer anim;
		int frame;

	public:
		Player():Movement(0,0),angle(8),move(0),anim(),frame(0) {}

		void update();
		void stop();
		void start(int);
		int direction();
		void turn(int);
		int get_frame();
};

#endif

