#include "move.h"
std::vector<Move> moves;
unsigned int movecount;

void move_init()
{
	std::ifstream f("data/moves.txt");
        if(f)
        {
              f >> movecount;
              for(int nmoves = 1;nmoves <= movecount; nmoves++)
              {
                    Move temp;
                    temp.id = nmoves;
                    std::string name;
                    char in = '\0';
                    while(in != '.')
                    {
                            f >> in;
                            if (in == '+')
                            {
                                  name.push_back(' ');
                            }
                            else
                            {
                                  name.push_back(in);
                            }
                    }
                    temp.name = name;
                    temp.id = nmoves;
                    f >> temp.type >> temp.power >> temp.acc >> temp.pp;
              }
        }
        else
        {
                std::cerr<<"Moves file not found... Abort!\n";
                exit(1);
        }
}