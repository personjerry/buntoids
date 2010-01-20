#include "video_sdl.h"
#include "music.h"
#include "map.h"

#include <fstream>
#include <algorithm>
#include <cmath>

std::vector<Ref> rugs;
std::vector<Ref> steps;
std::vector<Ref> doors;
std::vector<Link> links;
std::vector<Ref> infos;
std::vector<std::vector<int> > Map;

void getref(std::ifstream& f, std::vector<Ref>& foo) {
	int x,y;
	std::string tmp;
	f>>x>>y>>tmp;
	Ref r={x-1,y-1,tmp};
	foo.push_back(r);
}

void loadmap(std::string tmp) {
	rugs.clear();
	steps.clear();
	doors.clear();
	links.clear();
	infos.clear();
	Map.clear();
	bots.clear();

	Game::map=tmp;
	tmp="data/map/"+tmp;

	std::ifstream f(tmp.c_str());
	if(!f) error("map \""+Game::map+"\" not found");

	std::vector<int> tmp_map;
	std::string song;

	while(f>>tmp) {
		if(tmp=="info") {
			int x,y;
			f>>x>>y;
			getline(f,tmp);
			Ref r={x-1,y-1,tmp};
			infos.push_back(r);
		}
		else if(tmp=="bot") {
			int type,x,y;
			f>>type>>x>>y;
			getline(f,tmp);
			Bot b(type,x,y,tmp);
			bots.push_back(b);
		}
		else if(tmp=="link") {
			int x,y,w,dx,dy;
			f>>x>>y>>w>>dx>>dy>>tmp;
			Link tmp_link={x-1,y-1,w,dx-1,dy-1,tmp};
			links.push_back(tmp_link);
		}
		else if(tmp=="step")
			getref(f,steps);
		else if(tmp=="door")
			getref(f,doors);
		else if(tmp=="rug")
			getref(f,rugs);
		else if(tmp=="music")
			f>>song;
		else
			tmp_map.push_back(convert<int>(tmp));
	}

	//Free last maps loaded sprites
	static std::vector<int> mapimgs;
	for(size_t i=0; i<mapimgs.size(); ++i) {
		imglist[mapimgs[i]].free();
		imglist.erase(mapimgs[i]);
	}
	mapimgs.clear();

	//Load the current maps sprites
	mapimgs.assign(tmp_map.begin(),tmp_map.end());
	sort(mapimgs.begin(),mapimgs.end());
	mapimgs.resize(unique(mapimgs.begin(),mapimgs.end())-mapimgs.begin());

	for(size_t i=0; i<mapimgs.size(); ++i) {
		if(mapimgs[i]==10 || mapimgs[i]==20)
			continue;

		loadimage(mapimgs[i]);
	}

	newSong(song);

	int k=0;
	for(int x=0; x<sqrt(double(tmp_map.size())); ++x) {
		Map.push_back(std::vector<int>());
		for(int y=0; y<sqrt(double(tmp_map.size())); ++y) {
			
			Map.at(x).push_back(tmp_map.at(k++));
		}
	}
}

