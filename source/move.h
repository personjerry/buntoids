#ifndef _MOVE_
#define _MOVE_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

struct Move {
        int id;
	std::string name;
        int type;
        int power;
        int acc;
        int pp;
};
extern std::vector<Move> moves;
extern void move_init();

#endif

