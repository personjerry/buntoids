#include "shared.h"
#include "map.h"
#include "bot.h"
#include "input.h"
#include "video_sdl.h"
#include "col.h"

#include <fstream>
#include <algorithm>

std::vector<int> walkable;

bool col(int foo[4], int bar[4]) {
	if(foo[2]>=bar[0] && foo[1]<=bar[3] && foo[0]<=bar[2] && foo[3]>=bar[1])
		return true;

	return false;
}

void col_init() {
	std::string tmp("data/gfx/"+Game::spritemod+"/WALK.txt");
	std::ifstream f(tmp.c_str());
	if(!f)
		error("missing \""+tmp+"\"");

	walkable.push_back(10); //Standard ghost value

	while(f>>tmp)
		walkable.push_back(convert<int>(tmp));

	sort(walkable.begin(),walkable.end());
	walkable.resize(unique(walkable.begin(),walkable.end())-walkable.begin());
}

void col_update() {
	player.walk[0]=player.x()>int(Map.size())*16-16?0:1;
	player.walk[1]=player.y()>int(Map.size())*16-16-1?0:1;
	player.walk[2]=player.x()<0?0:1;
	player.walk[3]=player.y()<0?0:1;

	for(int y=0; y<int(Map.size()); ++y) {
		for(int x=0; x<int(Map.size()); ++x) {
			int player_col[4]={player.x()+2,player.y()+12,player.x()+14,player.y()+16};
			int obj[4]={y*16,x*16,y*16+16,x*16+16};

			bool check=true;
			for(size_t i=0; i<walkable.size(); ++i) {
				if(walkable[i]==Map[x][y]) {
					check=false;
					break;
				}
			}

			if(check) {
				for(int i=0; i<4; ++i) {
					obj[i]-=i<2?1:-1;
					if(col(player_col,obj)) {
						player.walk[i]=0;
						for(size_t j=0; j<infos.size(); ++j) {
							if(y==infos[j].x && x==infos[j].y && KEY_E_DOWN)
								info_dialog(infos[j].str);
						}
					}
					obj[i]+=i<2?1:-1;
				}

				for(size_t i=0; i<bots.size(); ++i) {
			 		int botcol[4]={bots[i].x()+1,bots[i].y(),bots[i].x()+15,bots[i].y()+15};
					if(bots[i].x()>int(Map.size())*16-16)
						bots[i].walk[0]=0;

					if(bots[i].y()>int(Map.size())*16-16-1)
						bots[i].walk[1]=0;

					if(bots[i].x()<0)
						bots[i].walk[2]=0;

					if(bots[i].y()<0)
						bots[i].walk[3]=0;

					for(int j=0; j<4; ++j) {
						obj[j]-=j<2?1:-1;
						if(col(botcol,obj))
							bots[i].walk[j]=0;
						obj[j]+=j<2?1:-1;
					}

					for(int j=0; j<4; ++j) {
						botcol[j]-=j<2?1:-1;
						if(col(botcol,player_col)) {
							player.walk[j]=0;
							if(KEY_E_DOWN)
								dialog(bots[i]);
						}
						botcol[j]+=j<2?1:-1;
					}
					for(int j=0; j<4; ++j) {
						player_col[j]-=j<2?1:-1;
						if(col(botcol,player_col))
							bots[i].walk[j]=0;
						player_col[j]+=j<2?1:-1;
					}
				}
			}

			//Stairs leading to another floor
			for(size_t i=0; i<steps.size(); ++i) {
				obj[0]=steps[i].x*16-1;
				obj[1]=steps[i].y*16;
				obj[2]=steps[i].x*16+16;
				obj[3]=steps[i].y*16+16+1;

				if(col(player_col,obj)) {
					if(Map[steps[i].y][steps[i].x]==1040) {
						if((player.direction()==8 && player.y()>steps[i].y*16+4 && player.x()>steps[i].x*16-15) || fading==2) {
							std::string target=Game::map;
							if(fading!=2)
								fading=1;

							player.talking=true;

							if(fading==2) {
								loadmap(steps[i].str);
								player.turn(4);
								for(size_t j=0; j<steps.size(); ++j) {
									if(steps[j].str==target) {
										player.set_x(steps[j].x*16-16);
										player.set_y(steps[j].y*16);
									}
								}
								fading=3;
							}
						}
					}
					else if(Map[steps[i].y][steps[i].x]==1050) {
						if((player.direction()==2 && player.x()<steps[i].x*16-14 && player.y()<steps[i].y*16+5) || fading==2) {
							std::string target=Game::map;
							if(fading!=2)
								fading=1;

							player.talking=true;

							if(fading==2) {
								loadmap(steps[i].str);
								player.turn(16);
								for(size_t j=0; j<steps.size(); ++j) {
									if(steps[j].str==target) {
										player.set_x(steps[j].x*16);
										player.set_y(steps[j].y*16+6);
									}
								}
								fading=3;
							}
						}
					}
				}
			}

			//doors leading inside
			for(size_t i=0; i<doors.size(); ++i) {
				obj[0]=doors[i].x*16+4;
				obj[1]=doors[i].y*16;
				obj[2]=doors[i].x*16+12;
				obj[3]=doors[i].y*16+16+1;

				if((col(player_col,obj) && player.direction()==8) || fading==2) {
					static size_t match;
					std::string target=Game::map;
					if(fading!=2) {
						fading=1;
						match=i;
					}
					player.talking=true;

					if(fading==2) {
						loadmap(doors[match].str);
						player.turn(8);
						for(size_t j=0; j<rugs.size(); ++j) {
							if(rugs[j].str==target) {
								player.set_x(rugs[j].x*16+8);
								player.set_y(rugs[j].y*16-2);
							}
						}
						fading=3;
					}
				}
			}

			//rugs leading outside
			for(size_t i=0; i<rugs.size(); ++i) {
				obj[0]=rugs[i].x*16+4;
				obj[1]=rugs[i].y*16+16;
				obj[2]=rugs[i].x*16+28;
				obj[3]=rugs[i].y*16+16;

				if((col(player_col,obj) && player.direction()==16) || fading==2) {
					static size_t match;
					std::string target=Game::map;
					if(fading!=2) {
						fading=1;
						match=i;
					}
					player.talking=true;

					if(fading==2) {
						loadmap(rugs[match].str);
						player.turn(16);
						for(size_t j=0; j<doors.size(); ++j) {
							if(doors[j].str==target) {
								player.set_x(doors[j].x*16);
								player.set_y(doors[j].y*16+8);
							}
						}
						fading=3;
					}
				}
			}

			//links leading to another map
			for(size_t i=0; i<links.size(); ++i) {
				obj[0]=links[i].x*16;
				obj[1]=links[i].y*16;
				obj[2]=links[i].x*16+(links[i].w*16);
				obj[3]=links[i].y*16+16;

				if(col(player_col,obj)) {
					int x_padding=0, y_padding=0;
					if(player.direction()==8)
						y_padding=13;

					player.set_x(links[i].dest_x*16-x_padding+(player.x()-links[i].x*16));
					player.set_y(links[i].dest_y*16-y_padding);
					loadmap(links[i].url);
				}
			}
		}
	}
}

