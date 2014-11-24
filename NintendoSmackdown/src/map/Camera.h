#ifndef CAMERA_H
#define CAMERA_H

#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class Camera : Universal {

	public:
		Camera();

		//camera
		float x;
		float y;
		float scale;
		float gridsize;

		void update();
		void reset();
		float getscaleoffsetx(int width);
		float getscaleoffsety(int height);

	private:
		//camera offset
};

#endif