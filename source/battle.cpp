#include "battle.h"
#include <cmath>

Battle::Battle(bool isWild, Poke defence, Poke opponent) : wild_battle(isWild),
														   pk_defence(defence),
														   pk_opponent(opponent),
														   dont_do_anything(false),
														   life_to_remove(0)
{
	pk_opponent.health = (int)pk_opponent.maxhp;

	// These variables are defined as extern, and are used on the
	// video_sdl.cpp file
	fight = pk_opponent;
	def = pk_defence;

	newSong("00.ogg");
}

int Battle::remove_little_life_opponent() {
	// Always remove 1 hitpoint during each passage
	if (life_to_remove > 0 && pk_opponent.health > 0) {
		pk_opponent.health -= 1;

		fight = pk_opponent;

		life_to_remove -= 1;
	}
	else
		dont_do_anything = false;
	return life_to_remove;
}

int Battle::battle_input() {
	SDL_Event event;

	if (dont_do_anything) // Simply remove a little life from the bar
		remove_little_life_opponent();

	else {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				Game::run = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

				case SDLK_w:
				case SDLK_s:
					battle_choice = (((battle_choice % 4) + 1 ) % 2 + ((battle_choice % 4) > 1) * 2)+ (battle_choice>3)*4;
					break;

				case SDLK_a:
				case SDLK_d:
					battle_choice = (((battle_choice % 4) + 2) % 4) + ((battle_choice>3)*4);
					break;

				case SDLK_e:
					switch (battle_choice) {

					case 0:
						battle_choice = 4;
						break;

					case 1:
					case 3:
						menu_text = "Not implemented yet.";
						info_dialog(menu_text);
						break;

					case 2: // delegate choosing pokemon to pokemenu
						// FIXME: This doesn't work so well now
						// Possible fix: copy/paste the code of input.cpp for the part
						// that takes care of r_pokemenu
						r_pokemenu = true;
						r_menu = false;
						menu_text = "Choose a buntoid.";
						info_dialog(menu_text);
						break;

					case 4:
					case 5:
					case 6:
					case 7:
						process_attack();

						// See if the opponent is dead
						if (pk_opponent.health <= 0) {
							battle_end();
							return 1;
						}

						break;

					default:
						break;
					}
					break;

				case SDLK_SPACE:
					if (battle_choice < 4) {
						r_pokemenu = true;
						r_menu = false;
						menu_text = "Choose a buntoid.";
						info_dialog(menu_text);
					}
					else {
						battle_choice = 0;
					}
					break;

				default:
					break;
				}
			}
		}
	}

	return 0;
}

void Battle::process_attack() {
	// The player has choosen an attack

	// The place where we can find the attack in the pokemon move vector
	int index = battle_choice % 4;

	if (index == 1)
		index = 3;
	else if (index == 2)
		index = 1;
	else if (index == 3)
		index = 2;

	// There should be a way to get a move by simply
	// searching for his name
	Move attack_choosen = moves[pk_defence.moven[index]];

	// TODO: Check if we have enought PP
	/* FIXME: Since PP is defined on the global moves
	 * vector, does this mean that all pokemons share
	 * the same PP? At least the PP should be local to
	 * each pokemon
	 */

	// Check to see if it's a miss
	bool miss = (rand() % 100 + 1) > attack_choosen.acc ? 1 : 0;

	// We need to cancel every other press otherwise the attack hits
	// twice from dialog closing.
	// FIXME: See above.
	static bool pressed = false;

	if (!pressed) {

		if (!miss) {
			// Still no type check (no weakness or imunities)
			// TODO: Animate health bar.
			dont_do_anything = true;
			//pk_opponent.health -= attack_choosen.power / (fight.defense+fight.specd);

			//fight = pk_opponent;

			life_to_remove = (int)ceil(attack_choosen.power / (fight.defense + fight.specd));

			menu_text = pk_defence.name + " used " + attack_choosen.name + "!";
		}
		else {
			menu_text = "It missed.";
		}
		info_dialog(menu_text);
		pressed = true;
	}
	else {
		info_dialog(menu_text);
		pressed = false;
	}

}

void Battle::opponent_down() {}

void Battle::battle_end() {
	/* FIXME: Due to the way messages work we can't display both the
	 * final attack message and the victory message at once, and the
	 * animations are missing too.
	 */
	info_dialog(menu_text); // Clear the attack message
	menu_text = "YOU ARE WINNER!";
	info_dialog(menu_text);

	// If we enter a new battle, the menu gets messed up (it jumps
	// directly to the fight submenu)
	// We need to do this, since battle_choice is a extern variable
	// declared on the file video_sdl.h
	battle_choice = 0;

	dont_do_anything = false;
}

void Battle::opponent_attacks() {}
