#include "player.h"
#include "shared.h"

void Player::update() {
	int extra=0, extra2=0;

	switch(anim.get_ticks()/130) {
		case 1:
		case 3: extra=0; extra2=0;	break;
		case 0:	extra=1; extra2=1;	break;
		case 2: extra=1; extra2=2;	break;
		default: anim.start();		break;
	}
	if(!talking) {
		switch(move) {
			case 2:		if(walk[0]) pos_x++; angle=3; frame=103+extra;		break;
			case 4:		if(walk[2]) pos_x--; angle=8; frame=108+extra;		break;
			case 8:		if(walk[3]) pos_y--; angle=0; frame=100+extra2;		break;
			case 16:	if(walk[1]) pos_y++; angle=5; frame=105+extra2;		break;
			default:
				switch(angle) {
					case 3:	frame=103;	break;
					case 8:	frame=108;	break;
					case 0:	frame=100;	break;
					case 5:	frame=105;	break;
				}
			break;
		}
	}
}

void Player::stop() {
	move=0;
	update();
}

void Player::start(int foo) {
	move=angle=foo;
}

int Player::direction() {
	switch(angle) {
		case 3:		return 2;
		case 8:		return 4;
		case 0:		return 8;
		default:	return 16;
	}
}

void Player::turn(int where) {
	bool was_talking=talking;
	talking=false;
	move=angle=where;
	std::fill_n(walk,4,false);
	update();
	stop();
	talking=was_talking;
}

int Player::get_frame() {
	return frame;
}

