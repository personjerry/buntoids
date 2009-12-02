#include "shared.h"
#include "timer.h"
#include "bot.h"

#include <iostream>

std::vector<Bot> bots;

int Movement::x() {
	return pos_x;
}

int Movement::y() {
	return pos_y;
}

void Movement::set_x(int foo) {
	pos_x=foo;
}

void Movement::set_y(int foo) {
	pos_y=foo;
}

int Bot::kind() {
	return type;
}

void Bot::turn(int where) {
	switch(where) {
		case 2: direction=3; break;
		case 4: direction=1; break;
		case 8: direction=2; break;
		case 16: direction=0; break;
	}
	std::fill_n(walk,4,false);
	update();
}

int Bot::get_direction() {
	switch(direction) {
		case 3: return 2;
		case 1: return 4;
		case 2: return 8;
		default: return 16;
	}
}

void Bot::update() {
	if(!talking) {
		int extra=0, extra2=0;
		frame=100+(type*10);

		if(tmr.get_ticks()<walktime) {
			switch(anim.get_ticks()/130) {
				case 1:
				case 3: extra=0; extra2=0;	break;
				case 0:	extra=1; extra2=1;	break;
				case 2: extra=1; extra2=2;	break;
				default: anim.start();		break;
			}

			switch(direction) {
				case 0: if(walk[3]) { pos_y--; frame+=extra2;	}	break;
				case 1: if(walk[0]) { pos_x++; frame+=3+extra;	}	break;
				case 2: if(walk[1]) { pos_y++; frame+=5+extra2;	}	break;
				case 3: if(walk[2]) { pos_x--; frame+=8+extra;	}	break;
			}
		}
		else {
			switch(direction) {
				case 1: frame+=3;	break;
				case 2: frame+=5;	break;
				case 3: frame+=8;	break;
			}
		}

		if(tmr.get_ticks()>walktime+2000) {
			tmr.start();
			walktime=(rand()%4*130)+260;
			direction=rand()%4;
		}
		std::fill_n(walk,4,true);
	}
}

std::string& Bot::say() {
	return message;
}

