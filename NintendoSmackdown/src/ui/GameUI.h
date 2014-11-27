#ifndef GAME_UI_H
#define GAME_UI_H

#include <vector>
#include "../tools/Universal.h"
#include "tools/Text.h"

class GameUI : Universal {

	public:
		void create();
		void create_damage_texts(int fighters);
		void update();
		void remove();

		void update_damage_text(int index, int damage);

	private:
		vector<Text*> damage_texts;
		vector<Text*> name_texts;
};

#endif