#ifndef _POKEMON_
#define _POKEMON_
#define POKECOUNT 150
#include <string>
#include <vector>
#include "move.h"

class Poke {
public:
	// Create a constructor that receives a string and creates the
	// pokemon and create a method that converts a pokemon to a string
	// (for use on the functions in file.cpp)

	Poke(int id, std::string name, std::string pose, std::string battle, int level,
		 double maxhp, double hp_per_lvl, double attack, double att_per_lvl,
		 double defense, double def_per_lvl, double speca, double speca_per_lvl,
		 double specd, double specd_per_lvl, double health, int exp,
		 std::vector<int> curpp, std::vector<int> moven);
	~Poke();
	
	void setFullHealth();
	void causeDamage(int hp);
	bool isAlive();
	bool isDead();


	int getId();
	std::string getName();
	std::string getPoseSpriteFilename();
	std::string getBattleSpriteFilename();
	int getLevel();
	double getMaxHp();
	double getHpPerLvl();
	double getAttack();
	double getAttPerLvl();
	double getDefense();
	double getDefPerLvl();
	double getSpeca();
	double getSpecaPerLvl();
	double getSpecd();
	double getSpecdPerLvl();
	double getHealth();
	int getExp();

	// If these functions receive no argument, return the full array that is asked
	std::vector<int> getCurpp();
	std::vector<int> getMoven();

	// Otherwise return just the one asked
	int getCurpp(int move);
	int getMoven(int move);

private:
	int _id;
	std::string _name;
	std::string _pose;
	std::string _battle;
	int _level;
	double _maxhp;
	double _hp_per_lvl;
	double _attack;
	double _att_per_lvl;
	double _defense;
	double _def_per_lvl;
	double _speca;
	double _speca_per_lvl;
	double _specd;
	double _specd_per_lvl;
	double _health;
	int _exp;
	std::vector<int> _curpp;
	std::vector<int> _moven;
};

extern std::vector<Poke> monsters;
extern std::vector<Poke> party;
extern Poke EMPTY;
extern Poke *fight;
extern Poke *def;
extern int pokecount;

void pokemon_init();

#endif

