#include "Main.h"
#include "Universe.h"

Universe* Main::universe;

int main(int argc, char* args[]) {
	Main::universe = new Universe();
	Main::universe->initiate();

	return 0;
}