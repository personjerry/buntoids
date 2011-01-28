#include "move.h"
#include "type.h"

Move::Move(int id, std::string name, int elemtype, int power, int acc, int pp) :
	_id(id), _name(name), _elemtype(elemtype), _power(power), _acc(acc), _pp(pp)
{}

int Move::getId(){
	return _id;
}

std::string Move::getName(){
	return _name;
}

int Move::getElemType(){
	return _elemtype;
}

int Move::getPower(){
	return _power;
}

int Move::getAcc(){
	return _acc;
}

int Move::getPP(){
	return _pp;
}


std::vector<Move> moves;
unsigned int movecount;

void move_init()
{
	std::ifstream f("data/moves.txt");

	if(f)
	{
		f >> movecount;
		for(unsigned int nmoves = 0; nmoves < movecount; nmoves++)
		{
			int id = nmoves;
			std::string name;
			char in = '\0';
			while(in != '.')
			{
				f >> in;
				if (in == '+')
				{
					name.push_back(' ');
				}
				else if (in != '.')
				{
					name.push_back(in);
				}
			}

			int elemtype = -1;
			int power = -1;
			int acc = -1;
			int pp = -1;

			f >> elemtype >> power >> acc >> pp;

			Move temp(id, name, elemtype, power, acc, pp);
		    moves.push_back(temp);
		}
	}
	else
	{
		std::cerr<<"Moves file not found... Abort!\n";
		exit(1);
	}
}
