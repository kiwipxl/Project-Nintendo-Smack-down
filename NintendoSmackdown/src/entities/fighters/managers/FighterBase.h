#ifndef FIGHTER_BASE_H
#define FIGHTER_BASE_H

class Fighter;
class Universe;

class FighterBase {

	public:
		FighterBase() { }

	protected:
		Universe* base_universe;
		Fighter* base_parent;
};

#endif