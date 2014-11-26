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
		float getoffsetx(float posx);
		float getoffsety(float posy);

	private:
		const int ZOOM_SMOOTHING = 20;
		const int MOVE_SMOOTHING = 10;
		const float ZOOM = 500.f;
		const float MAX_ZOOM = 2;
		const float MIN_ZOOM = .8f;
		int minboundsx;
		int maxboundsx;
		int minboundsy;
		int maxboundsy;
};

#endif