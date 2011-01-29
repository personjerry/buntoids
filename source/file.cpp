#include "player.h"
#include "map.h"
#include "shared.h"
#include "file.h"
#include "pokemon.h"

#include <fstream>
#include <string>

void savegame() {
	std::ofstream f("data/save.txt");
	f<<Game::map<<'\n'<<player.x()<<' '<<player.y()<<' '<<player.direction()<<'\n';
	for(size_t i=0; i<bots.size(); ++i) {
		f<<bots[i].x()<<' '<<bots[i].y()<<' '<<bots[i].get_direction()<<'\n';
	}
	for(size_t i=0; i<6; ++i) {
		if (party[i].getName() != "EMPTY") {

			// FIXME: party[i].getCurpp() and party[i].getMoven() is
			// storing an int* so things will probably break when
			// loading
			f<<party[i].getId()<<party[i].getName()<<' '<<party[i].getPoseSpriteFilename()<<' '<<party[i].getBattleSpriteFilename()<<' '<<party[i].getLevel()<<' '<<party[i].getMaxHp()<<' '<<party[i].getHpPerLvl()<<' '<<party[i].getAttack()<<' '<<party[i].getAttPerLvl()<<' '<<party[i].getDefense()<<' '<<party[i].getDefPerLvl()<<' '<<party[i].getSpeca()<<' '<<party[i].getSpecaPerLvl()<<' '<<party[i].getSpecd()<<' '<<party[i].getSpecdPerLvl()<<' '<<party[i].getHealth()<<' '<<party[i].getExp()<<' ';

			std::vector<int> pokeCurpp = party[i].getCurpp();
			for (std::vector<int>::iterator k = pokeCurpp.begin(); k != pokeCurpp.end(); k++) {
			    f << *k << ' ';
			}
			
			std::vector<int> pokeMoven = party[i].getMoven();
			for (std::vector<int>::iterator k = pokeMoven.begin(); k != pokeMoven.end(); k++) {
			    f << *k << ' ';
			}
			f << '\n';
		}
		else
			f<<"N/A\n";
	}
}

void loadgame() {
	std::ifstream f("data/save.txt");
	if(!f) {
		//New game
		loadmap("map001.map");
		player.set_x(48);
		player.set_y(85);
		player.turn(8);
	}
	else {
		std::string tmp;
		int x,y,direction;

		getline(f,tmp);
		f>>x>>y>>direction;

		loadmap(tmp);
		player.set_x(x);
		player.set_y(y);
		player.turn(direction);

		for(int i=0; f>>x>>y>>direction; ++i) {
			bots.at(i).set_x(x);
			bots.at(i).set_y(y);
			bots.at(i).turn(direction);
		}

		
		for(size_t i=0; i<6; ++i) {
			int id = -1;
			f >> id;

			std::string name;
			f >> name;
			if (name != "N/A\n") {
				std::string pose;
				std::string battle;
				int level = -1;
				double maxhp = -1;
				double hp_per_lvl = -1;
				double attack = -1;
				double att_per_lvl = -1;
				double defense = -1;
				double def_per_lvl = -1;
				double speca = -1;
				double speca_per_lvl = -1;
				double specd = -1;
				double specd_per_lvl = -1;
				double health = -1;
				int exp = -1;
				std::vector<int> curpp;
				std::vector<int> moven;

				f >> pose;
				f >> battle;
				f >> level;

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
				f >> health;
				f >> exp;
				// FIXME: curpp and moven don't work yet
				// f >> curpp;
				// f >> moven;

				party[i] = Poke(id, name, pose, battle, level,
								maxhp, hp_per_lvl,
								attack, att_per_lvl,
								defense, def_per_lvl,
								speca, speca_per_lvl,
								specd, specd_per_lvl,
								health, exp, curpp, moven);
			}
		}
	}
}

