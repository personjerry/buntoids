#ifndef _SHARED_
#define _SHARED_

#include "player.h"

#include <string>
#include <sstream>

#define FRAMERATE 60

extern Player player;

void error(const std::string&);
void warning(const std::string&);

namespace Game {
	extern bool run;
	extern std::string map;
	extern std::string spritemod;
}

namespace Video {
	extern unsigned int width;
	extern unsigned int height;
	extern unsigned int scale;
	extern bool fullscreen;
}

namespace Format {
	extern const std::string image;
	extern const std::string sound;
	extern const std::string music;
}

template <typename TO, typename FROM> TO convert (FROM foo) {
	std::stringstream ss;
	ss<<foo;
	TO bar;
	ss>>bar;
	return bar;
}

#endif

