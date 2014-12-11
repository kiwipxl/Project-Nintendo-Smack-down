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
		float grid_size;

		void update();
		void reset();
		float get_offset_x(float pos_x);
		float get_offset_y(float pos_y);

		int min_bounds_x;
		int max_bounds_x;
		int min_bounds_y;
		int max_bounds_y;

	private:
		const int ZOOM_SMOOTHING = 10;
		const int MOVE_SMOOTHING = 5;
		const float ZOOM = 1000.f;
		const float MAX_ZOOM = 2;
		const float MIN_ZOOM = .8f;
};

#endif