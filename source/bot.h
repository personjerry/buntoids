#ifndef _BOT_
#define _BOT_

#include <vector>
#include <string>

class Movement {
	public:
		int pos_x,pos_y;
		bool walk[4];
		bool talking;

		Movement(int a, int b):pos_x(a),pos_y(b),walk(),talking(false) {}
		virtual ~Movement() {}

		int x();
		int y();
		void set_x(int);
		void set_y(int);
};

class Bot : public Movement {
	private:
		int type;
		int area[4];
		std::string message;
		timer anim,tmr;
		int walktime, direction;

	public:
		int frame;

		Bot(int a, int b, int c,std::string d):Movement(b,c),type(a),
		area(),message(d),anim(),tmr(),walktime((rand()%4*130)+260),
		direction(rand()%4),frame() {
			
		}

		void turn(int);
		int get_direction();
		void update();
		int kind();
		std::string& say();
};

extern std::vector<Bot> bots;

#endif

