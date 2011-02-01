#include "shared.h"
#include "pokemon.h"
#include "img.h"
#include "SDL/SDL_rotozoom.h"
#include <cstring>

Poke::Poke(int id, std::string name, std::string pose, std::string battle, int level,
		   double maxhp, double hp_per_lvl, double attack, double att_per_lvl,
		   double defense, double def_per_lvl, double speca, double speca_per_lvl,
		   double specd, double specd_per_lvl, double health, int exp,
		   std::vector<int> curpp, std::vector<int> moven) :
	_id(id), _name(name), _pose(pose), _battle(battle),
	_level(level), _maxhp(maxhp), _hp_per_lvl(hp_per_lvl),
	_attack(attack), _att_per_lvl(att_per_lvl),
	_defense(defense), _def_per_lvl(def_per_lvl),
	_speca(speca), _speca_per_lvl(speca_per_lvl),
	_specd(specd), _specd_per_lvl(specd_per_lvl),
	_health(health), _exp(exp), _curpp(curpp),
	_moven(moven)
{}

Poke::~Poke() {}

void Poke::setFullHealth() {
	_health = _maxhp;
}

void Poke::causeDamage(int hp) {
	_health -= hp;
}

bool Poke::isAlive() {
	return _health > 0;
}

bool Poke::isDead() {
	return _health <= 0;
}

int Poke::getId(){
	return _id;
}

std::string Poke::getName(){
	return _name;
}

std::string Poke::getPoseSpriteFilename(){
	return _pose;
}

std::string Poke::getBattleSpriteFilename(){
	return _battle;
}

int Poke::getLevel(){
	return _level;
}

double Poke::getMaxHp(){
	return _maxhp;
}

double Poke::getHpPerLvl(){
	return _hp_per_lvl;
}

double Poke::getAttack(){
	return _attack;
}

double Poke::getAttPerLvl(){
	return _att_per_lvl;
}

double Poke::getDefense(){
	return _defense;
}

double Poke::getDefPerLvl(){
	return _def_per_lvl;
}

double Poke::getSpeca(){
	return _speca;
}

double Poke::getSpecaPerLvl(){
	return _speca_per_lvl;
}

double Poke::getSpecd(){
	return _specd;
}

double Poke::getSpecdPerLvl(){
	return _specd_per_lvl;
}

double Poke::getHealth(){
	return _health;
}

int Poke::getExp(){
	return _exp;
}

std::vector<int> Poke::getCurpp(){
	return _curpp;
}

std::vector<int> Poke::getMoven(){
	return _moven;
}

int Poke::getCurpp(int move) {
	return _curpp[move];
}

int Poke::getMoven(int move) {
	return _moven[move];
}

std::vector<Poke> monsters;
std::vector<Poke> party;

// Create empty Pokemon
std::vector<int> emptymove;
Poke EMPTY(-1,"EMPTY","","",0,0,0,0,0,0,0,0,0,0,0,0,0,emptymove,emptymove);

Poke *fight;
Poke *def;
int pokecount;

void pokemon_init() {
	//do we want to make our own pokemon?
	std::ifstream f("data/poke.txt");

	if(f)
	{
		// The first line of poke.txt indicates the number of pokemons
		// defined on that file
		f >> pokecount;

		monsters.reserve(pokecount+1);    //pokemon
		poseimg.reserve(pokecount+1);     //pictures of pokemon facing, to the right
		battleimg.reserve(pokecount+1);   //pictures of from the rear
		iconimg.reserve(pokecount+1);     //small icons of the pokemon

		for(int npoke=0; npoke < pokecount; npoke++)
		{
			int id = npoke;
			std::string name;
			int level = 1;

			f >> name;

			double maxhp;
			double hp_per_lvl;
			double attack;
			double att_per_lvl;
			double defense;
			double def_per_lvl;
			double speca;
			double speca_per_lvl;
			double specd;
			double specd_per_lvl;
			int tempMoven[4];

			f >> maxhp;
			f >> hp_per_lvl;
			f >> attack;
			f >> att_per_lvl;
			f >> defense;
			f >> def_per_lvl;
			f >> speca;
			f >> speca_per_lvl;
			f >> specd;
			f >> specd_per_lvl;
			f >> tempMoven[0];
			f >> tempMoven[1];
			f >> tempMoven[2];
			f >> tempMoven[3];

			std::vector<int> moven;
			moven.push_back(tempMoven[0]);
			moven.push_back(tempMoven[1]);
			moven.push_back(tempMoven[2]);
			moven.push_back(tempMoven[3]);

			// A pokemon starts with full health
			double health = maxhp;

			std::ostringstream img1, img2, img3;
			img1<<npoke+1<<"_pose";
			img2<<npoke+1<<"_battle";
			img3<<npoke+1<<"_icon";

			std::ostringstream loc1, loc2, loc3;

			loc1 << "pokemon/" << img1.str();
			Image * temp1 = new Image;
			temp1->load(loc1.str());
			poseimg[npoke] = *temp1;
			delete(temp1);

			loc2 << "pokemon/" << img2.str();
			Image * temp2 = new Image;
			temp2->load(loc2.str());
			battleimg[npoke] = *temp2;
			delete(temp2);

			loc3<< "pokemon/" << img3.str();
			Image * temp3 = new Image;
			temp3->load(loc3.str());
			iconimg[npoke] = *temp3;
			delete(temp3);

			Poke temp(id, name, loc1.str(), loc2.str(), level,
					  maxhp, hp_per_lvl,
					  attack, att_per_lvl,
					  defense, def_per_lvl,
					  speca, speca_per_lvl,
					  specd, specd_per_lvl,
					  health, 1, moven, moven);

			monsters.push_back(temp);
		}
	}
	else
	{
		std::cerr<<"Pokemon file not found... Abort!\n";
		exit(1);
	}

	// fill party slots with empty at first.
	party.push_back(EMPTY);
	party.push_back(EMPTY);
	party.push_back(EMPTY);
	party.push_back(EMPTY);
	party.push_back(EMPTY);
	party.push_back(EMPTY);

	// testing with all bulbasaurs.
	party[0] = monsters[0];
	party[1] = monsters[0];
	party[2] = monsters[0];
	party[3] = monsters[0];
	party[4] = monsters[0];
	party[5] = monsters[0];
}

