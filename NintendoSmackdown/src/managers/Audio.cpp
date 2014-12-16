#include "Audio.h"
#include <iostream>
#include "WindowManager.h"
#include "../tools/ImageTools.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static ImageTools* imagetools;
};

void Audio::initiate() {
	theme_song = Mix_LoadMUS("assets/themesong.mp3");
	theme_song_loop = Mix_LoadMUS("assets/themesongloop.mp3");
	pirate_song = Mix_LoadMUS("assets/piratesong.mp3");
}

void Audio::update() {
	if (current_song == theme_song && Mix_PlayingMusic() == 0) {
		play_music(theme_song_loop, INT_MAX);
	}
}

/**
plays specified music
**/
void Audio::play_music(Mix_Music* music, int loops) {
	if (current_song == music && Mix_PlayingMusic() != 0) { return; }
	Mix_PlayMusic(music, loops);
	current_song = music;
}

/**
free memory from all audio loaded
**/
void Audio::free_audio() {

}