#ifndef _MAP_
#define _MAP_

#include <string>
#include <vector>

struct Ref {
	int x;
	int y;
	std::string str;
};

struct Link {
	int x;
	int y;
	int w;
	int dest_x;
	int dest_y;
	std::string url;
};

extern std::vector<Ref> rugs;
extern std::vector<Ref> steps;
extern std::vector<Ref> doors;
extern std::vector<Link> links;
extern std::vector<Ref> infos;
extern std::vector<std::vector<int> > Map;

void loadmap(std::string);

#endif

