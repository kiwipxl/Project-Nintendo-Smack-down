#ifndef DROPDOWN_BOX_H
#define DROPDOWN_BOX_H

#include <iostream>
#include "../../tools/Universal.h"

class DropdownBox : Universal {

	public:
		DropdownBox(int c_x, int c_y);
		~DropdownBox();

		void render();

	private:
		int x;
		int y;
};

#endif