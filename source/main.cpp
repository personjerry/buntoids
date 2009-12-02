#include "shared.h"
#include "master.h"

#include <iostream>

int main(int argc, char **argv) {
	for(int i=1; i<argc; ++i) {
		if(std::string(argv[i])=="-s" || std::string(argv[i])=="--skin") {
			if(i+1<argc)
				Game::spritemod=argv[++i];
			else
				error("no skin specified");
		}
		else if(std::string(argv[i])=="-h" || std::string(argv[i])=="--help") {
			std::cout<<	"Free Pokémon client version 1.0.0\n"
					"An open source game engine licensed under GPLv3.\n"
					"Basis by Robin Stjerndorff,\nwork in progress by Jerry Liu.\n\n"
					"short\tlong\t\taction\n"
					"-f\t--fullscreen\tenable fullscreen\n"
					"-h\t--help\t\toutput this information\n"
					"-s\t--skin\t\tselect a skin folder\n"
					"-z\t--zoom\t\tzoom the window (2 to 8)"<<std::endl;
			exit(0);
		}
		else if(std::string(argv[i])=="-z" || std::string(argv[i])=="--zoom") {
			if(i+1<argc) {
				int value=convert<int>(argv[++i]);
				if(value<2)
					error("too small zoom value");

				if(value>8)
					error("too big zoom value");

				Video::scale=value;
			}
			else
				error("no zoom value given");
		}
		else if(std::string(argv[i])=="-f" || std::string(argv[i])=="--fullscreen") {
			Video::fullscreen=true;
		}
		else {
			warning("unknown argv \""+std::string(argv[i])+"\" has no effect");
		}
	}

	atexit(master_kill);

	master_init();

	while(Game::run) {
		master_update();
	}

	return 0;
}

