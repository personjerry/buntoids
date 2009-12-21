#include "move.h"
std::vector<Move> moves;
                    std::string name;
void move_init()
{
	std::ifstream f("data/moves.txt");
        if(f)
        {
              int nmoves;
              f >> nmoves;
              for(;nmoves > 0; nmoves--)
              {
                    Move temp;
                    temp.id = nmoves;

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
                    f >> temp.type >> temp.power >> temp.acc >> temp.pp;
              }
        }
        else
        {
                std::cerr<<"Moves file not found... Abort!\n";
                exit(1);
        }
}