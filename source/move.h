#ifndef _MOVE_
#define _MOVE_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

class Move {
public:
	Move(int id, std::string name, int elemtype, int power, int acc, int pp);

	int getId();
	std::string getName();
	int getElemType();
	int getPower();
	int getAcc();
	int getPP();
private:	
	int _id;
	std::string _name;
	int _elemtype;
	int _power;
	int _acc;
	int _pp;
};

extern std::vector<Move> moves;
extern unsigned int movecount;
extern void move_init();

#endif

