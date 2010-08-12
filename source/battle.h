#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "shared.h"
#include "video_sdl.h"
#include "sound.h"
#include "file.h"
#include "input.h"
#include "pokemon.h"
#include "music.h"

#include <SDL/SDL.h>

class Battle
{
public:
    /* isWild indicates if we are in a wild battle.
     * For now isWild should always be true.
     * The player's pokemons (def) should probably be passed as a vector.
     * The same for the opponent's pokemons (fight)
     */
    Battle(bool isWild, Poke def, Poke fight);
    int battle_input();

    // Gives out experience
    void opponent_down();

    // Give out money
    void battle_end();

    // The opponent strikes back
    void opponent_attacks();
    ~Battle() {};

	int remove_little_life_opponent();
private:
    Poke pk_defence;
    Poke pk_opponent;
    bool wild_battle;
	
	// If true, don't process anything during this passage of
	// battle_input
	// This is used so that the health bar can be decreased little by
	// little without input from the user
	bool dont_do_anything;

	int life_to_remove;

	void process_attack();
};

#endif /* _BATTLE_H_ */
