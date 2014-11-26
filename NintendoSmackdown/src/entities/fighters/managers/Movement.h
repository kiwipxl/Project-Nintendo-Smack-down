#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../moves/CaptainFalcon.h"
#include "../../../tools/Point2DF.h"
#include "../../../tools/Animator.h"
#include "../../../managers/Texture.h"
#include "../../../map/Node.h"

class Universe;
class Fighter;

class Movement {

	public:
		Movement();

		//position
		Point2DF pos;
		Point2DF coords;

		//animation
		SDL_RendererFlip flip;

		//movement
		float gravity;
		float speedx;

		//moves
		Moves moves;
		int currentmove;

		//input
		bool upkeypressed = false;
		bool downkeypressed = false;
		bool akeypressed = false;

		bool leftkeydown = false;
		bool rightkeydown = false;
		bool upkeydown = false;
		bool downkeydown = false;
		bool akeydown = false;
		bool bkeydown = false;

		//force
		float forcex;
		const float FORCEFRICTION = .95f;

		/**
		updates the movement
		**/
		void updatemovement();

		/**
		adds force in positive or negative direction depending on flip parameter
		**/
		void addflipforce(SDL_RendererFlip newflip, float forcemultiplierx, float forcemultipliery);

		/**
		adds force depending on health
		**/
		void addforce(float forcemultiplierx, float forcemultipliery);

	private:
		//movement restrictions
		bool restrictinputx;
		bool restrictinputy;

		//movement values
		float movespeed = 1.2f;
		float maxspeed = 12;
		float friction = .92f;
		float jumpheight = 8;
		float fallspeed = .4f;
		float maxfallspeed = 10;

		//jumping
		bool doublejump;
		bool holdingjump;

		//edge grab
		bool grabbingedge;
		Node* edgenode;

		//punching
		int punchtimer;
		int punchcycle;
		const int PUNCHCYCLETIME = 20;
		bool punching;

		//dash attack
		bool dashing;
		int dashcooldowntimer;
		const int DASHCOOLDOWN = 25;

		//slide attack
		bool sliding;
		int slidingcooldowntimer;
		const int SLIDECOOLDOWN = 25;

		//air kicks
		bool downairkick;
		bool rightairknee;
		bool airsomersault;
		bool rightairkick;

		//collision
		bool floorcollided;
		bool rightcollided;
		bool leftcollided;

		//animation
		bool lockmoveupdate;

		/**
		changes the current move to a new move and updates the animation
		**/
		void updatemove(int newmove, int fps, bool loop = true, bool lock = false);

	protected:
		//universe
		Universe* muniverse;
		Fighter* mparent;

		//rendering
		SDL_Rect rect;
		SDL_Rect srcrect;

		//animation
		Animator* animator;
		Texture* animationsheet;
		SDL_Point origin;
		float rotation;
};

#endif