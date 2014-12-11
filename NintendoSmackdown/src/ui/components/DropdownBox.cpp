#include "DropdownBox.h"
#include <sstream>
#include "../../managers/WindowManager.h"
#include "../../managers/Assets.h"
#include "../../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static Renderer* renderer;
};

DropdownBox::DropdownBox(int c_x, int c_y) {
	x = c_x;
	y = c_y;
}

DropdownBox::~DropdownBox() {

}

void DropdownBox::render() {

}