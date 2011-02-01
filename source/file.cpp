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

	// Save the bots' information
	f << bots.size() << '\n';
	for(size_t i=0; i<bots.size(); ++i) {
		f<<bots[i].x()<<' '<<bots[i].y()<<' '<<bots[i].get_direction()<<'\n';
	}

	// Save the party information
	for(size_t i=0; i<6; ++i) {
		if (party[i].getName() != "EMPTY")
			f << party[i].toString();
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

		int n_bots = -1;
		f >> n_bots;
		bots.reserve(n_bots);

		for(int i=0; i != n_bots; ++i) {
			f >> x >> y >> direction;
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

				int temp = -1;
				f >> temp;
				curpp.push_back(temp);
				f >> temp;
				curpp.push_back(temp);
				f >> temp;
				curpp.push_back(temp);
				f >> temp;
				curpp.push_back(temp);

				f >> temp;
				moven.push_back(temp);
				f >> temp;
				moven.push_back(temp);
				f >> temp;
				moven.push_back(temp);
				f >> temp;
				moven.push_back(temp);

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

