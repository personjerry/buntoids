#ifndef _POKEMON_
#define _POKEMON_
#define POKECOUNT 150
#include <string>
#include "move.h"

struct Poke {
        int id;
	std::string name;
	std::string pose;
	std::string battle;
        int level;
        double health;
        double hp_per_lvl;
        double attack;
        double att_per_lvl;
        double defense;
        double def_per_lvl;
	double speca;
	double speca_per_lvl;
	double specd;
	double specd_per_lvl;
	double exp;
	int curpp[4];
        int moven[4];
};

extern std::vector<Poke> monsters;
extern Poke party[6];
extern Poke EMPTY;
extern Poke fight;
extern Poke def;
extern int pokecount;

void pokemon_init();

#endif

