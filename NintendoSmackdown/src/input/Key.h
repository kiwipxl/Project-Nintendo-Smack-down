#ifndef KEY_H
#define KEY_H

enum KeyType {
	KEYBOARD, 
	JOY_BUTTON, 
	JOY_AXIS, 
	JOY_HAT
};

class Key {

	public:
		Key() { }

		int key = 0;
		bool down = false;
		bool pressed = false;
		KeyType type = KEYBOARD;

		void set_key(int new_key, KeyType new_type) {
			key = new_key;
			type = new_type;
		}
};

#endif