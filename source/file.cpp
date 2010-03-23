#include "player.h"
#include "map.h"
#include "shared.h"
#include "file.h"
#include "pokemon.h"

#include <fstream>

void savegame() {
	std::ofstream f("data/save.txt");
	f<<Game::map<<'\n'<<player.x()<<' '<<player.y()<<' '<<player.direction()<<'\n';
	for(size_t i=0; i<bots.size(); ++i) {
		f<<bots[i].x()<<' '<<bots[i].y()<<' '<<bots[i].get_direction()<<'\n';
	}
        for(size_t i=0; i<6; ++i) {
                if (party[i].name != "EMPTY")
                f<<party[i].name<<' '<<party[i].pose<<' '<<party[i].battle<<' '<<party[i].level<<' '<<party[i].maxhp<<' '<<party[i].hp_per_lvl<<' '<<party[i].attack<<' '<<party[i].att_per_lvl<<' '<<party[i].defense<<' '<<party[i].def_per_lvl << '\n';
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
                      f>>party[i].name;
                      if (party[i].name != "N/A\n")
                            f>>party[i].pose>>party[i].battle>>party[i].level>>party[i].maxhp>>party[i].hp_per_lvl>>party[i].attack>>party[i].att_per_lvl>>party[i].defense>>party[i].def_per_lvl;
                }
        }
}

