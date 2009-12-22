#include "shared.h"
#include "pokemon.h"
#include "img.h"
#include "SDL/SDL_rotozoom.h"

std::vector<Poke> monsters;
Poke party[6];
Poke EMPTY;
Poke fight;
int pokecount;

void loadpoke(const std::string& name) {
	static int id=0;
	std::ostringstream img1, img2, img3;

	img1<<++id<<"_pose";
	img2<<id<<"_battle";
        img3<<id<<"_icon";

	Poke p={id,name,img1.str(),img2.str(),0,0,0,0,0,0,0};
	monsters.push_back(p);
        
        std::ostringstream loc1, loc2, loc3;

        loc1 << "pokemon/" << img1.str();
        Image * temp1 = new Image;
        temp1->load(loc1.str());
        poseimg[id] = *temp1;
        delete(temp1);
        
        rposeimg[id].set((SDL_Surface*)(zoomSurface(poseimg[id].get(),-1,1,1)));

        loc2 << "pokemon/" << img2.str();
        Image * temp2 = new Image;
        temp2->load(loc2.str());
        battleimg[id] = *temp2;
        delete(temp2);
        
        loc3<< "pokemon/" << img3.str();
        Image * temp3 = new Image;
        temp3->load(loc3.str());
        iconimg[id] = *temp3;
        delete(temp3);
        
        
}
void setpokemon(Poke* target,int id, int level, double health, double hp_per_lvl, double attack, double att_per_lvl, double defense, double def_per_lvl)
{
        target->level = level;
        target->id = id;
        target->health = health;
        target->hp_per_lvl = hp_per_lvl;
        target->attack = attack;
        target->att_per_lvl = att_per_lvl;
        target->defense = defense;
        target->def_per_lvl = def_per_lvl;
}

void pokemon_init() { //do we want to make our own pokemon?
	const static std::string monster_names[]={
		"Bulbasaur","Ivysaur","Venusaur",
		"Charmander","Charmeleon","Charizard",
		"Squirtle","Wartortle","Blastoise",
		"Caterpie","Metapod","Butterfree",
		"Weedle","Kakuna","Beedrill",
		"Pidgey","Pidgeotto","Pidgeot",
		"Rattata","Raticate",
		"Spearow","Fearow",
		"Ekans","Arbok",
		"Pikachu","Raichu",
		"Sandshrew","Sandslash",
		"Nidoran ♀","Nidorina","Nidoqueen",
		"Nidoran ♂","Nidorino","Nidoking",
		"Clefairy","Clefable",
		"Vulpix","Ninetales",
		"Jigglypuff","Wigglytuff",
		"Zubat","Golbat",
		"Oddish","Gloom","Vileplume"
	};
        
        std::ifstream f("data/poke.txt");
        if(f)
        {
              f >> pokecount;
          
              monsters.reserve(pokecount+1);    //pokemon
              poseimg.reserve(pokecount+1);     //pictures of pokemon facing, to the right
              rposeimg.reserve(pokecount+1);    //pictures of pokemon facing, reversed
              battleimg.reserve(pokecount+1);   //pictures of from the rear
              iconimg.reserve(pokecount+1);     //small icons of the pokemon
          
		for(int npoke=0;npoke < pokecount; npoke++)
		{
			Poke temp;

			std::string name;
			f >> name;
                
			temp.id = npoke;
			temp.name = name;
			temp.level = 1;
			f >> temp.health;
			f >> temp.hp_per_lvl;
			f >> temp.attack;
			f >> temp.att_per_lvl;
			f >> temp.defense;
			f >> temp.def_per_lvl;
			f >> temp.moven[0];
			f >> temp.moven[1];
			f >> temp.moven[2];
			f >> temp.moven[3];
                    
                
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
                    
			rposeimg[npoke].set((SDL_Surface*)(zoomSurface(poseimg[npoke].get(),-1,1,1)));
	
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
			
			monsters.push_back(temp);
		}
        }
        else
        {
                std::cerr<<"Pokemon file not found... Abort!\n";
                exit(1);
        }
        
        
        // make sure the empty pokemon is consistent.
        setpokemon(&EMPTY,0,0,0,0,0,0,0,0);
        EMPTY.name = "EMPTY";
        EMPTY.battle = "";
        EMPTY.pose = "";
          
        // fill party slots with empty at first.
        party[0] = EMPTY;
        party[1] = EMPTY;
        party[2] = EMPTY;
        party[3] = EMPTY;
        party[4] = EMPTY;
        party[5] = EMPTY;
          
        // testing with all bulbasaurs.
        party[0] = monsters[0];
        party[1] = monsters[0];
        party[2] = monsters[0];
        party[3] = monsters[0];
        party[4] = monsters[0];
        party[5] = monsters[0];
        


}

